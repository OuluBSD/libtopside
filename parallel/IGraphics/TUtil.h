#ifndef _IGraphics_TUtil_h_
#define _IGraphics_TUtil_h_

NAMESPACE_PARALLEL_BEGIN


/*template <class Gfx>
struct DrawFramebufferT : GfxStateDraw {
	RTTI_DECL1(DrawFramebufferT, GfxStateDraw)
	using Base = DrawFramebufferT<Gfx>;
	using Renderer = typename Gfx::Renderer;
	using Framebuffer = typename Gfx::Framebuffer;
	using ShaderPipeline = typename Gfx::ShaderPipeline;
	
	GfxRenderer* rend = 0;
	GfxFramebuffer* fb = 0;
	
	//GfxRenderer* GetRenderer() override {return rend;}
	//GfxFramebuffer* GetFramebuffer() override {return fb;}
	
	
	void DrawShaderPipeline(ShaderPipeline&);
	
	
};*/

template <class Gfx>
struct TextureT {
	using NativeColorBufferRef = typename Gfx::NativeColorBufferRef;
	
	NativeColorBufferRef tex;
	
	TextureT() {}
	~TextureT() {Clear();}
	void Clear();
	void Load(const ByteImage& img);
	void Load(const FloatImage& img);
	bool IsEmpty() const {return tex;}
	
};

template <class Gfx>
struct StateDrawT : GfxStateDraw {
	RTTI_DECL1(StateDrawT, GfxStateDraw)
	using Base = StateDrawT<Gfx>;
	using ShaderPipeline = typename Gfx::ShaderPipeline;
	using NativeRenderer = typename Gfx::NativeRenderer;
	using DataState = DataStateT<Gfx>;
	using Framebuffer = FramebufferT<Gfx>;
	
	//NativeRenderer* rend = 0;
	//Framebuffer* fb = 0;
	DataState* state = 0;
	Size size;
	byte channels = 0;
	GVar::Sample sample;
	
	void SetFormat(Framebuffer& fb) {size = fb.size; channels = fb.channels; sample = fb.sample;}
	void SetTarget(DataState& s) {state = &s;}
	void DrawShaderPipeline(ShaderPipeline&) {TODO}
	
	bool HasTarget() const override {return /*rend && fb &&*/ state;}
	DataState& GetState() {return *state;}
	GfxDataState& GetGfxState() override {return *state;}
	Size GetPageSize() const override {return size;}
	
	void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) override {TODO}
	void DrawRectOp(int x, int y, int cx, int cy, Color color) override {TODO}
	void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		            Color ink, int n, const int *dx) override {TODO}
	void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        int width, Color color, Color doxor) override {TODO}
	bool ClipOp(const Rect& r) override {TODO}
	void EndOp() override {TODO}
	void DrawImage(int x, int y, Image img, byte alpha=255) override {TODO}
	Draw& Alpha() {TODO}
};

#if 0
template <class Gfx>
struct BinderIfaceT : GfxBinderIface {
	RTTI_DECL1(BinderIfaceT, GfxBinderIface);
	using Base = BinderIfaceT<Gfx>;
	using Buffer = typename Gfx::Buffer;
	using DataState = DataStateT<Gfx>;
	
	
};
#endif

NAMESPACE_PARALLEL_END

#endif
