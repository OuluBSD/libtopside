#ifndef _GL_Renderer_h_
#define _GL_Renderer_h_


NAMESPACE_OULU_BEGIN


class Renderer {
	
public:
	
	Size screen_sz;
	
	#if defined(flagSDL2)
	SDL_Window* win = NULL;
    SDL_Renderer* rend = NULL;
	#endif
	
	Renderer();
	virtual ~Renderer() {}
	
	Size GetSize() {return screen_sz;}
	
	virtual Framebuffer& GetOutputFramebuffer() = 0;
	virtual void PreFrame() = 0;
	virtual void PostFrame() = 0;
	virtual int AddModel(Model& model) = 0;
	
	
	
};


NAMESPACE_OULU_END

#endif
