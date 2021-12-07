#ifndef _GRAPHICS_Framebuffer_h_
#define _GRAPHICS_Framebuffer_h_


NAMESPACE_TOPSIDE_BEGIN

class Renderer;
class Viewable;


class Framebuffer {
	
protected:
	Size sz;
	int channels = 0;
	int pitch = 0;
	int sample_size = 1;
public:
	Framebuffer() : sz(0,0) {}
	virtual ~Framebuffer() {}
	
	virtual bool Create(int w, int h, int channels=3) = 0;
	virtual void Enter() = 0;
	virtual void Leave() = 0;
	virtual byte* GetIterator(int x, int y) = 0;
	virtual void DrawFill(const byte* mem, int sz) = 0;
	
	int GetWidth() const {return sz.cx;}
	int GetHeight() const {return sz.cy;}
	int GetStride() const {return channels * sample_size;}
	int GetSampleSize() const {return sample_size;}
	int GetPitch() const {return pitch;}
	Size GetSize() const {return sz;}
	
};

class DrawFramebuffer : public StateDraw {
public:
	RTTI_DECL1(DrawFramebuffer, StateDraw)
	
	virtual Renderer* GetRenderer() = 0;
	virtual Framebuffer* GetFramebuffer() = 0;
	
	virtual void DrawShaderPipeline(ShaderPipeline&) {Panic("not implemented");}
	
	
};

NAMESPACE_TOPSIDE_END


#endif
