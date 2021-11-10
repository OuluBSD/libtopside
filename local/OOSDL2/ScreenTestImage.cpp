#include "OOSDL2.h"

#ifdef flagGUI

NAMESPACE_SDL2_BEGIN

const char* def_shader = R"SH4D3R(
#define M_PI	3.1415926535897932384626433832795

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec3 res = iResolution;
    float t = iTime;
    bool mode = mod(t, 6.0) > 3.0;
    //t = t * 504;
    //t = t * 0.2;
    vec3 shift = vec3(
        sin(t),
        sin(t + M_PI/3.0),
        sin(t + M_PI*2.0/3.0));
    if (mode)
        fragColor = vec4(
            fragCoord.x / res.x + shift.x,
            fragCoord.y / res.y + shift.y,
            1.0 - fragCoord.y / res.y + shift.z, 0);
    else
        fragColor = vec4(fragCoord.y/res.y + shift.x, (shift.y + 1.0) * 0.5, fragCoord.x/res.x, 0);
}
)SH4D3R";



bool Screen::TestImageInitialize() {
	ASSERT(ogl_buf)
	if (!ogl_buf) return false;
	
	OglBuffer& buf = *ogl_buf;
	buf.is_win_fbo = true;
	buf.fb_size = screen_sz;
	buf.fps = 60;
	
	if (filepath.GetCount()) {
		if (!buf.LoadFragmentShaderFile(filepath, library_paths))
			return false;
	}
	else {
		buf.SetFragmentShaderSource(def_shader);
	}
	
	return buf.Initialize();
}


NAMESPACE_SDL2_END

#endif
