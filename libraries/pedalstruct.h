struct PedalSettingsStruct {
    float compressor_enabled;
    float compressor_threshold;
    float compressor_ratio;
    float compressor_makeup_gain;

    float delay_enabled;
    float delay_sampleRate;
    float delay_delayTimeSec;
    float delay_feedback;
    float delay_mix;

    float detune_enabled;
    float detune_detuneAmount;
    float detune_phase;
    float detune_sampleRate;
    float detune_baseFreq;

    float distortion_enabled;
    float distortion_gain;

    float echo_enabled;
    float echo_sampleRate;
    float echo_delayTimeSec;
    float echo_feedback;
    float echo_mix;

    float fuzz_enabled;
    float fuzz_gain;

    float highpass_enabled;
    float highpass_cutoff;
    float highpass_sampleRate;

    float lowpass_enabled;
    float lowpass_cutoff;
    float lowpass_sampleRate;

    float reverb_enabled;
    float reverb_sampleRate;
    float reverb_feedback;
    float reverb_mix;

    float reverse_enabled;
    float reverse_sampleRate;
    float reverse_delayTimeSec;
    float reverse_mix;
};
