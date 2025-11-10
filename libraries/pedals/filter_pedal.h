#include "lowpass_pedal.h"
#include "highpass_pedal.h"


// General filter pedal (LP + HP combined for band-pass)
void filter_pedal(float& input, float lowCut, float highCut, float sampleRate)
{
    float temp = input;

    // Apply high-pass first
    highpass_pedal(temp, lowCut, sampleRate);
    // Then low-pass
    lowpass_pedal(temp, highCut, sampleRate);

    input = temp;
}