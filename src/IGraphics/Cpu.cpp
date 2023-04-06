#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN





template <class Gfx>
typename SwGfxT<Gfx>::Thread& SwGfxT<Gfx>::Local() {thread_local static Thread t; return t;}

template <class Gfx>
SoftRend& SwGfxT<Gfx>::Rend() {return Local().rend;}


template <class Gfx>
typename SwGfxT<Gfx>::NativeColorBufferConstRef SwGfxT<Gfx>::GetLocalTexture(int ch) {
	ASSERT(ch >= 0 && ch < CHANNEL_COUNT);
	return Local().texture[ch].GetReadTexture();
}

template <class Gfx>
void SwGfxT<Gfx>::SetDebugOutput(bool b) {
	Rend().SetDebugOutput(b);
}

template <class Gfx>
void SwGfxT<Gfx>::ClearBuffers() {
	auto fb = Local().fb;
	ASSERT(fb);
	if (fb)
		Rend().DrawDefault(*fb);
}

template <class Gfx>
void SwGfxT<Gfx>::SetSmoothShading(bool b) {
	Rend().SetSmoothShading(b);
}

template <class Gfx>
void SwGfxT<Gfx>::SetDepthTest(bool b) {
	Rend().SetDepthTest(b);
}

template <class Gfx>
void SwGfxT<Gfx>::SetDepthOrderLess(bool b) {
	Rend().SetDepthOrderLess(b);
}

template <class Gfx>
void SwGfxT<Gfx>::SetClearValue(RGBA clr, byte depth) {
	Rend().SetClearValue(clr, depth);
}

template <class Gfx>
void SwGfxT<Gfx>::SetFastPerspectiveCorrection(bool b) {
	Rend().SetFastPerspectiveCorrection(b);
}

template <class Gfx>
void SwGfxT<Gfx>::SetTriangleBacksideCulling(bool b) {
	Rend().SetTriangleBacksideCulling(b);
}

template <class Gfx>
void SwGfxT<Gfx>::SetTriangleFrontsideCCW(bool b) {
	Rend().SetTriangleFrontsideCCW(b);
}

template <class Gfx>
void SwGfxT<Gfx>::SetViewport(Size sz) {
	Rend().SetViewport(sz);
}

template <class Gfx>
void SwGfxT<Gfx>::UseProgram(NativeProgram& prog) {
	ASSERT(prog.pipeline);
	Local().prog = &prog;
}

template <class Gfx>
void SwGfxT<Gfx>::BindProgramPipeline(NativePipeline& pipeline) {
	Local().pipe = &pipeline;
}

template <class Gfx>
void SwGfxT<Gfx>::UnbindProgramPipeline() {
	Local().pipe = 0;
	Local().prog = 0;
}

template <class Gfx>
void SwGfxT<Gfx>::DrawBuffers(GVar::RenderTarget tgt) {
	auto& l = Local();
	l.rend.SetDrawBuffers(tgt);
	
}

template <class Gfx>
void SwGfxT<Gfx>::ActiveTexture(int ch) {
	ASSERT(ch >= 0 && ch < CHANNEL_COUNT);
	Local().active_texture = ch;
}

template <class Gfx>
void SwGfxT<Gfx>::DeactivateTexture() {
	Local().active_texture = -1;
}


template <class Gfx>
String SwGfxT<Gfx>::GetShaderTemplate(GVar::ShaderType t) {
	static const char* shader_tmpl = "";
	return shader_tmpl;
}

template <class Gfx>
void SwGfxT<Gfx>::HotfixShaderCode(String& s) {}

template <class Gfx>
void SwGfxT<Gfx>::Uniform1i(int idx, int i) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVar(idx, (float)i);
}

template <class Gfx>
void SwGfxT<Gfx>::Uniform2i(int idx, int i0, int i1) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVar(idx, (float)i0, (float)i1);
}

template <class Gfx>
void SwGfxT<Gfx>::Uniform3i(int idx, int i0, int i1, int i2) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVar(idx, (float)i0, (float)i1, (float)i2);
}

template <class Gfx>
void SwGfxT<Gfx>::Uniform1f(int idx, float f) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVar(idx, f);
}

template <class Gfx>
void SwGfxT<Gfx>::Uniform2f(int idx, float f0, float f1) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVar(idx, f0, f1);
}

template <class Gfx>
void SwGfxT<Gfx>::Uniform3f(int idx, float f0, float f1, float f2) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVar(idx, f0, f1, f2);
}

template <class Gfx>
void SwGfxT<Gfx>::Uniform4f(int idx, float f0, float f1, float f2, float f3) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVar(idx, f0, f1, f2, f3);
}

template <class Gfx>
void SwGfxT<Gfx>::Uniform1fv(int idx, int count, float* f) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVarArray(idx, 1, count, f);
}

template <class Gfx>
void SwGfxT<Gfx>::Uniform3fv(int idx, int count, float* f) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVarArray(idx, 3, count, f);
}

template <class Gfx>
void SwGfxT<Gfx>::Uniform4fv(int idx, int count, float* f) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVarArray(idx, 4, count, f);
}

template <class Gfx>
void SwGfxT<Gfx>::ProgramUniform3f(NativeProgram& prog, int idx, float f0, float f1, float f2) {
	TODO
}

template <class Gfx>
void SwGfxT<Gfx>::UniformMatrix4fv(int idx, const mat4& mat) {
	auto& prog = Local().prog;
	ASSERT(prog);
	if (prog) prog->SetVar(idx, mat);
}

template <class Gfx>
bool SwGfxT<Gfx>::CreateShader(GVar::ShaderType t, NativeShaderRef& new_shdr) {
	new_shdr = new SoftShader();
	new_shdr->SetType(t);
	return true;
}

template <class Gfx>
void SwGfxT<Gfx>::ShaderSource(NativeShaderRef s, String code) {
	s->SetSource(code);
}

template <class Gfx>
bool SwGfxT<Gfx>::CompileShader(NativeShaderRef s) {
	return Local().comp.Compile(*s);
}

template <class Gfx>
String SwGfxT<Gfx>::GetLastErrorS(NativeShaderRef s) {
	return s->GetLastError();
}

template <class Gfx>
String SwGfxT<Gfx>::GetLastErrorP(NativeProgram& p) {
	return p.GetLastError();
}

template <class Gfx>
bool SwGfxT<Gfx>::CreateProgram(NativeProgram& prog) {
	return prog.Create();
}

template <class Gfx>
void SwGfxT<Gfx>::ProgramParameteri(NativeProgram& prog, GVar::ParamType type, int i) {
	prog.SetParameter(type, i);
}

template <class Gfx>
bool SwGfxT<Gfx>::LinkProgram(NativeProgram& prog) {
	return prog.LinkProgram();
}

template <class Gfx>
void SwGfxT<Gfx>::GetProgramiv(NativeProgram& prog, GVar::ProgParamType type, int& out) {
	out = prog.GetParamInt(type);
}

template <class Gfx>
String SwGfxT<Gfx>::GetActiveUniform(NativeProgram& prog, int i, int* size_out, int* type_out) {
	if (size_out)
		*size_out = prog.GetVarSize(i);
	if (type_out)
		*type_out = prog.GetVarType(i);
	
	return prog.GetVar(i);
}

template <class Gfx>
void SwGfxT<Gfx>::Clear(GVar::BufferType type) {
	auto& fb = Local().fb;
	ASSERT(fb);
	if (fb)
		fb->ClearData(type);
}

template <class Gfx>
void SwGfxT<Gfx>::AttachShader(NativeProgram& prog, NativeShaderRef shdr) {
	prog.Attach(*shdr);
}

template <class Gfx>
void SwGfxT<Gfx>::DeleteShader(NativeShaderRef& shdr) {
	shdr->Clear();
	shdr = 0;
}

template <class Gfx>
void SwGfxT<Gfx>::GenProgramPipeline(NativePipeline& pipe) {
	pipe.Create();
}

template <class Gfx>
void SwGfxT<Gfx>::UseProgramStages(NativePipeline& pipe, uint32 bmask, NativeProgram& prog) {
	pipe.Use(prog, bmask);
}

template <class Gfx>
void SwGfxT<Gfx>::DeleteProgramPipeline(NativePipeline& pipe) {
	pipe.Clear();
}

template <class Gfx>
void SwGfxT<Gfx>::TexParameteri(GVar::TextureMode type, GVar::Filter filter, GVar::Wrap repeat) {
	auto& fb = Local().fb;
	ASSERT(fb);
	if (fb)
		fb->SetParam(type, filter, repeat);
}

template <class Gfx>
void SwGfxT<Gfx>::BindFramebuffer(NativeFrameBufferRef fb) {
	auto& l = Local();
	ASSERT_(!l.fb || (l.ctx_default_fb && l.fb == l.ctx_default_fb), "previous frambuffer have not been unbound");
	l.fb = fb;
}

template <class Gfx>
void SwGfxT<Gfx>::BindFramebufferRO(NativeFrameBufferConstRef fb) {
	auto& l = Local();
	ASSERT_(!l.fb || (l.ctx_default_fb && l.fb == l.ctx_default_fb), "previous frambuffer have not been unbound");
	l.fb = (NativeFrameBufferRef)fb;
}

template <class Gfx>
void SwGfxT<Gfx>::BindTextureRO(GVar::TextureMode type, NativeColorBufferConstRef tex) {
	auto& l = Local();
	auto& t = l.T();
	t.r = tex;
	t.rw = 0;
	if (l.prog)
		l.prog->BindTexture(l.active_texture, tex);
}

template <class Gfx>
void SwGfxT<Gfx>::BindTextureRW(GVar::TextureMode type, NativeColorBufferRef tex) {
	auto& l = Local();
	auto& t = l.T();
	t.r = 0;
	t.rw = tex;
	if (l.prog)
		l.prog->BindTexture(l.active_texture, tex);
}

template <class Gfx>
void SwGfxT<Gfx>::UnbindTexture(GVar::TextureMode type) {
	auto& t = Local().T();
	t.r = 0;
	t.rw = 0;
}

template <class Gfx>
void SwGfxT<Gfx>::ReserveTexture(GVar::TextureMode type, FramebufferT<Gfx>& fb) {
	// pass
}

template <class Gfx>
void SwGfxT<Gfx>::GenerateMipmap(GVar::TextureMode type) {
	// not supported
}

template <class Gfx>
void SwGfxT<Gfx>::BindFramebufferDefault() {
	Local().fb = Local().ctx_default_fb;
}

template <class Gfx>
void SwGfxT<Gfx>::RenderScreenRect() {
	auto& l = Local();
	ASSERT_(l.fb, "framebuffer is not bound yet");
	//ASSERT_(l.shdr, "shader is not bound yet");
	//ASSERT_(l.prog, "program is not bound yet");
	ASSERT_(l.pipe, "pipe is not bound yet");
	ASSERT_(*l.pipe, "pipeline is not inited");
	
	l.rend.SetTarget(*l.pipe, *l.fb);
	l.rend.RenderScreenRect();
}

template <class Gfx>
bool SwGfxT<Gfx>::GenTexture(NativeColorBufferRef& b) {
	ASSERT(!b);
	b = new ByteImage();
	return true;
}

template <class Gfx>
void SwGfxT<Gfx>::SetContextDefaultFramebuffer(NativeFrameBufferRef fb) {
	auto& l = Local();
	l.ctx_default_fb = fb;
	if (!l.fb)
		l.fb = fb;
}

template <class Gfx>
void SwGfxT<Gfx>::GenVertexArray(NativeVertexArray& va) {
	va.Create();
}

template <class Gfx>
void SwGfxT<Gfx>::GenVertexBuffer(NativeVertexBuffer& vb) {
	vb.Create();
}

template <class Gfx>
void SwGfxT<Gfx>::GenElementBuffer(NativeElementBuffer& eb) {
	eb.Create();
}

template <class Gfx>
void SwGfxT<Gfx>::BindVertexArray(NativeVertexArray& vao) {
	Local().vao = &vao;
}

template <class Gfx>
void SwGfxT<Gfx>::BindVertexBuffer(NativeVertexBuffer& vbo) {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->vbo = &vbo;
}

template <class Gfx>
void SwGfxT<Gfx>::VertexBufferData(const Vector<Vertex>& vtx) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->vbo);
	l.vao->vbo->vertices <<= vtx;
}

template <class Gfx>
void SwGfxT<Gfx>::BindElementBuffer(NativeElementBuffer& ebo) {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->ebo = &ebo;
}

template <class Gfx>
void SwGfxT<Gfx>::ElementBufferData(const Vector<uint32>& el) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->ebo);
	l.vao->ebo->indices <<= el;
}

template <class Gfx>
void SwGfxT<Gfx>::UnbindVertexArray() {
	Local().vao = 0;
}

template <class Gfx>
void SwGfxT<Gfx>::UnbindVertexBuffer() {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->vbo = 0;
}

template <class Gfx>
void SwGfxT<Gfx>::UnbindElementBuffer() {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->ebo = 0;
}

template <class Gfx>
void SwGfxT<Gfx>::DrawVertexElements(int element_limit, bool use_quad) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->vbo);
	ASSERT(l.vao->ebo);
	ASSERT_(l.fb, "framebuffer is not bound yet");
	ASSERT_(l.pipe, "pipe is not bound yet");
	ASSERT_(*l.pipe, "pipeline is not inited");
	ASSERT(l.prog);
	
	//for(int i = 0; i < TEXTYPE_COUNT; i++)
	//	l.rend.BindTexture(i, l.texture[i].GetReadTexture());
	
	l.rend.Render(*l.prog, *l.vao, use_quad);
}

template <class Gfx>
void SwGfxT<Gfx>::TexImage2D(ByteImage& tex) {
	auto& t = Local().T();
	ASSERT(!t.r);
	ASSERT(t.rw);
	*t.rw = tex;
}

template <class Gfx>
void SwGfxT<Gfx>::TexImage2D(FloatImage& tex) {
	TODO
}

template <class Gfx>
void SwGfxT<Gfx>::DeleteVertexArray(NativeVertexArray& vao) {
	vao.Clear();
}

template <class Gfx>
void SwGfxT<Gfx>::DeleteVertexBuffer(NativeVertexBuffer& vbo) {
	vbo.Clear();
}

template <class Gfx>
void SwGfxT<Gfx>::DeleteElementBuffer(NativeElementBuffer& ebo) {
	ebo.Clear();
}

template <class Gfx>
void SwGfxT<Gfx>::DeleteTexture(NativeColorBufferRef& b) {
	ASSERT(b);
	if (b) {
		delete b;
		b = 0;
	}
	//b.Clear();
}

template <class Gfx>
void SwGfxT<Gfx>::DeleteRenderbuffer(NativeDepthBufferRef& b) {
	ASSERT(b);
	if (b) {
		delete b;
		b = 0;
	}
	//b.Clear();
}

template <class Gfx>
void SwGfxT<Gfx>::DeleteFramebuffer(NativeFrameBufferRef& b) {
	ASSERT(b);
	if (b)
		delete b;
	b = 0;
}

template <class Gfx>
void SwGfxT<Gfx>::DeactivateVertexStructure() {
	// pass
}

template <class Gfx>
void SwGfxT<Gfx>::BeginRenderObject() {
	auto& l = Local();
	ASSERT(l.prog);
	l.prog->BeginObject();
}

template <class Gfx>
void SwGfxT<Gfx>::EndRenderObject() {
	auto& l = Local();
	ASSERT(l.prog);
	l.prog->EndObject();
}

template <class Gfx>
void SwGfxT<Gfx>::BeginRender() {
	auto& l = Local();
	ASSERT_(l.fb, "framebuffer is not bound yet");
	ASSERT_(l.pipe, "pipe is not bound yet");
	ASSERT_(*l.pipe, "pipeline is not inited");
	
	l.pipe->Begin();
	l.rend.SetTarget(*l.pipe, *l.fb);
	l.rend.Begin();
}

template <class Gfx>
void SwGfxT<Gfx>::EndRender() {
	auto& l = Local();
	l.rend.End();
}

template <class Gfx> void SwGfxT<Gfx>::SetupVertexStructure() {}
template <class Gfx> void SwGfxT<Gfx>::ActivateVertexStructure() {}

template <class Gfx> bool SwGfxT<Gfx>::CreateRenderbuffer(NativeDepthBufferRef& b) {
	ASSERT(!b);
	b = new DepthImage();
	return true;
}

template <class Gfx> void SwGfxT<Gfx>::BindRenderbuffer(NativeDepthBufferRef rb) {
	Local().depth = rb;
}

template <class Gfx> void SwGfxT<Gfx>::RenderbufferStorage(Size sz) {
	auto& depth = Local().depth;
	ASSERT(depth);
	if (depth)
		depth->Set(sz, 1);
}

template <class Gfx> void SwGfxT<Gfx>::UnbindRenderbuffer() {
	Local().depth = 0;
}

template <class Gfx> bool SwGfxT<Gfx>::CreateFramebuffer(NativeFrameBufferRef& fb) {
	fb = new SoftFramebuffer;
	return true;
}

template <class Gfx> void SwGfxT<Gfx>::FramebufferTexture2D(TexType tgt, NativeColorBufferRef tex) {
	auto& fb = Local().fb;
	ASSERT(fb);
	ASSERT(tex);
	if (fb && tex)
		fb->SetColor(tgt, tex);
}

template <class Gfx> void SwGfxT<Gfx>::FramebufferRenderbuffer(NativeDepthBufferRef depth) {
	auto& fb = Local().fb;
	ASSERT(fb);
	ASSERT(depth);
	if (fb && depth)
		fb->SetDepth(depth);
}

template <class Gfx> void SwGfxT<Gfx>::UnbindFramebuffer() {
	Local().fb = 0;
}

template <class Gfx>
void SwGfxT<Gfx>::SetTexture(GVar::TextureMode type, Size sz, GVar::Sample sample, int channels, const byte* data) {
	TODO
}

template <class Gfx>
void SwGfxT<Gfx>::SetTexture(GVar::TextureMode type, Size3 sz, GVar::Sample sample, int channels, const byte* data) {
	TODO
}

template <class Gfx>
void SwGfxT<Gfx>::ReadPixels(int x, int y, int w, int h, GVar::Sample sample, int channels, byte* dst) {
	TODO
}

template <class Gfx> void SwGfxT<Gfx>::ClearFramebufferRef(NativeFrameBufferRef& fb) {
	fb = 0;
}

template<class Gfx> void SwGfxT<Gfx>::ClearColorBufferRef(NativeColorBufferRef& b) {
	b = 0;
}

template<class Gfx> void SwGfxT<Gfx>::ClearDepthBufferRef(NativeDepthBufferRef& b) {
	b = 0;
}


#if defined flagSDL2
template struct SwGfxT<SdlSwGfx>;
#endif

#if defined flagPOSIXDESKTOP && defined flagSCREEN
template struct SwGfxT<X11SwGfx>;
#endif


NAMESPACE_PARALLEL_END
