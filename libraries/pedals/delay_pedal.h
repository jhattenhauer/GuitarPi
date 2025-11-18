//pass by value to avoid duping signal
//allows for inline signal processing

void delayFx(float &inputSample, float sampleRate = 44100.0f, float delayTimeSec = 0.5f, float feedback = 0.5f, float mix = 0.5f) {
    static std::vector<float> buffer(static_cast<int>(sampleRate * delayTimeSec), 0.0f);
    static int writeIndex = 0;
    float delayedSample = buffer[writeIndex];
    buffer[writeIndex] = inputSample + delayedSample * feedback;
    writeIndex = (writeIndex + 1) % buffer.size();
    inputSample * (1.0f - mix) + delayedSample * mix;
}