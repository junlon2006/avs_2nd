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

#include <cstring>
#include <string>

#include <rapidjson/document.h>

#include <AVSCommon/Utils/Configuration/ConfigurationNode.h>
#include <AVSCommon/Utils/Logger/Logger.h>
#include "SampleApp/PortAudioMicrophoneWrapper.h"
#include "SampleApp/ConsolePrinter.h"
#include "uni_sys_hal.h"
#include "uni_iot.h"
#include "uni_types.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

namespace alexaClientSDK {
namespace sampleApp {

using avsCommon::avs::AudioInputStream;

static const int UNISOUND_AUDIO_CHANNLES_NUMBER = 1;
static const int UNISOUND_AUDIO_BITS = 16;
static const int UNISOUND_AUDIO_RATE = 16000;
static const int UNISOUND_DEFAULT_FRAME_LEN_MS = 16;
static void *m_unisound_audio_handler;
static int m_unisound_audio_frame_size;
static char *m_unisound_audio_buffer;
static bool m_unisound_audio_start = false;
static std::shared_ptr<avsCommon::avs::AudioInputStream::Writer> m_writer;
/// String to identify log entries originating from this file.
static const std::string TAG("PortAudioMicrophoneWrapper");

/**
 * Create a LogEntry using this file's TAG and the specified event string.
 *
 * @param The event string for this @c LogEntry.
 */
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

std::unique_ptr<PortAudioMicrophoneWrapper> PortAudioMicrophoneWrapper::create(
    std::shared_ptr<AudioInputStream> stream) {
    if (!stream) {
        ACSDK_CRITICAL(LX("Invalid stream passed to PortAudioMicrophoneWrapper"));
        return nullptr;
    }
    std::unique_ptr<PortAudioMicrophoneWrapper> portAudioMicrophoneWrapper(new PortAudioMicrophoneWrapper(stream));
    if (!portAudioMicrophoneWrapper->initialize()) {
        ACSDK_CRITICAL(LX("Failed to initialize PortAudioMicrophoneWrapper"));
        return nullptr;
    }
    return portAudioMicrophoneWrapper;
}

PortAudioMicrophoneWrapper::PortAudioMicrophoneWrapper(std::shared_ptr<AudioInputStream> stream) :
        m_audioInputStream{stream} {
}

PortAudioMicrophoneWrapper::~PortAudioMicrophoneWrapper() {
}

static void __restart_audio_handler() {
    struct hal_audio_config audio_config;
    audio_config.channels = UNISOUND_AUDIO_CHANNLES_NUMBER;
    audio_config.bits = UNISOUND_AUDIO_BITS;
    audio_config.rate = UNISOUND_AUDIO_RATE;
    audio_config.period_size = 2048;
    audio_config.period_count = 4;
    audio_config.is_play = 0;
    uni_hal_audio_close(m_unisound_audio_handler);
    m_unisound_audio_handler = uni_hal_audio_open(&audio_config);
    printf("%s%d: unisound audio restart ok\n", __FUNCTION__, __LINE__);
}

static void *__unisound_record_tsk(void *args) {
    printf("%s%d: unisound start record task\n", __FUNCTION__, __LINE__);
    int len;
    while (true) {
        len = uni_hal_audio_read(m_unisound_audio_handler, m_unisound_audio_buffer, m_unisound_audio_frame_size);
        if (len != m_unisound_audio_frame_size) {
            __restart_audio_handler();
            continue;
        }
        if (m_unisound_audio_start) {
            m_writer->write(m_unisound_audio_buffer, len / 2);
        }
    }
    return nullptr;
}

static void __unisound_audio_record_worker_thread_create() {
    pthread_t pid;
    pthread_create(&pid, NULL, __unisound_record_tsk, NULL);
    pthread_detach(pid);
}

static int __unisound_audio_record_init() {
    struct hal_audio_config audio_config;
    audio_config.channels = UNISOUND_AUDIO_CHANNLES_NUMBER;
    audio_config.bits = UNISOUND_AUDIO_BITS;
    audio_config.rate = UNISOUND_AUDIO_RATE;
    audio_config.period_size = 2048;
    audio_config.period_count = 4;
    audio_config.is_play = 0;
    printf("%s%d: unisound channel=%d, bits=%d, rate=%d, period_size=%d, period_count=%d\n",
           __FUNCTION__, __LINE__, UNISOUND_AUDIO_CHANNLES_NUMBER,
           UNISOUND_AUDIO_BITS, UNISOUND_AUDIO_RATE,
           audio_config.period_size, audio_config.period_count);
    m_unisound_audio_handler = uni_hal_audio_open(&audio_config);
    if (nullptr == m_unisound_audio_handler) {
        printf("%s%d: unisound create audio in handler failed\n", __FUNCTION__, __LINE__);
        return -1;
    }
    m_unisound_audio_frame_size = UNISOUND_DEFAULT_FRAME_LEN_MS * 32;
    if (nullptr == (m_unisound_audio_buffer = (char *)malloc(m_unisound_audio_frame_size))) {
        printf("%s%d: unisound alloc memory failed\n", __FUNCTION__, __LINE__);
        return -1;
    }
    __unisound_audio_record_worker_thread_create();
    return 0;
}

bool PortAudioMicrophoneWrapper::initialize() {
    m_writer = m_audioInputStream->createWriter(AudioInputStream::Writer::Policy::NONBLOCKABLE);
    if (!m_writer) {
        ACSDK_CRITICAL(LX("Failed to create stream writer"));
        return false;
    }

    m_unisound_audio_start = false;
    if (0 == __unisound_audio_record_init()) {
      return true;
    }
    return false;
}

bool PortAudioMicrophoneWrapper::startStreamingMicrophoneData() {
    std::lock_guard<std::mutex> lock{m_mutex};
    m_unisound_audio_start = true;
    return true;
}

bool PortAudioMicrophoneWrapper::stopStreamingMicrophoneData() {
    std::lock_guard<std::mutex> lock{m_mutex};
    m_unisound_audio_start = false;
    return true;
}

}  // namespace sampleApp
}  // namespace alexaClientSDK
