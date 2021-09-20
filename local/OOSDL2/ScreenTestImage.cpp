#include "OOSDL2.h"

#ifdef flagGUI

NAMESPACE_SDL2_BEGIN

const char* def_shader = R"SH4D3R(
#define M_PI	3.1415926535897932384626433832795

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec3 res = iResolution;
    float t = float(iFrame) / 60.0;
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
	test_image.is_win_fbo = true;
	test_image.fb_size = screen_sz;
	
	test_image.SetFragmentShaderSource(def_shader);
	
	return test_image.Initialize();
}


NAMESPACE_SDL2_END

#endif
