#ifndef _SoftRend_Library_h_
#define _SoftRend_Library_h_

NAMESPACE_TOPSIDE_BEGIN
namespace Shaders {

enum {
	IRESOLUTION,
	ITIME,
	
	UNIFORM_COUNT
};

inline const char* GetUniformName(int i) {
	switch (i) {
		case IRESOLUTION:		return "iResolution";
		case ITIME:				return "iTime";
		default: return "";
	}
}

extern vec3 iResolution;
extern float iTime;

void FS_SimpleSingle(vec4& fragColor, const vec2& fragCoord );


}
NAMESPACE_TOPSIDE_END

#endif
