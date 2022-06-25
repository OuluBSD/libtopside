in vec3 normal;

#define M_PI	3.1415926535897932384626433832795

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec3 res = iResolution;
    float t = iTime;
    vec3 shift = vec3(
        sin(t),
        sin(t + M_PI/3.0),
        sin(t + M_PI*2.0/3.0));
    fragColor = vec4(
        fragCoord.x / res.x + shift.x,
        fragCoord.y / res.y + shift.y,
        1.0 - fragCoord.y / res.y + shift.z,
        1);
    
    vec2 uv = (fragCoord / iResolution.xy) * 2 - 1;
    if (abs(uv.x+uv.y) < 0.01) {
        fragColor = vec4(1,0,0,1);
    }
    if (abs(uv.x-uv.y) < 0.01) {
        fragColor = vec4(0,0,1,1);
    }
}
