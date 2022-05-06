
#define M_PI	3.1415926535897932384626433832795

vec2 mainSound(float time)
{
    vec2 uv = gl_FragCoord.xy / iResolution.xy;
    vec2 center = texture(iChannel0, uv).xy;

    float freq = 440.0;
    float wave_time = 1.0 / freq;
    float wave_phase = mod(time, wave_time) / wave_time;
    float v = (1.0 + sin(wave_phase * 2.0 * M_PI)) * 0.5;

    float mix_freq = 0.5;
    float mix_time = 1.0 / mix_freq;
    float mix_phase = mod(time, mix_time) / mix_time;
    float mix_v = (1.0 + sin(mix_phase * 2.0 * M_PI)) * 0.5;

    float stereo_freq = 0.25;
    float stereo_time = 1.0 / mix_freq;
    float stereo_phase = mod(time, mix_time) / mix_time;
    float stereo_v = (1.0 + sin(mix_phase * 2.0 * M_PI)) * 0.5;


    return vec2(stereo_v * v, (1.0 - stereo_v) * v) * mix_v + center * (1.0 - mix_v);
}
