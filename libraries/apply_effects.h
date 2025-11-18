#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
#include <string>

#include "json.hpp"

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

void read_settings(){
    ifstream file("pedalSettings.json");
    if (!file.is_open()){
        std::cerr << "Pedal Settings failed to open" << std::endl;
    }
    
    json data;
    file >> data;
    json pedal = data["pedal_settings"][0];

    float compressor_enabled = pedal["compressor_enabled"]
    float compressor_threshold = pedal["compressor_threshold"]
    float compressor_ratio = pedal["compressor_ratio"]
    float compressor_makeup_gain = pedal["compressor_makeup_gain"]

    float delay_enabled = pedal["delay_enabled]"]
    float delay_sampleRate = pedal["delay_sampleRate"]
    float delay_delayTimeSec = pedal["delay_delayTimeSec"]
    float delay_feedback = pedal["delay_feedback"]
    float delay_mix = pedal["delay_mix"]

    float detune_enabled = pedal["detune_enabled]"]
    float detune_detuneAmount = pedal["detune_detuneAmount"]
    float detune_phase = pedal["detune_phase"]
    float detune_sampleRate = pedal["detune_sampleRate"]
    float detune_baseFreq = pedal["detune_baseFreq"]

    float distortion_enabled = pedal["distortion_enabled]"]
    float distortion_gain = pedal["distortion_gain"]

    float echo_enabled = pedal["echo_enabled]"]
    float echo_sampleRate = pedal["echo_sampleRate"]
    float echo_delayTimeSec = pedal["echo_delayTimeSec"]
    float echo_feedback = pedal["echo_feedback"]
    float echo_mix = pedal["echo_mix"]

    float fuzz_enabled = pedal["fuzz_enabled]"]
    float fuzz_gain = pedal["fuzz_gain"]

    float highpass_enabled = pedal["highpass_enabled]"]
    float highpass_cutoff = pedal["highpass_cutoff"]
    float highpass_sampleRate = pedal["highpass_sampleRate"]

    float lowpass_enabled = pedal["lowpass_enabled]"]
    float lowpass_cutoff = pedal["lowpass_cutoff",]
    float lowpass_sampleRate = pedal["lowpass_sampleRate"]

    float reverb_enabled = pedal["reverb_enabled]"]
    float reverb_sampleRate = pedal["reverb_sampleRate"]
    float reverb_feedback = pedal["reverb_feedback"]
    float reverb_mix = pedal["reverb_mix"]

    float reverse_enabled = pedal["reverse_enabled"]
    float reverse_sampleRate = pedal["reverse_sampleRate"]
    float reverse_delayTimeSec = pedal["reverse_delayTimeSec"]
    float reverse_mix = pedal["reverse_mix"]
}

void apply_effects(std::vector<float>& sample){
    for (float peiceOfSample: sample){
        distortion_pedal_func(peiceOfSample);
    }
}