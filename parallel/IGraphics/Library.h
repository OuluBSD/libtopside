#ifndef _SoftRend_Library_h_
#define _SoftRend_Library_h_

NAMESPACE_PARALLEL_BEGIN
namespace Shaders {

/*enum {
	IVIEW,
	ILIGHTDIR,
	//IPROJ,
	//ISCALE,
	//IMODEL,
	
	IRESOLUTION,
	ITIME,
	
	UNIFORM_COUNT
};*/

inline const char* GetUniformName(int i) {
	if (i >= 0 && i < GVar::VAR_COUNT)
		return GVar::names[i];
	return "";
}



/*#ifdef flagSDL2
struct FS_Sdl2CpuSimpleSingle : SoftShaderBase {
	void Process(GfxFragmentShaderArgs&) override;
};
#endif
*/

}
NAMESPACE_PARALLEL_END

#endif
