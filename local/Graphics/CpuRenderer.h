#ifndef _GL_CpuRenderer_h_
#define _GL_CpuRenderer_h_

NAMESPACE_OULU_BEGIN

class CpuFramebuffer : public Framebuffer {
	
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
	
	RawSysTexture* GetRawSysTexture() {return 0;}
	
};


#if defined flagSDL2GUI3DALT
class CpuOutputFramebuffer : public CpuFramebuffer {
	SDL_Texture* fb;
	byte* pixels;
	int pitch;
	int w, h, stride;
	bool locked = false;
	
public:
	CpuOutputFramebuffer() {}
	~CpuOutputFramebuffer() {Leave();}
	
	void Init(SDL_Texture* fb, int w, int h, int stride) {
		this->fb = fb;
		this->w = w;
		this->h = h;
		this->stride = stride;
	}
	
	bool Create(int w, int h, int channels=3) override {ASSERT(this->w == w && this->h == h && this->stride == channels); return true;}
	void Enter() override {
		if (!locked) {
			SDL_Rect r {0, 0, w, h};
			void* pixels;
			SDL_LockTexture(fb, &r, &pixels, &pitch);
			this->pixels = (byte*)pixels;
			locked = true;
		}
	}
	void Leave() override {
		if (locked) {
			SDL_UnlockTexture(fb);
			locked = false;
		}
	}
	byte* GetIterator(int x, int y) override {return &pixels[x * stride + y * pitch];}
	int GetWidth() const override {return w;}
	int GetHeight() const override {return h;}
	int GetStride() const override {return stride;}
	int GetPitch() const override {return pitch;}
	
	RawSysTexture* GetRawSysTexture() {return fb;}
	
};

#else

class CpuOutputFramebuffer : public CpuMemoryFramebuffer {};

#endif


class CpuRenderer : public Renderer {
	CpuOutputFramebuffer output;
	
public:
	
	CpuOutputFramebuffer& GetOutputCpuFramebuffer() {return output;}
	
	Framebuffer& GetOutputFramebuffer() override {return output;}
	void PreFrame() override;
	void PostFrame() override;
	int AddModel(Model& model) override;
	
};

class CpuFramebufferDraw : public FramebufferDraw {
public:
	CpuRenderer* rend = 0;
	CpuFramebuffer* fb = 0;
	
	
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
	
};


NAMESPACE_OULU_END

#endif
