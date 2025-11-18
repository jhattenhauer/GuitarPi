//pass by value to avoid duping signal
//allows for inline signal processing

void fuzz_pedal_func(float& input, float gain = 40.0f){
    float x = input * gain;

    if (x > 1.0f) x = 1.0f;
    else if (x < -1.0f) x = -1.0f;
    input = x * 0.5f;
}
