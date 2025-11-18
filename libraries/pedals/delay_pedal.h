//pass by value to avoid duping signal
//allows for inline signal processing

//create a delay buffer, hold it for delay and add output to input
void delayFx(float &inputSample) {
    constexpr float sampleRate = 44100.0f;
    constexpr float delayTimeSec = 0.5f; // 500 ms
    constexpr float feedback = 0.5f;     // 50% feedback
    constexpr float mix = 0.5f;          // 50% wet/dry

    static std::vector<float> buffer(static_cast<int>(sampleRate * delayTimeSec), 0.0f);
    static int writeIndex = 0;
    float delayedSample = buffer[writeIndex];
    buffer[writeIndex] = inputSample + delayedSample * feedback;
    writeIndex = (writeIndex + 1) % buffer.size();
    inputSample * (1.0f - mix) + delayedSample * mix;
}