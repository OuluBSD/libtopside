#ifndef _GRAPHICS_Renderer_h_
#define _GRAPHICS_Renderer_h_


NAMESPACE_TOPSIDE_BEGIN


class Renderer {
	
protected:
	Size output_sz;
	
	
public:
	Renderer();
	virtual ~Renderer() {}
	
	virtual Framebuffer& GetOutputFramebuffer() = 0;
	virtual void PreFrame() = 0;
	virtual void PostFrame() = 0;
	
	virtual void SetSize(Size sz) {output_sz = sz;}
	
	Size GetSize() const {return output_sz;}
	
	
};


NAMESPACE_TOPSIDE_END

#endif
 