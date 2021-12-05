#ifndef _Graphics_OglRenderer_h_
#define _Graphics_OglRenderer_h_

NAMESPACE_TOPSIDE_BEGIN


class OglFramebuffer : public Framebuffer {
	GLuint fb_name = 0;
	GLuint fb_texture = 0;
	int channels = 0;
	Size sz;
	bool locked = false;
	
	
public:
	typedef OglFramebuffer CLASSNAME;
	OglFramebuffer();
	~OglFramebuffer() {Clear();}
	
	
	GLuint GetTexture() const {return fb_texture;}
	Size GetSize() const {return sz;}
	
	bool Create(int w, int h, int channels=3) override;
	void Enter() override {ASSERT(!locked); locked = true;}
	void Leave() override {ASSERT(locked);  locked = false;}
	byte* GetIterator(int x, int y) override {Panic("Not usable: OglFramebuffer::GetIterator"); return 0;}
	int GetWidth() const override {return sz.cx;}
	int GetHeight() const override {return sz.cy;}
	int GetStride() const override {return channels;}
	int GetPitch() const override {return sz.cx * channels;}
	void DrawFill(const byte* mem, int sz) override {TODO}
	
	void Bind();
	void Clear();
	void Render();
};


class OglRenderer : public Renderer {
	OglFramebuffer output;
	
	
public:
	
	Framebuffer& GetOutputFramebuffer() override {return output;}
	void PreFrame() override;
	void PostFrame() override;
	
	OglFramebuffer& GetFramebuffer() {return output;}
	
};


class OglDrawFramebuffer : public DrawFramebuffer {
public:
	RTTI_DECL1(OglDrawFramebuffer, DrawFramebuffer)
	
	OglRenderer* rend = 0;
	OglFramebuffer* fb = 0;
	
	Renderer* GetRenderer() override {return rend;}
	Framebuffer* GetFramebuffer() override {return fb;}
	
	
};


NAMESPACE_TOPSIDE_END

#endif
