#ifndef _Graphics_OglBuffer_h_
#define _Graphics_OglBuffer_h_


NAMESPACE_TOPSIDE_BEGIN



int GetOglChCode(int channels, bool is_float=false);


class OglBuffer;


#if 0
class OglBufferInput {
	
public:
	
	
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
	
	
};
#endif

class OglBuffer : RTTIBase {
	RTTI_DECL0(OglBuffer)
	
protected:
	
	
	Vector<String>				link_ids;
	//Array<OglBufferInput>		in_buf;
	Vector<BinderIfaceOgl*>		binders;
	
	//OglShader					shader[ShaderVar::PROG_COUNT];
	String						last_error;
	
	
	
	
public:
	
	
	// set by user
	Vector<byte>				fb_out;
	EnvStateRef					env;
	int							loopback = -1;
	bool						initialized = false;
	
	
/*	int							fb_channels = 4;
	ShaderVar::Sample			fb_sampletype = ShaderVar::SAMPLE_U8;
	//int							fb_wrap = OglBufferInput::WRAP_REPEAT;
	//int							fb_filter = OglBufferInput::FILTER_LINEAR;
	//int							sample_rate = 44100;
	
	/*GLint						fb_type = -1;
	GLint						fb_fmt = -1;
	int							fb_depth = 0;
	int							fb_size_bytes = 0;
	int							fb_sample_size = 0;
	GLint						fb_accel_type = -1;
	GLint						fb_accel_fmt = -1;
	int							fb_accel_size_bytes = 0;
	int							fb_accel_sample_size = 0;*/
	
	
public:
	using State = OglFramebufferState;
	using Sample = ShaderVar::Sample;
	
	void Visit(RuntimeVisitor& vis) {vis & env;}
	
	bool				LoadShaderFile(ShaderVar::Type shader_type, String shader_path, String library_path);
	bool				LoadOutputLink(Size3 sz, int in_id, InternalPacketData& v);
	void				StoreOutputLink(InternalPacketData& v);
	
	bool				Initialize();
	bool				InitializeTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	bool				InitializeCubemap(Size sz, int channels, Sample sample, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	bool				InitializeVolume(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
	void				Update(double dt);
	void				ProcessStage(const RealtimeSourceConfig& cfg);
	
	void				ReadTexture(Size sz, int channels, Sample sample, const byte* data, int len);
	void				ReadTexture(Size3 sz, int channels, Sample sample, const Vector<byte>& data);
	void				SetEnvState(EnvStateRef env) {this->env = env;}
	bool				SetLoopback(String loopback_str);
	void				SetInputVolume(int input_i);
	void				SetInputCubemap(int input_i);
	void				SetFramebufferSize(Size sz);
	void				AddBinder(BinderIfaceOgl* iface);
	void				AddLink(String s) {if (!s.IsEmpty()) link_ids << s;}
	void				RemoveBinder(BinderIfaceOgl* iface);
	void				OnError(const char* fn, String s);
	
	bool				IsInitialized() const {return initialized;}
	String				GetError() const {return last_error;}
	
	
	State				state;
	static Callback2<String, OglBuffer*> WhenLinkInit;
	
protected:
	void				TexFlags(int type, ShaderVar::Filter filter, ShaderVar::Wrap repeat);
	bool				SetupLoopback();
	bool				CompilePrograms();
	void				RefreshPipeline();
	void				CreatePipeline();
	void				ClearPipeline();
	void				UpdateTexBuffers();
	void				Reset();
	void				ClearTex();
	void				CreateTex(bool create_depth, bool create_fbo);
	void				FindVariables();
	int					NewWriteBuffer();
	void				SetVars(GLint prog, const RealtimeSourceConfig& cfg);
	void				SetVar(int var, GLint prog, const RealtimeSourceConfig& cfg);
	void				UseRenderedFramebuffer();
	GLint				GetInputTex(int input_i) const;
	int					GetTexType(int input_i) const;
	GLint				GetOutputTexture(bool reading_self) const;
	
	
	
	
	/*
	bool				LoadFragmentShaderFile(String filepath, String library_paths);
	bool				LoadVertexShaderFile(String filepath, String library_paths);
	void				SetFragmentShaderSource(String s) {code[PROG_FRAGMENT] = s;}
	void				SetVertexShaderSource(String s) {code[PROG_VERTEX] = s;}
	
	bool				IsCubemap() const {return is_cubemap;}
	
	
	void				ClearProg();
	bool				CompileFragmentShader();
	bool				CompileVertexShader();
	bool				CompileProgram(int prog_i, String shader_source);
	GLint				CompileShader(int prog_i, String shader_source);
	bool				LinkStages();
	bool				LinkProgram(int prog_i);
	bool				CheckInputTextures();
	const OglBuffer*	GetComponentById(int id) const;
	void				ReadCubemap(Size sz, int channels, const Vector<byte>& d0, const Vector<byte>& d1, const Vector<byte>& d2, const Vector<byte>& d3, const Vector<byte>& d4, const Vector<byte>& d5);
	Size				GetFramebufferSize() const {return fb_size;}
	int					GetFramebufferChannels() const {return fb_channels;}
	
	
	
	*/
	
	
};


NAMESPACE_TOPSIDE_END

#endif
