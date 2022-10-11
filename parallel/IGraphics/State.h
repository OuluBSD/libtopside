#ifndef _IGraphics_State_h_
#define _IGraphics_State_h_

NAMESPACE_PARALLEL_BEGIN


struct GfxShaderState : RTTIBase {
	 RTTI_DECL0(GfxShaderState)
	
	using ShaderType = GVar::ShaderType;
	
	virtual ~GfxShaderState() {}
	
	// meta
	bool enabled;
	
	// shader stage
	ShaderType	type = GVar::SHADERTYPE_NULL;
	String		code;
	String		library;
	
	// vertex shader
	mat4	view;
	mat4	projection;
	mat4	scale;
	mat4	offset;
	
	
	
	void Clear() {
		enabled = 0;
		type = GVar::SHADERTYPE_NULL;
		code.Clear();
		library.Clear();
		view.Clear();
		projection.Clear();
		scale.Clear();
		offset.Clear();
	}
	
};



NAMESPACE_PARALLEL_END


#endif
