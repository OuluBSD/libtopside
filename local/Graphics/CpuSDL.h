#ifndef _Graphics_CpuSDL_h_
#define _Graphics_CpuSDL_h_


NAMESPACE_TOPSIDE_BEGIN


#ifdef flagSCREEN
class SdlOutputFramebuffer : public CpuFramebuffer {
	SDL_Texture* fb = 0;
	byte* pixels = 0;
	int pitch = 0;
	int w = 0, h = 0, stride = 0;
	bool locked = false;
	
public:
	SdlOutputFramebuffer();
	~SdlOutputFramebuffer();
	
	void Init(SDL_Texture* fb, int w, int h, int stride);
	bool Create(int w, int h, int channels=3) override;
	void Enter() override;
	void Leave() override;
	byte* GetIterator(int x, int y) override;
	/*int GetWidth() const override;
	int GetHeight() const override;
	int GetStride() const override;
	int GetPitch() const override;*/
	void DrawFill(const byte* mem, int sz) override;
	
	RawSysTexture* GetRawSysTexture() {return fb;}
	
};

class SdlCpuRenderer : public RendererT<SdlCpuGfx> {
	SdlOutputFramebuffer output;
	
public:
	
	SdlOutputFramebuffer& GetOutputCpuFramebuffer() {return output;}
	
	Framebuffer& GetOutputFramebuffer() override {return output;}
	void PreFrame() override;
	void PostFrame() override;
	
};

class SdlDrawFramebuffer : public CpuDrawFramebuffer {
public:
	RTTI_DECL1(SdlDrawFramebuffer, DrawFramebuffer)
	SdlCpuRenderer* rend = 0;
	SdlOutputFramebuffer* fb = 0;
	
	
	Renderer* GetRenderer() override {return rend;}
	Framebuffer* GetFramebuffer() override {return fb;}
	
	Size GetPageSize() const override {return rend ? rend->GetSize() : Size(0,0);}
	void DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) override;
	void DrawRectOp(int x, int y, int cx, int cy, Color color) override;
	void DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
		             Color ink, int n, const int *dx) override;
	void DrawPolyPolylineOp(const Point *vertices, int vertex_count,
	                        const int *counts, int count_count,
	                        int width, Color color, Color doxor) override;
	bool ClipOp(const Rect& r) override;
	void EndOp() override;
	
	void DrawImageMemory(const  byte* mem, int sz, int x, int y, int w, int h, int ch_var_size, int channels);
	
};

#endif


NAMESPACE_TOPSIDE_END


#endif
