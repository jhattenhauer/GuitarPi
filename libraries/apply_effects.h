#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

#include "json.hpp"

#include "pedals/compressor_pedal.h"
#include "pedals/delay_pedal.h"
#include "pedals/detune.h"
#include "pedals/distortion_pedal.h"
#include "pedals/echo_pedal.h"
#include "pedals/fuzz_pedal.h"
#include "pedals/highpass_pedal.h"
#include "pedals/looper_pedal.h"
#include "pedals/lowpass_pedal.h"
#include "pedals/reverb_pedal.h"
#include "pedals/reverse_delay_pedal.h"

void apply_effects(std::vector<float>& sample){
    for (float peiceOfSample: sample){
        distortion_pedal_func(peiceOfSample);
    }
}