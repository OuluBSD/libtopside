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
        1.0, //fragCoord.y / res.y + shift.y,
        fragCoord.x / res.x + shift.x,
        1.0 - fragCoord.y / res.y + shift.z, 1);
}
