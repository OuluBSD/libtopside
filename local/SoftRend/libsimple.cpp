#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN
namespace Shaders {

vec3 iResolution;
float iTime;



void FS_SimpleSingle(vec4& fragColor, const vec2& fragCoord )
{
    vec3 res = iResolution;
    ASSERT(res[0] > 0 && res[1] > 0);
    float t = iTime;
    vec3 shift = vec3(
        sin(t),
        sin(t + M_PI/3.0),
        sin(t + M_PI*2.0/3.0));
    fragColor = vec4(
        fragCoord[0] / res[0] + shift[0],
        fragCoord[1] / res[1] + shift[1],
        1.0 - fragCoord[1] / res[1] + shift[2], 0);
}



}
NAMESPACE_TOPSIDE_END
