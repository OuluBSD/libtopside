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
	int								id = -1;
	int								buf_i = 0;
	bool							is_doublebuf = false;
	bool							is_searched_vars = false;
	bool							is_open = false;
	
	
	
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
	
	template <class T> bool IsIn() {return IsContext(AsTypeCls<T>());}
	
	virtual bool		IsContext(TypeCls t) const = 0;
	virtual void		UpdateTexBuffers() = 0;
	
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



class AccelComponentGroup : public RefScopeEnabler<AccelComponentGroup,AccelContextComponent> {
	RTTI_DECL_R0(AccelComponentGroup)
	COPY_PANIC(AccelComponentGroup);
	
public:
	LinkedList<AccelComponentRef> comps;
	Vector<uint32> gl_stages;
	
	LinkedList<TypeCls> group_classes;
	AccelStream stream;
	
public:
	
	
	AccelComponentGroup();
	bool				Open();
	void				Clear();
	void				Reset();
	void				Process();
	void				Close();
	void				CloseTemporary();
	void				FindComponents();
	AccelComponentRef	GetComponentById(int id) const;
	void				Add(AccelComponentRef r) {comps.FindAdd(r);}
	void				Remove(AccelComponentRef r) {comps.RemoveKey(r);}
	void				FindUniqueInputs(AcceleratorHeaderVector& v);
	bool				LoadExisting(TypeCls type, ObjectMap& st_map, int stage_i, String frag_code);
	void				ConnectInputs(AcceleratorHeaderVector& v);
	void				UpdateBuffers();
	bool				CheckInputTextures();
	void				RefreshStreamValues();
	bool				IsLast(const AccelComponent* comp) const;
	
	template <class T> void AddContext() {group_classes.FindAdd(AsTypeCls<T>());}
	template <class T> bool HasContext() const {return HasContext(AsTypeCls<T>());}
	bool HasContext(TypeCls type) const {return group_classes.Find(type) != 0;}
	
#if HAVE_OPENGL
	void				Ogl_ProcessStage(AccelComponentRef s, GLuint gl_stage);
	void				Ogl_ClearPipeline();
	void				Ogl_CreatePipeline();
#endif
	
};




NAMESPACE_TOPSIDE_END


#endif
