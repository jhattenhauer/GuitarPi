

#include <algorithm>  // for std::min, std::max
#include <cmath>      // for fabs

void compressor_func(float& input)
{
    float threshold = 0.5f;  // level above which compression occurs
    float ratio = 4.0f;      // compression ratio
    float makeup_gain = 1.2f; // optional gain after compression

    float abs_input = std::fabs(input);

    if (abs_input > threshold)
    {
        // apply compression above threshold
        float exceeded = abs_input - threshold;
        float compressed = exceeded / ratio;
        abs_input = threshold + compressed;
    }

    // restore sign and apply makeup gain
    input = (input >= 0.0f ? 1.0f : -1.0f) * abs_input * makeup_gain;
}
