#ifndef _StaticInterface_Sdl2_h_
#define _StaticInterface_Sdl2_h_

#ifdef flagSDL2

NAMESPACE_TOPSIDE_BEGIN


struct Sdl2FileBackend : StaticIfaceBackend {
	RTTI_DECL1(Sdl2FileBackend, StaticIfaceBackend)
	
	
	Image LoadFileAny(String path) override;
	Image LoadStringAny(String str) override;
	
};


NAMESPACE_TOPSIDE_END

#endif

#endif
