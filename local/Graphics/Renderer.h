#ifndef _GRAPHICS_Renderer_h_
#define _GRAPHICS_Renderer_h_


NAMESPACE_TOPSIDE_BEGIN


class Renderer {
	
public:
	
	Size screen_sz;
	
#if HAVE_SDL2
	SDL_Window* win = NULL;
    SDL_Renderer* rend = NULL;
#endif
	
	Renderer();
	virtual ~Renderer() {}
	
	Size GetSize() {return screen_sz;}
	
	virtual Framebuffer& GetOutputFramebuffer() = 0;
	virtual void PreFrame() = 0;
	virtual void PostFrame() = 0;
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
