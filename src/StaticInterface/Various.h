#ifndef _StaticInterface_Various_h_
#define _StaticInterface_Various_h_

#if defined flagPOSIX && !PLATFORM_EMSCRIPTEN
	#define HAVE_LIBPNG 1
#endif


NAMESPACE_TOPSIDE_BEGIN


struct TgaReaderBackend : StaticIfaceBackend {
	typedef TgaReaderBackend CLASSNAME;
	RTTI_DECL1(TgaReaderBackend, StaticIfaceBackend)
	
	
	Image LoadFileAny(String path) override;
	Image LoadStringAny(String str) override;
	void ClearImage(SysImage& img) override;
	
};


#if HAVE_LIBPNG
struct LibPngBackend : StaticIfaceBackend {
	typedef LibPngBackend CLASSNAME;
	RTTI_DECL1(LibPngBackend, StaticIfaceBackend)
	
	
	Image LoadFileAny(String path) override;
	Image LoadStringAny(String str) override;
	void ClearImage(SysImage& img) override;
	
};
#endif


NAMESPACE_TOPSIDE_END


#endif
