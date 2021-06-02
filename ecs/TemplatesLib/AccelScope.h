#ifndef _TemplatesLib_DevClasses_h_
#define _TemplatesLib_DevClasses_h_

NAMESPACE_TOPSIDE_BEGIN



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
	int					id = -1;
	int					buf_i = 0;
	bool				is_doublebuf = false;
	bool				is_searched_vars = false;
	bool				is_open = false;
	bool				has_fbo = false;
	
	
	bool				IsAudioSpec() const {TODO}
	
protected:
	void				ClearTex();
	String				ToString() const {return "(id: " + IntStr(id) + ")";}
	
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
	
};


NAMESPACE_TOPSIDE_END

#endif
