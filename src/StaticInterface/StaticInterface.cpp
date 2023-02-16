#include "StaticInterface.h"

NAMESPACE_UPP_BEGIN


INITBLOCK_(StaticInterface) {
	using namespace TS;
	
	#ifdef flagSDL2
	StaticIfaceFactory::AddFileFormat<Sdl2FileBackend>("jpg", true, false);
	StaticIfaceFactory::AddFileFormat<Sdl2FileBackend>("png", true, false);
	StaticIfaceFactory::AddFileFormat<Sdl2FileBackend>("tiff", true, false);
	StaticIfaceFactory::AddFileFormat<Sdl2FileBackend>("tga", true, false);
	StaticIfaceFactory::AddFileFormat<Sdl2FileBackend>("ttf", true, false);
	#endif
	
	StaticIfaceFactory::AddFileFormat<TgaReaderBackend>("tga", true, false);
	
	#if HAVE_LIBPNG
	StaticIfaceFactory::AddFileFormat<LibPngBackend>("png", true, false);
	#endif
	
}


NAMESPACE_UPP_END