// "sound-in" message from https://www.shadertoy.com/view/MtyXRW by Fabrice Neyret
// --- access to the image of ascii code c
//#define C(c) U.x-=.5; T+= U.x<.0||U.x>1.||U.y<0.||U.y>1. ?vec4(0): texture( iChannel3, U/16. + fract( vec2(c, 15-c/16) / 16.))
//#define C(c) U.x-=.5; T+= U.x<.0||U.x>1.||U.y<0.||U.y>1. ?vec4(0): textureLod( iChannel3, U/16. + fract( vec2(c, 15-c/16) / 16.), \
//                                                                               log2(length(fwidth(U/16.*iResolution.xy))) )
  #define C(c) U.x-=.5; T+= U.x<.0||U.x>1.||U.y<0.||U.y>1. ?vec4(0): textureGrad(iChannel3, U/16. + fract( vec2(c, 15-c/16) / 16.), dFdx(U/16.),dFdy(U/16.) )
#define initMsg vec4 T = vec4(0)
#define endMsg  return length(T.yz)==0. ? 0. : T.x

float message(vec2 U) { // to alter in the icon with the alter message
    vec4 T = vec4(0);   // or: initMsg;
    C(83);C(111);C(117);C(110);C(100);C(32);C(105);C(110); // message "Sound in"
    return length(T.yz)==0. ? -1. : T.x; // or: endMsg;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    //  if (iResolution.y<200.) to display only in the icon 
    if (iResolution.y<2000.) {float c=message((fragCoord/iResolution.y-vec2(.1,.2))*8.);if(c>=0.){fragColor=vec4(c);return;}}

    
    vec2 uv = fragCoord.xy / iResolution.xy;
	fragColor = vec4(uv,0.5+0.5*sin(iTime),1.0);
}

/*
#define plot(Y) o += smoothstep(40./R.y, 0., abs(Y-U.y))
#define plot_r(Y) o.r += smoothstep(40./R.y, 0., abs(Y-U.y))
#define plot_g(Y) o.g += smoothstep(40./R.y, 0., abs(Y-U.y))

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
    return smoothed_sawtooth(0.05 + 0.95 * sigmoid(t * 10.0), f * t);
}

float scale(float n)
{
    return mod(floor(n) * 7.0, 12.0);
}

void mainImage( out vec4 o, in vec2 U )
{
    float T = mod(iTime / 2.0, 4.0);
    float t = mod(iTime, 2.0);
    vec2 R = iResolution.xy;

    U = 10.* (2.*U-R)/R.y;
    o -= o;
    
    float f = pow(2.0, scale(T)/12.0);
    plot(trumpet(t - U.x, f * 2.0 * pi * 440.0 / 4.0));
    //plot(plucked_string(2.0 * pi * 440.0 * mod(t, 5.0) - U.x) + 0.0);
    
    //plot(  sin(t - U.x) + 0.);
 
    o.b += .2;
}
*/
    