
#define M_PI	3.1415926535897932384626433832795

vec2 mainSound(float time)
{
    #if 0
    // very hackish method to get continuous time, but works
    float frame_time = time - iAudioSeconds;
    float x = frame_time * iSampleRate;
    float total_x = iResolution.x * iFrame;
    float sample_x = total_x + x;
    time = sample_x / iSampleRate;
    #elif 0
    // this method is slightly cleaner, but is not shadertoy compatible
    float sample_x = gl_FragCoord.x + iFrame * iResolution.x;
    time = sample_x / iSampleRate;
    #else
    // Using given time as local continuous time (and not as global realtime) requires additional configuration from shader player.
    // If the sound quality is bad, instruct shader player to use local time for sound (which breaks realtime audio/video sync though :/)
    #endif

    //float sample_freq = 440.0 * 2.0 / iSampleRate;
    float freq = 440.0;
    float wave_time = 1.0 / freq;
    float wave_phase = mod(time, wave_time) / wave_time;
    float v = (1.0 + sin(wave_phase * 2.0 * M_PI)) * 0.5;
    return vec2(v,0);
}
