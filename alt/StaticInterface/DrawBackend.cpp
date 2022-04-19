#include "StaticInterface.h"


NAMESPACE_UPP


int SysImage::GetWidth() const {return raw ? raw->w : 0;}
int SysImage::GetHeight() const {return raw ? raw->h : 0;}
int SysImage::GetStride() const {return raw ? raw->ch : 0;}
int SysImage::GetPitch() const {return raw ? raw->pitch : 0;}
const unsigned char* SysImage::GetData() const {return raw ? (const unsigned char*)raw->data : 0;}

Image StreamRaster::LoadStringAny(String content) {
	TODO // try all readers
}

Image StreamRaster::LoadFileAny(String path) {
	String ext = GetFileExt(path).Mid(1);
	TS::StaticIfaceBackend* e = TS::StaticIfaceFactory::GetReader(ext);
	if (e)
		return e->LoadFileAny(path);
	return Image();
}

RawSysFont* LoadSysFont(String path, int size) {
	TODO
	return 0;
}

Size GetSysFontTextSize(RawSysFont* fnt, String s) {
	TODO
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

Image ImageBuffer::GetImage() {
	TODO
}


END_UPP_NAMESPACE
