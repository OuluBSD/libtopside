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
	TODO
}

void CpuGfx::BindProgramPipeline(NativePipeline& pipeline) {
	TODO
}

void CpuGfx::UnbindProgramPipeline() {
	TODO
}

void CpuGfx::DrawBuffers(GVar::RenderTarget tgt) {
	TODO
}

/*void CpuGfx::Clear_Color() {
	glClear(GL_COLOR_BUFFER_BIT);
}*/

void CpuGfx::ActiveTexture(int ch) {
	TODO
}

/*void CpuRendererBase::ActivateNextFrame() {
	// pass
}*/

const char* CpuGfx::GetShaderTemplate() {
	static const char* shader_tmpl = "";
	return shader_tmpl;
}

void CpuGfx::HotfixShaderCode(String& s) {}

void CpuGfx::Uniform1i(int idx, int i) {
	auto& shdr = Local().shdr;
	ASSERT(shdr)
	if (shdr) shdr->SetVar(idx, i);
}

void CpuGfx::Uniform1f(int idx, float f) {
	auto& shdr = Local().shdr;
	ASSERT(shdr)
	if (shdr) shdr->SetVar(idx, f);
}

void CpuGfx::Uniform2f(int idx, float f0, float f1) {
	auto& shdr = Local().shdr;
	ASSERT(shdr)
	if (shdr) shdr->SetVar(idx, f0, f1);
}

void CpuGfx::Uniform3f(int idx, float f0, float f1, float f2) {
	auto& shdr = Local().shdr;
	ASSERT(shdr)
	if (shdr) shdr->SetVar(idx, f0, f1, f2);
}

void CpuGfx::Uniform4f(int idx, float f0, float f1, float f2, float f3) {
	auto& shdr = Local().shdr;
	ASSERT(shdr)
	if (shdr) shdr->SetVar(idx, f0, f1, f2, f3);
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

void CpuGfx::TexParameteri(int type, GVar::Filter filter, GVar::Wrap repeat) {
	auto& fb = Local().fb;
	ASSERT(fb);
	if (fb)
		fb->SetParam(type, filter, repeat);
}


NAMESPACE_TOPSIDE_END
