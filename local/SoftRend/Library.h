#ifndef _SoftRend_Library_h_
#define _SoftRend_Library_h_

NAMESPACE_PARALLEL_BEGIN
namespace Shaders {

enum {
	IVIEW,
	ILIGHTDIR,
	/*IPROJ,
	ISCALE,
	IMODEL,*/
	
	IRESOLUTION,
	ITIME,
	
	UNIFORM_COUNT
};

inline const char* GetUniformName(int i) {
	switch (i) {
		case IVIEW:				return "iView";
		case ILIGHTDIR:			return "iLightDir";
		/*case IMODEL:			return "iModel";
		case IPROJ:				return "iProj";
		case ISCALE:			return "iScale";*/
		case IRESOLUTION:		return "iResolution";
		case ITIME:				return "iTime";
		default: return "";
	}
}



#ifdef flagSDL2
struct FS_Sdl2CpuSimpleSingle : SoftShaderBase {
	void Process(GfxFragmentShaderArgs&) override;
};
#endif


}
NAMESPACE_PARALLEL_END

#endif
