//pass by value to avoid duping signal
//allows for inline signal processing

void fuzz_pedal_func(float& input)
{
    constexpr float gain = 40.0f;
    float x = input * gain;

    // Hard clip
    if (x > 1.0f) x = 1.0f;
    else if (x < -1.0f) x = -1.0f;

    // Output scaling
    input = x * 0.5f;
}
