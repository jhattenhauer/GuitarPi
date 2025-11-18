#include <vector>
#include <cmath>

void reverbFx(float &inputSample) {
    constexpr float sampleRate = 44100.0f;
    constexpr int numTaps = 4;
    constexpr float delayTimes[numTaps] = {0.029f, 0.037f, 0.041f, 0.053f};
    constexpr float feedback = 0.5f;
    constexpr float mix = 0.5f;

    static std::vector<float> buffers[numTaps] = {
        std::vector<float>(static_cast<int>(sampleRate * delayTimes[0]), 0.0f),
        std::vector<float>(static_cast<int>(sampleRate * delayTimes[1]), 0.0f),
        std::vector<float>(static_cast<int>(sampleRate * delayTimes[2]), 0.0f),
        std::vector<float>(static_cast<int>(sampleRate * delayTimes[3]), 0.0f)
    };
    static int indices[numTaps] = {0, 0, 0, 0};

    float output = 0.0f;

    for (int i = 0; i < numTaps; ++i) {
        float delayedSample = buffers[i][indices[i]];
        buffers[i][indices[i]] = inputSample + delayedSample * feedback;
        indices[i] = (indices[i] + 1) % buffers[i].size();
        output += delayedSample;
    }

    output = inputSample * (1.0f - mix) + (output / numTaps) * mix;
}
