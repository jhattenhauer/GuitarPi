#include <alsa/asoundlib.h>
#include <fftw3.h>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <chrono>
#include <thread>

snd_pcm_t* _soundDevice = nullptr;

bool InitCapture(const char* name) { //setup alsa device
    int err;
    snd_pcm_hw_params_t* hw_params;
    err = snd_pcm_open(&_soundDevice, name ? name : "hw:3,0", SND_PCM_STREAM_CAPTURE, 0); //magic number 'hw:3,0' is just alsa endpoint
    if (err < 0) {
        std::cerr << "Cannot open audio device for capture (" << snd_strerror(err) << ")" << std::endl;
        return false;
    }

    snd_pcm_hw_params_malloc(&hw_params);
    snd_pcm_hw_params_any(_soundDevice, hw_params);

    snd_pcm_hw_params_set_access(_soundDevice, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
    snd_pcm_hw_params_set_format(_soundDevice, hw_params, SND_PCM_FORMAT_S32_LE);
    snd_pcm_hw_params_set_channels(_soundDevice, hw_params, 4);

    unsigned int sample_rate = 44100;
    snd_pcm_hw_params_set_rate_near(_soundDevice, hw_params, &sample_rate, 0);

    snd_pcm_hw_params(_soundDevice, hw_params);
    snd_pcm_hw_params_free(hw_params);

    snd_pcm_prepare(_soundDevice);
    return true;
}

std::vector<int32_t> CaptureSample() { //capture a sample of audio
    const int framesPerChunk = 1024; // sample size of chunk
    const int channels = 4;
    std::vector<int32_t> buffer(framesPerChunk * channels);  // allocate vector
    
    int err = snd_pcm_readi(_soundDevice, buffer.data(), framesPerChunk);
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
    return buffer;
}

void doFFT(const std::vector<double>& in, std::vector<std::complex<double>>& out) {//fast fourier transform
    int N = in.size();
    fftw_complex* out_c = reinterpret_cast<fftw_complex*>(out.data());
    fftw_plan p = fftw_plan_dft_r2c_1d(N, const_cast<double*>(in.data()), out_c, FFTW_ESTIMATE);
    fftw_execute(p);
    fftw_destroy_plan(p);
}

std::vector<std::complex<double>> fft_wrapper(const std::vector<int32_t>& intInput) {//wrap fft to output frequency domain
    std::vector<double> input(intInput.begin(), intInput.end());
    std::vector<std::complex<double>> output(input.size() / 2 + 1);
    doFFT(input, output);
    return output; // full frequency-domain vector
}

int findDominantFrequency(const std::vector<double>& samples, double sampleRate) {//find dominant frequency
    int N = samples.size();
    std::vector<std::complex<double>> spectrum(N / 2 + 1);
    doFFT(samples, spectrum);

    // Find index of the largest magnitude
    int maxIndex = 0;
    double maxMag = 0.0;
    for (int i = 0; i < spectrum.size(); ++i) {
        double mag = std::norm(spectrum[i]);  // magnitude squared
        if (mag > maxMag) {
            maxMag = mag;
            maxIndex = i;
        }
    }
    return maxIndex;
}

void UnInit() {
    if (_soundDevice) {
        snd_pcm_close(_soundDevice);
        _soundDevice = nullptr;
        std::cout << "Capture device closed." << std::endl;
    }
}
