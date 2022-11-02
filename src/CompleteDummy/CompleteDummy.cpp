#include "CompleteDummy.h"



NAMESPACE_TOPSIDE_BEGIN



Image StreamRaster::LoadStringAny(String content) {
	return Image();
}

Image StreamRaster::LoadFileAny(String path) {
	return Image();
}


Size GetSysFontTextSize(RawSysFont* fnt, String s) {
	return Size(0, 0);
}

RawSysImage* SysFont::RenderTextBlended(const char* s, SysColor c) {
	return 0;
}

void SysFont::Clear() {}

void SysImage::Clear() {}

RawSysFont* LoadSysFont(String path, int size) {
	return 0;
}


bool SingleMachine::Open(bool gui) {return 1;}
void SingleMachine::Close() {}



NAMESPACE_TOPSIDE_END
