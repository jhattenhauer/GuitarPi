#include <cmath>

void detune_func(float& input, float detuneAmount)
{
    // detuneAmount is in range [-1.0, 1.0], representing +/- small pitch shift
    // simple phase-based detune simulation
    static float phase = 0.0f;
    const float sampleRate = 48000.0f; // Hz
    const float baseFreq = 440.0f;     // Hz, can be parameterized

    float detunedFreq = baseFreq * (1.0f + detuneAmount * 0.01f); // ±1% detune
    phase += 2.0f * M_PI * detunedFreq / sampleRate;
    if (phase > 2.0f * M_PI) phase -= 2.0f * M_PI;

    input = std::sin(phase); // replace input with detuned sine value
}