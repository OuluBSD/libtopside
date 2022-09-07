#include <Local/Local.h>


NAMESPACE_UPP_BEGIN

Image StreamRaster::LoadFileAny(String path) {
	TODO
}

RawSysFont* LoadSysFont(String path, int size) {
	TODO
}

Size GetSysFontTextSize(RawSysFont* fnt, String s) {
	TODO
}

void SysFont::Clear() {
	if (raw)
		delete raw;
	raw = 0;
}

RawSysImage* SysFont::RenderTextBlended(const char* s, SysColor c) {
	TODO
}

void SysImage::Clear() {
	if (raw)
		delete raw;
	raw = 0;
}

NAMESPACE_UPP_END
/*
#define STB_IMAGE_IMPLEMENTATION
#include <Various/stb_image.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <Various/stb_truetype.h>
*/