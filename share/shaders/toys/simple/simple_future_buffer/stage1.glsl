
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 coord = fragCoord;
    vec2 change;
    float t = iTime * 6;
    change.x = sin(t);
    change.y = cos(t);
    coord = coord + change * cos(iTime * 0.2);
    vec2 uv = coord / iResolution.xy;   
    fragColor = texture(iChannel0,uv);
}
