#include "Graphics.h"


NAMESPACE_TOPSIDE_BEGIN


CpuOutputFramebuffer::CpuOutputFramebuffer() {
	
}

CpuOutputFramebuffer::~CpuOutputFramebuffer() {
	Leave();
}

bool CpuOutputFramebuffer::Create(int w, int h, int channels) {
	this->w = w;
	this->h = h;
	this->stride = channels;
	int len = w * h * stride;
	data.SetCount(len);
	pixels = data.Begin();
	return len > 0;
}

void CpuOutputFramebuffer::Enter() {
	/*if (!locked) {
		SDL_Rect r {0, 0, w, h};
		void* pixels;
		SDL_LockTexture(fb, &r, &pixels, &pitch);
		this->pixels = (byte*)pixels;
		locked = true;
	}*/
}

void CpuOutputFramebuffer::Leave() {
	/*if (locked) {
		SDL_UnlockTexture(fb);
		locked = false;
	}*/
}

byte* CpuOutputFramebuffer::GetIterator(int x, int y) {
	ASSERT(pixels);
	return &pixels[x * stride + y * pitch];
}

int CpuOutputFramebuffer::GetWidth() const {
	return w;
}

int CpuOutputFramebuffer::GetHeight() const {
	return h;
}

int CpuOutputFramebuffer::GetStride() const {
	return stride;
}

int CpuOutputFramebuffer::GetPitch() const {
	return pitch;
}

void CpuOutputFramebuffer::DrawFill(const byte* mem, int sz) {
	if (sz == h * pitch) {
		memcpy(pixels, mem, sz);
	}
	else
		if (sz == w * h * stride) {
			int row = w * stride;
			byte* dst = pixels;
			for (int y = 0; y < h; y++) {
				memcpy(dst, mem, row);
				mem += row;
				dst += pitch;
			}
		}
		else {
			sz = min(sz, h * pitch);
			memcpy(pixels, mem, sz);
		}
}




void CpuRenderer::PreFrame() {
	output.Create(screen_sz.cx, screen_sz.cy, 3);
}

void CpuRenderer::PostFrame() {
	TODO
	/*RawSysTexture* fb = output.GetRawSysTexture();
	
	if (rend && fb) {
		SDL_RenderCopy(rend, fb, NULL, NULL);
		SDL_RenderPresent(rend);
	}*/
	
}









void CpuDrawFramebuffer::DrawImageMemory(const byte* mem, int sz, int x, int y, int w, int h, int ch_var_size, int channels) {
	int w0 = fb->GetWidth();
	int h0 = fb->GetHeight();
	int stride0 = fb->GetStride();
	
	if (x == 0 && y == 0 &&
		w == w0 && h == h0 &&
		stride0 == ch_var_size * channels)
		fb->DrawFill(mem, sz);
	else {
		TODO
	}
}

void CpuDrawFramebuffer::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	ASSERT(fb);
	if (!fb) return;
	if (width == 1)
		fb->DrawLine(x1, y1, x2, y2, color);
	else {
		TODO
	}
}

void CpuDrawFramebuffer::DrawRectOp(int x, int y, int cx, int cy, Color color) {
	ASSERT(fb);
	if (!fb) return;
	int w = fb->GetWidth();
	int h = fb->GetHeight();
	int x0 = max(0, min(w-1, x));
	int x1 = max(0, min(w-1, x+cx));
	int y0 = max(0, min(h-1, y));
	int y1 = max(0, min(h-1, y+cy));
	for(int y = y0; y <= y1; y++)
		fb->DrawHLine(x0, x1, y, color);
}

void CpuDrawFramebuffer::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
	                                Color ink, int n, const int *dx) {
	TODO
}

void CpuDrawFramebuffer::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
                                            const int *counts, int count_count,
                                            int width, Color color, Color doxor) {
	ASSERT(fb);
	if (!fb) return;
	if (width == 1) {
	    const Point *it = vertices;
		for(int i = 0; i < count_count; i++) {
			int count = counts[i];
			if (count >= 2) {
				const Point* end = it + count;
				Point a = *it++;
				while (it != end) {
					Point b = *it++;
					fb->DrawLine(a.x, a.y, b.x, b.y, color);
					Swap(a, b);
				}
			}
		}
	}
	else {
		TODO
	}
}

bool CpuDrawFramebuffer::ClipOp(const Rect& r) {
	TODO
}

void CpuDrawFramebuffer::EndOp() {
	TODO
}

NAMESPACE_TOPSIDE_END
