#include <cmath>

// Simple low-pass filter
void lowpass_pedal_func(float& input, float cutoff, float sampleRate)
{
    static float prevOutput = 0.0f;

    float RC = 1.0f / (2.0f * M_PI * cutoff);
    float dt = 1.0f / sampleRate;
    float alpha = dt / (RC + dt);

    float output = prevOutput + alpha * (input - prevOutput);

    prevOutput = output;
    input = output;
}