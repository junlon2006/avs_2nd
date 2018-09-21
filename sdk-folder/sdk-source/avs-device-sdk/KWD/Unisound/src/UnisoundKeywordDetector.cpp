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

bool UnisoundKeywordDetector::init(const std::string& modelFilePath) {
    m_streamReader = m_stream->createReader(AudioInputStream::Reader::Policy::BLOCKING);
    if (!m_streamReader) {
        ACSDK_ERROR(LX("initFailed").d("reason", "createStreamReaderFailed"));
        return false;
    }

    m_isShuttingDown = false;
    m_detectionThread = std::thread(&UnisoundKeywordDetector::detectionLoop, this);
    return true;
}

void UnisoundKeywordDetector::detectionLoop() {
    m_beginIndexOfStreamReader = m_streamReader->tell();
    notifyKeyWordDetectorStateObservers(KeyWordDetectorStateObserverInterface::KeyWordDetectorState::ACTIVE);
    std::vector<int16_t> audioDataToPush(m_maxSamplesPerPush);
    ssize_t wordsRead;
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
        }
    }
    m_streamReader->close();
}

}  // namespace kwd
}  // namespace alexaClientSDK
