#define PERIOD 10.0 // in seconds

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord / iResolution.xy;
    vec2 onePixel = vec2(1, 1) / iResolution.xy;
    
    float wave = 3.0 + 0.75*sin(1.0/PERIOD * iTime * 6.28); // Oscillates between 2.25 and 3.75
    
	fragColor = texture(iChannel0, uv + vec2(-onePixel.x, -onePixel.y))
              + texture(iChannel0, uv + vec2(          0, -onePixel.y))
              + texture(iChannel0, uv + vec2( onePixel.x, -onePixel.y))
              + texture(iChannel0, uv + vec2(-onePixel.x,           0))
              + texture(iChannel0, uv + vec2(          0,           0)) * -wave;
              + texture(iChannel0, uv + vec2( onePixel.x,           0))
              + texture(iChannel0, uv + vec2(-onePixel.x,  onePixel.y))
              + texture(iChannel0, uv + vec2(          0,  onePixel.y))
              + texture(iChannel0, uv + vec2( onePixel.x,  onePixel.y));
    fragColor = 1.0 - fragColor;
}