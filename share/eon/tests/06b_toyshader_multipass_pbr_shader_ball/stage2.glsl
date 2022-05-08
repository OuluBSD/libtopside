/**
 * -----------------------------------------------------------
 * - Anti-Aliasing
 * -----------------------------------------------------------
 * 
 * Implements the 'Random 8x8 Dynamic' supersampling from:
 *
 *     'Anti-Aliasing Compare' - JasonD
 *     'https://www.shadertoy.com/view/4dGXW1'
 *
 * The results are acceptable, and I couldn't find anything 
 * that worked better with this particular scene.
 *
 * Originally used temporal anti-aliasing (TAA), but it caused the  
 * outer edges to blur too much while doing little for the inner edges.
 *
 * The 8x8 supersampling tends to blur the scene too much overall
 * and so I only apply it to the geometry edges. Edges are calculated
 * by performing a surface ID difference which is demonstrated at:
 *
 *     'SDF Outline Comparison' - ssell
 *     https://www.shadertoy.com/view/4lfyR2
 *
 * The primary downside to this approach is that anti-aliasing in
 * reflections is not really ever addressed.
 */

const int SampleSteps = 4;      // Increase to 8 for better quality

//------------------------------------------------------------------------------------------
// AA 
//------------------------------------------------------------------------------------------

vec2 noise2(vec2 location, vec2 delta) 
{
    const vec2 c = vec2(12.9898, 78.233);
    const float m = 43758.5453;
    return vec2(
        fract(sin(dot(location +      delta            , c)) * m),
        fract(sin(dot(location + vec2(delta.y, delta.x), c)) * m)
        );
}


vec4 SampleAA(sampler2D sampler, in vec2 uv)
{
    vec4 source = texture(sampler, uv);
    
    // IDs are the integer part of the .w (depth is stored in fractional)
    float sourceID   = floor(source.w);     
    float sourceDiff = 0.0;
    
    vec3 color = vec3(0.0);
    vec2 s = vec2(1.0 / iResolution.x, 1.0 / iResolution.y) * 2.25;
    
    float t = iTime + 0.1;
    
    for (int i = 0; i < SampleSteps; i++)
    {
        for (int j = 0; j < SampleSteps; j++) 
        {
            vec2 q = t * vec2(float(i), float(j));
            vec2 n = noise2(uv , q);
            vec2 offset = vec2(n.x, n.y) - vec2(0.5, 0.5);
            
            vec4 tx = texture(sampler, uv + offset * s);
            color += tx.rgb;
            
            sourceDiff += abs(sourceID - tx.w);
        }
    }
    
    color      /= float(SampleSteps * SampleSteps); 
    sourceDiff /= float(SampleSteps * SampleSteps);
    sourceDiff  = pow(sourceDiff, 8.0);
    
    return vec4(mix(source.rgb, color, clamp(sourceDiff, 0.2, 1.0)), source.w);
}

//------------------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------------------

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 uv = fragCoord / iResolution.xy;
    fragColor = SampleAA(iChannel0, uv);
}