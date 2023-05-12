#ifndef _IGraphics_GfxClasses_h_
#define _IGraphics_GfxClasses_h_

NAMESPACE_PARALLEL_BEGIN




////////////// STATE

struct GfxDataState;


struct GfxDataObject : GfxMesh {
	RTTI_DECL1(GfxDataObject, GfxMesh)
	
	virtual ~GfxDataObject() {}
	
    virtual void MakeTexture(int tex_id, int w, int h, int pitch, int stride, const Vector<byte>& data) = 0;
    virtual void Refresh(Mesh& m) = 0;
    virtual GVar::GfxType GetGfxType() const = 0;
	virtual void RefreshTexture(Mesh& m) = 0;
	
	bool is_visible = true;
    mat4 view_override;
    mat4 proj_override;
    mat4 scale;
    mat4 model;
    vec4 color;
    int id = -1;
    bool use_quad = false;
    
	
	void Set(const mat4& model, const mat4& scale) {this->model = model; this->scale = scale;}
	bool IsSoftware() const {return GetGfxType() == GVar::SW;}
	bool IsOpenGL() const {return GetGfxType() == GVar::OGL;}
	
};

struct GfxMaterial : RTTIBase {
	RTTI_DECL0(GfxMaterial)
	
	int		id = -1;
	
	int tex_id[TEXTYPE_COUNT] = {-1,-1,-1,-1,-1,-1, -1,-1,-1,-1,-1,-1,-1};
	GVar::Filter tex_filter[TEXTYPE_COUNT];
	
};

struct GfxModelState : ErrorReporter {
	RTTI_DECL1(GfxModelState, ErrorReporter)
	
	// meta
	hash_t id = -1;
	int env_material = -1; // own material
	hash_t env_material_model = 0; // other model in same DataState
	
	virtual GfxDataObject& CreateObject() = 0;
	virtual int GetObjectCount() const = 0;
	virtual GfxDataObject& GetObject(int i) = 0;
	virtual void Refresh(Model& m) = 0;
	virtual void Clear() = 0;
	virtual bool LoadModel(ModelLoader& l) = 0;
	virtual bool LoadModel(Model& m) = 0;
	virtual bool LoadModelTextures(Model& m) = 0;
	virtual int GetMaterialKey(int i) const = 0;
	virtual bool SetProgram(String name) = 0;
	
};

struct GfxDataState : ErrorReporter {
	RTTI_DECL1(GfxDataState, ErrorReporter)
	
	// meta
	int		id = -1;
	
	// models
	hash_t		env_material_model = 0;
	
	// renderer
    mat4				view;
    mat4				view_stereo[2];
    vec3				light_dir;
    vec3				camera_pos;
    vec3				camera_dir;
    bool				is_stereo = false;
    bool				user_view = false;
    bool				dbg_render = false;
    
	// target framebuffer
	vec2				resolution;
	vec2				offset;
	
	// generic
	Machine* mach = 0;
	
	GfxDataState();
	virtual GfxModelState& AddModel() = 0;
	virtual GfxModelState& GetModel(hash_t h) = 0;
	virtual GfxModelState& RealizeModel(hash_t link) = 0;
	virtual int GetModelCount() const = 0;
	
};


////////////// FRAMEBUFFER



struct GfxInputState : ErrorReporter {
	RTTI_DECL1(GfxInputState, ErrorReporter)
	
	using InputType = GVar::InputType;
	
	virtual ~GfxInputState() {}
	
	int id = -1;
	InputType type;
	bool is_loopback = false;
	
	void Clear() {id = -1; type = GVar::InputType::INVALID;}
	
	String GetSamplerString() const;
	
};


struct GfxRenderer;

struct GfxFramebuffer : ErrorReporter {
	using Sample = GVar::Sample;
	using Filter = GVar::Filter;
	using Wrap = GVar::Wrap;
	
	// stage
	bool	is_win_fbo = 0;
	bool	is_read_fb_output = 0;
	bool	is_audio = 0;
	bool	is_cubemap = 0;
	bool	is_affine = 0;
	Filter	filter;
	Wrap	wrap;
	
	// framebuffer
	int8	channels = 0;
	Size	size;
	int		depth = 0;
	Sample	sample = GVar::SAMPLE_FLOAT;
	Point	offset;
	bool	is_doublebuf = 0;
	bool	is_stereo_lenses = 0;
	bool	is_stereo_left = 0;
	bool	is_stereo_right = 0;
	int		pitch = 0;
	int8	buf_i = 0;
	double	fps = 0;
	
	
	
	RTTI_DECL1(GfxFramebuffer, ErrorReporter)
	GfxFramebuffer() : size(0,0) {}
	virtual ~GfxFramebuffer() {}
	
	virtual bool Create(int w, int h, int channels=3) = 0;
	virtual void Enter() = 0;
	virtual void Leave() = 0;
	virtual byte* GetIterator(int x, int y) = 0;
	virtual void DrawFill(const byte* mem, int sz, int pitch) = 0;
	
	int GetWidth() const {return size.cx;}
	int GetHeight() const {return size.cy;}
	int GetStride() const {return channels * GVar::GetSampleSize(sample);}
	int GetSampleSize() const {return GVar::GetSampleSize(sample);}
	int GetPitch() const {return pitch;}
	Size GetSize() const {return size;}
	
};




////////////// RUNTIME




struct GfxShader;

struct GfxShader : RTTIBase {
	
protected:
	Vector<mat4> stack;
	bool is_loaded = false;
	
	
public:
	RTTI_DECL0(GfxShader)
	
	virtual ~GfxShader() {}
	
	void PushMultiplyMat4(String key, const mat4& mat);
	void PopMat4();
	void SetStackMat4(const mat4& mat);
	
	virtual GfxDataObject* CreateObject() = 0;
	
};

struct GfxProgramState : ErrorReporter {
	RTTI_DECL1(GfxProgramState, ErrorReporter)
	
	int		id = -1;
	bool	pending_compilation = false;
	
};

struct GfxPipelineState : RTTIBase {
	RTTI_DECL0(GfxPipelineState)
	GfxPipelineState() {}
	virtual ~GfxPipelineState() {}
	
	
};

struct GfxCompilerArgs {
	bool is_audio = false;
	bool is_affine = false;
};
	
struct GfxCompiler : ErrorReporter {
	RTTI_DECL1(GfxCompiler, ErrorReporter)
	
	virtual ~GfxCompiler() {}
	
};

struct GfxLinker : ErrorReporter {
	RTTI_DECL1(GfxLinker, ErrorReporter)
	
	virtual ~GfxLinker() {}
	
};

struct GfxBuffer : ErrorReporter {
	RTTI_DECL1(GfxBuffer, ErrorReporter)
	
	// For compatibility
	void BaseUpdateTexBuffers(GfxFramebuffer&) {}
	
};

struct GfxBufferStage : ErrorReporter {
	RTTI_DECL1(GfxBufferStage, ErrorReporter)
	
};






////////////// CONTEXT




struct GfxContextState : RTTIBase {
	RTTI_DECL0(GfxContextState)
	
	virtual ~GfxContextState() {}
	
	// meta
	String	name;
	String	description;
	
	// context values
	double	time_total = 0;
	double	frame_time = 0;
	double	block_offset = 0;
	int		frames = 0;
	double	time_us = 0;
	double	sample_rate = 0;
	Time	time;
	
	
};

struct GfxRenderer : RTTIBase {
	
protected:
	Size output_sz = Size(0,0);
	
	
public:
	RTTI_DECL0(GfxRenderer)
	GfxRenderer() {}
	virtual ~GfxRenderer() {}
	
	virtual GfxFramebuffer& GetOutputFramebuffer() = 0;
	virtual void PreFrame() = 0;
	virtual void PostFrame() = 0;
	
	virtual void SetSize(Size sz) {output_sz = sz;}
	
	Size GetSize() const {return output_sz;}
	
	
};




////////////// UTILS




struct GfxStateDraw : Draw2 {
	RTTI_DECL1(GfxStateDraw, Draw)
	
	virtual GfxDataState& GetGfxState() = 0;
	virtual bool HasTarget() const = 0;
	virtual GfxDataState& GetState() = 0;
	
};












#ifdef flagOGL
struct OglFramebufferBase : GfxFramebuffer{
	int gl_sample_size;
	GLint gl_type;
	
	GLint GetGlType() const;
	GLint GetGlFormat() const;
	int GetGlSize() const;
	int GetGlSampleSize() const;
	
};

struct OglBufferBase : GfxBuffer {
	GLuint fb_accel_type;
	GLuint fb_size_bytes;
	GLuint fb_accel_size_bytes;
	GLint fb_fmt;
	GLuint fb_accel_fmt;
	
	GVar::Sample fb_accel_sampletype = GVar::SAMPLE_U8;
	GLuint fb_accel_channels = 4;
	int fb_sample_size = 0;
	
	
	void BaseUpdateTexBuffers(OglFramebufferBase& fb) ;
	
};
#endif










#ifdef flagDX11
struct Dx11FramebufferBase : GfxFramebuffer{
	/*int gl_sample_size;
	GLint gl_type;
	
	GLint GetGlType() const;
	GLint GetGlFormat() const;
	int GetGlSize() const;
	int GetGlSampleSize() const;*/
	
};

struct Dx11BufferBase : GfxBuffer {
	/*GLuint fb_accel_type;
	GLuint fb_size_bytes;
	GLuint fb_accel_size_bytes;
	GLint fb_fmt;
	GLuint fb_accel_fmt;
	
	GVar::Sample fb_accel_sampletype = GVar::SAMPLE_U8;
	GLuint fb_accel_channels = 4;
	int fb_sample_size = 0;
	
	
	void BaseUpdateTexBuffers(OglFramebufferBase& fb) ;
	*/
};
#endif






//////// PBR

struct PbrResources : RTTIBase {
	RTTI_DECL0(PbrResources)
	
	
	virtual void SetLight(const vec4& direction, const vec4& diffuse_color) = 0;
	
	
};


NAMESPACE_PARALLEL_END

#endif
