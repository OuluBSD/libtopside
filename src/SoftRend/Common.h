#ifndef _SoftRend_Common_h_
#define _SoftRend_Common_h_

NAMESPACE_TOPSIDE_BEGIN


 struct VertexShaderArgs;
 struct FragmentShaderArgs;



struct SoftShaderBase : RTTIBase {
	RTTI_DECL0(SoftShaderBase)
	Index<dword> used_uniforms;
	
	SoftShaderBase() {
		UseUniform(GVar::VAR_VIEW);
		UseUniform(GVar::VAR_LIGHTDIR);
		UseUniform(GVar::VAR_COMPAT_RESOLUTION);
		UseUniform(GVar::VAR_COMPAT_TIME);
	}
	virtual ~SoftShaderBase() {}
	
	virtual void Process(VertexShaderArgs& args) {Panic("not implemented");}
	virtual void Process(FragmentShaderArgs& args) {Panic("not implemented");}
	
	void UseUniform(dword d) {used_uniforms.FindAdd(d);}
	
	int GetUsedUniformCount() const {return used_uniforms.GetCount();}
	
};


struct PassthroughSoftShaderBase : SoftShaderBase {
	using Base = SoftShaderBase;
	RTTI_DECL1(PassthroughSoftShaderBase, Base);
	
	void Process(VertexShaderArgs& args) override {}
	void Process(FragmentShaderArgs& args) override {}
};


struct GenericShaderArgs {
	vec3 iResolution;
	vec3 iChannelResolution[4];
	int iChannel0;
	int iChannel1;
	int iChannel2;
	int iChannel3;
	int iStageColor0;
	int iStageColor1;
	int iStageColor2;
	int iStageColor3;
	int iStageColor4;
	float iTime;
	
	const ByteImage* color_buf[CHANNEL_COUNT];
};

struct GenericVertexShaderArgs {
    mat4 view;
    mat4 model;
    
};

struct GenericFragmentShaderArgs {
	vec3 light_dir;
	vec3 camera_pos;
	vec3 camera_dir;
	
	int iNone;
	int iDiffuse;
	int iSpecular;
	int iAmbient;
	int iEmissive;
	int iHeight;
	int iNormals;
	int iShininess;
	int iOpacity;
	int iDisplacement;
	int iLightmap;
	int iReflection;
	int iUnknown;
	int iCubeDiffuse;
	int iCubeIrradiance;
	
	const ByteImage* color_buf[TEXTYPE_COUNT];
	
};






// IGraphics

struct GfxVertexShaderArgs : RTTIBase {
	RTTI_DECL0(GfxVertexShaderArgs)
	
	virtual ~GfxVertexShaderArgs() {}
};

struct GfxFragmentShaderArgs : RTTIBase {
	RTTI_DECL0(GfxFragmentShaderArgs)
	
	virtual ~GfxFragmentShaderArgs() {}
};





struct VertexShaderArgs : GfxVertexShaderArgs {
	using Base = VertexShaderArgs;
	RTTI_DECL1(VertexShaderArgs, GfxVertexShaderArgs)
	
	
	GenericShaderArgs* generic = 0;
	GenericVertexShaderArgs* va = 0;
	
	Vertex v;
	
};


struct FragmentShaderArgs : GfxFragmentShaderArgs {
	RTTI_DECL1(FragmentShaderArgs, GfxFragmentShaderArgs)
	
	
	GenericShaderArgs* generic = 0;
	GenericFragmentShaderArgs* fa = 0;
	//ConstByteImage* tex_img[TEXTYPE_COUNT];
	
	vec3 normal;
	vec2 tex_coord;
	vec4 bc_screen;
	vec2 frag_coord;
	vec4 frag_color_out;
	bool use_quad;
	
	
	FragmentShaderArgs() {
		//for(int i = 0; i < TEXTYPE_COUN; i++)
		//	tex_img[i] = 0;
	}
	
	vec3 GetResolution() const {return generic->iResolution;}
	float GetTime() const {return generic->iTime;}
	ConstByteImage* GetTexture(int i) {
		ASSERT(i >= 0 && i < CHANNEL_COUNT);
		if (i < 0) return 0;
		if (i < TEXTYPE_COUNT && fa->color_buf[i]) return fa->color_buf[i];
		if (i < CHANNEL_COUNT) return generic->color_buf[i];
		return 0;
	}
};

NAMESPACE_TOPSIDE_END

#endif
