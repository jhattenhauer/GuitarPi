#include <cmath>

// Simple high-pass filter
void highpass_pedal_func(float& input, float cutoff, float sampleRate)
{
    static float prevInput = 0.0f;
    static float prevOutput = 0.0f;

    float RC = 1.0f / (2.0f * M_PI * cutoff);
    float dt = 1.0f / sampleRate;
    float alpha = RC / (RC + dt);

    float output = alpha * (prevOutput + input - prevInput);

    prevInput = input;
    prevOutput = output;
    input = output;
}