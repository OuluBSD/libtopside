#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN


CpuGfx::Thread& CpuGfx::Local() {thread_local static Thread t; return t;}
SoftRend& CpuGfx::Rend() {return Local().rend;}



void CpuGfx::SetDebugOutput(bool b) {
	Rend().SetDebugOutput(b);
}

void CpuGfx::ClearBuffers() {
	Rend().ClearBuffers();
}

void CpuGfx::SetSmoothShading(bool b) {
	Rend().SetSmoothShading(b);
}

void CpuGfx::SetDepthTest(bool b) {
	Rend().SetDepthTest(b);
}

void CpuGfx::SetDepthOrderLess(bool b) {
	Rend().SetDepthOrderLess(b);
}

void CpuGfx::SetClearValue(RGBA clr, byte depth) {
	Rend().SetClearValue(clr, depth);
}

void CpuGfx::SetFastPerspectiveCorrection(bool b) {
	Rend().SetFastPerspectiveCorrection(b);
}

void CpuGfx::SetTriangleBacksideCulling(bool b) {
	Rend().SetTriangleBacksideCulling(b);
}

void CpuGfx::SetTriangleFrontsideCCW(bool b) {
	Rend().SetTriangleFrontsideCCW(b);
}

void CpuGfx::SetViewport(Size sz) {
	Rend().SetViewport(sz);
}

void CpuGfx::UseProgram(NativeProgram& prog) {
	Local().prog = &prog;
}

void CpuGfx::BindProgramPipeline(NativePipeline& pipeline) {
	Local().pipe = &pipeline;
}

void CpuGfx::UnbindProgramPipeline() {
	Local().pipe = 0;
	Local().prog = 0;
}

void CpuGfx::DrawBuffers(GVar::RenderTarget tgt) {
	TODO
}

/*void CpuGfx::Clear_Color() {
	glClear(GL_COLOR_BUFFER_BIT);
}*/

void CpuGfx::ActiveTexture(int ch) {
	ASSERT(ch >= 0 && ch < CHANNEL_COUNT);
	Local().active_texture = ch;
}

/*void CpuRendererBase::ActivateNextFrame() {
	// pass
}*/

const char* CpuGfx::GetShaderTemplate(GVar::ShaderType t) {
	static const char* shader_tmpl = "";
	return shader_tmpl;
}

void CpuGfx::HotfixShaderCode(String& s) {}

void CpuGfx::Uniform1i(int idx, int i) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, i);
}

void CpuGfx::Uniform1f(int idx, float f) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f);
}

void CpuGfx::Uniform2f(int idx, float f0, float f1) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f0, f1);
}

void CpuGfx::Uniform3f(int idx, float f0, float f1, float f2) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f0, f1, f2);
}

void CpuGfx::Uniform4f(int idx, float f0, float f1, float f2, float f3) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, f0, f1, f2, f3);
}

void CpuGfx::UniformMatrix4fv(int idx, const mat4& mat) {
	auto& prog = Local().prog;
	ASSERT(prog)
	if (prog) prog->SetVar(idx, mat);
}

bool CpuGfx::CreateShader(GVar::ShaderType t, NativeShader& new_shdr) {
	return new_shdr.Create(t);
}

void CpuGfx::ShaderSource(NativeShader& s, String code) {
	s.SetSource(code);
}

bool CpuGfx::CompileShader(NativeShader& s) {
	/*ASSERT(ctx && rt && shdr);
	if (!ctx || !rt || !shdr)
		return false;
	
	if (comp.IsEmpty())
		comp.Create();
	
	return comp->Compile(*ctx, *rt, *shdr, s, s->GetType();*/
	return Local().comp.Compile(s);
}

String CpuGfx::GetLastErrorS(NativeShader& s) {
	return s.GetLastError();
}

String CpuGfx::GetLastErrorP(NativeProgram& p) {
	return p.GetLastError();
}

bool CpuGfx::CreateProgram(NativeProgram& prog) {
	return prog.Create();
}

void CpuGfx::ProgramParameteri(NativeProgram& prog, GVar::ParamType type, int i) {
	prog.SetParameter(type, i);
}

bool CpuGfx::LinkProgram(NativeProgram& prog) {
	return prog.LinkProgram();
}

void CpuGfx::GetProgramiv(NativeProgram& prog, GVar::ProgParamType type, int& out) {
	out = prog.GetParamInt(type);
}

String CpuGfx::GetActiveUniform(NativeProgram& prog, int i, int* size_out, int* type_out) {
	if (size_out)
		*size_out = prog.GetVarSize(i);
	if (type_out)
		*type_out = prog.GetVarType(i);
	
	return prog.GetVar(i);
}

void CpuGfx::Clear(GVar::BufferType type) {
	auto& fb = Local().fb;
	ASSERT(fb);
	if (fb)
		fb->ClearData(type);
}

void CpuGfx::AttachShader(NativeProgram& prog, NativeShader& shdr) {
	prog.Attach(shdr);
}

void CpuGfx::DeleteShader(NativeShader& shdr) {
	shdr.Clear();
}

void CpuGfx::GenProgramPipeline(NativePipeline& pipe) {
	pipe.Create();
}

void CpuGfx::UseProgramStages(NativePipeline& pipe, uint32 bmask, NativeProgram& prog) {
	pipe.Use(prog, bmask);
}

void CpuGfx::DeleteProgramPipeline(NativePipeline& pipe) {
	pipe.Clear();
}

void CpuGfx::TexParameteri(GVar::TextureType type, GVar::Filter filter, GVar::Wrap repeat) {
	auto& fb = Local().fb;
	ASSERT(fb);
	if (fb)
		fb->SetParam(type, filter, repeat);
}

void CpuGfx::BindFramebufferEXT(NativeFrameBuffer& fb) {
	auto& l = Local();
	ASSERT_(!l.fb || (l.ctx_default_fb && l.fb == l.ctx_default_fb), "previous frambuffer have not been unbound");
	l.fb = &fb;
}

void CpuGfx::BindTextureRO(GVar::TextureType type, const NativeFrameBuffer& tex) {
	auto& t = Local().T();
	t.r = &tex;
	t.rw = 0;
}

void CpuGfx::BindTextureRW(GVar::TextureType type, NativeFrameBuffer& tex) {
	auto& t = Local().T();
	t.r = 0;
	t.rw = &tex;
}

void CpuGfx::UnbindTexture(GVar::TextureType type) {
	auto& t = Local().T();
	t.r = 0;
	t.rw = 0;
}

void CpuGfx::GenerateMipmap(GVar::TextureType type) {
	// not supported
}

void CpuGfx::BindFramebufferDefault() {
	Local().fb = Local().ctx_default_fb;
}

void CpuGfx::RenderScreenRect() {
	auto& l = Local();
	ASSERT_(l.fb, "framebuffer is not bound yet");
	//ASSERT_(l.shdr, "shader is not bound yet");
	//ASSERT_(l.prog, "program is not bound yet");
	ASSERT_(l.pipe, "pipe is not bound yet");
	ASSERT_(*l.fb, "framebuffer is not inited");
	ASSERT_(*l.pipe, "pipeline is not inited");
	
	l.rend.RenderScreenRect(*l.pipe, *l.fb);
}

bool CpuGfx::GenTexture(SoftFramebuffer& fb) {
	return fb.Create();
}

void CpuGfx::SetContextDefaultFramebuffer(NativeFrameBuffer& fb) {
	auto& l = Local();
	l.ctx_default_fb = &fb;
	if (!l.fb)
		l.fb = &fb;
}

void CpuGfx::GenVertexArray(NativeVertexArray& va) {
	va.Create();
}

void CpuGfx::GenVertexBuffer(NativeVertexBuffer& vb) {
	vb.Create();
}

void CpuGfx::GenElementBuffer(NativeElementBuffer& eb) {
	eb.Create();
}

void CpuGfx::BindVertexArray(NativeVertexArray& vao) {
	Local().vao = &vao;
}

void CpuGfx::BindVertexBuffer(NativeVertexBuffer& vbo) {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->vbo = &vbo;
}

void CpuGfx::VertexBufferData(const Vector<Vertex>& vtx) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->vbo);
	l.vao->vbo->vertices <<= vtx;
}

void CpuGfx::BindElementBuffer(NativeElementBuffer& ebo) {
	auto& l = Local();
	ASSERT(l.vao);
	l.vao->ebo = &ebo;
}

void CpuGfx::ElementBufferData(const Vector<uint32>& el) {
	auto& l = Local();
	ASSERT(l.vao);
	ASSERT(l.vao->ebo);
	l.vao->ebo->indices <<= el;
}

void CpuGfx::UnbindVertexArray() {
	Local().vao = 0;
}

void CpuGfx::DrawVertexElements(int element_limit) {
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
	
	l.rend.Render(*l.pipe, *l.fb, *l.vao);
}

void CpuGfx::TexImage2D(Texture& tex) {
	auto& t = Local().T();
	ASSERT(!t.r);
	ASSERT(t.rw);
	*t.rw = &tex;
}

void CpuGfx::DeleteVertexArray(NativeVertexArray& vao) {
	vao.Clear();
}

void CpuGfx::DeleteVertexBuffer(NativeVertexBuffer& vbo) {
	vbo.Clear();
}

void CpuGfx::DeleteElementBuffer(NativeElementBuffer& ebo) {
	ebo.Clear();
}

void CpuGfx::DeleteTexture(NativeColorBuffer& b) {
	b.Clear();
}


NAMESPACE_TOPSIDE_END
