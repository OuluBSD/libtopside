/**
 * -----------------------------------------------------------
 * - Shader Ball PBR
 * - Created by Steven Sell (ssell) / 2017
 * - License Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
 * - https://www.shadertoy.com/view/MtXczf
 * -----------------------------------------------------------
 *
 * -----------------------------------------------------------
 * - General 
 * -----------------------------------------------------------
 *
 * Revisting my PBR code and applying it to a shader ball model.
 * The primary difference in the lighting is the addition of:
 *
 *     - Single bounce reflection/environment sampling
 *     - Ambient occlusion
 *
 * The scene itself is fairly simple as this is more a demo of 
 * the lighting algorithm.
 *
 * See the individual buffers for more details.
 *
 *     - Buf A: Scene marching and rendering
 *     - Buf B: AA
 *     - Buf C: DoF
 *     - Image: Vignette and final output
 * 
 * -----------------------------------------------------------
 * - References
 * -----------------------------------------------------------
 *
 * -- PBR Lighting
 *
 *     'PBR Lighting Demo' - ssell
 *     https://www.shadertoy.com/view/MsXBzl
 *
 *     Source for the general PBR lighting model.
 *
 * -- Anti-Aliasing
 *
 *     'Anti-Aliasing Compare' - JasonD
 *     'https://www.shadertoy.com/view/4dGXW1'
 *
 *     Adapted the 'Random 8x8 Dynamic' supersampling method.
 *
 * -- Edge Detection
 *
 *     'SDF Outline Comparison' - ssell
 *     https://www.shadertoy.com/view/4lfyR2
 *
 *     Concentrate anti-aliasing on the geometry edges.
 */

//------------------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------------------

float Vignette(in vec2 uv)
{
    return 0.1 + 0.8 * pow(64.0 * uv.x * uv.y * (1.0 - uv.x) * (1.0 - uv.y), 0.2);
}

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 uv = fragCoord / iResolution.xy;
    
	fragColor      = vec4(texture(iChannel0, uv).rgb, 1.0);
    fragColor.rgb *= clamp(Vignette(uv), 0.0, 1.0);
}