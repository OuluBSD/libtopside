#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN





template <class Gfx>
typename CpuGfxT<Gfx>::Thread& CpuGfxT<Gfx>::Local() {thread_local static Thread t; return t;}

template <class Gfx>
SoftRendT<Gfx>& CpuGfxT<Gfx>::Rend() {return Local().rend;}



template <class Gfx>
void CpuGfxT<Gfx>::SetDebugOutput(bool b) {
	Rend().SetDebugOutput(b);
}

template <class Gfx>
void CpuGfxT<Gfx>::ClearBuffers() {
	Rend().ClearBuffers();
}

template <class Gfx>
void CpuGfxT<Gfx>::SetSmoothShading(bool b) {
	Rend().SetSmoothShading(b);
}

template <class Gfx>
void CpuGfxT<Gfx>::SetDepthTest(bool b) {
	Rend().SetDepthTest(b);
}

template <class Gfx>
void CpuGfxT<Gfx>::SetDepthOrderLess(bool b) {
	Rend().SetDepthOrderLess(b);
}

template <class Gfx>
void CpuGfxT<Gfx>::SetClearValue(RGBA clr, byte depth) {
	Rend().SetClearValue(clr, depth);
}

template <class Gfx>
void CpuGfxT<Gfx>::SetFastPerspectiveCorrection(bool b) {
	Rend().SetFastPerspectiveCorrection(b);
}

template <class Gfx>
void CpuGfxT<Gfx>::SetTriangleBacksideCulling(bool b) {
	Rend().SetTriangleBacksideCulling(b);
}

template <class Gfx>
void CpuGfxT<Gfx>::SetTriangleFrontsideCCW(bool b) {
	Rend().SetTriangleFrontsideCCW(b);
}

template <class Gfx>
void CpuGfxT<Gfx>::SetViewport(Size sz) {
	Rend().SetViewport(sz);
}

template <class Gfx>
void CpuGfxT<Gfx>::UseProgram(NativeProgram& prog) {
	Local().prog = &prog;
}

template <class Gfx>
void CpuGfxT<Gfx>::BindProgramPipeline(NativePipeline& pipeline) {
	Local().pipe = &pipeline;
}

template <class Gfx>
void CpuGfxT<Gfx>::UnbindProgramPipeline() {
	Local().pipe = 0;
	Local().prog = 0;
}

template <class Gfx>
void CpuGfxT<Gfx>::DrawBuffers(GVar::RenderTarget tgt) {
	TODO
}

/*void CpuGfxT<Gfx>::Clear_Color() {
	glClear(GL_COLOR_BUFFER_BIT);
}*/

template <class Gfx>
void CpuGfxT<Gfx>::ActiveTexture(int ch) {
	ASSERT(ch >= 0 && ch < CHANNEL_COUNT);
	Local().active_texture = ch;
}

/*void CpuRendererBase::ActivateNextFrame() {
	// pass
}*/

template <class Gfx>
const char* CpuGfxT<Gfx>::GetShaderTemplate(GVar::ShaderType t) {
	static const char* shader_tmpl = "";
	return shader_tmpl;
}

template <class Gfx>
void CpuGfxT<Gfx>::HotfixShaderCode(String& s) {}

template <class Gfx>
void CpuGfxT<Gfx>::Uniform1i(int idx, int i) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, i);
}

template <class Gfx>
void CpuGfxT<Gfx>::Uniform1f(int idx, float f) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f);
}

template <class Gfx>
void CpuGfxT<Gfx>::Uniform2f(int idx, float f0, float f1) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f0, f1);
}

template <class Gfx>
void CpuGfxT<Gfx>::Uniform3f(int idx, float f0, float f1, float f2) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f0, f1, f2);
}

template <class Gfx>
void CpuGfxT<Gfx>::Uniform4f(int idx, float f0, float f1, float f2, float f3) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f0, f1, f2, f3);
}

template <class Gfx>
void CpuGfxT<Gfx>::UniformMatrix4fv(int idx, const mat4& mat) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, mat);
}

template <class Gfx>
bool CpuGfxT<Gfx>::CreateShader(GVar::ShaderType t, NativeShader& new_shdr) {
	return new_shdr.Create(t);
}

template <class Gfx>
void CpuGfxT<Gfx>::ShaderSource(NativeShader& s, String code) {
	s.SetSource(code);
}

template <class Gfx>
bool CpuGfxT<Gfx>::CompileShader(NativeShader& s) {
	/*ASSERT(ctx && rt && shdr);
	if (!ctx || !rt || !shdr)
		return false;
	
	if (comp.IsEmpty())
		comp.Create();
	
	return comp->Compile(*ctx, *rt, *shdr, s, s->GetType();*/
	return Local().comp.Compile(s);
}

template <class Gfx>
String CpuGfxT<Gfx>::GetLastErrorS(NativeShader& s) {
	return s.GetLastError();
}

template <class Gfx>
String CpuGfxT<Gfx>::GetLastErrorP(NativeProgram& p) {
	return p.GetLastError();
}

template <class Gfx>
bool CpuGfxT<Gfx>::CreateProgram(NativeProgram& prog) {
	return prog.Create();
}

template <class Gfx>
void CpuGfxT<Gfx>::ProgramParameteri(NativeProgram& prog, GVar::ParamType type, int i) {
	prog.SetParameter(type, i);
}

template <class Gfx>
bool CpuGfxT<Gfx>::LinkProgram(NativeProgram& prog) {
	return prog.LinkProgram();
}

template <class Gfx>
void CpuGfxT<Gfx>::GetProgramiv(NativeProgram& prog, GVar::ProgParamType type, int& out) {
	out = prog.GetParamInt(type);
}

template <class Gfx>
String CpuGfxT<Gfx>::GetActiveUniform(NativeProgram& prog, int i, int* size_out, int* type_out) {
	if (size_out)
		*size_out = prog.GetVarSize(i);
	if (type_out)
		*type_out = prog.GetVarType(i);
	
	return prog.GetVar(i);
}

template <class Gfx>
void CpuGfxT<Gfx>::Clear(GVar::BufferType type) {
	auto& fb = Local().fb;
	ASSERT(fb);
	if (fb)
		fb->ClearData(type);
}

template <class Gfx>
void CpuGfxT<Gfx>::AttachShader(NativeProgram& prog, NativeShader& shdr) {
	prog.Attach(shdr);
}

template <class Gfx>
void CpuGfxT<Gfx>::DeleteShader(NativeShader& shdr) {
	shdr.Clear();
}

template <class Gfx>
void CpuGfxT<Gfx>::GenProgramPipeline(NativePipeline& pipe) {
	pipe.Create();
}

template <class Gfx>
void CpuGfxT<Gfx>::UseProgramStages(NativePipeline& pipe, uint32 bmask, NativeProgram& prog) {
	pipe.Use(prog, bmask);
}

template <class Gfx>
void CpuGfxT<Gfx>::DeleteProgramPipeline(NativePipeline& pipe) {
	pipe.Clear();
}

template <class Gfx>
void CpuGfxT<Gfx>::TexParameteri(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat) {
	auto& fb = Local().fb;
	ASSERT(fb);
	if (fb)
		fb->SetParam(type, filter, repeat);
}

template <class Gfx>
void CpuGfxT<Gfx>::BindFramebuffer(NativeFrameBuffer& fb) {
	auto& l = Local();
	ASSERT_(!l.fb || (l.ctx_default_fb && l.fb == l.ctx_default_fb), "previous frambuffer have not been unbound");
	l.fb = &fb;
}

template <class Gfx>
void CpuGfxT<Gfx>::BindTextureRO(GVar::TextureType type, const NativeFrameBuffer& tex) {
	auto& t = Local().T();
	t.r = &tex;
	t.rw = 0;
}

template <class Gfx>
void CpuGfxT<Gfx>::BindTextureRW(GVar::TextureType type, NativeFrameBuffer& tex) {
	auto& t = Local().T();
	t.r = 0;
	t.rw = &tex;
}

template <class Gfx>
void CpuGfxT<Gfx>::UnbindTexture(GVar::TextureType type) {
	auto& t = Local().T();
	t.r = 0;
	t.rw = 0;
}

template <class Gfx>
void CpuGfxT<Gfx>::GenerateMipmap(GVar::TextureType type) {
	// not supported
}

template <class Gfx>
void CpuGfxT<Gfx>::BindFramebufferDefault() {
	Local().fb = Local().ctx_default_fb;
}

template <class Gfx>
void CpuGfxT<Gfx>::RenderScreenRect() {
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

template <class Gfx>
bool CpuGfxT<Gfx>::GenTexture(SoftFramebuffer& fb) {
	return fb.Create();
}

template <class Gfx>
void CpuGfxT<Gfx>::SetContextDefaultFramebuffer(NativeFrameBuffer& fb) {
	auto& l = Local();
	l.ctx_default_fb = &fb;
	if (!l.fb)
		l.fb = &fb;
}

template <class Gfx>
void CpuGfxT<Gfx>::GenVertexArray(NativeVertexArray& va) {
	va.Create();
}

template <class Gfx>
void CpuGfxT<Gfx>::GenVertexBuffer(NativeVertexBuffer& vb) {
	vb.Create();
}

template <class Gfx>
void CpuGfxT<Gfx>::GenElementBuffer(NativeElementBuffer& eb) {
	eb.Create();
}

template <class Gfx>
void CpuGfxT<Gfx>::BindVertexArray(NativeVertexArray& vao) {
	Local().vao = &vao;
}

template <class Gfx>
void CpuGfxT<Gfx>::BindVertexBuffer(NativeVertexBuffer& vbo) {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->vbo = &vbo;
}

template <class Gfx>
void CpuGfxT<Gfx>::VertexBufferData(const Vector<Vertex>& vtx) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->vbo);
	l.vao->vbo->vertices <<= vtx;
}

template <class Gfx>
void CpuGfxT<Gfx>::BindElementBuffer(NativeElementBuffer& ebo) {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->ebo = &ebo;
}

template <class Gfx>
void CpuGfxT<Gfx>::ElementBufferData(const Vector<uint32>& el) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->ebo);
	l.vao->ebo->indices <<= el;
}

template <class Gfx>
void CpuGfxT<Gfx>::UnbindVertexArray() {
	Local().vao = 0;
}

template <class Gfx>
void CpuGfxT<Gfx>::UnbindVertexBuffer() {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->vbo = 0;
}

template <class Gfx>
void CpuGfxT<Gfx>::UnbindElementBuffer() {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->ebo = 0;
}

template <class Gfx>
void CpuGfxT<Gfx>::DrawVertexElements(int element_limit) {
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

template <class Gfx>
void CpuGfxT<Gfx>::TexImage2D(Texture& tex) {
	auto& t = Local().T();
	ASSERT(!t.r);
	ASSERT(t.rw);
	//*t.rw = &tex;
	t.rw->SetTexture(&tex);
}

template <class Gfx>
void CpuGfxT<Gfx>::DeleteVertexArray(NativeVertexArray& vao) {
	vao.Clear();
}

template <class Gfx>
void CpuGfxT<Gfx>::DeleteVertexBuffer(NativeVertexBuffer& vbo) {
	vbo.Clear();
}

template <class Gfx>
void CpuGfxT<Gfx>::DeleteElementBuffer(NativeElementBuffer& ebo) {
	ebo.Clear();
}

template <class Gfx>
void CpuGfxT<Gfx>::DeleteTexture(NativeColorBuffer& b) {
	b.Clear();
}

template <class Gfx>
void CpuGfxT<Gfx>::DeleteRenderbuffer(NativeDepthBuffer& b) {
	b.Clear();
}

template <class Gfx>
void CpuGfxT<Gfx>::DeleteFramebuffer(NativeFrameBuffer& b) {
	b.Clear();
}

template <class Gfx>
void CpuGfxT<Gfx>::DeactivateVertexStructure() {
	// pass
}

template <class Gfx>
void CpuGfxT<Gfx>::BeginRender() {
	auto& l = Local();
	ASSERT_(l.fb, "framebuffer is not bound yet");
	ASSERT_(l.pipe, "pipe is not bound yet");
	ASSERT_(*l.fb, "framebuffer is not inited");
	ASSERT_(*l.pipe, "pipeline is not inited");
	
	l.rend.SetTarget(*l.pipe, *l.fb);
	l.rend.Begin();
}

template <class Gfx>
void CpuGfxT<Gfx>::EndRender() {
	auto& l = Local();
	l.rend.End();
}

template <class Gfx> void CpuGfxT<Gfx>::SetupVertexStructure() {}
template <class Gfx> void CpuGfxT<Gfx>::ActivateVertexStructure() {}

template <class Gfx> void CpuGfxT<Gfx>::CreateRenderbuffer(NativeDepthBuffer& b) {
	TODO
}

template <class Gfx> void CpuGfxT<Gfx>::BindRenderbuffer(NativeDepthBuffer& rb) {
	TODO
}

template <class Gfx> void CpuGfxT<Gfx>::RenderbufferStorage(Size sz) {
	TODO
}

template <class Gfx> void CpuGfxT<Gfx>::UnbindRenderbuffer() {
	TODO
}

template <class Gfx> bool CpuGfxT<Gfx>::CreateFramebuffer(NativeFrameBuffer& fb) {
	TODO
	return true;
}

template <class Gfx> void CpuGfxT<Gfx>::FramebufferTexture2D(NativeFrameBuffer& fb) {
	TODO
}

template <class Gfx> void CpuGfxT<Gfx>::FramebufferRenderbuffer(NativeDepthBuffer& fb) {
	TODO
}

template <class Gfx> void CpuGfxT<Gfx>::UnbindFramebuffer() {
	TODO
}

#if defined flagSDL2
template struct CpuGfxT<SdlCpuGfx>;
#endif

template struct CpuGfxT<X11SwGfx>;


NAMESPACE_PARALLEL_END
