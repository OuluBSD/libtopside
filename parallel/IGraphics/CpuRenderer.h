#ifndef _IGraphics_CpuRenderer_h_
#define _IGraphics_CpuRenderer_h_

#if 0

NAMESPACE_PARALLEL_BEGIN

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
	static void DrawPixel0(byte* data, int stride, int pitch, int x, int y, Color color);
	static byte AtRGBA(RGBA rgba, int i);
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
	/*int GetWidth() const override {return w;}
	int GetHeight() const override {return h;}
	int GetStride() const override {return stride;}
	int GetPitch() const override {return pitch;}*/
	void DrawFill(const byte* mem, int sz) override {TODO}
	
	RawSysTexture* GetRawSysTexture() {return 0;}
	
};

class CpuMemFramebuffer : public CpuFramebuffer {
	Vector<byte> data;
	byte* pixels = 0;
	int pitch = 0;
	int w = 0, h = 0, stride = 0;
	bool locked = false;
	
public:
	CpuMemFramebuffer();
	~CpuMemFramebuffer();
	
	bool Create(int w, int h, int channels=3) override;
	void Enter() override;
	void Leave() override;
	byte* GetIterator(int x, int y) override;
	/*int GetWidth() const override;
	int GetHeight() const override;
	int GetStride() const override;
	int GetPitch() const override;*/
	void DrawFill(const byte* mem, int sz) override;
	
	
};

class CpuRenderer : public Renderer {
	CpuMemFramebuffer output;
	
public:
	
	CpuMemFramebuffer& GetOutputCpuFramebuffer() {return output;}
	
	Framebuffer& GetOutputFramebuffer() override {return output;}
	void PreFrame() override;
	void PostFrame() override;
	
};

class CpuDrawFramebuffer : public DrawFramebuffer {
public:
	RTTI_DECL1(CpuDrawFramebuffer, DrawFramebuffer)
	CpuRenderer* rend = 0;
	CpuMemFramebuffer* fb = 0;
	
	
	Renderer* GetRenderer() override {return rend;}
	Framebuffer* GetFramebuffer() override {return fb;}
	
	void DrawShaderPipeline(ShaderPipeline&) override;
	void DrawShaderPipeline(CpuShaderPipeline&);
	
};


NAMESPACE_PARALLEL_END

#endif
#endif
