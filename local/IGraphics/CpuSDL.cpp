#include "IGraphics.h"

#if 0

NAMESPACE_PARALLEL_BEGIN


#ifdef flagSCREEN

SdlOutputFramebuffer::SdlOutputFramebuffer() {
	
}

SdlOutputFramebuffer::~SdlOutputFramebuffer() {
	Leave();
}

void SdlOutputFramebuffer::Init(SDL_Texture* fb, int w, int h, int stride) {
	this->fb = fb;
	this->w = w;
	this->h = h;
	this->stride = stride;
}

bool SdlOutputFramebuffer::Create(int w, int h, int channels) {
	ASSERT(this->w == w && this->h == h && this->stride == channels);
	return true;
}

void SdlOutputFramebuffer::Enter() {
	if (!locked) {
		SDL_Rect r {0, 0, w, h};
		void* pixels;
		SDL_LockTexture(fb, &r, &pixels, &pitch);
		this->pixels = (byte*)pixels;
		locked = true;
	}
}

void SdlOutputFramebuffer::Leave() {
	if (locked) {
		SDL_UnlockTexture(fb);
		locked = false;
	}
}

byte* SdlOutputFramebuffer::GetIterator(int x, int y) {
	ASSERT(pixels);
	return &pixels[x * stride + y * pitch];
}

/*int SdlOutputFramebuffer::GetWidth() const {
	return w;
}

int SdlOutputFramebuffer::GetHeight() const {
	return h;
}

int SdlOutputFramebuffer::GetStride() const {
	return stride;
}

int SdlOutputFramebuffer::GetPitch() const {
	return pitch;
}*/

void SdlOutputFramebuffer::DrawFill(const byte* mem, int sz) {
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




void SdlCpuRenderer::PreFrame() {
	output.Create(output_sz.cx, output_sz.cy, 3);
}

void SdlCpuRenderer::PostFrame() {
	RawSysTexture* fb = output.GetRawSysTexture();
	
	TODO
	/*if (rend && fb) {
		SDL_RenderCopy(rend, fb, NULL, NULL);
		SDL_RenderPresent(rend);
	}*/
	
}









void SdlDrawFramebuffer::DrawImageMemory(const byte* mem, int sz, int x, int y, int w, int h, int ch_var_size, int channels) {
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

void SdlDrawFramebuffer::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	ASSERT(fb);
	if (!fb) return;
	if (width == 1)
		fb->DrawLine(x1, y1, x2, y2, color);
	else {
		TODO
	}
}

void SdlDrawFramebuffer::DrawRectOp(int x, int y, int cx, int cy, Color color) {
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

void SdlDrawFramebuffer::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
	                        Color ink, int n, const int *dx) {
	TODO
}

void SdlDrawFramebuffer::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
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

bool SdlDrawFramebuffer::ClipOp(const Rect& r) {
	TODO
}

void SdlDrawFramebuffer::EndOp() {
	TODO
}

#endif

NAMESPACE_PARALLEL_END

#endif
