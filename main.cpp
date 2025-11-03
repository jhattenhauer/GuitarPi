#include <iostream>
#include <vector>
#include <chrono>

#include "libraries/alsa_utils.h"
#include "libraries/apply_effects.h"

int main() {
    /*if (InitCapture(NULL)){
    std::cout << "Starting Recording..." << std::endl;
    std::vector<int32_t> sample = CaptureSample();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for (int i = 0; i < sample.size(); i++){
        std::cout << sample[i] << std::endl;
        }
    UnInit();
    return 0;
    }*/
    apply_effects();

    return 0;
}

