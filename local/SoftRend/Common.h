#ifndef _SoftRend_Common_h_
#define _SoftRend_Common_h_

NAMESPACE_TOPSIDE_BEGIN


struct SdlCpuVertexShaderArgs;
struct SdlCpuFragmentShaderArgs;

struct SoftShaderBase : RTTIBase {
	RTTI_DECL0(SoftShaderBase)
	
	virtual ~SoftShaderBase() {}
	
	virtual void Process(SdlCpuVertexShaderArgs& args) {Panic("not implemented");}
	virtual void Process(SdlCpuFragmentShaderArgs& args) {Panic("not implemented");}
};


struct GenericShaderArgs {
	vec3 iResolution;
	float iTime;
	
};



NAMESPACE_TOPSIDE_END

#endif
