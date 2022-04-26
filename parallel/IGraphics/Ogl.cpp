#include "IGraphics.h"

#ifdef flagOGL

NAMESPACE_PARALLEL_BEGIN



void GLAPIENTRY
OpenGLMessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{
	if (!IsGfxAccelDebugMessages())
		return;
	String s;
	s << "OpenGL debug: ";
	if (type == GL_DEBUG_TYPE_ERROR)
		s << "error: ";
	s << "type = " << HexStr(type);
	s << ", severity = " << HexStr(severity);
	s << ", message = " << String(message);
	LOG(s);
}

GLenum GetOglTextureType(GVar::TextureType type) {
	GLenum gl_t = 0;
	switch (type) {
		#define TEX_TYPE(x) case GVar::TEXTYPE##x: gl_t = GL_TEXTURE##x; break;
		GVAR_TEXTYPE_LIST
		#undef TEX_TYPE
		default: break;
	}
	ASSERT(gl_t > 0);
	return gl_t;
}





GLint OglFramebufferBase::GetGlType() const {
	using namespace GVar;
	switch (sample) {
		case SAMPLE_FLOAT:	return GL_FLOAT;
		case SAMPLE_U8:		return GL_UNSIGNED_BYTE;
		case SAMPLE_U16:	return GL_UNSIGNED_SHORT;
		case SAMPLE_U32:	return GL_UNSIGNED_INT;
		case SAMPLE_S32:	return GL_INT;
	}
	return -1;
}

GLint OglFramebufferBase::GetGlFormat() const {
	using namespace GVar;
	ASSERT(channels >= 1 && channels <= 4);
	if (sample != SAMPLE_FLOAT) {
		switch (channels) {
			case 1: return GL_RED;
			case 2: return GL_RG;
			case 3: return GL_RGB;
			case 4: return GL_RGBA;
			default: return -1;
		}
	}
	else {
		switch (channels) {
			case 1: return GL_R32F;
			case 2: return GL_RG32F;
			case 3: return GL_RGB32F;
			case 4: return GL_RGBA32F;
			default: return -1;
		}
	}
	return -1;
}

int OglFramebufferBase::GetGlSize() const {
	return size.cx * size.cy * GetGlSampleSize() * channels;
}

int OglFramebufferBase::GetGlSampleSize() const {
	using namespace GVar;
	switch (sample) {
		case SAMPLE_FLOAT:	return 4;
		case SAMPLE_U8:		return 1;
		case SAMPLE_U16:	return 2;
		case SAMPLE_U32:	return 4;
		case SAMPLE_S32:	return 4;
	}
	ASSERT(0);
	return 0;
}





void OglBufferBase::BaseUpdateTexBuffers(OglFramebufferBase& fb) {
	
	//TODO improve this sample reading
	ASSERT(fb.sample == GVar::SAMPLE_U8 || fb.sample == GVar::SAMPLE_FLOAT);
	
	fb.gl_sample_size		= fb.sample == GVar::SAMPLE_U8 ? 1 : 4;
	fb.gl_type				= fb.sample == GVar::SAMPLE_U8 ? GL_UNSIGNED_BYTE : GL_FLOAT;
	fb_accel_type			= fb_accel_sampletype == GVar::SAMPLE_U8 ? GL_UNSIGNED_BYTE : GL_FLOAT;
	
	int sample_size = GVar::GetSampleSize(fb.sample);
	fb_size_bytes			= fb.size.cx * fb.size.cy * sample_size * fb.channels;
	fb_accel_size_bytes		= fb.size.cx * fb.size.cy * fb.gl_sample_size * fb_accel_channels;
	fb_fmt					= GetOglChCode(fb.channels, fb.gl_type == GL_FLOAT);
	fb_accel_fmt			= GetOglChCode(fb_accel_channels, fb_accel_type == GL_FLOAT);
	
	ASSERT(fb_size_bytes > 0);
	ASSERT(fb.GetGlSize() > 0);
	ASSERT(fb.GetGlFormat() >= 0);
	ASSERT(fb.GetGlType() >= 0);
}



template <class Gfx>
void OglGfxT<Gfx>::SetDebugOutput(bool b) {
	if (b) {
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback( OpenGLMessageCallback, 0 );
	}
	else {
		glDisable(GL_DEBUG_OUTPUT);
	}
}

template <class Gfx>
void OglGfxT<Gfx>::ClearBuffers() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

template <class Gfx>
void OglGfxT<Gfx>::SetSmoothShading(bool b) {
	glShadeModel(b ? GL_SMOOTH : GL_FLAT);
}

template <class Gfx>
void OglGfxT<Gfx>::SetDepthTest(bool b) {
	if (b) glEnable(GL_DEPTH_TEST);
	else   glDisable(GL_DEPTH_TEST);
}

template <class Gfx>
void OglGfxT<Gfx>::SetDepthOrderLess(bool b) {
	if (b) glDepthFunc( GL_LEQUAL );
	else   glDepthFunc( GL_GEQUAL );
}

template <class Gfx>
void OglGfxT<Gfx>::SetClearValue(RGBA clr, byte depth) {
	// Set the background black
	glClearColor( clr.r/255.0f, clr.g/255.0f, clr.b/255.0f, clr.a/255.0f );
	
	// Depth buffer setup
	glClearDepth( depth/255.0f );
	
}

template <class Gfx>
void OglGfxT<Gfx>::SetFastPerspectiveCorrection(bool b) {
	if (b)
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST );
	else
		glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

template <class Gfx>
void OglGfxT<Gfx>::SetTriangleBacksideCulling(bool b) {
	if (b) {
		glEnable( GL_CULL_FACE );
		glCullFace( GL_BACK );
	}
	else
		glDisable( GL_CULL_FACE );
}

template <class Gfx> void OglGfxT<Gfx>::SetTriangleFrontsideCCW(bool b) {
	glFrontFace( b ? GL_CCW : GL_CW );
}

template <class Gfx> void OglGfxT<Gfx>::SetViewport(Size sz) {
	ASSERT(sz.cx > 0 && sz.cy > 0);
	glViewport(0, 0, sz.cx, sz.cy);
}

template <class Gfx> void OglGfxT<Gfx>::UseProgram(NativeProgram& prog) {
	glUseProgram(prog);
}

template <class Gfx> void OglGfxT<Gfx>::BindProgramPipeline(NativePipeline& pipeline) {
	glBindProgramPipeline(pipeline);
}

template <class Gfx> void OglGfxT<Gfx>::BindFramebuffer(NativeFrameBufferRef fb) {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
}

template <class Gfx> void OglGfxT<Gfx>::UnbindFramebuffer() {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

template <class Gfx> void OglGfxT<Gfx>::BindRenderbuffer(NativeDepthBufferRef rb) {
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rb);
}

template <class Gfx> void OglGfxT<Gfx>::UnbindRenderbuffer() {
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
}

template <class Gfx> void OglGfxT<Gfx>::RenderbufferStorage(Size sz) {
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, sz.cx, sz.cy);
}

template <class Gfx> void OglGfxT<Gfx>::UnbindProgramPipeline() {
	glBindProgramPipeline(0);
}

template <class Gfx> void OglGfxT<Gfx>::BindFramebufferDefault() {
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
}

template <class Gfx> void OglGfxT<Gfx>::DrawBuffers(GVar::RenderTarget tgt) {
	Vector<GLenum> bufs;
	for(uint32 i = 0; i < 32; i++) {
		uint32 j = 1 << i;
		if ((uint32)tgt & j) {
			switch (j) {
				case GVar::COLOR0_EXT: bufs << GL_COLOR_ATTACHMENT0_EXT; break;
				case GVar::COLOR1_EXT: bufs << GL_COLOR_ATTACHMENT1_EXT; break;
				case GVar::COLOR2_EXT: bufs << GL_COLOR_ATTACHMENT2_EXT; break;
				case GVar::COLOR3_EXT: bufs << GL_COLOR_ATTACHMENT3_EXT; break;
				default: TODO; break;
			}
		}
	}
	if (bufs.GetCount())
		glDrawBuffers(bufs.GetCount(), (GLenum*)bufs.Begin());
}

/*template <class Gfx> void OglGfxT<Gfx>::Clear_Color() {
	glClear(GL_COLOR_BUFFER_BIT);
}*/

template <class Gfx> void OglGfxT<Gfx>::RenderScreenRect() {
	glRectf(-1.0, -1.0, 1.0, 1.0);
}

template <class Gfx> void OglGfxT<Gfx>::DeactivateTexture() {
	// not supported
}

template <class Gfx> void OglGfxT<Gfx>::ActiveTexture(int ch) {
	glActiveTexture(GL_TEXTURE0 + ch);
}

template <class Gfx> void OglGfxT<Gfx>::BindTextureRO(GVar::TextureType type, NativeColorBufferConstRef tex) {
	glBindTexture(GetOglTextureType(type), tex);
}

template <class Gfx> void OglGfxT<Gfx>::BindTextureRW(GVar::TextureType type, NativeColorBufferRef tex) {
	glBindTexture(GetOglTextureType(type), tex);
}

template <class Gfx> void OglGfxT<Gfx>::UnbindTexture(GVar::TextureType type) {
	glBindTexture(GetOglTextureType(type), 0);
}

/*void OglRendererBase::ActivateNextFrame() {
	// pass
}*/

template <class Gfx> const char* OglGfxT<Gfx>::GetShaderTemplate(GVar::ShaderType t) {
	static const char* common_tmpl = R"SH4D3R(
#if ${IS_FRAGMENT_SHADER}

#elif ${IS_VERTEX_SHADER}

#endif
)SH4D3R";

	static const char* frag_tmpl = R"SH4D3R(
#version 410
#define GL_ES

uniform sampler2D iNone;
uniform sampler2D iDiffuse;
uniform sampler2D iSpecular;
uniform sampler2D iAmbient;
uniform sampler2D iEmissive;
uniform sampler2D iHeight;
uniform sampler2D iNormals ;
uniform sampler2D iShininess;
uniform sampler2D iOpacity;
uniform sampler2D iDisplacement;
uniform sampler2D iLightmap;
uniform sampler2D iReflection;
uniform sampler2D iUnknown;

uniform ${SAMPLER0} iChannel0;
uniform ${SAMPLER1} iChannel1;
uniform ${SAMPLER2} iChannel2;
uniform ${SAMPLER3} iChannel3;

uniform float     iAudioSeconds;
uniform mat4      iView;
uniform mat4      iProjection;
uniform mat4      iScale;
uniform mat4      iTransform;
uniform mat4      iModel;
uniform vec3      iLightDir;

uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;                 // shader playback time (in seconds)
uniform float     iTimeDelta;            // duration since the previous frame (in seconds)
uniform int       iFrame;                // frames since the shader (re)started
uniform vec2      iOffset;
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform vec4      iDate;                 // (year, month, day, time in secs)
uniform float     iFrameRate;
uniform float     iSampleRate;           // sound sample rate (i.e., 44100)
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform float     iBlockOffset;          // total consumed samples (mostly for audio, for video it's same as iFrame)

in vec3 vNormal;
in vec2 vTexCoord;

out vec4 out_Color;

${USER_LIBRARY}
${USER_CODE}

#if ${IS_AUDIO}
void main() {
	float t = iAudioSeconds + gl_FragCoord.x / iSampleRate;
	vec2 value = mainSound (t);
	out_Color = vec4(value, 0.0, 1.0);
}
#else
void main() {
	vec4 color = vec4 (0.0, 0.0, 0.0, 1.0);
	mainImage (color, gl_FragCoord.xy);
	out_Color = color;
}
#endif
)SH4D3R";


static const char* vtx_tmpl = R"SH4D3R(
#version 430
#define GL_ES
layout (location = 0) in vec4 iPos;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec2 iTexCoord;

in int iVertexID;
in int iInstanceID;

out vec2 TexCoords;
out gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

uniform sampler2D iNone;
uniform sampler2D iDiffuse;
uniform sampler2D iSpecular;
uniform sampler2D iAmbient;
uniform sampler2D iEmissive;
uniform sampler2D iHeight;
uniform sampler2D iNormals ;
uniform sampler2D iShininess;
uniform sampler2D iOpacity;
uniform sampler2D iDisplacement;
uniform sampler2D iLightmap;
uniform sampler2D iReflection;
uniform sampler2D iUnknown;

uniform float     iAudioSeconds;
uniform mat4      iView;
uniform mat4      iProjection;
uniform mat4      iScale;
uniform mat4      iTransform;
uniform mat4      iModel;
uniform vec3      iLightDir;

out vec3 vNormal;
out vec2 vTexCoord;

${USER_LIBRARY}
${USER_CODE}

void main() {
	vTexCoord = iTexCoord;
	vNormal = iNormal;
	mainVertex(gl_Position);
}

)SH4D3R";
	switch (t) {
		case GVar::VERTEX_SHADER: return vtx_tmpl;
		case GVar::FRAGMENT_SHADER: return frag_tmpl;
		default: Panic("shader is not supported yet");
	}
	return "";
}

template <class Gfx>
void OglGfxT<Gfx>::HotfixShaderCode(String& s) {
	s.Replace("precision float;", "");
	if (s.Find("vec4 char(") >= 0)
		s.Replace("char(", "_char(");
}

template <class Gfx>
bool OglGfxT<Gfx>::CreateShader(GVar::ShaderType type, NativeShader& new_shdr) {
	GLenum shader_type;
	if (type == GVar::FRAGMENT_SHADER) {
		shader_type = GL_FRAGMENT_SHADER;
	}
	else if (type == GVar::VERTEX_SHADER) {
		shader_type = GL_VERTEX_SHADER;
	}
	else {
		CHKLOGRET0(0, "OglGfx::CreateShader: TODO: other programs than fragment shader");
	}
	new_shdr = glCreateShader(shader_type);
	return new_shdr;
}

template <class Gfx> void OglGfxT<Gfx>::ShaderSource(NativeShader& s, String code) {
	const GLchar* src = code.Begin();
	int len = code.GetCount();
	glShaderSource(s, 1, &src, &len);
}

template <class Gfx>
bool OglGfxT<Gfx>::CompileShader(NativeShader& s) {
	glCompileShader(s);
	GLint status = GL_FALSE;
	glGetShaderiv(s, GL_COMPILE_STATUS, &status);
	return status == GL_TRUE;
}

template <class Gfx>
String OglGfxT<Gfx>::GetLastErrorS(NativeShader& s) {
	GLint loglen = 0;
	glGetShaderiv(s, GL_INFO_LOG_LENGTH, &loglen);
	Vector<GLchar> msg;
	msg.SetCount(loglen);
	glGetShaderInfoLog(s, loglen, NULL, msg.Begin());
	return String(msg.Begin());
}

template <class Gfx>
String OglGfxT<Gfx>::GetLastErrorP(NativeProgram& p) {
	GLint loglen = 0;
	glGetProgramiv(p, GL_INFO_LOG_LENGTH, &loglen);
	Vector<GLchar> msg;
	msg.SetCount(loglen);
	glGetProgramInfoLog(p, loglen, NULL, msg.Begin());
	return String(msg.Begin());
}

template <class Gfx>
bool OglGfxT<Gfx>::CreateProgram(NativeProgram& prog) {
	prog = glCreateProgram();
	return prog != 0;
}

template <class Gfx> void OglGfxT<Gfx>::ProgramParameteri(NativeProgram& prog, GVar::ParamType type, int i) {
	glProgramParameteri(prog, type, i);
}

template <class Gfx>
bool OglGfxT<Gfx>::LinkProgram(NativeProgram& prog) {
	glLinkProgram(prog);
	GLint status = GL_FALSE;
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	return status == GL_TRUE;
}

template <class Gfx> void OglGfxT<Gfx>::GetProgramiv(NativeProgram& prog, GVar::ProgParamType type, int& out) {
	GLenum gl_type = 0;
	switch (type) {
		#define PARAM_TYPE(x) case GVar::x: gl_type = GL_##x; break;
		GVAR_PROGPARAMTYPE_LIST
		#undef PARAM_TYPE
		default: break;
	}
	ASSERT(gl_type > 0);
	glGetProgramiv(prog, gl_type, &out);
}

template <class Gfx>
String OglGfxT<Gfx>::GetActiveUniform(NativeProgram& prog, int i, int* size_out, int* type_out) {
	GLchar name[80];
	GLsizei namelen;
	GLint size;
	GLenum type;
	
	glGetActiveUniform(prog, i, 79, &namelen, &size, &type, name);
	int last = max(0, min(79, (int)namelen));
	name[last] = '\0';
	
	return name;
}

template <class Gfx> void OglGfxT<Gfx>::Clear(GVar::BufferType type) {
	GLenum gl_type = 0;
	switch (type) {
		#define BUFFER_TYPE(x) case GVar::x: gl_type = GL_##x##_BIT; break;
		GVAR_BUFFERTYPE_LIST
		#undef BUFFER_TYPE
		default: break;
	}
	ASSERT(gl_type > 0);
	glClear(gl_type);
}

template <class Gfx> void OglGfxT<Gfx>::AttachShader(NativeProgram& prog, NativeShader& shdr) {
	glAttachShader(prog, shdr);
}

template <class Gfx> void OglGfxT<Gfx>::DeleteShader(NativeShader& shdr) {
	glDeleteShader(shdr);
}

template <class Gfx> void OglGfxT<Gfx>::GenProgramPipeline(NativePipeline& pipe) {
	glGenProgramPipelines(1, &pipe);
}

template <class Gfx> void OglGfxT<Gfx>::UseProgramStages(NativePipeline& pipe, uint32 bmask, NativeProgram& prog) {
	GLenum gl_bmask = 0;
	for(int i = 0; i < GVar::SHADERTYPE_COUNT; i++) {
		uint32 j = 1UL << i;
		if (bmask & j) {
			switch (i) {
				#define GVAR_SHADERTYPE(x) case GVar::x: gl_bmask |= GL_##x##_BIT; break;
				GVAR_SHADERTYPE_LIST
				#undef GVAR_SHADERTYPE
				default: break;
			}
		}
	}
	ASSERT(gl_bmask > 0);
	glUseProgramStages(pipe, gl_bmask, prog);
}

template <class Gfx> void OglGfxT<Gfx>::DeleteProgramPipeline(NativePipeline& pipe) {
	glDeleteProgramPipelines(1, &pipe);
	pipe = 0;
}

template <class Gfx> void OglGfxT<Gfx>::TexParameteri(GVar::TextureType type, GVar::Filter filter, GVar::Wrap wrap) {
	GLenum gl_t = GetOglTextureType(type);
	
	GLenum gl_filter = 0;
	switch (filter) {
		#define FILTER(x) case GVar::FILTER_##x: gl_filter = GL_##x; break;
		FILTER_LIST
		#undef FILTER
		default: break;
	}
	ASSERT(gl_filter > 0);
	
	GLenum gl_wrap = 0;
	switch (wrap) {
		#define WRAP(x) case GVar::WRAP_##x: gl_wrap = GL_##x; break;
		WRAP_LIST
		#undef WRAP
		default: break;
	}
	ASSERT(gl_wrap > 0);
	
	glTexParameteri(gl_t, GL_TEXTURE_MIN_FILTER, gl_filter);
	glTexParameteri(gl_t, GL_TEXTURE_MAG_FILTER, gl_filter);
	
	glTexParameteri(gl_t, GL_TEXTURE_WRAP_S, gl_wrap);
	glTexParameteri(gl_t, GL_TEXTURE_WRAP_T, gl_wrap);
	if (type == GVar::TEXTYPE_3D)
		glTexParameteri(gl_t, GL_TEXTURE_WRAP_R, gl_wrap);
}

template <class Gfx>
bool OglGfxT<Gfx>::GenTexture(NativeColorBufferRef& fb) {
	glGenTextures(1, &fb);
	return true;
}

template <class Gfx>
bool OglGfxT<Gfx>::CreateFramebuffer(NativeFrameBufferRef& fbo) {
	glGenFramebuffersEXT(1, &fbo);
	return true;
}

template <class Gfx> void OglGfxT<Gfx>::GenVertexArray(NativeVertexArray& vao) {
	glGenVertexArrays(1, &vao);
}

template <class Gfx> void OglGfxT<Gfx>::GenVertexBuffer(NativeVertexBuffer& vbo) {
	glGenBuffers(1, &vbo);
}

template <class Gfx> void OglGfxT<Gfx>::GenElementBuffer(NativeElementBuffer& ebo) {
	glGenBuffers(1, &ebo);
}

template <class Gfx> void OglGfxT<Gfx>::BindVertexArray(NativeVertexArray& vao) {
	glBindVertexArray(vao);
}

template <class Gfx> void OglGfxT<Gfx>::BindVertexBuffer(NativeVertexBuffer& vbo) {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

template <class Gfx> void OglGfxT<Gfx>::VertexBufferData(const Vector<Vertex>& vtx) {
	glBufferData(GL_ARRAY_BUFFER, vtx.GetCount() * sizeof(Vertex), &vtx[0], GL_STATIC_DRAW);
}

template <class Gfx> void OglGfxT<Gfx>::BindElementBuffer(NativeElementBuffer& ebo) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

template <class Gfx> void OglGfxT<Gfx>::ElementBufferData(const Vector<uint32>& indices) {
	glBufferData(	GL_ELEMENT_ARRAY_BUFFER,
					indices.GetCount() * sizeof(unsigned int),
					&indices[0], GL_STATIC_DRAW);
}

template <class Gfx> void OglGfxT<Gfx>::SetupVertexStructure() {
	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
}

template <class Gfx> void OglGfxT<Gfx>::UnbindVertexArray() {
	glBindVertexArray(0);
}

template <class Gfx> void OglGfxT<Gfx>::UnbindVertexBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template <class Gfx> void OglGfxT<Gfx>::UnbindElementBuffer() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

template <class Gfx> void OglGfxT<Gfx>::ActivateVertexStructure() {
	const int vtx = 0;
	const int nm = 1;
	const int tex = 2;
	glEnableVertexAttribArray(vtx);          // activate vertex position array
	glEnableVertexAttribArray(nm);           // activate vertex normal array
	glEnableVertexAttribArray(tex);          // activate texture coords array
	
	// set vertex arrays with generic API
	const int stride = sizeof(Vertex);
	const void* offset1 = (void*)offsetof(Vertex, position);
	const void* offset2 = (void*)offsetof(Vertex, normal);
	const void* offset3 = (void*)offsetof(Vertex, tex_coord);
	glVertexAttribPointer(vtx, 4, GL_FLOAT, false, stride, offset1);
	glVertexAttribPointer(nm,  3, GL_FLOAT, false, stride, offset2);
	glVertexAttribPointer(tex, 2, GL_FLOAT, false, stride, offset3);
	
}

template <class Gfx> void OglGfxT<Gfx>::DeactivateVertexStructure() {
	const int vtx = 0;
	const int nm = 1;
	const int tex = 2;
	glDisableVertexAttribArray(vtx);         // deactivate vertex position
	glDisableVertexAttribArray(nm);          // deactivate vertex normal
	glDisableVertexAttribArray(tex);         // deactivate texture coords
}

template <class Gfx> void OglGfxT<Gfx>::DrawVertexElements(int element_limit) {
	glDrawElements(GL_TRIANGLES, element_limit, GL_UNSIGNED_INT, 0);
}

template <class Gfx> void OglGfxT<Gfx>::UniformMatrix4fv(int idx, const mat4& mat) {
	glUniformMatrix4fv(idx, 1, GL_FALSE, &mat[0][0]);
}

template <class Gfx> void OglGfxT<Gfx>::TexImage2D(ByteImage& tex) {
	ASSERT(tex.channels == 4 || tex.channels == 3);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		tex.GetWidth(), tex.GetHeight(),
		0,
		tex.channels == 4 ? GL_BGRA : GL_BGR,
		GL_UNSIGNED_BYTE, tex.data);
}

template <class Gfx> void OglGfxT<Gfx>::GenerateMipmap(GVar::TextureType type) {
	glGenerateMipmap(GetOglTextureType(type));
}

template <class Gfx> void OglGfxT<Gfx>::DeleteVertexArray(NativeVertexArray& vao) {
	glDeleteVertexArrays(1, &vao);
}

template <class Gfx> void OglGfxT<Gfx>::DeleteVertexBuffer(NativeVertexBuffer& vbo) {
	glDeleteBuffers(1, &vbo);
}

template <class Gfx> void OglGfxT<Gfx>::DeleteElementBuffer(NativeElementBuffer& ebo) {
	glDeleteBuffers(1, &ebo);
}

template <class Gfx> void OglGfxT<Gfx>::DeleteTexture(NativeColorBufferRef& b) {
	glDeleteTextures(1, &b);
}

template <class Gfx>
bool OglGfxT<Gfx>::CreateRenderbuffer(NativeDepthBufferRef& b) {
	glGenRenderbuffersEXT(1, &b);
	return true;
}

template <class Gfx> void OglGfxT<Gfx>::DeleteRenderbuffer(NativeDepthBufferRef& b) {
	glDeleteRenderbuffersEXT(1, &b);
	b = 0;
}

template <class Gfx> void OglGfxT<Gfx>::DeleteFramebuffer(NativeFrameBufferRef& b) {
	glDeleteFramebuffers(1, &b);
	b = 0;
}

template <class Gfx>
Serial::FboFormat& OglGfxT<Gfx>::GetFormat(Parallel::Format& fmt) {
	return fmt;
}

template <class Gfx> void OglGfxT<Gfx>::Uniform1i(int idx, int i) {
	glUniform1i(idx, i);
}

template <class Gfx> void OglGfxT<Gfx>::Uniform1f(int idx, float f) {
	glUniform1f(idx, f);
}

template <class Gfx> void OglGfxT<Gfx>::Uniform2f(int idx, float f0, float f1) {
	glUniform2f(idx, f0, f1);
}

template <class Gfx> void OglGfxT<Gfx>::Uniform3f(int idx, float f0, float f1, float f2) {
	glUniform3f(idx, f0, f1, f2);
}

template <class Gfx> void OglGfxT<Gfx>::Uniform4f(int idx, float f0, float f1, float f2, float f3) {
	glUniform4f(idx, f0, f1, f2, f3);
}

template <class Gfx> void OglGfxT<Gfx>::BeginRender() {}
template <class Gfx> void OglGfxT<Gfx>::EndRender() {}

template <class Gfx> void OglGfxT<Gfx>::SetContextDefaultFramebuffer(NativeFrameBufferRef fb) {
	// pass
}

template <class Gfx> void OglGfxT<Gfx>::FramebufferTexture2D(TexType tgt, NativeColorBufferRef b) {
	TODO // decode: tgt -> GL_COLOR_ATTACH...
	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, fb, 0);
}

template <class Gfx> void OglGfxT<Gfx>::FramebufferRenderbuffer(NativeDepthBufferRef fb) {
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, fb);
}


#if defined flagOGL && defined flagSCREEN
template struct OglGfxT<X11OglGfx>;
#ifdef flagSDL2
template struct OglGfxT<SdlOglGfx>;
#endif
#endif


NAMESPACE_PARALLEL_END

#endif