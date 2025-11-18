#include <cmath>

void detune_func(float& input, float detuneAmount, float phase = 0.0f, float sampleRate = 44100.0f, float baseFreq = 440.0f) {
    float detunedFreq = baseFreq * (1.0f + detuneAmount * 0.01f); 
    phase += 2.0f * M_PI * detunedFreq / sampleRate;
    if (phase > 2.0f * M_PI) phase -= 2.0f * M_PI;

    input = std::sin(phase); 
}