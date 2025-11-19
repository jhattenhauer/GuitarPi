#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

#include "pedalstruct.h"

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

PedalSettingsStruct PedalSettings;

void read_settings(PedalSettingsStruct& PedalSettings){

    std::ifstream file("../libraries/pedalSettings.json");
    if (!file.is_open()){
        std::cerr << "Pedal Settings failed to open" << std::endl;
        return;
    }
    
    json data;
    file >> data;
    json pedal = data["pedal_settings"][0];

    PedalSettings.compressor_enabled = pedal.value("compressor_enabled", 0.0f);
    PedalSettings.compressor_threshold = pedal.value("compressor_threshold", 0.0f);
    PedalSettings.compressor_ratio = pedal.value("compressor_ratio", 0.0f);
    PedalSettings.compressor_makeup_gain = pedal.value("compressor_makeup_gain", 0.0f);
    
    PedalSettings.delay_enabled = pedal.value("delay_enabled", 0.0f);
    PedalSettings.delay_sampleRate = pedal.value("delay_sampleRate", 0.0f);
    PedalSettings.delay_delayTimeSec = pedal.value("delay_delayTimeSec", 0.0f);
    PedalSettings.delay_feedback = pedal.value("delay_feedback", 0.0f);
    PedalSettings.delay_mix = pedal.value("delay_mix", 0.0f);

    PedalSettings.detune_enabled = pedal.value("detune_enabled", 0.0f);
    PedalSettings.detune_detuneAmount = pedal.value("detune_detuneAmount", 0.0f);
    PedalSettings.detune_phase = pedal.value("detune_phase", 0.0f);
    PedalSettings.detune_sampleRate = pedal.value("detune_sampleRate", 0.0f);
    PedalSettings.detune_baseFreq = pedal.value("detune_baseFreq", 0.0f);

    PedalSettings.distortion_enabled = pedal.value("distortion_enabled", 0.0f);
    PedalSettings.distortion_gain = pedal.value("distortion_gain", 0.0f);

    PedalSettings.echo_enabled = pedal.value("echo_enabled", 0.0f);
    PedalSettings.echo_sampleRate = pedal.value("echo_sampleRate", 0.0f);
    PedalSettings.echo_delayTimeSec = pedal.value("echo_delayTimeSec", 0.0f);
    PedalSettings.echo_feedback = pedal.value("echo_feedback", 0.0f);
    PedalSettings.echo_mix = pedal.value("echo_mix", 0.0f);

    PedalSettings.fuzz_enabled = pedal.value("fuzz_enabled", 0.0f);
    PedalSettings.fuzz_gain = pedal.value("fuzz_gain", 0.0f);

    PedalSettings.highpass_enabled = pedal.value("highpass_enabled", 0.0f);
    PedalSettings.highpass_cutoff = pedal.value("highpass_cutoff", 0.0f);
    PedalSettings.highpass_sampleRate = pedal.value("highpass_sampleRate", 0.0f);

    PedalSettings.lowpass_enabled = pedal.value("lowpass_enabled", 0.0f);
    PedalSettings.lowpass_cutoff = pedal.value("lowpass_cutoff", 0.0f);
    PedalSettings.lowpass_sampleRate = pedal.value("lowpass_sampleRate", 0.0f);

    PedalSettings.reverb_enabled = pedal.value("reverb_enabled", 0.0f);
    PedalSettings.reverb_sampleRate = pedal.value("reverb_sampleRate", 0.0f);
    PedalSettings.reverb_feedback = pedal.value("reverb_feedback", 0.0f);
    PedalSettings.reverb_mix = pedal.value("reverb_mix", 0.0f);

    PedalSettings.reverse_enabled = pedal.value("reverse_enabled", 0.0f);
    PedalSettings.reverse_sampleRate = pedal.value("reverse_sampleRate", 0.0f);
    PedalSettings.reverse_delayTimeSec = pedal.value("reverse_delayTimeSec", 0.0f);
    PedalSettings.reverse_mix = pedal.value("reverse_mix", 0.0f);


    std::cout << "compressor_enabled: " << PedalSettings.compressor_enabled << std::endl;
    std::cout << "compressor_threshold: " << PedalSettings.compressor_threshold << std::endl;
    std::cout << "compressor_ratio: " << PedalSettings.compressor_ratio << std::endl;
    std::cout << "compressor_makeup_gain: " << PedalSettings.compressor_makeup_gain << std::endl;
    std::cout << "delay_enabled: " << PedalSettings.delay_enabled << std::endl;
    std::cout << "delay_sampleRate: " << PedalSettings.delay_sampleRate << std::endl;
    std::cout << "delay_delayTimeSec: " << PedalSettings.delay_delayTimeSec << std::endl;
    std::cout << "delay_feedback: " << PedalSettings.delay_feedback << std::endl;
    std::cout << "delay_mix: " << PedalSettings.delay_mix << std::endl;
    std::cout << "detune_enabled: " << PedalSettings.detune_enabled << std::endl;
    std::cout << "detune_detuneAmount: " << PedalSettings.detune_detuneAmount << std::endl;
    std::cout << "detune_phase: " << PedalSettings.detune_phase << std::endl;
    std::cout << "detune_sampleRate: " << PedalSettings.detune_sampleRate << std::endl;
    std::cout << "detune_baseFreq: " << PedalSettings.detune_baseFreq << std::endl;
    std::cout << "distortion_enabled: " << PedalSettings.distortion_enabled << std::endl;
    std::cout << "distortion_gain: " << PedalSettings.distortion_gain << std::endl;
    std::cout << "echo_enabled: " << PedalSettings.echo_enabled << std::endl;
    std::cout << "echo_sampleRate: " << PedalSettings.echo_sampleRate << std::endl;
    std::cout << "echo_delayTimeSec: " << PedalSettings.echo_delayTimeSec << std::endl;
    std::cout << "echo_feedback: " << PedalSettings.echo_feedback << std::endl;
    std::cout << "echo_mix: " << PedalSettings.echo_mix << std::endl;
    std::cout << "fuzz_enabled: " << PedalSettings.fuzz_enabled << std::endl;
    std::cout << "fuzz_gain: " << PedalSettings.fuzz_gain << std::endl;
    std::cout << "highpass_enabled: " << PedalSettings.highpass_enabled << std::endl;
    std::cout << "highpass_cutoff: " << PedalSettings.highpass_cutoff << std::endl;
    std::cout << "highpass_sampleRate: " << PedalSettings.highpass_sampleRate << std::endl;
    std::cout << "lowpass_enabled: " << PedalSettings.lowpass_enabled << std::endl;
    std::cout << "lowpass_cutoff: " << PedalSettings.lowpass_cutoff << std::endl;
    std::cout << "lowpass_sampleRate: " << PedalSettings.lowpass_sampleRate << std::endl;
    std::cout << "reverb_enabled: " << PedalSettings.reverb_enabled << std::endl;
    std::cout << "reverb_sampleRate: " << PedalSettings.reverb_sampleRate << std::endl;
    std::cout << "reverb_feedback: " << PedalSettings.reverb_feedback << std::endl;
    std::cout << "reverb_mix: " << PedalSettings.reverb_mix << std::endl;
    std::cout << "reverse_enabled: " << PedalSettings.reverse_enabled << std::endl;
    std::cout << "reverse_sampleRate: " << PedalSettings.reverse_sampleRate << std::endl;
    std::cout << "reverse_delayTimeSec: " << PedalSettings.reverse_delayTimeSec << std::endl;
    std::cout << "reverse_mix: " << PedalSettings.reverse_mix << std::endl;

}

void apply_effects(std::vector<float>& sample){
    for (float peiceOfSample: sample){
        distortion_pedal_func(peiceOfSample);
    }
}

