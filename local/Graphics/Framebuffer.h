#ifndef _GL_Framebuffer_h_
#define _GL_Framebuffer_h_


NAMESPACE_TOPSIDE_BEGIN

class Renderer;
class Viewable;


class Framebuffer {
	
public:
	virtual ~Framebuffer() {}
	
	virtual bool Create(int w, int h, int channels=3) = 0;
	virtual void Enter() = 0;
	virtual void Leave() = 0;
	virtual byte* GetIterator(int x, int y) = 0;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;
	virtual int GetStride() const = 0;
	virtual int GetPitch() const = 0;
	
	
};

class DrawFramebuffer : public Draw {
public:
	RTTI_DECL1(DrawFramebuffer, Draw)
	
	virtual Renderer* GetRenderer() = 0;
	virtual Framebuffer* GetFramebuffer() = 0;
	
};

NAMESPACE_TOPSIDE_END


#endif
