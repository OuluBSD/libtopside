#include <Local/Local.h>


NAMESPACE_UPP_BEGIN

Image StreamRaster::LoadStringAny(String content) {
	return Image();
}

Image StreamRaster::LoadFileAny(String path) {
	return Image();
}

RawSysFont* LoadSysFont(String path, int size) {
	return 0;
}

Size GetSysFontTextSize(RawSysFont* fnt, String s) {
	return Size(0, 0);
}

void SysFont::Clear() {
	if (raw)
		delete raw;
	raw = 0;
}

RawSysImage* SysFont::RenderTextBlended(const char* s, SysColor c) {
	return 0;
}

void SysImage::Clear() {
	if (raw)
		delete raw;
	raw = 0;
}


NAMESPACE_UPP_END
