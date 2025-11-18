
#include <vector>
#include <cmath>

float echoFx(float inputSample) {
    // Settings
    constexpr float sampleRate = 44100.0f;
    constexpr float delayTimeSec = 0.7f; // 700 ms delay
    constexpr float feedback = 0.6f;     // 60% repeats
    constexpr float mix = 0.5f;          // Wet/dry mix

    // Persistent buffer
    static std::vector<float> buffer(static_cast<int>(sampleRate * delayTimeSec), 0.0f);
    static int writeIndex = 0;
    float delayedSample = buffer[writeIndex];
    buffer[writeIndex] = inputSample + delayedSample * feedback;
    writeIndex = (writeIndex + 1) % buffer.size();
    return inputSample * (1.0f - mix) + delayedSample * mix;
}
