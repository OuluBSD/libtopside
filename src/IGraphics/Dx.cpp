#include "IGraphics.h"

#ifdef flagDX11

NAMESPACE_PARALLEL_BEGIN


template<class Gfx> void D11GfxT<Gfx>::BindProgramPipeline(NativePipeline& pipeline) {TODO}
template<class Gfx> void D11GfxT<Gfx>::UseProgram(NativeProgram& prog) {TODO}
//template<class Gfx> void D11GfxT<Gfx>::EnterFramebuffer(NativeFrameBuffer& fb) {TODO}
template<class Gfx> void D11GfxT<Gfx>::FramebufferTexture2D(TexType tgt, NativeColorBufferRef b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::FramebufferRenderbuffer(NativeDepthBufferRef fb) {TODO}
template<class Gfx> void D11GfxT<Gfx>::BindFramebuffer(NativeFrameBufferRef fb) {TODO}
template<class Gfx> void D11GfxT<Gfx>::BindFramebufferRO(NativeFrameBufferConstRef fb) {TODO}
template<class Gfx> void D11GfxT<Gfx>::BindRenderbuffer(NativeDepthBufferRef rb) {TODO}
template<class Gfx> void D11GfxT<Gfx>::UnbindRenderbuffer() {TODO}
template<class Gfx> void D11GfxT<Gfx>::RenderbufferStorage(Size sz) {TODO}
template<class Gfx> void D11GfxT<Gfx>::UnbindProgramPipeline() {TODO}
template<class Gfx> void D11GfxT<Gfx>::BindFramebufferDefault() {TODO}
template<class Gfx> void D11GfxT<Gfx>::DrawBuffers(GVar::RenderTarget tgt) {TODO}
//template<class Gfx> void D11GfxT<Gfx>::SetRender_Color() {TODO}
template<class Gfx> void D11GfxT<Gfx>::RenderScreenRect() {TODO}
template<class Gfx> String D11GfxT<Gfx>::GetShaderTemplate(GVar::ShaderType t) {TODO}
template<class Gfx> void D11GfxT<Gfx>::HotfixShaderCode(String& s) {TODO}
template<class Gfx> void D11GfxT<Gfx>::ActiveTexture(int ch) {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeactivateTexture() {TODO}
template<class Gfx> void D11GfxT<Gfx>::BindTextureRO(GVar::TextureMode type, NativeColorBufferConstRef tex) {TODO}
template<class Gfx> void D11GfxT<Gfx>::BindTextureRW(GVar::TextureMode type, NativeColorBufferRef tex) {TODO}
template<class Gfx> void D11GfxT<Gfx>::ReserveTexture(GVar::TextureMode type, FramebufferT<Gfx>& fb) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetTexture(GVar::TextureMode type, Size sz, GVar::Sample sample, int ch, const byte* data) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetTexture(GVar::TextureMode type, Size3 sz, GVar::Sample sample, int ch, const byte* data) {TODO}
template<class Gfx> void D11GfxT<Gfx>::UnbindTexture(GVar::TextureMode type) {TODO}
template<class Gfx> void D11GfxT<Gfx>::GenerateMipmap(GVar::TextureMode type) {TODO}
template<class Gfx> bool D11GfxT<Gfx>::CreateShader(GVar::ShaderType t, NativeShaderRef& new_shdr) {TODO}
template<class Gfx> void D11GfxT<Gfx>::ShaderSource(NativeShaderRef s, String code) {TODO}
template<class Gfx> bool D11GfxT<Gfx>::CompileShader(NativeShaderRef s) {TODO}
template<class Gfx> String D11GfxT<Gfx>::GetLastErrorS(NativeShaderRef s) {TODO}
template<class Gfx> String D11GfxT<Gfx>::GetLastErrorP(NativeProgram& s) {TODO}
template<class Gfx> bool D11GfxT<Gfx>::CreateProgram(NativeProgram& prog) {TODO}
template<class Gfx> bool D11GfxT<Gfx>::CreateRenderbuffer(NativeDepthBufferRef& b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::ProgramParameteri(NativeProgram& prog, GVar::ParamType type, int i) {TODO}
template<class Gfx> void D11GfxT<Gfx>::AttachShader(NativeProgram& prog, NativeShaderRef shdr) {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeleteShader(NativeShaderRef& shdr) {TODO}
template<class Gfx> bool D11GfxT<Gfx>::LinkProgram(NativeProgram& prog) {TODO}
template<class Gfx> void D11GfxT<Gfx>::GetProgramiv(NativeProgram& prog, GVar::ProgParamType type, int& out) {TODO}
template<class Gfx> String D11GfxT<Gfx>::GetActiveUniform(NativeProgram& prog, int i, int* size_out, int* type_out) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Clear(GVar::BufferType type) {TODO}
template<class Gfx> void D11GfxT<Gfx>::GenProgramPipeline(NativePipeline& pipe) {TODO}
template<class Gfx> void D11GfxT<Gfx>::UseProgramStages(NativePipeline& pipe, uint32 shader_type_bmask, NativeProgram& prog) {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeleteProgramPipeline(NativePipeline& pipe) {TODO}
template<class Gfx> void D11GfxT<Gfx>::TexParameteri(GVar::TextureMode type, GVar::Filter filter, GVar::Wrap repeat) {TODO}
template<class Gfx> bool D11GfxT<Gfx>::GenTexture(NativeColorBufferRef& fb) {TODO}
template<class Gfx> bool D11GfxT<Gfx>::CreateFramebuffer(NativeFrameBufferRef& fb) {TODO}
template<class Gfx> void D11GfxT<Gfx>::GenVertexArray(NativeVertexArray& vao) {TODO}
template<class Gfx> void D11GfxT<Gfx>::GenVertexBuffer(NativeVertexBuffer& vbo) {TODO}
template<class Gfx> void D11GfxT<Gfx>::GenElementBuffer(NativeElementBuffer& ebo) {TODO}
template<class Gfx> void D11GfxT<Gfx>::BindVertexArray(NativeVertexArray& vao) {TODO}
template<class Gfx> void D11GfxT<Gfx>::BindVertexBuffer(NativeVertexBuffer& vbo) {TODO}
template<class Gfx> void D11GfxT<Gfx>::BindElementBuffer(NativeElementBuffer& ebo) {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeleteVertexArray(NativeVertexArray& vao) {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeleteVertexBuffer(NativeVertexBuffer& vbo) {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeleteElementBuffer(NativeElementBuffer& ebo) {TODO}
template<class Gfx> void D11GfxT<Gfx>::VertexBufferData(const Vector<Vertex>& vtx) {TODO}
template<class Gfx> void D11GfxT<Gfx>::ElementBufferData(const Vector<uint32>& el) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetupVertexStructure() {TODO}
template<class Gfx> void D11GfxT<Gfx>::UnbindVertexArray() {TODO}
template<class Gfx> void D11GfxT<Gfx>::UnbindVertexBuffer() {TODO}
template<class Gfx> void D11GfxT<Gfx>::UnbindElementBuffer() {TODO}
template<class Gfx> void D11GfxT<Gfx>::UnbindFramebuffer() {TODO}
template<class Gfx> void D11GfxT<Gfx>::ActivateVertexStructure() {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeactivateVertexStructure() {TODO}
template<class Gfx> void D11GfxT<Gfx>::DrawVertexElements(int element_limit, bool use_quad) {TODO}
template<class Gfx> void D11GfxT<Gfx>::TexImage2D(ByteImage& tex) {TODO}
template<class Gfx> void D11GfxT<Gfx>::TexImage2D(FloatImage& tex) {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeleteTexture(NativeColorBufferRef& b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeleteRenderbuffer(NativeDepthBufferRef& b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::DeleteFramebuffer(NativeFrameBufferRef& b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetContextDefaultFramebuffer(NativeFrameBufferRef fb) {TODO}
template<class Gfx> void D11GfxT<Gfx>::BeginRender() {TODO}
template<class Gfx> void D11GfxT<Gfx>::EndRender() {TODO}
template<class Gfx> void D11GfxT<Gfx>::BeginRenderObject() {TODO}
template<class Gfx> void D11GfxT<Gfx>::EndRenderObject() {TODO}
//template<class Gfx> NativeColorBufferConstRef GetFrameBufferColor(NativeFrameBufferConstRef fb, TexType t) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform1i(int idx, int i) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform2i(int idx, int i0, int i1) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform3i(int idx, int i0, int i1, int i2) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform1f(int idx, float f) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform2f(int idx, float f0, float f1) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform3f(int idx, float f0, float f1, float f2) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform4f(int idx, float f0, float f1, float f2, float f3) {TODO}
template<class Gfx> void D11GfxT<Gfx>::ProgramUniform3f(NativeProgram& prog, int idx, float f0, float f1, float f2) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform1fv(int idx, int count, float* f) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform3fv(int idx, int count, float* f) {TODO}
template<class Gfx> void D11GfxT<Gfx>::Uniform4fv(int idx, int count, float* f) {TODO}
template<class Gfx> void D11GfxT<Gfx>::UniformMatrix4fv(int idx, const mat4& mat) {TODO}
template<class Gfx> void D11GfxT<Gfx>::ReadPixels(int x, int y, int w, int h, GVar::Sample sample, int channels, byte* dst) {TODO}
template<class Gfx> void D11GfxT<Gfx>::ClearBuffers() {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetSmoothShading(bool b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetDepthTest(bool b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetDepthOrderLess(bool b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetClearValue(RGBA clr, byte depth) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetFastPerspectiveCorrection(bool b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetTriangleBacksideCulling(bool b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetTriangleFrontsideCCW(bool b) {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetViewport(Size sz) {TODO}
//template<class Gfx> void D11GfxT<Gfx>::ActivateNextFrame() {TODO}
template<class Gfx> void D11GfxT<Gfx>::SetDebugOutput(bool b) {TODO}

template<class Gfx> void D11GfxT<Gfx>::ClearFramebufferRef(NativeFrameBufferRef& fb) {
	fb.Reset();
}

template<class Gfx> void D11GfxT<Gfx>::ClearColorBufferRef(NativeColorBufferRef& b) {
	b.Reset();
}

template<class Gfx> void D11GfxT<Gfx>::ClearDepthBufferRef(NativeDepthBufferRef& b) {
	b.Reset();
}

template<class Gfx> Serial::FboFormat& D11GfxT<Gfx>::GetFormat(Parallel::Format& fmt) {TODO}

#if defined flagWIN32 && defined flagDX11
template struct D11GfxT<WinD11Gfx>;
#endif


void WinD11Gfx::ActivateNextFrame(NativeDisplay& d, NativeWindow& w, NativeRenderer& r, NativeColorBufferRef color_buf) {
	
	TODO
	
}

Size DxGfx::GetWindowSize(NativeWindow& win) {TODO}
bool DxGfx::CreateWindowAndRenderer(Size screen_sz, dword flags, NativeWindow& win, NativeRenderer& rend) {TODO}

void DxGfx::SetTitle(NativeDisplay& display, NativeWindow& win, String title) {
	SetWindowTextA(win, title.Begin());
}

void DxGfx::SetWindowFullscreen(NativeWindow& win, bool b) {TODO}
void DxGfx::DestroyRenderer(NativeRenderer& rend) {TODO}

void DxGfx::ClearRendererRef(NativeRenderer& rend) {
	rend.Reset();
}

void DxGfx::DestroyWindow(NativeWindow& win) {TODO}
void DxGfx::DeleteContext(NativeGLContext& ctx) {TODO}
void DxGfx::MaximizeWindow(NativeWindow& win) {TODO}
void DxGfx::RestoreWindow(NativeWindow& win) {TODO}
void DxGfx::SetWindowPosition(NativeWindow& win, Point pt) {TODO}
void DxGfx::SetWindowSize(NativeWindow& win, Size sz) {TODO}


NAMESPACE_PARALLEL_END

#endif
