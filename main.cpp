#include <alsa/asoundlib.h>
#include <fftw3.h>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
#include <chrono>
#include <thread>

#include "alsa_utils.h"
#include "pedals/all_pedals.h"

int main() {
    if (InitCapture(NULL)){
    std::cout << "Starting Recording..." << std::endl;
    std::vector<int32_t> sample = CaptureSample();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    for (int i = 0; i < sample.size(); i++){
        std::cout << sample[i] << std::endl;
        }
    UnInit();
    return 0;
    }
    return 0;
}

