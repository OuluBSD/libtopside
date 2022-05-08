/**
 * -----------------------------------------------------------
 * - Depth of Field
 * -----------------------------------------------------------
 * 
 * Applies a very simple DoF effect to the image.
 *
 * Essentially just blurs distant geometry and is most visible
 * on the far corners of the wooden platform.
 */

//------------------------------------------------------------------------------------------
// DoF
//------------------------------------------------------------------------------------------

vec3 ApplyDoF(sampler2D sampler, in vec2 uv)
{
    // Retrieve depth from buffer.
    // Depth is stored in the fractional part of the w component [0.0001, 1.0].
    float depth = fract(texture(sampler, uv).w);
    depth = (depth < 0.0001 ? 1.0 : depth);
    depth = abs(0.175 - depth) * 4.0;             // Exaggerate distant geometry depths
    
    vec3 color = vec3(0.0);
    
    float angle  = 0.0;
    float radius = 0.0;
    
    for(int i = 0; i < 10; ++i)
    {
        vec2 suv = uv + (vec2(sin(angle), cos(angle)) * radius);
        color += texture(sampler, suv).rgb;
        
        angle  += 0.3;
        radius += 0.0001 * depth;
    }
    
    color *= 0.1;
    
    return color;
}

//------------------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------------------

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 uv = fragCoord / iResolution.xy;
    fragColor.rgb = ApplyDoF(iChannel0, uv);
}