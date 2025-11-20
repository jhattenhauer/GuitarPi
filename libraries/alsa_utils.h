#include <alsa/asoundlib.h>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <chrono>
#include <thread>

snd_pcm_t* _captureDevice = nullptr;

bool InitCapture(const char* name){ //setup alsa capture device
    int err;
    snd_pcm_hw_params_t* hw_params;
    err = snd_pcm_open(&_captureDevice, name ? name : "hw:3,0", SND_PCM_STREAM_CAPTURE, 0); //magic number 'hw:3,0' is just alsa endpoint
    if (err < 0) {
        std::cerr << "Cannot open audio device for capture (" << snd_strerror(err) << ")" << std::endl;
        return false;
    }

    snd_pcm_hw_params_malloc(&hw_params);
    snd_pcm_hw_params_any(_captureDevice, hw_params);

    snd_pcm_hw_params_set_access(_captureDevice, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(_captureDevice, hw_params, SND_PCM_FORMAT_S32_LE);
    snd_pcm_hw_params_set_channels(_captureDevice, hw_params, 4);

    unsigned int sample_rate = 44100;
    snd_pcm_hw_params_set_rate_near(_captureDevice, hw_params, &sample_rate, 0);

    snd_pcm_hw_params(_captureDevice, hw_params);
    snd_pcm_hw_params_free(hw_params);

    snd_pcm_prepare(_captureDevice);
    return true;
}

snd_pcm_t* _playbackDevice = nullptr;

bool InitPlayback(const char* name){ //setup alsa playback device //pretty much same function but may need to mod later
    int err;
    snd_pcm_hw_params_t* hw_params;
    err = snd_pcm_open(&_playbackDevice, name ? name : "hw:3,0", SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        std::cerr << "Cannot open audio device for playback )" << snd_strerror(err) << ")" << std::endl;
        return false;
    }

    snd_pcm_hw_params_malloc(&hw_params);
    snd_pcm_hw_params_any(_playbackDevice, hw_params);

    snd_pcm_hw_params_set_access(_playbackDevice, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(_playbackDevice, hw_params, SND_PCM_FORMAT_S32_LE);
    snd_pcm_hw_params_set_channels(_playbackDevice, hw_params, 4);
    
    unsigned int sample_rate = 44100;
    snd_pcm_hw_params_set_rate_near(_playbackDevice, hw_params, &sample_rate, 0);

    snd_pcm_hw_params(_playbackDevice, hw_params);
    snd_pcm_hw_params_free(hw_params);

    snd_pcm_prepare(_playbackDevice);
    return true;
}


std::vector<float> Int_to_Float(const std::vector<int32_t>& intBuffer){
    std::vector<float> floatBuffer(intBuffer.size());
    const float scale = 1.0f / static_cast<float>(INT32_MAX);
    for (size_t i = 0; i < intBuffer.size(); ++i)
        floatBuffer[i] = static_cast<float>(intBuffer[i]) * scale;
    return floatBuffer;
}

std::vector<int32_t> Float_to_Int(const std::vector<float>& floatBuffer){
    std::vector<int32_t> intBuffer(floatBuffer.size());
    for (size_t i = 0; i < floatBuffer.size(); ++i) {
        float clamped = std::max(-1.0f, std::min(1.0f, floatBuffer[i])); // avoid overflow
        intBuffer[i] = static_cast<int32_t>(clamped * INT32_MAX);
    }
    return intBuffer;
}

std::vector<int32_t> CaptureSample(){
    const int framesPerChunk = 1024;
    const int channels = 4;
    std::vector<int32_t> intBuffer(framesPerChunk * channels);

    int err = snd_pcm_readi(_captureDevice, intBuffer.data(), framesPerChunk);
    if (err == -EPIPE) {
        std::cerr << "Overrun occurred!" << std::endl;
        snd_pcm_prepare(_captureDevice);
    } else if (err < 0) {
        std::cerr << "Read error: " << snd_strerror(err) << std::endl;
        snd_pcm_prepare(_captureDevice);
    } else if (err != framesPerChunk) {
        std::cerr << "Short read, got " << err << " frames" << std::endl;
    }

    return intBuffer;
}

void PlaybackSamples(snd_pcm_t* playbackDevice, const std::vector<int32_t>& samples, int channels = 4){
    int framesPerChunk = samples.size() / channels;
    const int32_t* buffer = samples.data();

    snd_pcm_sframes_t frames = snd_pcm_writei(playbackDevice, buffer, framesPerChunk);
    if (frames < 0) {
        frames = snd_pcm_recover(playbackDevice, frames, 0);
        if (frames < 0) {
            std::cerr << "Playback error: " << snd_strerror(frames) << std::endl;
            return;
        }
    } else if (frames != framesPerChunk){
        std::cerr << "Short write, wrote " << frames << " frames instead of " << framesPerChunk << std::endl;
    }
}

void UnInitCaptureDevice() {
    if (_captureDevice) {
        snd_pcm_close(_captureDevice);
        _captureDevice = nullptr;
        std::cout << "Capture device closed." << std::endl;
    }
}

void UnInitPlaybackDevice() {
    if (_playbackDevice) {
        snd_pcm_drain(_playbackDevice);
        snd_pcm_close(_playbackDevice);
        _playbackDevice = nullptr;
        std::cout << "Playback device closed." << std::endl;
    }
}