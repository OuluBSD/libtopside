#ifndef _Graphics_OpenGLBuffer_h_
#define _Graphics_OpenGLBuffer_h_


NAMESPACE_TOPSIDE_BEGIN



int GetOglChCode(int channels, bool is_float=false);


class OglBuffer;


class OglBufferInput {
	
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
	
	Type				GetFusionType() const {return type;}
	String				GetTypeString() const {return GetStringFromType(type);}
	String				GetFilterString() const {return GetStringFromFilter(filter);}
	String				GetWrapString() const {return GetStringFromWrap(wrap);}
	bool				IsTypeComponentSource() {return IsTypeComponentSource(type);}
	String				GetFilepath() const {return filepath;}
	String				ToString() const {return GetTypeString();}
	bool				IsEqualHeader(const OglBufferInput& in) const;
	void				SetHeader(const OglBufferInput& in);
	bool				IsVertFlip() const {return vflip;}
	int					GetFilter() const {return filter;}
	int					GetWrap() const {return wrap;}
	bool				IsTypeEmpty() const {return type == EMPTY;}
	const OglBuffer*	GetBuffer() const {return in_buf;}
	
	static String		GetStringFromType(Type i);
	static String		GetStringFromFilter(int i);
	static String		GetStringFromWrap(int i);
	static Type			GetTypeFromString(String typestr);
	static int			GetFilterFromString(String s);
	static int			GetWrapFromString(String s);
	static bool			IsTypeComponentSource(Type i);
	
protected:
	friend class OglBuffer;
	friend class FusionContextComponent;
	friend struct OglBufferInputVector;
	
	const OglBuffer*		in_buf = 0;
	String					filepath;
	int						id = -1;
	Type					type = INVALID;
	int						wrap = WRAP_REPEAT;
	int						filter = FILTER_LINEAR;
	bool					vflip = 0;
	
	
};


class OglBuffer : RTTIBase {
	RTTI_DECL0(OglBuffer)
	
protected:
	
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
		VAR_COMPAT_BLOCKOFFSET,
		
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
			"iBlockOffset",
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
	
	Vector<String>				link_ids;
	Array<OglBufferInput>		in_buf;
	Vector<String>				common_source_frag;
	Vector<String>				common_source_vtx;
	Vector<BinderIfaceOgl*>		binders;
	
	OpenGLShader shader;
	
	GLint						prog[PROG_COUNT] = {-1,-1,-1,-1,-1};
	GLuint						color_buf[2] = {0,0};
	GLuint						depth_buf[2] = {0,0};
	GLuint						frame_buf[2] = {0,0};
	GLint						var_idx[VAR_COUNT];
	
	String						name;
	String						description;
	String						last_error;
	String						code[PROG_COUNT];
	int							id = -1;
	int							buf_i = 0;
	bool						is_doublebuf = false;
	bool						is_searched_vars = false;
	
	GLuint						gl_stage = 0;
	
	
	
public:
	typedef enum {
		SAMPLE_BYTE,
		SAMPLE_FLOAT,
	} SampleType;
	
	
	// set by user
	bool						is_win_fbo = false;
	bool						is_read_fb_output = false;
	bool						is_shader_audio_main = false;
	int							fb_channels = 4;
	int							fb_accel_channels = 4;
	Size						fb_size;
	SampleType					fb_sampletype = SAMPLE_BYTE;
	SampleType					fb_accel_sampletype = SAMPLE_FLOAT;
	int							fb_wrap = OglBufferInput::WRAP_REPEAT;
	int							fb_filter = OglBufferInput::FILTER_LINEAR;
	int							sample_rate = 44100;
	
	GLint						fb_type = -1;
	GLint						fb_fmt = -1;
	int							fb_depth = 0;
	int							fb_size_bytes = 0;
	int							fb_sample_size = 0;
	GLint						fb_accel_type = -1;
	GLint						fb_accel_fmt = -1;
	int							fb_accel_size_bytes = 0;
	int							fb_accel_sample_size = 0;
	Vector<byte>				fb_out;
	
	double						time_total = 0;
	double						frame_time = 0;
	double						block_offset = 0;
	int							frames = -1;
	double						fps = 0;
	Point						fb_offset;
	double						time_us = 0;
	Time						time;
	bool						is_cubemap = false;
	EnvStateRef					env;
	int							loopback = -1;
	
	bool						initialized = false;
	
	
	
public:
	
	void Visit(RuntimeVisitor& vis) {vis & env;}
	
	
	bool				LoadFragmentShaderFile(String filepath, String library_paths);
	bool				LoadVertexShaderFile(String filepath, String library_paths);
	void				SetFragmentShaderSource(String s) {code[PROG_FRAGMENT] = s;}
	void				SetVertexShaderSource(String s) {code[PROG_VERTEX] = s;}
	void				AddLink(String s) {if (!s.IsEmpty()) link_ids << s;}
	
	bool				IsInitialized() const {return initialized;}
	bool				IsCubemap() const {return is_cubemap;}
	
	bool				Initialize();
	bool				InitializeTextureRGBA(Size sz, int channels, const byte* data, int len);
	bool				InitializeCubemapRGBA(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	bool				InitializeVolume(Size3 sz, int channels, const Vector<byte>& data);
	void				RefreshPipeline();
	void				UpdateTexBuffers();
	void				Reset();
	int					NewWriteBuffer();
	void				Update(double dt);
	bool				SetLoopback(String loopback_str);
	
	void				ProcessStage(const RealtimeSourceConfig& cfg);
	void				ClearPipeline();
	void				CreatePipeline();
	void				FindVariables(GLint prog);
	void				SetVars(GLint prog, const RealtimeSourceConfig& cfg);
	void				SetVar(int var, GLint prog, const RealtimeSourceConfig& cfg);
	void				SetInputVolume(int input_i);
	void				SetInputCubemap(int input_i);
	void				ClearTex();
	void				ClearProg();
	void				CreateTex(bool create_depth, bool create_fbo, int filter, int repeat);
	GLint				GetInputTex(int input_i) const;
	int					GetTexType(int input_i) const;
	bool				SetupLoopback();
	bool				CompilePrograms();
	bool				CompileFragmentShader();
	bool				CompileVertexShader();
	bool				CompileProgram(int prog_i, String shader_source);
	GLint				CompileShader(int prog_i, String shader_source);
	bool				LinkStages();
	bool				LinkProgram(int prog_i);
	bool				CheckInputTextures();
	GLint				GetOutputTexture(bool reading_self) const;
	void				TexFlags(int type, int filter, int repeat);
	void				UseRenderedFramebuffer();
	const OglBuffer*	GetComponentById(int id) const;
	void				ReadTexture(Size sz, int channels, const byte* data, int len);
	void				ReadTexture(Size3 sz, int channels, const Vector<byte>& data);
	void				ReadCubemap(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	Size				GetFramebufferSize() const {return fb_size;}
	int					GetFramebufferChannels() const {return fb_channels;}
	GLuint				GetReadFramebuffer() const {return frame_buf[buf_i];}
	void				SetEnvState(EnvStateRef env) {this->env = env;}
	void				SetFramebufferSize(Size sz);
	
	void				OnError(const char* fn, String s);
	String				GetError() const {return last_error;}
	
	void				StoreOutputLink(InternalPacketData& v);
	bool				LoadOutputLink(Size3 sz, int in_id, InternalPacketData& v);
	
	void				AddBinder(BinderIfaceOgl* iface);
	void				RemoveBinder(BinderIfaceOgl* iface);
	
	
	static Callback2<String, OglBuffer*> WhenLinkInit;
	
};


NAMESPACE_TOPSIDE_END

#endif
