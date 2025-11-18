

#include <algorithm>  // for std::min, std::max
#include <cmath>      // for fabs

void compressor_func(float& input, float threshold = 0.5f, float ratio = 4.0f, float makeup_gain = 1.2f)
{
    float abs_input = std::fabs(input);

    if (abs_input > threshold)
    {
        float exceeded = abs_input - threshold;
        float compressed = exceeded / ratio;
        abs_input = threshold + compressed;
    }

    input = (input >= 0.0f ? 1.0f : -1.0f) * abs_input * makeup_gain;
}
