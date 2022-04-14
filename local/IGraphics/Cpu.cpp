#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN





template <class B>
typename CpuGfxT<B>::Thread& CpuGfxT<B>::Local() {thread_local static Thread t; return t;}

template <class B>
SoftRendT<B>& CpuGfxT<B>::Rend() {return Local().rend;}



template <class B>
void CpuGfxT<B>::SetDebugOutput(bool b) {
	Rend().SetDebugOutput(b);
}

template <class B>
void CpuGfxT<B>::ClearBuffers() {
	Rend().ClearBuffers();
}

template <class B>
void CpuGfxT<B>::SetSmoothShading(bool b) {
	Rend().SetSmoothShading(b);
}

template <class B>
void CpuGfxT<B>::SetDepthTest(bool b) {
	Rend().SetDepthTest(b);
}

template <class B>
void CpuGfxT<B>::SetDepthOrderLess(bool b) {
	Rend().SetDepthOrderLess(b);
}

template <class B>
void CpuGfxT<B>::SetClearValue(RGBA clr, byte depth) {
	Rend().SetClearValue(clr, depth);
}

template <class B>
void CpuGfxT<B>::SetFastPerspectiveCorrection(bool b) {
	Rend().SetFastPerspectiveCorrection(b);
}

template <class B>
void CpuGfxT<B>::SetTriangleBacksideCulling(bool b) {
	Rend().SetTriangleBacksideCulling(b);
}

template <class B>
void CpuGfxT<B>::SetTriangleFrontsideCCW(bool b) {
	Rend().SetTriangleFrontsideCCW(b);
}

template <class B>
void CpuGfxT<B>::SetViewport(Size sz) {
	Rend().SetViewport(sz);
}

template <class B>
void CpuGfxT<B>::UseProgram(NativeProgram& prog) {
	Local().prog = &prog;
}

template <class B>
void CpuGfxT<B>::BindProgramPipeline(NativePipeline& pipeline) {
	Local().pipe = &pipeline;
}

template <class B>
void CpuGfxT<B>::UnbindProgramPipeline() {
	Local().pipe = 0;
	Local().prog = 0;
}

template <class B>
void CpuGfxT<B>::DrawBuffers(GVar::RenderTarget tgt) {
	TODO
}

/*void CpuGfxT<B>::Clear_Color() {
	glClear(GL_COLOR_BUFFER_BIT);
}*/

template <class B>
void CpuGfxT<B>::ActiveTexture(int ch) {
	ASSERT(ch >= 0 && ch < CHANNEL_COUNT);
	Local().active_texture = ch;
}

/*void CpuRendererBase::ActivateNextFrame() {
	// pass
}*/

template <class B>
const char* CpuGfxT<B>::GetShaderTemplate(GVar::ShaderType t) {
	static const char* shader_tmpl = "";
	return shader_tmpl;
}

template <class B>
void CpuGfxT<B>::HotfixShaderCode(String& s) {}

template <class B>
void CpuGfxT<B>::Uniform1i(int idx, int i) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, i);
}

template <class B>
void CpuGfxT<B>::Uniform1f(int idx, float f) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f);
}

template <class B>
void CpuGfxT<B>::Uniform2f(int idx, float f0, float f1) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f0, f1);
}

template <class B>
void CpuGfxT<B>::Uniform3f(int idx, float f0, float f1, float f2) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f0, f1, f2);
}

template <class B>
void CpuGfxT<B>::Uniform4f(int idx, float f0, float f1, float f2, float f3) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f0, f1, f2, f3);
}

template <class B>
void CpuGfxT<B>::UniformMatrix4fv(int idx, const mat4& mat) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, mat);
}

template <class B>
bool CpuGfxT<B>::CreateShader(GVar::ShaderType t, NativeShader& new_shdr) {
	return new_shdr.Create(t);
}

template <class B>
void CpuGfxT<B>::ShaderSource(NativeShader& s, String code) {
	s.SetSource(code);
}

template <class B>
bool CpuGfxT<B>::CompileShader(NativeShader& s) {
	/*ASSERT(ctx && rt && shdr);
	if (!ctx || !rt || !shdr)
		return false;
	
	if (comp.IsEmpty())
		comp.Create();
	
	return comp->Compile(*ctx, *rt, *shdr, s, s->GetType();*/
	return Local().comp.Compile(s);
}

template <class B>
String CpuGfxT<B>::GetLastErrorS(NativeShader& s) {
	return s.GetLastError();
}

template <class B>
String CpuGfxT<B>::GetLastErrorP(NativeProgram& p) {
	return p.GetLastError();
}

template <class B>
bool CpuGfxT<B>::CreateProgram(NativeProgram& prog) {
	return prog.Create();
}

template <class B>
void CpuGfxT<B>::ProgramParameteri(NativeProgram& prog, GVar::ParamType type, int i) {
	prog.SetParameter(type, i);
}

template <class B>
bool CpuGfxT<B>::LinkProgram(NativeProgram& prog) {
	return prog.LinkProgram();
}

template <class B>
void CpuGfxT<B>::GetProgramiv(NativeProgram& prog, GVar::ProgParamType type, int& out) {
	out = prog.GetParamInt(type);
}

template <class B>
String CpuGfxT<B>::GetActiveUniform(NativeProgram& prog, int i, int* size_out, int* type_out) {
	if (size_out)
		*size_out = prog.GetVarSize(i);
	if (type_out)
		*type_out = prog.GetVarType(i);
	
	return prog.GetVar(i);
}

template <class B>
void CpuGfxT<B>::Clear(GVar::BufferType type) {
	auto& fb = Local().fb;
	ASSERT(fb);
	if (fb)
		fb->ClearData(type);
}

template <class B>
void CpuGfxT<B>::AttachShader(NativeProgram& prog, NativeShader& shdr) {
	prog.Attach(shdr);
}

template <class B>
void CpuGfxT<B>::DeleteShader(NativeShader& shdr) {
	shdr.Clear();
}

template <class B>
void CpuGfxT<B>::GenProgramPipeline(NativePipeline& pipe) {
	pipe.Create();
}

template <class B>
void CpuGfxT<B>::UseProgramStages(NativePipeline& pipe, uint32 bmask, NativeProgram& prog) {
	pipe.Use(prog, bmask);
}

template <class B>
void CpuGfxT<B>::DeleteProgramPipeline(NativePipeline& pipe) {
	pipe.Clear();
}

template <class B>
void CpuGfxT<B>::TexParameteri(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat) {
	auto& fb = Local().fb;
	ASSERT(fb);
	if (fb)
		fb->SetParam(type, filter, repeat);
}

template <class B>
void CpuGfxT<B>::BindFramebuffer(NativeFrameBuffer& fb) {
	auto& l = Local();
	ASSERT_(!l.fb || (l.ctx_default_fb && l.fb == l.ctx_default_fb), "previous frambuffer have not been unbound");
	l.fb = &fb;
}

template <class B>
void CpuGfxT<B>::BindTextureRO(GVar::TextureType type, const NativeFrameBuffer& tex) {
	auto& t = Local().T();
	t.r = &tex;
	t.rw = 0;
}

template <class B>
void CpuGfxT<B>::BindTextureRW(GVar::TextureType type, NativeFrameBuffer& tex) {
	auto& t = Local().T();
	t.r = 0;
	t.rw = &tex;
}

template <class B>
void CpuGfxT<B>::UnbindTexture(GVar::TextureType type) {
	auto& t = Local().T();
	t.r = 0;
	t.rw = 0;
}

template <class B>
void CpuGfxT<B>::GenerateMipmap(GVar::TextureType type) {
	// not supported
}

template <class B>
void CpuGfxT<B>::BindFramebufferDefault() {
	Local().fb = Local().ctx_default_fb;
}

template <class B>
void CpuGfxT<B>::RenderScreenRect() {
	auto& l = Local();
	ASSERT_(l.fb, "framebuffer is not bound yet");
	//ASSERT_(l.shdr, "shader is not bound yet");
	//ASSERT_(l.prog, "program is not bound yet");
	ASSERT_(l.pipe, "pipe is not bound yet");
	ASSERT_(*l.fb, "framebuffer is not inited");
	ASSERT_(*l.pipe, "pipeline is not inited");
	
	l.rend.SetTarget(*l.pipe, *l.fb);
	l.rend.Begin();
	l.rend.RenderScreenRect();
	l.rend.End();
}

template <class B>
bool CpuGfxT<B>::GenTexture(SoftFramebuffer& fb) {
	return fb.Create();
}

template <class B>
void CpuGfxT<B>::SetContextDefaultFramebuffer(NativeFrameBuffer& fb) {
	auto& l = Local();
	l.ctx_default_fb = &fb;
	if (!l.fb)
		l.fb = &fb;
}

template <class B>
void CpuGfxT<B>::GenVertexArray(NativeVertexArray& va) {
	va.Create();
}

template <class B>
void CpuGfxT<B>::GenVertexBuffer(NativeVertexBuffer& vb) {
	vb.Create();
}

template <class B>
void CpuGfxT<B>::GenElementBuffer(NativeElementBuffer& eb) {
	eb.Create();
}

template <class B>
void CpuGfxT<B>::BindVertexArray(NativeVertexArray& vao) {
	Local().vao = &vao;
}

template <class B>
void CpuGfxT<B>::BindVertexBuffer(NativeVertexBuffer& vbo) {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->vbo = &vbo;
}

template <class B>
void CpuGfxT<B>::VertexBufferData(const Vector<Vertex>& vtx) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->vbo);
	l.vao->vbo->vertices <<= vtx;
}

template <class B>
void CpuGfxT<B>::BindElementBuffer(NativeElementBuffer& ebo) {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->ebo = &ebo;
}

template <class B>
void CpuGfxT<B>::ElementBufferData(const Vector<uint32>& el) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->ebo);
	l.vao->ebo->indices <<= el;
}

template <class B>
void CpuGfxT<B>::UnbindVertexArray() {
	Local().vao = 0;
}

template <class B>
void CpuGfxT<B>::UnbindVertexBuffer() {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->vbo = 0;
}

template <class B>
void CpuGfxT<B>::UnbindElementBuffer() {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->ebo = 0;
}

template <class B>
void CpuGfxT<B>::DrawVertexElements(int element_limit) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->vbo);
	ASSERT(l.vao->ebo);
	ASSERT_(l.fb, "framebuffer is not bound yet");
	ASSERT_(l.pipe, "pipe is not bound yet");
	ASSERT_(*l.fb, "framebuffer is not inited");
	ASSERT_(*l.pipe, "pipeline is not inited");
	
	for(int i = 0; i < TEXTYPE_COUNT; i++)
		l.rend.BindTexture(i, l.texture[i].GetReadTexture());
	
	l.rend.Render(*l.vao);
}

template <class B>
void CpuGfxT<B>::TexImage2D(Texture& tex) {
	auto& t = Local().T();
	ASSERT(!t.r);
	ASSERT(t.rw);
	*t.rw = &tex;
}

template <class B>
void CpuGfxT<B>::DeleteVertexArray(NativeVertexArray& vao) {
	vao.Clear();
}

template <class B>
void CpuGfxT<B>::DeleteVertexBuffer(NativeVertexBuffer& vbo) {
	vbo.Clear();
}

template <class B>
void CpuGfxT<B>::DeleteElementBuffer(NativeElementBuffer& ebo) {
	ebo.Clear();
}

template <class B>
void CpuGfxT<B>::DeleteTexture(NativeColorBuffer& b) {
	b.Clear();
}

template <class B>
void CpuGfxT<B>::DeleteRenderbuffer(NativeDepthBuffer& b) {
	b.Clear();
}

template <class B>
void CpuGfxT<B>::DeleteFramebuffer(NativeFrameBuffer& b) {
	b.Clear();
}

template <class B>
void CpuGfxT<B>::DeactivateVertexStructure() {
	// pass
}

template <class B>
void CpuGfxT<B>::BeginRender() {
	auto& l = Local();
	ASSERT_(l.fb, "framebuffer is not bound yet");
	ASSERT_(l.pipe, "pipe is not bound yet");
	ASSERT_(*l.fb, "framebuffer is not inited");
	ASSERT_(*l.pipe, "pipeline is not inited");
	
	l.rend.SetTarget(*l.pipe, *l.fb);
	l.rend.Begin();
}

template <class B>
void CpuGfxT<B>::EndRender() {
	auto& l = Local();
	l.rend.End();
}

template <class B> void CpuGfxT<B>::SetupVertexStructure() {}
template <class B> void CpuGfxT<B>::ActivateVertexStructure() {}

template <class B> void CpuGfxT<B>::CreateRenderbuffer(NativeDepthBuffer& b) {
	TODO
}

template <class B> void CpuGfxT<B>::BindRenderbuffer(NativeDepthBuffer& rb) {
	TODO
}

template <class B> void CpuGfxT<B>::RenderbufferStorage(Size sz) {
	TODO
}

template <class B> void CpuGfxT<B>::UnbindRenderbuffer() {
	TODO
}

template <class B> bool CpuGfxT<B>::CreateFramebuffer(NativeFrameBuffer& fb) {
	TODO
	return true;
}

template <class B> void CpuGfxT<B>::FramebufferTexture2D(NativeFrameBuffer& fb) {
	TODO
}

template <class B> void CpuGfxT<B>::FramebufferRenderbuffer(NativeDepthBuffer& fb) {
	TODO
}

template <class B> void CpuGfxT<B>::UnbindFramebuffer() {
	TODO
}

#if defined flagSDL2
template struct CpuGfxT<Sdl>;
#endif

template struct CpuGfxT<X11Sw>;


NAMESPACE_PARALLEL_END
