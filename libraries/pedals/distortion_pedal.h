//pass by value to avoid duping signal
//allows for inline signal processing


void distortion_pedal_func(float& input)
{
    float gain = 8.0f;
    float x = input * gain;
    float shaped = (2.0f / M_PI) * std::atan(x);
    float output = shaped * 0.3f;
}