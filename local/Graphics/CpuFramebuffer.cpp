#include "GL.h"

NAMESPACE_TOPSIDE_BEGIN


void CpuFramebuffer::Zero() {
	int pitch = GetPitch();
	int height = GetHeight();
	byte* begin = GetIterator(0, 0);
	memset(begin, 0, height*pitch);
}

void DrawPixel0(byte* data, int stride, int pitch, int x, int y, Color color) {
	ASSERT(data);
	data += x * stride + y * pitch;
	RGBA c = color;
	if (stride == 3) {
		data[0] = c.r;
		data[1] = c.g;
		data[2] = c.b;
	}
	else if (stride == 4) {
		data[0] = c.r;
		data[1] = c.g;
		data[2] = c.b;
		data[3] = 255;
	}
	else {
		byte gray = ((int)c.r + (int)c.g + (int)c.b) / 3;
		for(int i = 0; i < stride; i++)
			data[i] = gray;
	}
}

void CpuFramebuffer::DrawPixel(int x, int y, RGBA color) {
	int width = GetWidth();
	int height = GetHeight();
	if (x >= 0 && x < width &&
		y >= 0 && y < height) {
		int stride = GetStride();
		byte* it = GetIterator(x, y);
		ASSERT(it);
		for(int i = 0; i < stride; i++)
			it[i] = Topside::AtRGBA(color, i);
	}
}

void CpuFramebuffer::DrawPixel(int x, int y, Color color) {
	int width = GetWidth();
	int height = GetHeight();
	RGBA c = color;
	if (x >= 0 && x < width &&
		y >= 0 && y < height) {
		int stride = GetStride();
		byte* it = GetIterator(x, y);
		ASSERT(it);
		if (stride == 3) {
			it[0] = c.r;
			it[1] = c.g;
			it[2] = c.b;
		}
		else if (stride == 4) {
			it[0] = c.r;
			it[1] = c.g;
			it[2] = c.b;
			it[3] = 255;
		}
		else {
			byte gray = ((int)c.r + (int)c.g + (int)c.b) / 3;
			for(int i = 0; i < stride; i++)
				it[i] = gray;
		}
	}
}

void CpuFramebuffer::DrawHLine(int x0, int x1, int y, Color color) {
	if (x0 > x1) Swap(x0, x1);
	
	int width = GetWidth();
	int height = GetHeight();
	y = height - 1 - y;
	if (y < 0 || y >= height) return;
	x0 = std::max(0, std::min(width-1, x0));
	x1 = std::max(0, std::min(width-1, x1));
	
	int stride = GetStride();
	byte* it = GetIterator(x0, y);
	ASSERT(it);
	RGBA c = color;
	if (stride == 3) {
		for(int x = x0; x <= x1; x++) {
			it[0] = c.r;
			it[1] = c.g;
			it[2] = c.b;
			it += 3;
		}
	}
	else  if (stride == 4) {
		for(int x = x0; x <= x1; x++) {
			it[0] = c.r;
			it[1] = c.g;
			it[2] = c.b;
			it[3] = 255;
			it += 4;
		}
	}
	else {
		byte gray = ((int)c.r + (int)c.g + (int)c.b) / 3;
		for(int x = x0; x <= x1; x++) {
			for(int i = 0; i < stride; i++)
				it[i] = gray;
			it += stride;
		}
	}
}

void CpuFramebuffer::DrawLine(int x0, int y0, int x1, int y1, Color color) {
	byte* data = GetIterator(0, 0);
	int pitch = GetPitch();
	int stride = GetStride();
	int width = GetWidth();
	int height = GetHeight();
	y0 = height - 1 - y0;
	y1 = height - 1 - y1;
	
	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int derror2 = std::abs(dy) * 2;
	int error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {
		if (steep) {
			if (x >= 0 && x < height && y >= 0 && y < width)
				DrawPixel0(data, stride, pitch, y, x, color);
		}
		else {
			if (x >= 0 && x < width && y >= 0 && y < height)
				DrawPixel0(data, stride, pitch, x, y, color);
		}
		
		error2 += derror2;
		if (error2 > dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}







void CpuFramebufferDraw::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	ASSERT(fb);
	if (!fb) return;
	if (width == 1)
		fb->DrawLine(x1, y1, x2, y2, color);
	else {
		TODO
	}
}

void CpuFramebufferDraw::DrawRectOp(int x, int y, int cx, int cy, Color color) {
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

void CpuFramebufferDraw::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
	                        Color ink, int n, const int *dx) {
	TODO
}

void CpuFramebufferDraw::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
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

NAMESPACE_TOPSIDE_END
