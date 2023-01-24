#ifndef _StaticInterface_Sdl2_h_
#define _StaticInterface_Sdl2_h_

#ifdef flagSDL2

NAMESPACE_TOPSIDE_BEGIN


struct Sdl2FileBackend : StaticIfaceBackend {
	RTTI_DECL1(Sdl2FileBackend, StaticIfaceBackend)
	
	
	Image LoadFileAny(String path) override;
	Image LoadStringAny(String str) override;
	void ClearImage(SysImage& img) override;
	
	Font LoadFont(String dir, String name, int ptsize, int weight, bool italic) override;
	Size GetTextSize(const SysFont& fnt, const String& s) override;
	void ClearFont(SysFont& fnt) override;
	Image RenderTextBlended(const SysFont& fnt, const char* s, SysColor c) override;
	
	Image ImageFromSDLSurface(void* surf);
	
};


NAMESPACE_TOPSIDE_END

#endif

#endif
