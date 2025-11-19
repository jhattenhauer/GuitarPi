#include <vector>
#include <cmath>

void reverseDelay_pedal_func(float &inputSample, float sampleRate = 44100.0f, float delayTimeSec = 0.5f, float mix = 0.5f) {
    static std::vector<float> buffer(static_cast<int>(sampleRate * delayTimeSec), 0.0f);
    static int writeIndex = 0;
    static bool bufferFull = false;

    buffer[writeIndex] = inputSample;
    writeIndex++;

    if (writeIndex >= buffer.size()) {
        writeIndex = 0;
        bufferFull = true;
    }

    float output = 0.0f;
    if (bufferFull) {
        int readIndex = (writeIndex - 1 + buffer.size()) % buffer.size();
        output = buffer[readIndex];
    }

    inputSample * (1.0f - mix) + output * mix;
}
