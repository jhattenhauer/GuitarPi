#include <iostream>
#include <vector>
#include <chrono>

#include "libraries/alsa_utils.h"
#include "libraries/apply_effects.h"

int main(int argc, char* argv[]) {

    char* capture_endpoint = NULL; //pass argument alsa endpoint ex: "hw:3,0"
    char* playback_endpoint = NULL; //pass argument alsa endpoint ex: "hw:1,0"

    if (argc == 1){
        std::cerr << "Please pass arguments as: './main capture playback'" << std::endl;
        return 0;
    }

    if (argc <= 2){ //need to pass both input and output
    try {capture_endpoint = argv[1];} catch (int e) {std::cerr << "Pass capture point as 'hw:3,0'" << std::endl;}
    try {playback_endpoint = argv[2];} catch (int e) {std::cerr << "Pass playback point as 'hw:1,0'" << std::endl;}
    }

    if (InitCapture(NULL)){
        std::cout << "Starting Recording..." << std::endl;
        if (InitPlayback(NULL)){
            std::cout << "Starting Playback..." << std::endl;
            while(true){
                std::vector<int32_t> sample = CaptureSample();
                std::vector<float> floatSample = Int_to_Float(sample);
                apply_effects(floatSample);
                sample = Float_to_Int(floatSample); 
                PlaybackSamples(_playbackDevice, sample, 4);                
            }
        UnInitPlaybackDevice();        
        }    
    UnInitCaptureDevice();
    }
    return 0;
}

