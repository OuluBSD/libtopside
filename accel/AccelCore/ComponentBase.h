#ifndef _AccelCore_ComponentBase_h_
#define _AccelCore_ComponentBase_h_


NAMESPACE_TOPSIDE_BEGIN

#if HAVE_OPENGL
int GetOglChCode(int channels, bool is_float=false);
void Ogl_RemoveToken(String& glsl, String token);
#endif

ArrayMap<String,String>& CommonHashToName();


#define ACCEL_VAR_LIST \
	ACCEL_VAR(MOUSE,						"in_mouse") \
	ACCEL_VAR(AUDIOTIME,					"in_audio_seconds") \
	ACCEL_VAR(COMPAT_RESOLUTION,			"iResolution") \
	ACCEL_VAR(COMPAT_TIME,					"iTime") \
	ACCEL_VAR(COMPAT_TIMEDELTA,				"iTimeDelta") \
	ACCEL_VAR(COMPAT_FRAME,					"iFrame") \
	ACCEL_VAR(COMPAT_MOUSE,					"iMouse") \
	ACCEL_VAR(COMPAT_DATE,					"iDate") \
	ACCEL_VAR(COMPAT_SAMPLERATE,			"iSampleRate") \
	ACCEL_VAR(COMPAT_OFFSET,				"iOffset") \
	ACCEL_VAR(COMPAT_CHANNEL0,				"iChannel0") \
	ACCEL_VAR(COMPAT_CHANNEL1,				"iChannel1") \
	ACCEL_VAR(COMPAT_CHANNEL2,				"iChannel2") \
	ACCEL_VAR(COMPAT_CHANNEL3,				"iChannel3") \
	ACCEL_VAR(COMPAT_FRAMERATE,				"iFrameRate") \
	ACCEL_VAR(COMPAT_CHANNELTIME,			"iChannelTime") \
	ACCEL_VAR(COMPAT_CHANNELRESOLUTION0,	"iChannelResolution[0]") \
	ACCEL_VAR(COMPAT_CHANNELRESOLUTION1,	"iChannelResolution[1]") \
	ACCEL_VAR(COMPAT_CHANNELRESOLUTION2,	"iChannelResolution[2]") \
	ACCEL_VAR(COMPAT_CHANNELRESOLUTION3,	"iChannelResolution[3]")

class AccelComponent : public RefScopeEnabler<AccelComponent,Entity> {
	RTTI_DECL_R0(AccelComponent)
	COPY_PANIC(AccelComponent);
	
public:
	enum {
		#define ACCEL_VAR(v, n) VAR_##v,
		ACCEL_VAR_LIST
		#undef ACCEL_VAR
		VAR_COUNT
	};
	
	static const char* names[VAR_COUNT+1];
	static const int CHANNEL_COUNT = 4;
	
	// note: relative to GL_VERTEX_SHADER_BIT etc.
	enum {
		PROG_VERTEX,
		PROG_FRAGMENT,
		PROG_GEOMETRY,
		PROG_TESS_CONTROL,
		PROG_TESS_EVALUATION,
		
		PROG_COUNT
	};
	
	AccelComponentGroupRef			ctx;
	LinkedList<AcceleratorHeader>	in;
#if HAVE_OPENGL
	GLint							prog[PROG_COUNT] = {-1,-1,-1,-1,-1};
	GLuint							color_buf[2] = {0,0};
	GLuint							depth_buf[2] = {0,0};
	GLuint							frame_buf[2] = {0,0};
	GLint							var_idx[VAR_COUNT];
#endif
	String							name;
	String							description;
	String							code[PROG_COUNT];
	Size							fb_size = {0,0};
	int								id = -1;
	int								buf_i = 0;
	bool							is_doublebuf = false;
	bool							is_searched_vars = false;
	bool							is_open = false;
	bool							has_fbo = false;
	
	
	
public:
	
	
	AccelComponent();
	~AccelComponent();
	void				Update0(double dt);
	void				Clear();
	void				ClearTex();
	void				ClearProg();
	bool				Load(ObjectMap& st_map, int stage_i, String frag_code);
	int					NewWriteBuffer();
	bool				IsSinkInAccelerator() const;
    String				GetTypeString() const {return GetStringFromType(GetRTTI().GetTypeId());}
	bool				Open();
	void				Close();
	void				Initialize();
	void				Uninitialize();
	void				OnError(String fn, String msg);
	String				ToString() const {return GetTypeString() + " (id: " + IntStr(id) + ")";}
	bool				IsOpen() const {return is_open;}
	AccelStream*		Stream();
	bool				IsTypeTemporary() {return IsTypeTemporary(GetTypeId());}
	
	template <class Ctx> void UpdateTexBuffersT();
	template <class T> bool IsIn() {return IsContext(AsTypeCls<T>());}
	
	virtual bool		IsContext(TypeCls t) const = 0;
	virtual void		UpdateTexBuffers() = 0;
	virtual bool		IsEmptyStream() const = 0;
	virtual void		ClearStream() = 0;
	
	virtual void		PreProcess() {}
	virtual void		PostProcess() {}
	virtual void		Update(double dt) {}
	virtual bool		LoadResources() {return true;}
	virtual bool		RequiresShaderCode() const {return false;}
	virtual void		UseRenderedFramebuffer() {}
	virtual void		ClearData() {}
	virtual void		Reset() {}
	virtual bool		LoadAsInput(const AcceleratorHeader& in) {OnError("LoadAsInput", "not implemented"); return false;}
	virtual AccelComponentVideoStream* GetVideoStream() {return NULL;}
	virtual AccelComponentAudioStream* GetAudioStream() {return NULL;}
	
#if HAVE_OPENGL
	void				Ogl_SetVars(GLint prog, const AccelStream& stream);
	void				Ogl_SetVar(int var, GLint prog, const AccelStream& stream);
	void				Ogl_CreateTex(Size sz, int channels, bool create_depth, bool create_fbo, int filter, int repeat);
	void				Ogl_FindVariables(GLint prog);
	GLint				Ogl_GetInputTex(int input_i) const;
	int					Ogl_GetTexType(int input_i) const;
	bool				Ogl_CompilePrograms();
	bool				Ogl_CompileFragmentShader();
	bool				Ogl_LinkStages();
	bool				Ogl_CompileProgram(int prog_i, String shader_source);
	GLint				Ogl_CompileShader(int prog_i, String shader_source);
	bool				Ogl_LinkProgram(int prog_i);
	bool				Ogl_CheckInputTextures();
	GLint				Ogl_GetOutputTexture(bool reading_self) const;
	void				Ogl_TexFlags(int type, int filter, int repeat);
	void				Ogl_ClearTex();
	void				Ogl_ClearProg();
	void				Ogl_UpdateTex(Size sz, const Vector<byte>& data);
	GLuint				Ogl_GetTex() const {return color_buf[buf_i];}
#endif
	
	static String		GetStringFromType(TypeCls type);
	static TypeCls		GetTypeFromString(String typestr);
	static bool			IsTypeTemporary(TypeCls type);
	
};

using AccelComponentRef				= Ref<AccelComponent,				RefParent1<Entity>>;








template <class Ctx> void AccelComponent::UpdateTexBuffersT() {
	auto* stream = Stream();
	if (stream) {
		fb_size.Clear();
		auto& state = stream->template Get<Ctx>();
		ASSERT(state.fmt.IsValid());
		ClearTex();
		TimeSeriesBase* ts = CastPtr<TimeSeriesBase>(&state.fmt);
		DimBase<1>* base1 = CastPtr<DimBase<1>>(&state.fmt);
		DimBase<2>* base2 = CastPtr<DimBase<2>>(&state.fmt);
		if (ts) {
			if (base1) {
				int sr = max(ts->sample_rate, 1);
				int ch = max(base1->channels, 1);
				fb_size = Size(sr, 1);
	#if HAVE_OPENGL
				Ogl_CreateTex(
					fb_size, ch,
					0, has_fbo,
					AcceleratorHeader::FILTER_LINEAR,
					AcceleratorHeader::WRAP_CLAMP);
	#endif
			}
			else if (base2) {
				fb_size = base2->size;
	#if HAVE_OPENGL
				Ogl_CreateTex(
					fb_size, 4,
					1, has_fbo,
					AcceleratorHeader::FILTER_LINEAR,
					AcceleratorHeader::WRAP_CLAMP);
	#endif
			}
			else {TODO}
		}
		else {TODO}
	}
	else {ASSERT_(false, "no stream");}
}

NAMESPACE_TOPSIDE_END


#endif
