#include "OOSDL2.h"

NAMESPACE_SDL2_BEGIN

bool is_sdl2_quit;
bool IsSDL2Open() {return !is_sdl2_quit;}

int Context::count;

bool Context::Open0() {
	
	// SDL
	uint32 sdl_flags = 0;
	for(Component* c : comps)
		sdl_flags |= c->GetInitFlag();
	
	if (SDL_Init(sdl_flags) < 0) {
		last_error = SDL_GetError();
		LOG("SDL2::Context: error : " << last_error);
		return false;
	}
	
	for(Component* c : comps)
		if (!c->Open())
			return false;
	
	++count;
	
	return true;
}

void Context::Close0() {
	for(Component* c : comps)
		c->Close();
	
	if (--count == 0) {
	    is_sdl2_quit = true;
	    SDL_Quit();
	}
}


NAMESPACE_SDL2_END
