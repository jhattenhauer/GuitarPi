#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

#include "pedals/compressor_pedal.h"
#include "pedals/delay_pedal.h"
#include "pedals/detune.h"
#include "pedals/distortion_pedal.h"
#include "pedals/echo_pedal.h"
#include "pedals/fuzz_pedal.h"
#include "pedals/highpass_pedal.h"
#include "pedals/lowpass_pedal.h"
#include "pedals/reverb_pedal.h"
#include "pedals/reverse_delay_pedal.h"

#include "json.hpp"
using json = nlohmann::json;

void read_settings(){

    std::ifstream file("../libraries/pedalSettings.json");
    if (!file.is_open()){
        std::cerr << "Pedal Settings failed to open" << std::endl;
        return;
    }
    
    json data;
    file >> data;
    json pedal = data["pedal_settings"][0];


    float compressor_enabled = pedal.value("compressor_enabled", 0.0f);
    float compressor_threshold = pedal.value("compressor_threshold", 0.0f);
    float compressor_ratio = pedal.value("compressor_ratio", 0.0f);
    float compressor_makeup_gain = pedal.value("compressor_makeup_gain", 0.0f);

    float delay_enabled = pedal.value("delay_enabled", 0.0f);
    float delay_sampleRate = pedal.value("delay_sampleRate", 0.0f);
    float delay_delayTimeSec = pedal.value("delay_delayTimeSec", 0.0f);
    float delay_feedback = pedal.value("delay_feedback", 0.0f);
    float delay_mix = pedal.value("delay_mix", 0.0f);

    float detune_enabled = pedal.value("detune_enabled", 0.0f);
    float detune_detuneAmount = pedal.value("detune_detuneAmount", 0.0f);
    float detune_phase = pedal.value("detune_phase", 0.0f);
    float detune_sampleRate = pedal.value("detune_sampleRate", 0.0f);
    float detune_baseFreq = pedal.value("detune_baseFreq", 0.0f);

    float distortion_enabled = pedal.value("distortion_enabled", 0.0f);
    float distortion_gain = pedal.value("distortion_gain", 0.0f);

    float echo_enabled = pedal.value("echo_enabled", 0.0f);
    float echo_sampleRate = pedal.value("echo_sampleRate", 0.0f);
    float echo_delayTimeSec = pedal.value("echo_delayTimeSec", 0.0f);
    float echo_feedback = pedal.value("echo_feedback", 0.0f);
    float echo_mix = pedal.value("echo_mix", 0.0f);

    float fuzz_enabled = pedal.value("fuzz_enabled", 0.0f);
    float fuzz_gain = pedal.value("fuzz_gain", 0.0f);

    float highpass_enabled = pedal.value("highpass_enabled", 0.0f);
    float highpass_cutoff = pedal.value("highpass_cutoff", 0.0f);
    float highpass_sampleRate = pedal.value("highpass_sampleRate", 0.0f);

    float lowpass_enabled = pedal.value("lowpass_enabled", 0.0f);
    float lowpass_cutoff = pedal.value("lowpass_cutoff", 0.0f);
    float lowpass_sampleRate = pedal.value("lowpass_sampleRate", 0.0f);

    float reverb_enabled = pedal.value("reverb_enabled", 0.0f);
    float reverb_sampleRate = pedal.value("reverb_sampleRate", 0.0f);
    float reverb_feedback = pedal.value("reverb_feedback", 0.0f);
    float reverb_mix = pedal.value("reverb_mix", 0.0f);

    float reverse_enabled = pedal.value("reverse_enabled", 0.0f);
    float reverse_sampleRate = pedal.value("reverse_sampleRate", 0.0f);
    float reverse_delayTimeSec = pedal.value("reverse_delayTimeSec", 0.0f);
    float reverse_mix = pedal.value("reverse_mix", 0.0f);


    std::cout << "compressor_enabled: " << compressor_enabled << std::endl;
    std::cout << "compressor_threshold: " << compressor_threshold << std::endl;
    std::cout << "compressor_ratio: " << compressor_ratio << std::endl;
    std::cout << "compressor_makeup_gain: " << compressor_makeup_gain << std::endl;
    std::cout << "delay_enabled: " << delay_enabled << std::endl;
    std::cout << "delay_sampleRate: " << delay_sampleRate << std::endl;
    std::cout << "delay_delayTimeSec: " << delay_delayTimeSec << std::endl;
    std::cout << "delay_feedback: " << delay_feedback << std::endl;
    std::cout << "delay_mix: " << delay_mix << std::endl;
    std::cout << "detune_enabled: " << detune_enabled << std::endl;
    std::cout << "detune_detuneAmount: " << detune_detuneAmount << std::endl;
    std::cout << "detune_phase: " << detune_phase << std::endl;
    std::cout << "detune_sampleRate: " << detune_sampleRate << std::endl;
    std::cout << "detune_baseFreq: " << detune_baseFreq << std::endl;
    std::cout << "distortion_enabled: " << distortion_enabled << std::endl;
    std::cout << "distortion_gain: " << distortion_gain << std::endl;
    std::cout << "echo_enabled: " << echo_enabled << std::endl;
    std::cout << "echo_sampleRate: " << echo_sampleRate << std::endl;
    std::cout << "echo_delayTimeSec: " << echo_delayTimeSec << std::endl;
    std::cout << "echo_feedback: " << echo_feedback << std::endl;
    std::cout << "echo_mix: " << echo_mix << std::endl;
    std::cout << "fuzz_enabled: " << fuzz_enabled << std::endl;
    std::cout << "fuzz_gain: " << fuzz_gain << std::endl;
    std::cout << "highpass_enabled: " << highpass_enabled << std::endl;
    std::cout << "highpass_cutoff: " << highpass_cutoff << std::endl;
    std::cout << "highpass_sampleRate: " << highpass_sampleRate << std::endl;
    std::cout << "lowpass_enabled: " << lowpass_enabled << std::endl;
    std::cout << "lowpass_cutoff: " << lowpass_cutoff << std::endl;
    std::cout << "lowpass_sampleRate: " << lowpass_sampleRate << std::endl;
    std::cout << "reverb_enabled: " << reverb_enabled << std::endl;
    std::cout << "reverb_sampleRate: " << reverb_sampleRate << std::endl;
    std::cout << "reverb_feedback: " << reverb_feedback << std::endl;
    std::cout << "reverb_mix: " << reverb_mix << std::endl;
    std::cout << "reverse_enabled: " << reverse_enabled << std::endl;
    std::cout << "reverse_sampleRate: " << reverse_sampleRate << std::endl;
    std::cout << "reverse_delayTimeSec: " << reverse_delayTimeSec << std::endl;
    std::cout << "reverse_mix: " << reverse_mix << std::endl;

}

void apply_effects(std::vector<float>& sample){
    for (float peiceOfSample: sample){
        distortion_pedal_func(peiceOfSample);
    }
}