#ifndef _SoftRend_Common_h_
#define _SoftRend_Common_h_

NAMESPACE_PARALLEL_BEGIN


template <class Backend> struct VertexShaderArgsT;
template <class Backend> struct FragmentShaderArgsT;


template <class Gfx>
struct SoftShaderBaseT : RTTIBase {
	RTTI_DECL0(SoftShaderBaseT)
	
	virtual ~SoftShaderBaseT() {}
	
	virtual void Process(VertexShaderArgsT<Gfx>& args) {Panic("not implemented");}
	virtual void Process(FragmentShaderArgsT<Gfx>& args) {Panic("not implemented");}
};


struct GenericShaderArgs {
	vec3 iResolution;
	float iTime;
	
};

struct GenericVertexShaderArgs {
    mat4 view;
    /*mat4 proj;
    mat4 scale;
    mat4 model;*/
    
};

struct GenericFragmentShaderArgs {
	vec3 light_dir;
	
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




template <class Backend>
struct VertexShaderArgsT : GfxVertexShaderArgs {
	using Base = VertexShaderArgsT<Backend>;
	RTTI_DECL1(VertexShaderArgsT, GfxVertexShaderArgs)
	
	
	GenericShaderArgs* generic = 0;
	GenericVertexShaderArgs* va = 0;
	
	Vertex v;
	
};

template <class Backend>
class SoftFramebufferT;

template <class Backend>
struct FragmentShaderArgsT : GfxFragmentShaderArgs {
	using Base = FragmentShaderArgsT<Backend>;
	using SoftFramebuffer = SoftFramebufferT<Backend>;
	using NativeColorBuffer = typename Backend::NativeColorBuffer;
	RTTI_DECL1(FragmentShaderArgsT, GfxFragmentShaderArgs)
	
	
	GenericShaderArgs* generic = 0;
	GenericFragmentShaderArgs* fa = 0;
	const SoftFramebuffer* tex_img[TEXTYPE_COUNT];
	
	vec3 normal;
	vec2 tex_coord;
	vec3 bc_screen;
	vec2 frag_coord;
	vec4 frag_color_out;
	
	
	FragmentShaderArgsT() {
		for(int i = 0; i < TEXTYPE_COUNT; i++)
			tex_img[i] = 0;
	}
	
};

NAMESPACE_PARALLEL_END

#endif
