#define M_PI	3.1415926535897932384626433832795
#define M_2PI (M_PI * 2.0)


float GetValueStd(int samp, float time, float freq) {
    float v_time = 1.0 / freq;
    float v_time_pos = time / v_time;
    float v_time_phase = mod(v_time_pos, 1.0);
    float v_len = iSampleRate / freq;
    float v_samp_pos = float(samp) / v_len;
    float v_samp_phase = mod(v_samp_pos, 1.0);
    float v_phase = mod(v_samp_pos + v_time_pos, 1.0);
    float v = min(1.0, max(-1.0, sin(v_phase * M_2PI)));
	return v;
}

float InvertWave(float f) {return -f;}
float InvertNormalizedWave(float f) {return 1.0 - f;}
float NormalizeWave(float f) {return (f + 1.0) * 0.5;}


vec2 mainSound(int samp, float time)
{
    float pan = GetValueStd(samp, time, 1.0 / 3.0);
    float tone = GetValueStd(samp, time, 440.0 / 4.0);
    float left_vol = NormalizeWave(pan);
    float right_vol = NormalizeWave(InvertWave(pan));
	vec2 ret = vec2(left_vol * tone, right_vol * tone);
    return ret;
}
