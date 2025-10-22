#include <alsa/asoundlib.h>
#include <iostream>
#include <csignal>

snd_pcm_t* _soundDevice = nullptr;
bool  keepRunning = true;

void signalHandler(int signum){keepRunning = false;}

bool InitCapture(const char* name) {
    int err;
    snd_pcm_hw_params_t* hw_params;

    // Open the PCM device for CAPTURE (input)
    err = snd_pcm_open(&_soundDevice, name ? name : "hw:3,0", SND_PCM_STREAM_CAPTURE, 0);
    if (err < 0) {
        std::std::cerr << "Cannot open audio device for capture (" << snd_strerror(err) << ")" << std::std::endl;
        return false;
    }

    snd_pcm_hw_params_malloc(&hw_params);
    snd_pcm_hw_params_any(_soundDevice, hw_params);

    snd_pcm_hw_params_set_access(_soundDevice, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(_soundDevice, hw_params, SND_PCM_FORMAT_S32_LE);
    snd_pcm_hw_params_set_channels(_soundDevice, hw_params, 4);

    unsigned int rate = 44100;
    snd_pcm_hw_params_set_rate_near(_soundDevice, hw_params, &rate, 0);

    snd_pcm_hw_params(_soundDevice, hw_params);
    snd_pcm_hw_params_free(hw_params);

    snd_pcm_prepare(_soundDevice);
    return true;
}

bool CaptureOnce() {
    const int framesPerChunk = 1024; // 1 second of stereo audio
    const int channels = 4;
    int32_t* buffer = new int32_t[framesPerChunk * channels]; // 4 channels
    
    while(keepRunning){
        int err = snd_pcm_readi(_soundDevice, buffer, framesPerChunk);
        if (err == -EPIPE) {
            // Overrun
            std::cerr << "Overrun occurred!" << std::endl;
            snd_pcm_prepare(_soundDevice);
        } else if (err < 0) {
            std::cerr << "Read error: " << snd_strerror(err) << std::endl;
            snd_pcm_prepare(_soundDevice);
        } else if (err != framesPerChunk) {
            std::cerr << "Short read, got " << err << " frames" << std::endl;
        }

        std::cout << "Samples: ";
        for (int ch=0; ch<channels;  ++ch){
            std::cout<<buffer[ch] << " ";
        }
        std::cout << "\r";
        std::cout.flush();
    }
    delete[] buffer;
}

void UnInit() {
    if (_soundDevice) {
        snd_pcm_close(_soundDevice);
        _soundDevice = nullptr;
        std::cout << "Capture device closed." << std::endl;
    }
}

int main() {
    signal(SIGINT, signalHandler);
    if (InitCapture(NULL)) {
        std::cout << "Starting Recording..." << std::endl;
        CaptureOnce();
        UnInit();
    }
    return 0;
}
