#include <iostream>
#include <vector>
#include <chrono>

#include "libraries/alsa_utils.h"
#include "libraries/apply_effects.h"

int main(int argc, char* argv[]) {

    //error handling stuff
    //std::freopen("output.log", "w", stdout); 
    //std::freopen("error.log", "w", stderr);

    char* capture_endpoint = NULL; //pass argument alsa endpoint ex: "plughw:1,0"
    char* playback_endpoint = NULL; //pass argument alsa endpoint ex: "plughw:1,0"

    if (argc == 1){
        std::cerr << "Please pass arguments as: './main capture playback'" << std::endl;
        return 0;
    }

    if (argc <= 3){ //need to pass both input and output
    try {capture_endpoint = argv[1];} catch (int e) {std::cerr << "Pass capture point as 'hw:3,0'" << std::endl;} //arecord -D hw:0,0 --dump-hw-params /dev/zero
    try {playback_endpoint = argv[2];} catch (int e) {std::cerr << "Pass playback point as 'hw:1,0'" << std::endl;}
    }

    
    PedalSettingsStruct PedalSettings;
    int update_settings_count = 0;

    if (InitCapture(capture_endpoint)){
        std::cout << "Starting Recording..." << std::endl;
        if (InitPlayback(playback_endpoint)){
            std::cout << "Starting Playback..." << std::endl;
            while(true){
                update_settings_count += 1;
                if (update_settings_count == 1000) {
                    read_settings(PedalSettings);
                    update_settings_count = 0;
                }

                std::vector<int32_t> sample = CaptureSample();
                for (int32_t samp: sample){
                    std::cout << samp << std::endl;
                }
                //std::vector<float> floatSample = Int_to_Float(sample);
                //apply_effects(floatSample, PedalSettings);
                //sample = Float_to_Int(floatSample); 
                PlaybackSamples(_playbackDevice, sample, 4);                
            }
        UnInitPlaybackDevice();        
        }    
    UnInitCaptureDevice();
    }
    return 0;
}

