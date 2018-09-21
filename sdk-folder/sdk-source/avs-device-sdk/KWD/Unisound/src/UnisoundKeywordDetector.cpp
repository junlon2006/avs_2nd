/*
 * Copyright 2017-2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <memory>

#include <AVSCommon/Utils/Logger/Logger.h>

#include "Unisound/UnisoundKeywordDetector.h"
#include "LinuxAsrFix.h"
#include "ofa_consts.h"

namespace alexaClientSDK {
namespace kwd {

using namespace avsCommon::utils::logger;

/// String to identify log entries originating from this file.
static const std::string TAG("UnisoundKeywordDetector");

/**
 * Create a LogEntry using this file's TAG and the specified event string.
 *
 * @param The event string for this @c LogEntry.
 */
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

/// The number of hertz per kilohertz.
static const size_t HERTZ_PER_KILOHERTZ = 1000;

/// The timeout to use for read calls to the SharedDataStream.
const std::chrono::milliseconds TIMEOUT_FOR_READ_CALLS = std::chrono::milliseconds(1000);

/// The Unisound compatible AVS sample rate of 16 kHz.
static const unsigned int UNISOUND_COMPATIBLE_SAMPLE_RATE = 16000;

/// The Unisound compatible bits per sample of 16.
static const unsigned int UNISOUND_COMPATIBLE_SAMPLE_SIZE_IN_BITS = 16;

/// The Unisound compatible number of channels, which is 1.
static const unsigned int UNISOUND_COMPATIBLE_NUM_CHANNELS = 1;

/**
 * Returns information about the ongoing sensory session. Primarily used to populate error messages.
 *
 * @param session The Unisound session handle.
 * @param result The Unisound return code.
 *
 * @return The pertinent message about the sensory session in string format.
 */

#if 0
SnsrRC UnisoundKeywordDetector::keyWordDetectedCallback(SnsrSession s, const char* key, void* userData) {
    UnisoundKeywordDetector* engine = static_cast<UnisoundKeywordDetector*>(userData);
    const char* keyword;
    double begin;
    double end;
    engine->notifyKeyWordObservers(
        engine->m_stream,
        keyword,
        engine->m_beginIndexOfStreamReader + begin,
        engine->m_beginIndexOfStreamReader + end);
    return SNSR_RC_OK;
}
#endif

std::unique_ptr<UnisoundKeywordDetector> UnisoundKeywordDetector::create(
    std::shared_ptr<avsCommon::avs::AudioInputStream> stream,
    avsCommon::utils::AudioFormat audioFormat,
    std::unordered_set<std::shared_ptr<avsCommon::sdkInterfaces::KeyWordObserverInterface>> keyWordObservers,
    std::unordered_set<std::shared_ptr<avsCommon::sdkInterfaces::KeyWordDetectorStateObserverInterface>>
        keyWordDetectorStateObservers,
    const std::string& modelFilePath,
    std::chrono::milliseconds msToPushPerIteration) {
    if (!stream) {
        ACSDK_ERROR(LX("createFailed").d("reason", "nullStream"));
        return nullptr;
    }

    std::unique_ptr<UnisoundKeywordDetector> detector(new UnisoundKeywordDetector(
        stream, keyWordObservers, keyWordDetectorStateObservers, audioFormat, msToPushPerIteration));
    if (!detector->init(modelFilePath)) {
        ACSDK_ERROR(LX("createFailed").d("reason", "initDetectorFailed"));
        return nullptr;
    }
    return detector;
}

UnisoundKeywordDetector::~UnisoundKeywordDetector() {
    m_isShuttingDown = true;
    if (m_detectionThread.joinable()) {
        m_detectionThread.join();
    }
}

UnisoundKeywordDetector::UnisoundKeywordDetector(
    std::shared_ptr<AudioInputStream> stream,
    std::unordered_set<std::shared_ptr<KeyWordObserverInterface>> keyWordObservers,
    std::unordered_set<std::shared_ptr<KeyWordDetectorStateObserverInterface>> keyWordDetectorStateObservers,
    avsCommon::utils::AudioFormat audioFormat,
    std::chrono::milliseconds msToPushPerIteration) :
        AbstractKeywordDetector(keyWordObservers, keyWordDetectorStateObservers),
        m_stream{stream},
        m_maxSamplesPerPush((audioFormat.sampleRateHz / HERTZ_PER_KILOHERTZ) * msToPushPerIteration.count()) {
}

static void __unisound_init(const char *resourceFilePath) {
    char model_path[512];
    char model_files[512];
    char domains[128] = {"wakeup"};
    int rc = -1;
    printf("%s%d: resourceFilePath=%s\n", __FUNCTION__, __LINE__, resourceFilePath);
    sprintf(model_path, "%s/models", resourceFilePath);
    sprintf(model_files, "%s/wakeup.dat", model_path);
    if (0 != (rc = init(model_path, model_files, 0))) {
        ACSDK_ERROR(LX("createFailed").d("reason", "initUnisoundEngineFailed"));
        printf("%s%d: unisound engine init failed[%d]\n", __FUNCTION__, __LINE__, rc);
        return;
    }
    setOptionInt(ASR_SILENCE_HANGOUT_THRESH, 10);
    setOptionInt(ASR_ENGINE_SET_RESET_FRONTEND_ID, 1);
    setOptionInt(ASR_ENGINE_SET_FAST_RETURN, 1);
    setOptionInt(ASR_CONF_OUT_INELIGIBLE, 1);
    setOptionInt(ASR_ENGINE_SET_TYPE_ID, 2);
    setOptionInt(ASR_LOG_ID, 1);

    if (0 != (rc = start(domains, 54))) {
        printf("%s%d: unisound engine start failed[%d]\n", __FUNCTION__, __LINE__, rc);
    }
    printf("%s%d: unisound engine init successfully\n", __FUNCTION__, __LINE__);
    return;
}

bool UnisoundKeywordDetector::init(const std::string& modelFilePath) {
    m_streamReader = m_stream->createReader(AudioInputStream::Reader::Policy::BLOCKING);
    if (!m_streamReader) {
        ACSDK_ERROR(LX("initFailed").d("reason", "createStreamReaderFailed"));
        return false;
    }
    __unisound_init(modelFilePath.c_str());
    m_isShuttingDown = false;
    m_detectionThread = std::thread(&UnisoundKeywordDetector::detectionLoop, this);
    return true;
}

static void __recognize_result_parse(char *result, char *keyword, float *score) {
    char buf[128] = {0};
    char *tmp = buf;
    int index = 0;
    int score_index = 0;
    int start = 0;
    char score_buf[16] = {0};
    while (*result != '\0') {
        if (*result != ' ' &&
            *result != '\t' &&
            *result != '\n') {
            tmp[index++] = *result;
        }
        result++;
    }
    index = 0;
    tmp = buf;
    while (*tmp != '\0') {
        if (*(tmp + 1) != '\0' && *tmp == '>' && *(tmp+1) != '<') {
            start++;
            tmp++;
            continue;
        }
        if (start == 1 && *tmp == '<') {
            start++;
        }
        if (start == 1) {
        keyword[index++] = *tmp;
        }
        if (start == 3 && *tmp != '>')  {
          score_buf[score_index++] = *tmp;
        }
        tmp++;
    }
    keyword[index] = '\0';
    *score = atof(score_buf);
    printf("keyword=%s, score=%f\n", keyword, *score);
    return;
}

static char* __unisound_recognize(char *buf, int len) {
    char *result = nullptr;
    float score;
    static char keyword[64] = {0};
    int ret = 0;
    ret = recognize(buf, len * 2);
    if (2 == ret) {
        result = getResult();
        __recognize_result_parse(result, keyword, &score);
        if (-10.0 < score) {
            return keyword;
        }
    }
    return nullptr;
}

void UnisoundKeywordDetector::detectionLoop() {
    notifyKeyWordDetectorStateObservers(KeyWordDetectorStateObserverInterface::KeyWordDetectorState::ACTIVE);
    std::vector<int16_t> audioDataToPush(m_maxSamplesPerPush);
    ssize_t wordsRead;
    char *keyword = nullptr;
    while (!m_isShuttingDown) {
        bool didErrorOccur = false;
        wordsRead = readFromStream(
            m_streamReader,
            m_stream,
            audioDataToPush.data(),
            audioDataToPush.size(),
            TIMEOUT_FOR_READ_CALLS,
            &didErrorOccur);
        if (didErrorOccur) {
            break;
        } else if (wordsRead == AudioInputStream::Reader::Error::OVERRUN) {
        } else if (wordsRead > 0) {
            if (nullptr != (keyword = __unisound_recognize((char *)audioDataToPush.data(), audioDataToPush.size()))) {
                UnisoundKeywordDetector* engine = static_cast<UnisoundKeywordDetector*>(this);
                engine->notifyKeyWordObservers(
                    engine->m_stream,
                    keyword,
                    KeyWordObserverInterface::UNSPECIFIED_INDEX,
                    m_streamReader->tell());
            }
        }
    }
    m_streamReader->close();
}


}  // namespace kwd
}  // namespace alexaClientSDK
