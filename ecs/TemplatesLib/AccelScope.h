#ifndef _TemplatesLib_DevClasses_h_
#define _TemplatesLib_DevClasses_h_

NAMESPACE_TOPSIDE_BEGIN



#define DEV(x) \
	struct x##ComponentGroupBase : RTTIBase { \
		RTTI_DECL0(x##ComponentGroupBase) \
		void RefreshPipeline() {} \
		void UpdateBuffers() {} \
		virtual bool				IsValSpec(TypeCls t) const = 0; \
		virtual x##StreamState&		GetStreamState() = 0; \
		bool CreateForwardPacket(InterfaceSinkBase& sink) {return false;} \
	};
DUMMY_DEV_LIST
#undef DEV



#if HAVE_OPENGL
int GetOglChCode(int channels, bool is_float=false);
void Ogl_RemoveToken(String& glsl, String token);
#endif


struct AccelComponentConfBase {

	
	#define ACCEL_FILTER_LIST \
		ACCEL_FILTER_ITEM(FILTER_INVALID, "invalid") \
		ACCEL_FILTER_ITEM(FILTER_NEAREST, "nearest") \
		ACCEL_FILTER_ITEM(FILTER_LINEAR, "linear") \
		ACCEL_FILTER_ITEM(FILTER_MIPMAP, "mipmap")
	
	typedef enum {
		#define ACCEL_FILTER_ITEM(x,y) x,
		ACCEL_FILTER_LIST
		#undef ACCEL_FILTER_ITEM
		
		ACCEL_FILTER_COUNT,
		DEFAULT_FILTER = FILTER_LINEAR
	} Filter;
	
	
	#define ACCEL_WRAP_LIST \
		ACCEL_WRAP_ITEM(WRAP_INVALID, "invalid") \
		ACCEL_WRAP_ITEM(WRAP_CLAMP, "clamp") \
		ACCEL_WRAP_ITEM(WRAP_REPEAT, "repeat")
	
	typedef enum {
		#define ACCEL_WRAP_ITEM(x,y) x,
		ACCEL_WRAP_LIST
		#undef ACCEL_WRAP_ITEM
		
		ACCEL_WRAP_COUNT,
		DEFAULT_WRAP = WRAP_REPEAT
	} Wrap;
	
	
	#define ACCEL_TYPE_LIST \
		ACCEL_TYPE_ITEM(TYPE_INVALID, "invalid") \
		ACCEL_TYPE_ITEM(TYPE_EMPTY, "empty") \
		ACCEL_TYPE_ITEM(TYPE_BUFFER, "buffer") \
		ACCEL_TYPE_ITEM(TYPE_KEYBOARD, "keyboard") \
		ACCEL_TYPE_ITEM(TYPE_TEXTURE, "texture") \
		ACCEL_TYPE_ITEM(TYPE_CUBEMAP, "cubemap") \
		ACCEL_TYPE_ITEM(TYPE_WEBCAM, "webcam") \
		ACCEL_TYPE_ITEM(TYPE_MUSIC, "music") \
		ACCEL_TYPE_ITEM(TYPE_MUSICSTREAM, "musicstream") \
		ACCEL_TYPE_ITEM(TYPE_VOLUME, "volume") \
		ACCEL_TYPE_ITEM(TYPE_VIDEO, "video")
		
	typedef enum {
		#define ACCEL_TYPE_ITEM(x,y) x,
		ACCEL_TYPE_LIST
		#undef ACCEL_TYPE_ITEM
		ACCEL_TYPE_COUNT
	} Type;
	
	
	static const char* filter_names[ACCEL_FILTER_COUNT+1];
	static const char* wrap_names[ACCEL_WRAP_COUNT+1];
	static const char* type_names[ACCEL_TYPE_COUNT+1];
	
	
	
	void				SetType(Type t) {type = t;}
	void				SetPath(String s) {filepath = s;}
	void				Set(Type t, String path, Filter filter, Wrap wrap, bool vflip);
	void				Set(const AccelComponentConfBase& in);
	void				CopyIdStream(const AccelComponentConfBase& in);
	
	Type				GetType() const {return type;}
	String				GetPath() const {return filepath;}
    String				GetTypeString() const {return GetStringFromType(type);}
	bool				IsTypeComponentSource() {return IsTypeComponentSource(type);}
	bool				IsTypeEmpty() const {return type == TYPE_EMPTY;}
	bool				IsEqualHeader(const AccelComponentConfBase& in) const;
	String				ToString() const {return GetTypeString();}
	String				GetFilterString() const {return GetStringFromFilter(filter);}
	String				GetWrapString() const {return GetStringFromWrap(wrap);}
	
	static String		GetStringFromType(Type i);
	static String		GetStringFromFilter(Filter i);
	static String		GetStringFromWrap(Wrap i);
	static Type			GetTypeFromString(String typestr);
	static Filter		GetFilterFromString(String s);
	static Wrap			GetWrapFromString(String s);
	static bool			IsTypeComponentSource(Type i);
	
protected:
	String filepath;
	Type type = TYPE_INVALID;
	Wrap wrap = WRAP_REPEAT;
	Filter filter = FILTER_LINEAR;
	bool vflip = 0;

};

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

struct AccelComponentBase :
	RTTIBase,
	public RefScopeEnabler<AccelComponentBase, Entity>
{
	RTTI_DECL0(AccelComponentBase)
	
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
	
#if HAVE_OPENGL
	GLint				prog[PROG_COUNT] = {-1,-1,-1,-1,-1};
	GLuint				color_buf[2] = {0,0};
	GLuint				depth_buf[2] = {0,0};
	GLuint				frame_buf[2] = {0,0};
	GLint				var_idx[VAR_COUNT];
#endif
	String				name;
	String				description;
	String				code[PROG_COUNT];
	Size				fb_size = {0,0};
	int					buf_i = 0;
	bool				is_doublebuf = false;
	bool				is_searched_vars = false;
	bool				is_open = false;
	bool				has_fbo = false;
	
	
	void				Clear();
	void				Close();
	bool				Open();
	void				UpdateCompFlags(TypeCls val_spec, int comp_i, int comp_count);
	bool				IsAudioSpec() const {TODO}
	void				Process();
	
	virtual bool		RequiresDeviceProgram() const {return false;}
	
	static TypeCls		GetTypeFromString(String type_str);
	
	
protected:
	friend class AccelComponentGroupBase;
	
	void				ClearTex();
	void				ClearProg();
	void				UseRenderedFramebuffer();
	int					NewWriteBuffer();
	bool				IsSinkInAccelerator() const;
	bool				CheckDevice();
	
#if HAVE_OPENGL
	void				Ogl_SetVars(GLint prog, const AccelStreamState& stream);
	void				Ogl_SetVar(int var, GLint prog, const AccelStreamState& stream);
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
	
	
};

using AccelComponentBaseRef = Ref<AccelComponentBase>;



struct AccelComponentGroupBase : RTTIBase {
	RTTI_DECL0(AccelComponentGroupBase)
	
	Vector<uint32> gl_stages;
	
	void RefreshPipeline();
	bool CreateForwardPacket(InterfaceSinkBase& sink);
	
	virtual bool				IsValSpec(TypeCls t) const = 0;
	virtual AccelStreamState&	GetStreamState() = 0;
	
	template <class T> bool IsIn() {return IsValSpec(AsTypeCls<T>());}
	
#if HAVE_OPENGL
	void				Ogl_ProcessStage(AccelComponentBase& s, GLuint gl_stage);
	void				Ogl_ClearPipeline();
	void				Ogl_CreatePipeline();
#endif
	
};


NAMESPACE_TOPSIDE_END

#endif
