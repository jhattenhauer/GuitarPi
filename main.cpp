#include <iostream>
#include <vector>
#include <chrono>

#include "libraries/alsa_utils.h"
#include "libraries/apply_effects.h"

int main() {
    if (InitCapture(NULL)){
        while(true){
            std::cout << "Starting Recording..." << std::endl;
            std::vector<int32_t> sample = CaptureSample();
            std::vector<float> floatSample = Int_to_Float(sample);
            apply_effects(floatSample);
        }
    UnInit();
    return 0;
    }
    return 0;
}

