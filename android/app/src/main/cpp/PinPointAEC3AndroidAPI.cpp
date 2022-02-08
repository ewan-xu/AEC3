//
//  PinPointAECAndroidAPI.cpp
//  PinPointAECAndroid
//
//

#include "PinPointAEC3AndroidAPI.h"

#include "api/echo_canceller3_factory.h"
#include "api/echo_canceller3_config.h"
#include "audio_processing/include/audio_processing.h"
#include "audio_processing/audio_buffer.h"
#include "audio_processing/high_pass_filter.h"

class PinPointAEC3 {
public:
    PinPointAEC3(int sampleRate) {
        if (sampleRate != 16000 && sampleRate != 32000 && sampleRate != 48000) {
            throw std::invalid_argument("Sample rate not supported. Valid sample rates are 16000, 32000 and 48000.");
        }
        this->sampleRate = sampleRate;
        this->numberOfChannels = 1;
        streamConfig = webrtc::StreamConfig(sampleRate, numberOfChannels, false);

        const size_t numRenderChannels = numberOfChannels;
        const size_t numCaptureChannels = numberOfChannels;

        aec_audio = std::make_unique<webrtc::AudioBuffer>(sampleRate, numberOfChannels, sampleRate, numberOfChannels, sampleRate, numberOfChannels);
        ref_audio = std::make_unique<webrtc::AudioBuffer>(sampleRate, numberOfChannels, sampleRate, numberOfChannels, sampleRate, numberOfChannels);
        echo_controller = aec_factory.Create(sampleRate, numRenderChannels, numCaptureChannels);
        hp_filter = std::make_unique<webrtc::HighPassFilter>(sampleRate, numberOfChannels);
    }

    void processCapture(float* audioBuffer, int numberOfFrames) {
        if (numberOfFrames != sampleRate / 100) {
            throw std::invalid_argument("numberOfFrames should be sampleRate / 100");
        }
        float* stackedBuffer[1] = {audioBuffer};
        aec_audio->CopyFrom(stackedBuffer, streamConfig);
        echo_controller->AnalyzeCapture(aec_audio.get());
        if (sampleRateSupportsMultiBand()) {
            aec_audio->SplitIntoFrequencyBands();
        }
        hp_filter->Process(aec_audio.get(), sampleRateSupportsMultiBand());
        echo_controller->SetAudioBufferDelay(0);
        echo_controller->ProcessCapture(aec_audio.get(), nullptr, false);
        if (sampleRateSupportsMultiBand()) {
            aec_audio->MergeFrequencyBands();
        }
        aec_audio->CopyTo(streamConfig, stackedBuffer);
    }

    void analyzeRender(float* audioBuffer, int numberOfFrames) {
        if (numberOfFrames != sampleRate / 100) {
            throw std::invalid_argument("numberOfFrames should be sampleRate / 100");
        }
        ref_audio->CopyFrom(&audioBuffer, streamConfig);
        if (sampleRateSupportsMultiBand()) {
            ref_audio->SplitIntoFrequencyBands();
        }
        echo_controller->AnalyzeRender(ref_audio.get());
        if (sampleRateSupportsMultiBand()) {
            ref_audio->MergeFrequencyBands();
        }
    }
    
private:
    int sampleRate;
    int numberOfChannels;

    webrtc::StreamConfig streamConfig;

    webrtc::EchoCanceller3Factory aec_factory;
    std::unique_ptr<webrtc::EchoControl> echo_controller;
    std::unique_ptr<webrtc::HighPassFilter> hp_filter;

    std::unique_ptr<webrtc::AudioBuffer> ref_audio;
    std::unique_ptr<webrtc::AudioBuffer> aec_audio;

    bool sampleRateSupportsMultiBand() {
        return sampleRate == 32000 || sampleRate == 48000;
    }
};

void* PinPointAEC3Create(int sampleRate) {
    PinPointAEC3* aec = new PinPointAEC3(sampleRate);
    return aec;
}

void PinPointAEC3Destroy(void *object) {
    PinPointAEC3 *aec = (PinPointAEC3*)object;
    delete aec;
}

void PinPointAEC3ProcessCapture(void* object, float* audioBuffer, int numberOfFrames) {
    PinPointAEC3 *aec = (PinPointAEC3*)object;
    aec->processCapture(audioBuffer, numberOfFrames);
}

void PinPointAEC3AnalyzeRender(void* object, float* audioBuffer, int numberOfFrames) {
    PinPointAEC3 *aec = (PinPointAEC3*)object;
    aec->analyzeRender(audioBuffer, numberOfFrames);
}
