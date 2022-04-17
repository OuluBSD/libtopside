#ifndef _IGraphics_Ogl_h_
#define _IGraphics_Ogl_h_

#ifdef flagOGL

NAMESPACE_PARALLEL_BEGIN



// default frame TODO should be conditional
/*using OglStateDraw		= SdlOglStateDraw;
using OglDataState		= SdlOglDataState;
using OglShaderPipeline	= SdlOglShaderPipeline;
//using OglShader			= SdlOglShader;
using OglFramebuffer	= SdlOglFramebuffer;
using OglBuffer			= SdlOglBuffer;
//using OglBinderIface	= SdlOglBinderIface;
using OglDataObject		= SdlOglDataObject;*/


#define GFX_CLS(x, g) struct g##x : x##T<g##Gfx> {\
	using Base = x##T<g##Gfx>; \
	RTTI_DECL1(g##x, Base) \
};

#if defined flagSDL2
GFX_CLS_LIST(SdlOgl)
#endif

GFX_CLS_LIST(X11Ogl)

#undef GFX_CLS


#ifdef flagSDL2
using OglBufferT		= BufferT<SdlOglGfx>;
#endif

int GetOglChCode(int channels, bool is_float=false);


template <class Gfx>
struct OglVertexShaderArgs {
	using Framebuffer = FramebufferT<Gfx>;
	using DataObject = DataObjectT<Gfx>;
	
	Framebuffer& state;
	DataObject& obj;
	const vec3& pos;
	const vec3& normal;
	const vec2& tex_coords;
	vec4& pos_out;
	vec2& tex_coord_out;
};

struct OglFragmentShaderArgs {
	
};

//using OglCpuVertexShaderArgs = OglVertexShaderArgs;
//using OglCpuFragmentShaderArgs = OglFragmentShaderArgs;






//struct OglFramebuffer;
//struct OglDataObject;

//struct OglStateDraw : StateDrawT<OglGfx> {RTTI_DECL1(OglStateDraw, Base)};
//struct OglFramebuffer : FramebufferT<OglGfx> {RTTI_DECL1(OglFramebuffer, Base)};



/*class SdlOglDrawFramebuffer : public DrawFramebufferT<SdlOglGfx> {
public:
	RTTI_DECL1(SdlOglDrawFramebuffer, Base)
	
};*/

template <class T>
struct OglDataObject : DataObjectT<T> {
	using Base = DataObjectT<T>;
	RTTI_DECL1(OglDataObject, Base)
	
    OglDataObject() {}
    ~OglDataObject() {FreeOgl();}
    void FreeOgl();
    void Paint() override;
    void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) override {TODO}
    void Refresh(Mesh& m) override;
};

template <class T>
struct OglDataState : DataStateT<T> {
	using Base = DataStateT<T>;
	RTTI_DECL1(OglDataState, Base)
	
};

template <class T>
struct OglInputState : InputStateT<T> {
	using Base = InputStateT<T>;
	RTTI_DECL1(OglInputState, Base)
	
};

template <class T>
struct OglShaderState : ShaderStateT<T> {
	using Base = ShaderStateT<T>;
	RTTI_DECL1(OglShaderState, Base)
	
};


/*#define GFX_CLS(x, g, y) struct y##g##x : g##x<y##g##Gfx> {\
	using Base = g##x<y##g##Gfx>; \
	RTTI_DECL1(y##g##x, Base) \
};

GFX_CLS(ShaderState, Ogl, X11)
GFX_CLS(InputState, Ogl, X11)
#undef GFX_CLS*/


/*#define GFX_CLS(x, g, y) struct y##g##x : x##T<y##g##Gfx> {\
	using Base = x##T<y##g##Gfx>; \
	RTTI_DECL1(y##g##x, Base) \
};

GFX_CLS(Framebuffer, Ogl, X11)
#undef GFX_CLS*/



/*#ifdef flagSDL2
struct SdlOglRenderer : public RendererT<SdlOglGfx> {
	RTTI_DECL1(SdlOglRenderer, Base)
};
#endif

struct X11OglRenderer : public RendererT<X11OglGfx> {
	RTTI_DECL1(X11OglRenderer, Base)
};*/




/*struct OglFramebuffer : FramebufferT<OglGfx> {
	RTTI_DECL1(OglFramebuffer, Base)
	
	GLint GetGlType() const;
	GLint GetGlFormat() const;
	int GetGlSize() const;
	int GetGlSampleSize() const;
	
};
*/

/*template <class T>
struct OglShader : ShaderT<T>
{
	using Base = ShaderT<T>;
	RTTI_DECL1(OglShader, Base)
	
	OglShader() {}
	//OglShader(OglFramebuffer& s) {state = &s;}
	
};*/

/*template <class T>
struct OglShaderPipeline : ShaderPipelineT<T>
{
	using Base = ShaderPipelineT<T>;
	RTTI_DECL1(OglShaderPipeline, Base)
	
};

template <class T>
struct OglContextState : ContextStateT<T> {
	using Base = ContextStateT<T>;
	RTTI_DECL1(OglContextState, Base)
	
};

template <class T>
struct OglRuntimeState : RuntimeStateT<T> {
	using Base = RuntimeStateT<T>;
	RTTI_DECL1(OglRuntimeState, Base)
	
};*/

template <class T>
struct OglCompiler : CompilerT<T> {
	using Base = CompilerT<T>;
	using ContextState = ContextStateT<T>;
	using RuntimeState = RuntimeStateT<T>;
	using Framebuffer = FramebufferT<T>;
	using ShaderState = ShaderStateT<T>;
	
	RTTI_DECL1(OglCompiler, Base)
	
	OglCompiler();
	bool CompileShader(String code, GVar::ShaderType type, GLuint& shader_out);
	bool Compile(const ContextState& ctx, RuntimeState& rt_state, Framebuffer& fb_state, ShaderState& shd_state, GVar::ShaderType type);
	
	static void HotfixWebGLSL(String& s);
};

template <class T>
struct OglLinker : LinkerT<T> {
	using Base = LinkerT<T>;
	using RuntimeState = RuntimeStateT<T>;
	RTTI_DECL1(OglLinker, Base)
	
	bool Link(RuntimeState& rt_state);
	
};

/*template <class T>
struct OglBuffer : BufferT<T> {
	using Base = BufferT<T>;
	RTTI_DECL1(OglBuffer, Base)
	
	
};*/


NAMESPACE_PARALLEL_END

#endif
#endif
