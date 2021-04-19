#ifndef _GL_Framebuffer_h_
#define _GL_Framebuffer_h_


NAMESPACE_OULU_BEGIN

class Renderer;
class Camerable;


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

class FramebufferDraw : public Draw {
public:
	virtual Renderer* GetRenderer() = 0;
	virtual Framebuffer* GetFramebuffer() = 0;
	
};

NAMESPACE_OULU_END


#endif
