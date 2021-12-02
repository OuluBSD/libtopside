#ifndef _GRAPHICS_CpuRenderer_h_
#define _GRAPHICS_CpuRenderer_h_

NAMESPACE_TOPSIDE_BEGIN

class CpuFramebuffer : public Framebuffer {
	
protected:
	CpuFramebuffer() {}
	
public:
	
	void Zero();
	void DrawPixel(int x, int y, RGBA color);
	void DrawPixel(int x, int y, Color color);
	void DrawHLine(int x0, int x1, int y, Color color);
	void DrawLine(int x0, int y0, int x1, int y1, Color color);
	//void DrawLine(const vec2& a, const vec2& b, byte* color) {DrawLine(a[0], a[1], b[0], b[1], color);}
	
};


class CpuMemoryFramebuffer : public CpuFramebuffer {
	Vector<byte> pixels;
	int pitch = 0;
	int w = 0, h = 0, stride = 0;
	bool locked = false;
	
public:
	
	CpuMemoryFramebuffer() {}
	bool Create(int w, int h, int channels=3) override;
	void Enter() override {ASSERT(!locked); locked = true;}
	void Leave() override {ASSERT(locked);  locked = false;}
	byte* GetIterator(int x, int y) override {return &pixels[x * stride + y * pitch];}
	int GetWidth() const override {return w;}
	int GetHeight() const override {return h;}
	int GetStride() const override {return stride;}
	int GetPitch() const override {return pitch;}
	void DrawFill(const byte* mem, int sz) override {TODO}
	
	RawSysTexture* GetRawSysTexture() {return 0;}
	
};

class CpuOutputFramebuffer : public CpuFramebuffer {
	Vector<byte> data;
	byte* pixels = 0;
	int pitch = 0;
	int w = 0, h = 0, stride = 0;
	bool locked = false;
	
public:
	CpuOutputFramebuffer();
	~CpuOutputFramebuffer();
	
	bool Create(int w, int h, int channels=3) override;
	void Enter() override;
	void Leave() override;
	byte* GetIterator(int x, int y) override;
	int GetWidth() const override;
	int GetHeight() const override;
	int GetStride() const override;
	int GetPitch() const override;
	void DrawFill(const byte* mem, int sz) override;
	
	
};

class CpuRenderer : public Renderer {
	CpuOutputFramebuffer output;
	
public:
	
	CpuOutputFramebuffer& GetOutputCpuFramebuffer() {return output;}
	
	Framebuffer& GetOutputFramebuffer() override {return output;}
	void PreFrame() override;
	void PostFrame() override;
	
};

class CpuDrawFramebuffer : public DrawFramebuffer {
public:
	RTTI_DECL1(CpuDrawFramebuffer, DrawFramebuffer)
	CpuRenderer* rend = 0;
	CpuOutputFramebuffer* fb = 0;
	
	
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


NAMESPACE_TOPSIDE_END

#endif
