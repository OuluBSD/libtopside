#ifndef _SoftRend_Library_h_
#define _SoftRend_Library_h_

NAMESPACE_TOPSIDE_BEGIN
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



struct FS_SimpleSingle : SoftShaderBase {
	void Process(SdlCpuFragmentShaderArgs& args) override;
};


}
NAMESPACE_TOPSIDE_END

#endif
