#include <IGraphics/IGraphics.h>

NAMESPACE_TOPSIDE_BEGIN
namespace Shaders {



#ifdef flagSDL2
void FS_Sdl2CpuSimpleSingle::Process(GfxFragmentShaderArgs& a)
{
	using Frag = FragmentShaderArgsT<Sdl>;
	Frag* fa = CastPtr<Frag>(&a);
	if (fa) {
		GenericShaderArgs& g = *fa->generic;
	    vec3 res = g.iResolution;
	    ASSERT(res[0] > 0 && res[1] > 0);
	    float t = g.iTime;
	    vec3 shift = vec3(
	        sin(t),
	        sin(t + M_PI/3.0),
	        sin(t + M_PI*2.0/3.0));
	    fa->frag_color_out = vec4(
	        fa->frag_coord[0] / res[0] + shift[0],
	        fa->frag_coord[1] / res[1] + shift[1],
	        1.0 - fa->frag_coord[1] / res[1] + shift[2], 0);
	}
	else TODO
}
#endif


}
NAMESPACE_TOPSIDE_END
