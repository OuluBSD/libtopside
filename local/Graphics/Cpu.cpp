#include "Graphics.h"

NAMESPACE_TOPSIDE_BEGIN



void CpuGfx::SetDebugOutput(bool b) {
	TODO
}

void CpuGfx::ClearBuffers() {
	TODO
}

void CpuGfx::SetSmoothShading(bool b) {
	TODO
}

void CpuGfx::SetDepthTest(bool b) {
	TODO
}

void CpuGfx::SetDepthOrderLess(bool b) {
	TODO
}

void CpuGfx::SetClearValue(RGBA clr, byte depth) {
	TODO
}

void CpuGfx::SetFastPerspectiveCorrection(bool b) {
	TODO
}

void CpuGfx::SetTriangleBacksideCulling(bool b) {
	TODO
}

void CpuGfx::SetTriangleFrontsideCCW(bool b) {
	TODO
}

void CpuGfx::SetViewport(Size sz) {
	TODO
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

void CpuGfx::HotfixShaderCode(String& s) {
	TODO
}

void CpuGfx::Uniform1i(int idx, int f) {
	TODO
}

void CpuGfx::Uniform1f(int idx, float f) {
	TODO
}

void CpuGfx::Uniform2f(int idx, float f0, float f1) {
	TODO
}

void CpuGfx::Uniform3f(int idx, float f0, float f1, float f2) {
	TODO
}

void CpuGfx::Uniform4f(int idx, float f0, float f1, float f2, float f3) {
	TODO
}


NAMESPACE_TOPSIDE_END
