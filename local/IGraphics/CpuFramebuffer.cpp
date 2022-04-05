#include "IGraphics.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN



void CpuFramebuffer::DrawPixel0(byte* data, int stride, int pitch, int x, int y, Color color) {
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

byte CpuFramebuffer::AtRGBA(RGBA rgba, int i) {
	ASSERT(i >= 0 && i < 4);
	switch (i) {
		case 0: return rgba.r;
		case 1: return rgba.g;
		case 2: return rgba.b;
		case 3: return rgba.a;
	}
	return 0;
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
			it[i] = AtRGBA(color, i);
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


NAMESPACE_TOPSIDE_END
#endif
