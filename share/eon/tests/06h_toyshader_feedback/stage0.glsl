// **********************************************************************
// Console rendering
// **********************************************************************
const vec4 glyphCount = vec4(80.0, 30.0, 80.0, 80.0);
const vec4 flashParams = vec4(1.0, 0.5, 0.0, 0.0); // x = freq(Hz), y = duty, z = unused, w = unused

const vec4 caretColour = vec4(0.5, 0.5, 0.5, 1.0);
const vec4 glyphColour = vec4(0.5, 0.5, 0.5, 1.0);

vec4 sampleLetter(float letterOrd, vec2 letterUV)
{
    float letterOrdD16 = floor(letterOrd / 16.0);
    float letterOrdM16 = floor(letterOrd - 16.0 * letterOrdD16);
    
    vec4 offsets;
    offsets = vec4(
        letterOrdM16,
        1.0 + letterOrdD16,
        1.0,
        -1.0);
    offsets *= vec4(10.0, 16.0, 8.0, 12.0);
    offsets.xy += vec2(1.0, -2.0);
    offsets /= iResolution.xyxy;

    vec2 mask = step(abs(0.5 - letterUV), vec2(0.5, 0.5));
    mask.x *= mask.y;

    return texture(iChannel0, offsets.xy + offsets.zw * letterUV).rrra * mask.x;
}

float getTappedLetter()
{
    return texture(iChannel0, vec2(160.5, 8.5) / iResolution.xy).r * 256.0;
}

float getHeldLetter()
{
    return texture(iChannel0, vec2(161.5, 8.5) / iResolution.xy).r * 256.0;
}

bool isCursorPos(vec2 dataUV)
{
    float numChars = glyphCount.z*glyphCount.w;
    float rawPos = texture(iChannel0, vec2(0.5, 209.5) / iResolution.xy).r * numChars;

    vec2 cursorPos;
    cursorPos.y = floor((rawPos + 0.5) / glyphCount.z);
    cursorPos.x = rawPos - glyphCount.z * cursorPos.y;

    dataUV *= glyphCount.zw;

    vec2 delta = abs(dataUV - cursorPos);

    return delta.x + delta.y < 0.5;
}

float getBufferLetter(vec2 dataUV)
{
    vec2 bufferL = vec2(0.5, 128.5);
    vec2 bufferH = vec2(80.5, 208.5);
    vec2 sampleUV = mix(bufferL, bufferH, dataUV) / iResolution.xy;

    float bufferLetter = texture(iChannel0, sampleUV).r * 256.0;

    return bufferLetter;
}

// Assumes 640x480 display with 8x12 glyphs and 4 rows between lines
vec4 renderScreenPos(in vec2 screenUV)
{
    vec2 glyphUV = vec2(screenUV * glyphCount.xy);
    vec2 dataUV = floor(glyphUV);
    glyphUV -= dataUV;

    dataUV.y = glyphCount.y - 1.0 - dataUV.y;
    dataUV /= glyphCount.zw;

    vec4 fragColour = sampleLetter(getBufferLetter(dataUV), glyphUV);
    vec4 flashColour = vec4(0.0, 0.0, 0.0, 1.0);
    if (isCursorPos(dataUV))
    {
        float flashChar = 127.0 * step(fract(iTime * flashParams.x), flashParams.y);
        
        flashColour = caretColour * sampleLetter(flashChar, glyphUV);
    }
    fragColour = mix(flashColour, glyphColour, fragColour);

    vec2 clip = step(abs(screenUV - 0.5), vec2(0.5, 0.5));
    fragColour *= clip.x * clip.y;

    return fragColour;
}

vec4 colourScreen(vec2 uv, vec4 colour)
{
    vec2 uvDelta = uv - 0.5;
    
    colour.rgb = mix(
        vec3(0.035, 0.040, 0.030),
        vec3(0.980, 1.0040, 0.960),
        colour.rgb);
    colour.rgb *= 1.0 - dot(uvDelta, uvDelta);
    colour.rgb *= colour.a;
    colour.a = 1.0;
    return colour;
}

vec4 toneMap(vec4 colour)
{
    colour.rgb = pow(colour.rgb, vec3(1.0 / 2.0));
    return colour;
}

vec2 distortUV(vec2 rawUV, float distortStrength)
{
    vec2 intermediateUV = rawUV - 0.5;
    intermediateUV *= 1.05;

    intermediateUV *= mix(1.0, 4.0 * dot(intermediateUV, intermediateUV), distortStrength);

    return 0.5 + intermediateUV;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord )
{
    vec2 quadUV = 0.5 + (fragCoord - 0.5 * iResolution.xy) / (iResolution.y * vec2(1.3333333, 1.0));
    vec2 distortedUV = distortUV(quadUV, 0.07);
    
    fragColor = renderScreenPos(distortedUV);
    fragColor = colourScreen(distortedUV, fragColor);
    fragColor = toneMap(fragColor);
}