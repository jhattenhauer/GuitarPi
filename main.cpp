#include <iostream>
#include <vector>
#include <chrono>

#include "libraries/alsa_utils.h"
#include "libraries/apply_effects.h"

int main(int argc, char* argv[]) {

    char* alsa_endpoint = NULL; //pass argument alsa endpoint ex: "hw:3,0"
    if (argc != 0){
    alsa_endpoint = argv[1];
    }
    if (InitCapture(NULL)){
        std::cout << "Starting Recording..." << std::endl;
        if (InitPlayback(NULL)){
            std::cout << "Starting Playback..." << std::endl;
            while(true){
                std::vector<int32_t> sample = CaptureSample();
                std::vector<float> floatSample = Int_to_Float(sample);
                apply_effects(floatSample);
                
            }
        UnInitPlaybackDevice();        
        }    
    UnInitCaptureDevice();
    }
    return 0;
}

