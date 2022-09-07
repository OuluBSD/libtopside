
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord.xy / iResolution.xy;   
    if (uv.x < 0.5)
        // fragColor = vec4(0.0,0.0,0.0,1.0);
        fragColor = texture(iChannel1,uv) * 0.5;
    else
        fragColor = texture(iChannel0,uv);
    
    //fragColor = vec4(1.0,0.5,0.0,1.0);
    fragColor = texture(iChannel2,uv);
    //fragColor = vec4(uv,0.0,1.0);
}
