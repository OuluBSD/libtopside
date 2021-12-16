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



struct FS_SimpleSingle : SoftShaderBase {
	void Process(SdlCpuFragmentShaderArgs& args) override;
};


}
NAMESPACE_TOPSIDE_END

#endif
