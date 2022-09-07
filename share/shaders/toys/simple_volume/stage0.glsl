void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = (fragCoord - 0.5 * iResolution.xy)/iResolution.y;
    
    float ff = iTime / 1.5;
    float t = floor(ff);
    float frac = ff - t;
    int i = int(t) % 2;
    
    if (i == 0) {
        vec3 noise = texture(iChannel0, uv).xyz;
        fragColor = vec4(noise,1.0);
    }
    else {
        vec4 f = texture(iChannel1, vec3(uv*2.0,frac));
        fragColor = f;
    }
    //fragColor = vec4(1.0,0.0,0.0,1.0);
}
