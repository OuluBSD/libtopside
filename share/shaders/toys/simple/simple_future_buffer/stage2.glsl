
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord.xy / iResolution.xy;
    vec4 orig = texture(iChannel0,uv);
    vec4 modified = texture(iChannel1,uv);
    float mixf = 0.005;
    fragColor = orig * mixf + modified * (1.0 - mixf);
}
