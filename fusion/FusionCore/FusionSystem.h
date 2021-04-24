#ifndef _FusionCore_FusionSystem_h_
#define _FusionCore_FusionSystem_h_

NAMESPACE_OULU_BEGIN

// Graphics Debug Log
#undef DLOG
#ifdef flagVERBOSE_SHADERCORE
	#define DLOG(x) LOG(x)
#else
	#define DLOG(x)
#endif


class FusionContextComponent;


int GetOglChCode(int channels, bool is_float=false);
ArrayMap<String,String>& CommonHashToName();

struct BasicFusionStream : public VolatileStream {
	Size sz;
	int depth = 0;
	
	void Clear() {sz = Size(0,0); depth = 0;}
	double GetSeconds() const override {return 0;}
	Size GetVideoSize() const override {return sz;}
	int  GetVideoDepth() const override {return depth;}
};

struct FusionStream : public VolatileStream {
	
	// Generic
	String name, description;
	Time time;
	TimeStop total_time;
	double frame_seconds = 0;
	int time_us = 0;
	
	// Controller
	Point mouse, mouse_toycompat_drag, mouse_toycompat_click;
	
	// Video
	SystemDraw* draw = 0;
	Size video_size;
	Point video_offset;
	TimeStop vframe_time;
	double vtotal_seconds = 0;
	int vframes = 0;
	double fps_limit = 60;
	
	// Audio
	
	Sound* sys_snd = 0;
	//TimeStop aframe_time;
	//double audio_sync_ival = 1.0f;
	double atotal_seconds = 0;
	double audio_last_sync_sec = 0;
	/*int audio_sample_freq = 44100;
	int audio_sample_rate = 512;
	int audio_sample_size = 4;
	int audio_sample_channels = 2;*/
	SoundFormat snd_fmt;
	int aframes_after_sync = 0;
	int asink_frame = 0;
	bool is_audio_sync;
	
	
	FusionStream() {Clear();}
	void Clear() {
		name.Clear();
		description.Clear();
		time = Time(2020,1,1);
		total_time.Reset();
		frame_seconds = 0;
		time_us = 0;
		
		mouse = Point(0,0);
		mouse_toycompat_drag = Point(0,0);
		mouse_toycompat_click = Point(0,0);
		
		draw = 0;
		video_size = Size(640,480);
		video_offset = Point(0,0);
		mouse = Point(0,0);
		vframe_time.Reset();
		vtotal_seconds = 0;
		vframes = 0;
		fps_limit = 60;
		
		//sys_snd = 0;
		//aframe_time.Reset();
		//audio_sync_ival = 1.0f;
		atotal_seconds = 0;
		audio_last_sync_sec = 0;
		/*audio_sample_freq = 0;
		audio_sample_rate = 0;
		audio_sample_size = 0;
		audio_sample_channels = 0;*/
		snd_fmt = SoundFormat();
		aframes_after_sync = 0;
		asink_frame = 0;
		is_audio_sync = false;
	}
	double GetSeconds() const override {return vtotal_seconds;}
	Size GetVideoSize() const override {return video_size;}
};



class FusionComponentInput {
	
public:
	enum {
		FILTER_NEAREST,
		FILTER_LINEAR,
		FILTER_MIPMAP,
		
		DEFAULT_FILTER = FILTER_LINEAR
	};
	
	enum {
		WRAP_CLAMP,
		WRAP_REPEAT,
		
		DEFAULT_WRAP = WRAP_REPEAT
	};
	
	typedef enum {
		INVALID = -1,
		EMPTY,
		BUFFER,
		KEYBOARD,
		TEXTURE,
		CUBEMAP,
		WEBCAM,
		MUSIC,
		MUSICSTREAM,
		VOLUME,
		VIDEO,
	} Type;
	
	Type				GetType() const {return type;}
	String				GetTypeString() const {return GetStringFromType(type);}
	String				GetFilterString() const {return GetStringFromFilter(filter);}
	String				GetWrapString() const {return GetStringFromWrap(wrap);}
	bool				IsTypeComponentSource() {return IsTypeComponentSource(type);}
	String				GetFilepath() const {return filepath;}
	String				ToString() const {return GetTypeString();}
	bool				IsEqualHeader(const FusionComponentInput& in) const;
	void				SetHeader(const FusionComponentInput& in);
	bool				IsVertFlip() const {return vflip;}
	int					GetFilter() const {return filter;}
	int					GetWrap() const {return wrap;}
	bool				IsTypeEmpty() const {return type == EMPTY;}
	
	static String		GetStringFromType(Type i);
	static String		GetStringFromFilter(int i);
	static String		GetStringFromWrap(int i);
	static Type			GetTypeFromString(String typestr);
	static int			GetFilterFromString(String s);
	static int			GetWrapFromString(String s);
	static bool			IsTypeComponentSource(Type i);
	
protected:
	friend class FusionComponent;
	friend class FusionContextComponent;
	friend struct FusionComponentInputVector;
	
	const VolatileStream* stream = 0;
	String filepath;
	int id = -1;
	Type type = INVALID;
	int wrap = WRAP_REPEAT;
	int filter = FILTER_LINEAR;
	bool vflip = 0;
	
	
};

struct FusionComponentInputVector {
	Array<FusionComponentInput> in;
	
	int Find(const FusionComponentInput& a) const;
	void Add(const FusionComponentInput& a);
};

class FusionComponent {
	
protected:
	// Stage
	
	
	enum {
		VAR_MOUSE,
		VAR_AUDIOTIME,
		
		VAR_COMPAT_RESOLUTION,
		VAR_COMPAT_TIME,
		VAR_COMPAT_TIMEDELTA,
		VAR_COMPAT_FRAME,
		VAR_COMPAT_MOUSE,
		VAR_COMPAT_DATE,
		VAR_COMPAT_SAMPLERATE,
		VAR_COMPAT_OFFSET,
		VAR_COMPAT_CHANNEL0,
		VAR_COMPAT_CHANNEL1,
		VAR_COMPAT_CHANNEL2,
		VAR_COMPAT_CHANNEL3,
		VAR_COMPAT_FRAMERATE,
		VAR_COMPAT_CHANNELTIME,
		VAR_COMPAT_CHANNELRESOLUTION0,
		VAR_COMPAT_CHANNELRESOLUTION1,
		VAR_COMPAT_CHANNELRESOLUTION2,
		VAR_COMPAT_CHANNELRESOLUTION3,
		
		VAR_COUNT,
	};
	static const char** VarNames() {
		static const char* names[VAR_COUNT+1] = {
			"in_mouse",
			"in_audio_seconds",
			"iResolution",
			"iTime",
			"iTimeDelta",
			"iFrame",
			"iMouse",
			"iDate",
			"iSampleRate",
			"iOffset",
			"iChannel0",
			"iChannel1",
			"iChannel2",
			"iChannel3",
			"iFrameRate",
			"iChannelTime",
			"iChannelResolution[0]",
			"iChannelResolution[1]",
			"iChannelResolution[2]",
			"iChannelResolution[3]",
			0
		};
		return names;
	}
	
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
	
	Array<FusionComponentInput>	in;
#ifdef flagOPENGL
	GLint						prog[PROG_COUNT] = {-1,-1,-1,-1,-1};
	GLuint						color_buf[2] = {0,0};
	GLuint						depth_buf[2] = {0,0};
	GLuint						frame_buf[2] = {0,0};
	GLint						var_idx[VAR_COUNT];
#endif
	String						name;
	String						description;
	String						code[PROG_COUNT];
	int							id = -1;
	int							buf_i = 0;
	bool						is_doublebuf = false;
	bool						is_searched_vars = false;
	

	
	
	virtual void		Update(float dt) {}
	
protected:
	
	friend class FusionSystem;
	
	void				Update0(float dt);
	
	
protected:
	// Context - Component Interaction
	
	friend class FusionContextComponent;
	
	
	FusionContextComponent* ctx = 0;
	
	
	virtual void		Reset() = 0;
	virtual void		PreProcess() = 0;
	virtual void		PostProcess() {}
	virtual void		UpdateTexBuffers() {}
	virtual void		Event(const CtrlEvent& e) {}
	virtual bool		LoadResources() {return true;}
	virtual bool		RequiresShaderCode() const {return false;}
	virtual void		ClearData() {}
	virtual void		UseRenderedFramebuffer() {}
	virtual bool		LoadAsInput(const FusionComponentInput& in) {OnError("LoadAsInput", "not implemented"); return false;}
	
	bool				Open();
	void				Close();
	void				Initialize();
	void				Uninitialize();
	int					NewWriteBuffer();
	int					GetId() const {return id;}
	void				Clear();
	void				ClearTex();
	void				ClearProg();
	bool				Load(ObjectMap& st_map, int stage_i, String frag_code);
	void				OnError(String fn, String msg);
	
#ifdef flagOPENGL
	void				Ogl_SetVars(GLint prog, const FusionStream& stream);
	void				Ogl_SetVar(int var, GLint prog, const FusionStream& stream);
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
	GLuint				Ogl_GetTex() const {return color_buf[buf_i];}
#endif

public:
	
	typedef enum {
		FUSION_INVALID,
		
		FUSION_CTRL_BUFFER,
		FUSION_DISPLAY_BUFFER,
		FUSION_AUDIO_BUFFER,
		FUSION_DATA_SINK,
		FUSION_MEDIA_SINK,
		// End of temporary types
		
		// Begin of persistent types (which context can't remove)
		FUSION_CTRL_SOURCE,
		FUSION_CTRL_SINK,
		
		FUSION_DISPLAY_SOURCE,
		FUSION_DISPLAY_SINK,
		
		FUSION_AUDIO_SOURCE,
		FUSION_AUDIO_SINK,
		
		FUSION_TYPE_COUNT,
		
		
		FUSION_PERSISTENT_BEGIN = FUSION_CTRL_SOURCE
	} Type;
	
	bool			IsTypeTemporary() const {return (int)type < (int)FUSION_PERSISTENT_BEGIN;}
	
	bool			IsOpen() const {return is_open;}
	FusionStream*	Stream();
    String			GetTypeString() const {return GetStringFromType(type);}
	String			ToString() const {return GetTypeString() + " (id: " + IntStr(id) + ")";}
	Type			GetType() const {return type;}
	
	virtual ComponentBase&	GetECS() = 0;
	
	static String	GetStringFromType(Type type);
	static String	GetDescriptionFromType(Type type);
	static String	GetStringFromInputType(int i);
	static Type		GetTypeFromString(String typestr);
	static bool		IsTypeTemporary(Type type) {return (int)type < (int)FUSION_PERSISTENT_BEGIN;}
	
	FusionComponent(Type fusion_type) : type(fusion_type) {}
	
private:
	Type type = FUSION_INVALID;
	bool is_open = false;
	
};


class FusionDataSink :
	public Component<FusionDataSink>,
	public FusionComponent,
	public StaticSink,
	public FusionSource
{
	
	void			Reset() override;
	void			PreProcess() override;
	void			ClearData() override;
	void			UpdateTexBuffers() override;
	void			Event(const CtrlEvent& e) override;
	bool			LoadResources() override;
	ComponentBase&	GetECS() override {return *this;}
	const FusionComponentInput& GetHeader() const override {return cfg;}
	void RecvStatic(const StaticSinkData& data) override;
	
#ifdef flagOPENGL
	void Ogl_RecvStatic(const StaticSinkData& data);
#endif
	
	FusionComponentInput cfg;
	BasicFusionStream stream;
	
public:
	COPY_PANIC(FusionDataSink);
	IFACE_CB(StaticSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	FusionDataSink() : FusionComponent(FUSION_DATA_SINK) {StaticSink::SetMultiConnection(false);}
	
	
	void			Initialize() override;
	void			Uninitialize() override;
	bool			LoadAsInput(const FusionComponentInput& in) override;
	
	VolatileStream*	GetVolatileStream() {return &stream;}
	
	static bool AllowDuplicates() {return true;} // override ComponentBase
	
};



class FusionMediaSink :
	public Component<FusionMediaSink>,
	public FusionComponent,
	public MediaSink,
	public FusionSource
{
	void			Reset() override;
	void			PreProcess() override;
	void			PostProcess() override;
	void			ClearData() override;
	void			UpdateTexBuffers() override;
	void			Event(const CtrlEvent& e) override;
	bool			LoadResources() override;
	ComponentBase&	GetECS() override {return *this;}
	const FusionComponentInput& GetHeader() const override {return cfg;}
	
	FusionComponentInput cfg;
	MediaFormat fmt;
	BasicFusionStream stream;
	
public:
	COPY_PANIC(FusionMediaSink);
	IFACE_CB(MediaSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	FusionMediaSink() : FusionComponent(FUSION_MEDIA_SINK) {}
	
	void			Initialize() override;
	void			Uninitialize() override;
	bool			LoadAsInput(const FusionComponentInput& in) override;
	void			RecvMedia(Media& media) override;
	VolatileStream*	GetVolatileStream() {return &stream;}
	
	static bool AllowDuplicates() {return true;} // override ComponentBase
	
};



class FusionControllerSink :
	public Component<FusionControllerSink>,
	public FusionComponent,
	public ControllerSink,
	public FusionSource
{
	//ArrayMap<int, FusionDataBuffer> data_bufs;
	bool is_left_down = false;
	
	void			Reset() override;
	void			PreProcess() override;
	void			ClearData() override;
	void			UpdateTexBuffers() override;
	void			Event(const CtrlEvent& e) override;
	bool			LoadResources() override;
	ComponentBase&	GetECS() override {return *this;}
	const FusionComponentInput& GetHeader() const override {return cfg;}
	
	FusionComponentInput cfg;
	BasicFusionStream stream;
	Vector<byte> data;
	Size data_res;
	bool changed = false;
	
public:
	COPY_PANIC(FusionControllerSink);
	IFACE_CB(ControllerSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	FusionControllerSink() : FusionComponent(FUSION_CTRL_SINK) {}
	
	
	void			Initialize() override;
	void			Uninitialize() override;
	bool			LoadAsInput(const FusionComponentInput& in) override;
	void			RecvController(const EventFrame& e) override;
	VolatileStream*	GetVolatileStream() {return &stream;}
	
	void			LeftDown(Point p, dword keyflags);
	void			LeftUp(Point p, dword keyflags);
	void			MouseMove(Point p, dword keyflags);
	bool			Key(dword key, int count);
	
	enum {
		CTRL_IN_KEYBOARD,
		CTRL_IN_MIDI,
	};
	
	static const int key_tex_w = 256;
	static const int key_tex_h = 256;
	
};



class FusionDisplaySource :
	public Component<FusionDisplaySource>,
	public FusionComponent,
	public DisplaySource,
	public FusionSink
{
	void			Reset() override;
	void			PreProcess() override;
	void			PostProcess() override;
	void			UpdateTexBuffers() override;
	void			Event(const CtrlEvent& e) override;
	bool			LoadResources() override;
	void			EmitDisplaySource(float dt) override;
	bool			Render(const DisplaySinkConfig& config, SystemDraw& draw) override;
	bool			Link(DisplaySink& sink) override;
	ComponentBase&	GetECS() override {return *this;}
	bool			RequiresShaderCode() const override {return true;}
	//FusionVideoInput*	FindVideoInput(String path);
	
	
public:
	COPY_PANIC(FusionDisplaySource);
	IFACE_CB(DisplaySource);
	IFACE_CB(FusionSink);
	IFACE_GENERIC;
	
	FusionDisplaySource() : FusionComponent(FUSION_DISPLAY_SOURCE) {}
	
	
	void			Initialize() override;
	void			Uninitialize() override;
	
	void			SetVideoSize(Size sz);
	void			SetFPS(int fps);
	
};



class FusionDisplayBuffer :
	public Component<FusionDisplayBuffer>,
	public FusionComponent,
	public FusionSink,
	public FusionSource
{
	void			Reset() override;
	void			PreProcess() override;
	void			PostProcess() override;
	void			UpdateTexBuffers() override;
	void			Event(const CtrlEvent& e) override;
	bool			LoadResources() override;
	ComponentBase&	GetECS() override {return *this;}
	//void			EmitDisplaySource(float dt) override;
	//bool			Render(const DisplaySinkConfig& config, SystemDraw& draw) override;
	//bool			Link(DisplaySink& sink) override;
	//FusionVideoInput* FindVideoInput(String path);
	const FusionComponentInput& GetHeader() const override {return cfg;}
	bool			RequiresShaderCode() const override {return true;}
	
	FusionComponentInput cfg;
	
	
public:
	COPY_PANIC(FusionDisplayBuffer);
	IFACE_CB(FusionSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	FusionDisplayBuffer() : FusionComponent(FUSION_DISPLAY_BUFFER) {}
	
	void			Initialize() override;
	void			Uninitialize() override;
	
	//void SetVideoSize(Size sz);
	//void SetFPS(int fps);
	
	static bool AllowDuplicates() {return true;} // override ComponentBase
	
};



class FusionAudioSource :
	public Component<FusionAudioSource>,
	public FusionComponent,
	public AudioSource,
	public FusionSink
{
	Vector<float> sound_buf;
	
	void			Reset() override;
	void			PreProcess() override;
	void			PostProcess() override;
	void			UpdateTexBuffers() override;
	bool			LoadResources() override;
	void			EmitAudioSource(float dt) override;
	void			Play(const AudioSinkConfig& config, Sound& snd) override;
	void			UseRenderedFramebuffer() override;
	ComponentBase&	GetECS() override {return *this;}
	
public:
	COPY_PANIC(FusionAudioSource);
	IFACE_CB(AudioSource);
	IFACE_CB(FusionSink);
	IFACE_GENERIC;
	
	FusionAudioSource() : FusionComponent(FUSION_AUDIO_SOURCE) {}
	
	
	void			Initialize() override;
	void			Uninitialize() override;
	
};



class FusionAudioBuffer :
	public Component<FusionAudioBuffer>,
	public FusionComponent,
	public FusionSink,
	public FusionSource
{
	Vector<float> sound_buf;
	
	void			Reset() override;
	void			PreProcess() override;
	void			PostProcess() override;
	void			UpdateTexBuffers() override;
	bool			LoadResources() override;
	ComponentBase&	GetECS() override {return *this;}
	//void UseRenderedFramebuffer(Stage& s) override;
	const FusionComponentInput& GetHeader() const override {return cfg;}
	bool			RequiresShaderCode() const override {return true;}
	
	FusionComponentInput cfg;
	
public:
	COPY_PANIC(FusionAudioBuffer);
	IFACE_CB(FusionSink);
	IFACE_CB(FusionSource);
	IFACE_GENERIC;
	
	FusionAudioBuffer() : FusionComponent(FUSION_AUDIO_BUFFER) {}
	
	void			Initialize() override;
	void			Uninitialize() override;
	
	static bool AllowDuplicates() {return true;} // override ComponentBase
	
};



class FusionContextComponent :
	public Component<FusionContextComponent>
{
	static int id_counter;
	
protected:
	friend class FusionDisplaySource;
	
	bool		Render();
	
	
protected:
	friend class FusionAudioSource;
	
	void		Play();
	
	
protected:
	friend class FusionComponent;
	
	typedef enum {
		MODE_DEFAULT,
		MODE_AUDIO,
	} Mode;
	
	Vector<FusionComponent*> comps;
	Vector<String> common_source;
	Vector<uint32> gl_stages;
	String last_error;
	Object post_load;
	
	// Generic
	FusionStream stream;
	bool is_open = false;
	
	
	void				Clear();
	void				RefreshStageQueue();
	void				RefreshPipeline();
	void				RemoveComponent(FusionComponent* s) {VectorRemoveKey(comps, s);}
	void				ProcessStageQueue(Mode m);
	bool				IsModeStage(const FusionComponent& comp, Mode m) const;
	void				RefreshStreamValues(Mode m);
	FusionComponent&	GetComponentById(int id) const;
	void				FindComponents();
	bool				LoadFileAny(String path, Object& dst);
	bool				LoadFileToy(String path, Object& dst);
	void				Reset();
	void				OnError(FusionComponent::Type type, String fn, String msg);
	void				OnError(String fn, String msg);
	void				MakeUniqueIds(Object& v);
	int					MakeUniqueId(VectorMap<int,int>& ids, int orig_id);
	bool				Load(Object v);
	void				UpdateTexBuffers();
	void				UpdateSoundBuffers();
	bool				CheckInputTextures();
	void				Close();
	bool				CreateComponents(FusionComponentInputVector& v);
	bool				ConnectComponents();
	
#ifdef flagOPENGL
	void				Ogl_ProcessStage(FusionComponent& s, GLuint gl_stage);
	void				Ogl_ClearPipeline();
	void				Ogl_CreatePipeline();
#endif
	
	template <class T> FusionComponent* AddEntityComponent() {
		T* o = GetEntity().Add<T>();
		o->ctx = this;
		return o;
	}
	template <class T> bool AddEntityFusionComponent(FusionComponentInput& in) {
		T* o = GetEntity().Add<T>();
		if (!o)
			return false;
		o->ctx = this;
		if (!o->LoadAsInput(in)) {
			o->Destroy();
			return false;
		}
		o->ctx = this;
		o->id = ++id_counter;
		in.id = o->id;
		in.stream = o->GetVolatileStream();
		comps.Add(o);
		return true;
	}
	
	
public:
	COPY_PANIC(FusionContextComponent);
	
	FusionContextComponent();
	
	void		Initialize() override;
	void		Uninitialize() override;
	
    void		Update(float dt);
	String		GetLastError() const {return last_error;}
	void		PostLoadFileAny(String path);
	void		DumpEntityComponents();
	
	//void Event(const CtrlEvent& e);
	
	Callback WhenError;
	
};



struct CompleteFusion :
	EntityPrefab<
		FusionDisplaySource,
		FusionAudioSource,
		FusionContextComponent,
		Connector
> {
    static ComponentMap Make(ComponentStore& store)
    {
        auto components = EntityPrefab::Make(store);
		return components;
    }
};





class FusionSystem : public System<FusionSystem> {
	Vector<FusionContextComponent*> ctxs;
	Vector<FusionComponent*> comps;
	
public:
	FusionSystem(Machine& m);
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(float dt) override;
    void Stop() override;
    void Uninitialize() override;
    
protected:
	friend class FusionContextComponent;
	friend class FusionComponent;
	
    void AddContext(FusionContextComponent& ctx);
    void RemoveContext(FusionContextComponent& ctx);
    void AddComponent(FusionComponent& comp);
    void RemoveComponent(FusionComponent& comp);
    void UpdateTexBuffers();
    
};

NAMESPACE_OULU_END

#endif
