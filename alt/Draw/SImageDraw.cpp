#include "Draw.h"

NAMESPACE_UPP


void SImageDraw::Create(Size sz) {
	Create(sz, 4);
}

void SImageDraw::Create(Size sz, int stride) {
	this->stride = stride;
	this->sz = sz;
	int len = sz.cx * sz.cy * stride;
	pitch = sz.cx * stride;
	pixels.SetCount(len);
	
	cur_area = sz;
	//Zero();
}

void SImageDraw::Finish() {
	
}

Size SImageDraw::GetPageSize() const {
	return sz;
}

void SImageDraw::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	if (width == 1) {
		if (x1 == x2 && y1 == y2)
			SImageDraw::DrawPixel(x1, GetHeight() - 1 - y1, color);
		else
			SImageDraw::DrawLine(x1, y1, x2, y2, color);
	}
	else {
		TODO
	}
}

void SImageDraw::DrawRectOp(int x, int y, int cx, int cy, Color color) {
	int w = GetWidth();
	int h = GetHeight();
	int x0 = max(0, min(w-1, x));
	int x1 = max(0, min(w-1, x+cx));
	int y0 = max(0, min(h-1, y));
	int y1 = max(0, min(h-1, y+cy));
	for(int y = y0; y <= y1; y++)
		DrawHLine(x0, x1, y, color);
}

void SImageDraw::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
	            Color ink, int n, const int *dx) {
	TODO
}

void SImageDraw::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
                        const int *counts, int count_count,
                        int width, Color color, Color doxor) {
	if (width <= 1) {
	    const Point *it = vertices;
		for(int i = 0; i < count_count; i++) {
			int count = counts[i];
			if (count >= 2) {
				const Point* end = it + count;
				Point a = *it++;
				while (it != end) {
					Point b = *it++;
					DrawLine(a.x, a.y, b.x, b.y, color);
					Swap(a, b);
				}
			}
		}
	}
	else {
		TODO
	}
}

bool SImageDraw::ClipOp(const Rect& r) {
	/*ASSERT(r == cur_area);
	Op& o = ops.Add();
	o.cur_area = cur_area;
	cur_area = r;*/
	return true;
}

void SImageDraw::EndOp() {
	/*Op& o = ops.Top();
	cur_area = o.cur_area;
	ops.SetCount(ops.GetCount()-1);*/
}

void SImageDraw::DrawImage(int x, int y, Image img, byte alpha) {
	//TODO
}

void SImageDraw::DrawTriangle(Point a, Point b, Point c, RGBA clr) {
	// sort the vertices, t0, t1, t2 lower−to−upper (bubblesort yay!)
	if (a.y > b.y) Swap(a, b);
	if (a.y > c.y) Swap(a, c);
	if (b.y > c.y) Swap(b, c);
	
	bool lower = true;
	bool upper = true;
	
	int total_height = c.y - a.y;
	if (lower) {
		for (int y = a.y; y <= b.y; y++) {
			int segment_height = b.y - a.y + 1;
			float alpha = (float)(y - a.y) / total_height;
			float beta  = (float)(y - a.y) / segment_height; // be careful with divisions by zero
			Point A = a + (c - a) * alpha;
			Point B = a + (b - a) * beta;
			if (A.x > B.x) Swap(A, B);
			/*if (border) {
				fb.DrawLine(A.x, y, A.x, y, 1, red);
				fb.DrawLine(B.x, y, B.x, y, 1, green);
				if (fill)
					fb.DrawHLine(A.x, B.x, y, 1, white);
			}
			else*/
				DrawHLine(A.x, B.x, y, clr);
		}
	}
	
	if (upper) {
		for (int y = b.y; y <= c.y; y++) {
			int segment_height =  c.y - b.y + 1;
			float alpha = (float)(y - a.y) / total_height;
			float beta  = (float)(y - b.y) / segment_height; // be careful with divisions by zero
			Point A = a + (c - a) * alpha;
			Point B = b + (c - b) * beta;
			if (A.x > B.x) Swap(A, B);
			/*if (border) {
				fb.DrawLine(A.x, y, A.x, y, 1, red);
				fb.DrawLine(B.x, y, B.x, y, 1, green);
				if (fill)
					fb.DrawHLine(A.x, B.x, y, 1, white);
			}
			else*/
				DrawHLine(A.x, B.x, y, clr);
		}
	}
}

byte* SImageDraw::GetIterator(int x, int y) {
	ASSERT(!pixels.IsEmpty());
	return &pixels[x * stride + y * pitch];
}

void SImageDraw::Zero() {
	memset(pixels.Begin(), 0, pixels.GetCount());
}

void SImageDraw::DrawPixel0(byte* data, int stride, int pitch, int x, int y, Color color) {
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

byte SImageDraw::AtRGBA(RGBA rgba, int i) {
	ASSERT(i >= 0 && i < 4);
	switch (i) {
		case 0: return rgba.r;
		case 1: return rgba.g;
		case 2: return rgba.b;
		case 3: return rgba.a;
	}
	return 0;
}

void SImageDraw::DrawPixel(int x, int y, RGBA color) {
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

void SImageDraw::DrawPixel(int x, int y, Color color) {
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

void SImageDraw::DrawHLine(int x0, int x1, int y, Color color) {
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

void SImageDraw::DrawLine(int x0, int y0, int x1, int y1, Color color) {
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




END_UPP_NAMESPACE
