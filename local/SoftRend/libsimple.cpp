#include <Graphics/Graphics.h>

NAMESPACE_TOPSIDE_BEGIN
namespace Shaders {




void FS_SimpleSingle::Process(SdlCpuFragmentShaderArgs& a)
{
	GenericShaderArgs& g = *a.generic;
    vec3 res = g.iResolution;
    ASSERT(res[0] > 0 && res[1] > 0);
    float t = g.iTime;
    vec3 shift = vec3(
        sin(t),
        sin(t + M_PI/3.0),
        sin(t + M_PI*2.0/3.0));
    a.frag_color_out = vec4(
        a.frag_coord[0] / res[0] + shift[0],
        a.frag_coord[1] / res[1] + shift[1],
        1.0 - a.frag_coord[1] / res[1] + shift[2], 0);
}



}
NAMESPACE_TOPSIDE_END
