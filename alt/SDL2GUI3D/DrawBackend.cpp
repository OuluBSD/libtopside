#include "SDL2GUI3D.h"

NAMESPACE_UPP_BEGIN



Image StreamRaster::LoadStringAny(String content) {
	SDL_RWops* mem = SDL_RWFromConstMem(content.Begin(), content.GetCount());
	return Image(IMG_Load_RW(mem, 1));
}

Image StreamRaster::LoadFileAny(String path) {
	return Image(IMG_Load(path.Begin()));
}

RawSysFont* LoadSysFont(String path, int size) {
	return TTF_OpenFont(path.Begin(), size);
}

Size GetSysFontTextSize(RawSysFont* fnt, String s) {
	Size sz;
	TTF_SizeText(fnt, s.Begin(), &sz.cx, &sz.cy);
	return sz;
}

void SysFont::Clear() {
	if (raw && TS::OOSDL2::IsSDL2Open())
		TTF_CloseFont(raw);
	raw = 0;
}

void SysImage::Clear() {
	if (raw && TS::OOSDL2::IsSDL2Open()) {
		if (--raw->refcount == 0)
			SDL_FreeSurface(raw);
	}
	raw = 0;
}








Size ImageDraw::GetPageSize() const {
	TODO
}

void ImageDraw::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	TODO
}

void ImageDraw::DrawRectOp(int x, int y, int cx, int cy, Color color) {
	TODO
}

void ImageDraw::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
	                       Color ink, int n, const int *dx) {
	TODO
}

void ImageDraw::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
                                   const int *counts, int count_count,
                                   int width, Color color, Color doxor) {
	TODO
}

bool ImageDraw::ClipOp(const Rect& r) {
	TODO
}

void ImageDraw::EndOp() {
	TODO
}

Draw& ImageDraw::Alpha() {
	TODO
}




NAMESPACE_UPP_END
