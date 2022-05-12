// Simple Trumpet sound - 2017 by JT

#define pi 3.1415926

float sigmoid(float x)
{
    return 1.0 / (1.0 + exp(-x));
}

float smoothed_sawtooth(float d, float x)
{
    return (1.0 - 2.0 * acos(d * -cos(x / 2.0)) / pi) * (2.0 *  atan(sin(x / 2.0) / (1.0 - d)) / pi);
}

float trumpet(float t, float f)
{
    // Sound starts with sine which turns into (smoothed) sawtooth.
    return smoothed_sawtooth(0.95 * sigmoid(t * 10.0), f * t);
}

float scale(float n)
{
    return mod(floor(n) * 7.0, 12.0);
}

vec2 mainSound(float time)
{
    float t = mod(time, 2.0);
    //float d = 0.5 + 0.499 * sin(time);
    //return vec2(smoothed_sawtooth(.001, 2.0 * pi * 440.0 * time));
    //return vec2(smoothed_sawtooth(0.00 + 0.95 * sigmoid(t * 10.0), 2.0 * pi * 440.0 * t));
    //return 0.25 * vec2(trumpet(t, 2.0 * pi * 440.0 / 4.0));
    ////float f = pow(2.0, mix(0.0, 7.0, step(1.0, t)) / 12.0);
    float f = pow(2.0, scale(mod(time / 2.0, 4.0))/12.0);
    return 0.25 * vec2(trumpet(t, f * 2.0 * pi * 440.0 / 4.0));
}
