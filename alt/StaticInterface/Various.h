#ifndef _StaticInterface_Various_h_
#define _StaticInterface_Various_h_



NAMESPACE_TOPSIDE_BEGIN


struct TgaReaderBackend : StaticIfaceBackend {
	RTTI_DECL1(TgaReaderBackend, StaticIfaceBackend)
	
	
	Image LoadFileAny(String path) override;
	Image LoadStringAny(String str) override;
	void ClearImage(SysImage& img) override;
	
};

struct LibPngBackend : StaticIfaceBackend {
	RTTI_DECL1(LibPngBackend, StaticIfaceBackend)
	
	
	Image LoadFileAny(String path) override;
	Image LoadStringAny(String str) override;
	void ClearImage(SysImage& img) override;
	
};


NAMESPACE_TOPSIDE_END


#endif
