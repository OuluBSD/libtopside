#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN


template<class Gfx> void DxGfxT<Gfx>::BindProgramPipeline(NativePipeline& pipeline) {TODO}
template<class Gfx> void DxGfxT<Gfx>::UseProgram(NativeProgram& prog) {TODO}
//template<class Gfx> void DxGfxT<Gfx>::EnterFramebuffer(NativeFrameBuffer& fb) {TODO}
template<class Gfx> void DxGfxT<Gfx>::FramebufferTexture2D(TexType tgt, NativeColorBufferRef b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::FramebufferRenderbuffer(NativeDepthBufferRef fb) {TODO}
template<class Gfx> void DxGfxT<Gfx>::BindFramebuffer(NativeFrameBufferRef fb) {TODO}
template<class Gfx> void DxGfxT<Gfx>::BindFramebufferRO(NativeFrameBufferConstRef fb) {TODO}
template<class Gfx> void DxGfxT<Gfx>::BindRenderbuffer(NativeDepthBufferRef rb) {TODO}
template<class Gfx> void DxGfxT<Gfx>::UnbindRenderbuffer() {TODO}
template<class Gfx> void DxGfxT<Gfx>::RenderbufferStorage(Size sz) {TODO}
template<class Gfx> void DxGfxT<Gfx>::UnbindProgramPipeline() {TODO}
template<class Gfx> void DxGfxT<Gfx>::BindFramebufferDefault() {TODO}
template<class Gfx> void DxGfxT<Gfx>::DrawBuffers(GVar::RenderTarget tgt) {TODO}
//template<class Gfx> void DxGfxT<Gfx>::SetRender_Color() {TODO}
template<class Gfx> void DxGfxT<Gfx>::RenderScreenRect() {TODO}
template<class Gfx> String DxGfxT<Gfx>::GetShaderTemplate(GVar::ShaderType t) {TODO}
template<class Gfx> void DxGfxT<Gfx>::HotfixShaderCode(String& s) {TODO}
template<class Gfx> void DxGfxT<Gfx>::ActiveTexture(int ch) {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeactivateTexture() {TODO}
template<class Gfx> void DxGfxT<Gfx>::BindTextureRO(GVar::TextureMode type, NativeColorBufferConstRef tex) {TODO}
template<class Gfx> void DxGfxT<Gfx>::BindTextureRW(GVar::TextureMode type, NativeColorBufferRef tex) {TODO}
template<class Gfx> void DxGfxT<Gfx>::ReserveTexture(GVar::TextureMode type, FramebufferT<Gfx>& fb) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetTexture(GVar::TextureMode type, Size sz, GVar::Sample sample, int ch, const byte* data) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetTexture(GVar::TextureMode type, Size3 sz, GVar::Sample sample, int ch, const byte* data) {TODO}
template<class Gfx> void DxGfxT<Gfx>::UnbindTexture(GVar::TextureMode type) {TODO}
template<class Gfx> void DxGfxT<Gfx>::GenerateMipmap(GVar::TextureMode type) {TODO}
template<class Gfx> bool DxGfxT<Gfx>::CreateShader(GVar::ShaderType t, NativeShaderRef& new_shdr) {TODO}
template<class Gfx> void DxGfxT<Gfx>::ShaderSource(NativeShaderRef s, String code) {TODO}
template<class Gfx> bool DxGfxT<Gfx>::CompileShader(NativeShaderRef s) {TODO}
template<class Gfx> String DxGfxT<Gfx>::GetLastErrorS(NativeShaderRef s) {TODO}
template<class Gfx> String DxGfxT<Gfx>::GetLastErrorP(NativeProgram& s) {TODO}
template<class Gfx> bool DxGfxT<Gfx>::CreateProgram(NativeProgram& prog) {TODO}
template<class Gfx> bool DxGfxT<Gfx>::CreateRenderbuffer(NativeDepthBufferRef& b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::ProgramParameteri(NativeProgram& prog, GVar::ParamType type, int i) {TODO}
template<class Gfx> void DxGfxT<Gfx>::AttachShader(NativeProgram& prog, NativeShaderRef shdr) {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeleteShader(NativeShaderRef& shdr) {TODO}
template<class Gfx> bool DxGfxT<Gfx>::LinkProgram(NativeProgram& prog) {TODO}
template<class Gfx> void DxGfxT<Gfx>::GetProgramiv(NativeProgram& prog, GVar::ProgParamType type, int& out) {TODO}
template<class Gfx> String DxGfxT<Gfx>::GetActiveUniform(NativeProgram& prog, int i, int* size_out, int* type_out) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Clear(GVar::BufferType type) {TODO}
template<class Gfx> void DxGfxT<Gfx>::GenProgramPipeline(NativePipeline& pipe) {TODO}
template<class Gfx> void DxGfxT<Gfx>::UseProgramStages(NativePipeline& pipe, uint32 shader_type_bmask, NativeProgram& prog) {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeleteProgramPipeline(NativePipeline& pipe) {TODO}
template<class Gfx> void DxGfxT<Gfx>::TexParameteri(GVar::TextureMode type, GVar::Filter filter, GVar::Wrap repeat) {TODO}
template<class Gfx> bool DxGfxT<Gfx>::GenTexture(NativeColorBufferRef& fb) {TODO}
template<class Gfx> bool DxGfxT<Gfx>::CreateFramebuffer(NativeFrameBufferRef& fb) {TODO}
template<class Gfx> void DxGfxT<Gfx>::GenVertexArray(NativeVertexArray& vao) {TODO}
template<class Gfx> void DxGfxT<Gfx>::GenVertexBuffer(NativeVertexBuffer& vbo) {TODO}
template<class Gfx> void DxGfxT<Gfx>::GenElementBuffer(NativeElementBuffer& ebo) {TODO}
template<class Gfx> void DxGfxT<Gfx>::BindVertexArray(NativeVertexArray& vao) {TODO}
template<class Gfx> void DxGfxT<Gfx>::BindVertexBuffer(NativeVertexBuffer& vbo) {TODO}
template<class Gfx> void DxGfxT<Gfx>::BindElementBuffer(NativeElementBuffer& ebo) {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeleteVertexArray(NativeVertexArray& vao) {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeleteVertexBuffer(NativeVertexBuffer& vbo) {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeleteElementBuffer(NativeElementBuffer& ebo) {TODO}
template<class Gfx> void DxGfxT<Gfx>::VertexBufferData(const Vector<Vertex>& vtx) {TODO}
template<class Gfx> void DxGfxT<Gfx>::ElementBufferData(const Vector<uint32>& el) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetupVertexStructure() {TODO}
template<class Gfx> void DxGfxT<Gfx>::UnbindVertexArray() {TODO}
template<class Gfx> void DxGfxT<Gfx>::UnbindVertexBuffer() {TODO}
template<class Gfx> void DxGfxT<Gfx>::UnbindElementBuffer() {TODO}
template<class Gfx> void DxGfxT<Gfx>::UnbindFramebuffer() {TODO}
template<class Gfx> void DxGfxT<Gfx>::ActivateVertexStructure() {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeactivateVertexStructure() {TODO}
template<class Gfx> void DxGfxT<Gfx>::DrawVertexElements(int element_limit, bool use_quad) {TODO}
template<class Gfx> void DxGfxT<Gfx>::TexImage2D(ByteImage& tex) {TODO}
template<class Gfx> void DxGfxT<Gfx>::TexImage2D(FloatImage& tex) {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeleteTexture(NativeColorBufferRef& b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeleteRenderbuffer(NativeDepthBufferRef& b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::DeleteFramebuffer(NativeFrameBufferRef& b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetContextDefaultFramebuffer(NativeFrameBufferRef fb) {TODO}
template<class Gfx> void DxGfxT<Gfx>::BeginRender() {TODO}
template<class Gfx> void DxGfxT<Gfx>::EndRender() {TODO}
template<class Gfx> void DxGfxT<Gfx>::BeginRenderObject() {TODO}
template<class Gfx> void DxGfxT<Gfx>::EndRenderObject() {TODO}
//template<class Gfx> NativeColorBufferConstRef GetFrameBufferColor(NativeFrameBufferConstRef fb, TexType t) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform1i(int idx, int i) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform2i(int idx, int i0, int i1) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform3i(int idx, int i0, int i1, int i2) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform1f(int idx, float f) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform2f(int idx, float f0, float f1) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform3f(int idx, float f0, float f1, float f2) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform4f(int idx, float f0, float f1, float f2, float f3) {TODO}
template<class Gfx> void DxGfxT<Gfx>::ProgramUniform3f(NativeProgram& prog, int idx, float f0, float f1, float f2) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform1fv(int idx, int count, float* f) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform3fv(int idx, int count, float* f) {TODO}
template<class Gfx> void DxGfxT<Gfx>::Uniform4fv(int idx, int count, float* f) {TODO}
template<class Gfx> void DxGfxT<Gfx>::UniformMatrix4fv(int idx, const mat4& mat) {TODO}
template<class Gfx> void DxGfxT<Gfx>::ReadPixels(int x, int y, int w, int h, GVar::Sample sample, int channels, byte* dst) {TODO}
template<class Gfx> void DxGfxT<Gfx>::ClearBuffers() {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetSmoothShading(bool b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetDepthTest(bool b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetDepthOrderLess(bool b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetClearValue(RGBA clr, byte depth) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetFastPerspectiveCorrection(bool b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetTriangleBacksideCulling(bool b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetTriangleFrontsideCCW(bool b) {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetViewport(Size sz) {TODO}
//template<class Gfx> void DxGfxT<Gfx>::ActivateNextFrame() {TODO}
template<class Gfx> void DxGfxT<Gfx>::SetDebugOutput(bool b) {TODO}

template<class Gfx> Serial::FboFormat& DxGfxT<Gfx>::GetFormat(Parallel::Format& fmt) {TODO}

#if defined flagWIN32 && defined flagDX
template struct DxGfxT<WinDxGfx>;
#endif


NAMESPACE_PARALLEL_END
