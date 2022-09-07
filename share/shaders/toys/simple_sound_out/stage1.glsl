
#define M_PI	3.1415926535897932384626433832795

vec2 mainSound(float time)
{
    //float sample_freq = 440.0 * 2.0 / iSampleRate;
    float freq = 440.0 * 0.25;
    float wave_time = 1.0 / freq;
    float wave = time / wave_time;
    float wave_phase = mod(wave, 1.0);
    float v = sin(wave_phase * M_PI);
    return vec2(v,0);
    //return vec2(1.0, 0.5);
    //return vec2(0.80, 0.25);
}
