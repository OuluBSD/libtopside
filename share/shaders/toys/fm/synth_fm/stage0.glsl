// Created by inigo quilez - iq/2015
// License Creative Commons Attribution-ShareAlike 3.0 Unported
// https://creativecommons.org/licenses/by-sa/3.0/

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 p = fragCoord.xy/iResolution.xy;
                  
    float im = 0.5 + 0.5*sin(0.21*6.2831*iTime);

    vec3 col = mix( vec3(0.0), vec3(0.4), 1.0-smoothstep(im,im+0.01,p.y) );
    
	fragColor = vec4( col, 1.0 );
}