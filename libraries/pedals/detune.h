#include <cmath>

void detune_func(float& input, float detuneAmount)
{

    static float phase = 0.0f;
    const float sampleRate = 48000.0f;
    const float baseFreq = 440.0f;    

    float detunedFreq = baseFreq * (1.0f + detuneAmount * 0.01f); 
    phase += 2.0f * M_PI * detunedFreq / sampleRate;
    if (phase > 2.0f * M_PI) phase -= 2.0f * M_PI;

    input = std::sin(phase); 
}