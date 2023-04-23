#include "Draw.h"
#include <StaticInterface/StaticInterface.h>

NAMESPACE_UPP

#if 0
DrawCommand& DrawCommandCache::Get() {
	if (unused.IsEmpty()) {
		DrawCommand& cmd = owned.Add();
		cmd.type = 0;
		cmd.is_cached = true;
		return cmd;
	}
	DrawCommand& cmd = *unused.Pop();
	cmd.next = NULL;
	cmd.prev = NULL;
	cmd.type = 0;
	cmd.is_cached = true;
	return cmd;
}

void DrawCommandCache::Return(DrawCommand* cmd) {
	unused.Add(cmd);
}
#endif


void SDraw::Init(const Rect& r) {
	this->sz = r.GetSize();
	this->sz.cx += max(0, r.left);
	this->sz.cy += max(0, r.top);
	
	cur_area = r;
	ops.Clear();
	ops.Add().cur_area = r;
	
	/*Point tl = r.TopLeft();
	if (tl.x != 0 || tl.y != 0)
		Offset(tl);*/
	
}

dword SDraw::GetInfo() const { return 0; }


void SDraw::Finish() {
	ASSERT(ops.GetCount() == 1);
	ops.Clear();
}

Size SDraw::GetPageSize() const {
	return sz;
}

void SDraw::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	if (width == 1) {
		if (x1 == x2 && y1 == y2)
			SDraw::DrawPixel(x1, GetHeight() - 1 - y1, color);
		else
			SDraw::DrawLine(x1, y1, x2, y2, color);
	}
	else {
		TODO
	}
}

void SDraw::DrawRectOp(int x, int y, int cx, int cy, Color color) {
	int w = GetWidth();
	int h = GetHeight();
	int x0 = max(0, min(w-1, x));
	int x1 = max(0, min(w-1, x+cx));
	int y0 = max(0, min(h-1, y));
	int y1 = max(0, min(h-1, y+cy));
	for(int y = y0; y <= y1; y++)
		DrawHLine(x0, x1, y, color);
}

void SDraw::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
	            Color ink, int n, const int *dx) {
	// TODO: improve and take other params into acoount
	String s = WString(text).ToString();
	Image img = RenderTextBlended(font, s, ink);
	DrawImageOp(x, y, img.GetWidth(), img.GetHeight(), img, img.GetSize(), Color());
}

void SDraw::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
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

bool SDraw::ClipoffOp(const Rect& r0) {
	ASSERT(!cur_area.IsEmpty());
	Rect r = r0;
	r.left = max(0, r.left);
	r.right = max(0, r.right);
	r.top = max(0, r.top);
	r.bottom = max(0, r.bottom);
	
	Rect new_area = RectC(
		cur_area.left + r.left,
		cur_area.top + r.top,
		r.GetWidth(),
		r.GetHeight());
	
	new_area.left = min(cur_area.right, new_area.left);
	new_area.right = min(cur_area.right, new_area.right);
	new_area.top = min(cur_area.bottom, new_area.top);
	new_area.bottom = min(cur_area.bottom, new_area.bottom);
	
	Op& o = ops.Add();
	o.cur_area = cur_area;
	cur_area = new_area;
	
	return new_area.GetWidth() > 0 && new_area.GetHeight() > 0;
}

bool SDraw::ClipOp(const Rect& r0) {
	return true;
}

void SDraw::EndOp() {
	Op& o = ops.Top();
	cur_area = o.cur_area;
	ops.SetCount(ops.GetCount()-1);
}

void SDraw::DrawImageOp(int x, int y, int cx, int cy, const Image& img, const Rect& src, Color color) {
	byte alpha = 255;
	Size sz = img.GetSize();
	Rect r = RectC(x, y, sz.cx, sz.cy);
	if (!DoOps(r))
		return;
	
	int x0 = x, y0 = y;
	DoOpsX(x0);
	DoOpsY(y0);
	
	int src_x0 = r.left - x0;
	int src_y0 = r.top - y0;
	int src_x1 = r.right - x0;
	int src_y1 = r.bottom - y0;
	int src_stride = img.GetStride();
	int src_pitch = img.GetPitch();
	const byte* begin = img.Begin();
	const byte* row_begin = begin +(src_x0 * src_stride + src_y0 * src_pitch);
	bool src_alpha = src_stride == 4;
	
	int stride = GetStride();
	int common_stride = min(stride, src_stride);
	
	for (int yi = src_y0; yi < src_y1; yi++) {
		int dst_x = r.left + src_x0;
		int dst_y = r.top + yi;
		byte* it = GetIterator(dst_x, dst_y);
		const byte* src = row_begin;
		
		for (int xi = src_x0; xi < src_x1; xi++) {
			byte pix_alpha = src_alpha ? (byte)(((int)alpha * (int)src[3]) / 256) : alpha;
			if (pix_alpha == 255) {
				for(int i = 0; i < common_stride; i++) {
					//it[i] = 255;
					it[i] = src[i];
				}
			}
			else {
				for(int i = 0; i < common_stride; i++) {
					it[i] = ((int)src[i] * (int)pix_alpha + (int)it[i] * (int)(255 - pix_alpha)) / (int)255;
				}
			}
			
			it += stride;
			src += src_stride;
		}
		
		row_begin += src_pitch;
	}
}

#if 0
void SDraw::DrawTriangle(Point a, Point b, Point c, RGBA clr) {
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
			DrawHLine(A.x, B.x, y, clr);
		}
	}
}
#endif

byte* SDraw::GetIterator(int x, int y) {
	ASSERT(pixels);
	if (!pixels) return 0;
	return &pixels[x * stride + y * pitch];
}

void SDraw::Zero() {
	if (pixels)
		memset(pixels, 0, GetLength());
}

void SDraw::SwapRG() {
	if (!pixels) return;
	int len = GetLength();
	byte* it = pixels;
	byte* end = it + len;
	int s = stride;
	while (it != end) {
		byte b = it[0];
		it[0] = it[2];
		it[2] = b;
		it += s;
	}
}

void SDraw::DrawPixel0(byte* data, int stride, int pitch, int x, int y, Color color) {
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

byte SDraw::AtRGBA(RGBA rgba, int i) {
	ASSERT(i >= 0 && i < 4);
	switch (i) {
		case 0: return rgba.r;
		case 1: return rgba.g;
		case 2: return rgba.b;
		case 3: return rgba.a;
	}
	return 0;
}

void SDraw::DrawPixel(int x, int y, RGBA color) {
	if (!DoOpsX(x) || !DoOpsY(y))
		return;
	
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

void SDraw::DrawPixel(int x, int y, Color color) {
	if (!DoOpsX(x) || !DoOpsY(y))
		return;
	
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

void SDraw::DrawHLine(int x0, int x1, int y, Color color) {
	if (!DoOpsHorz(x0, x1) || !DoOpsY(y))
		return;
	
	if (x0 > x1) Swap(x0, x1);
	
	int width = GetWidth();
	int height = GetHeight();
	//y = height - 1 - y;
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

void SDraw::DrawLine(int x0, int y0, int x1, int y1, Color color) {
	DoOpsX(x0);
	DoOpsX(x1);
	DoOpsY(y0);
	DoOpsY(y1);
	
	byte* data = GetIterator(0, 0);
	int pitch = GetPitch();
	int stride = GetStride();
	int width = GetWidth();
	int height = GetHeight();
	//y0 = height - 1 - y0;
	//y1 = height - 1 - y1;
	
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

bool SDraw::DoOpsX(int& x) {
	x += cur_area.left;
	return x < cur_area.right && x >= cur_area.left;
}

bool SDraw::DoOpsY(int& y) {
	y += cur_area.top;
	return y < cur_area.bottom && y >= cur_area.top;
}

bool SDraw::DoOpsHorz(int& x0, int& x1) {
	x0 += cur_area.left;
	x1 += cur_area.left;
	if ((x0 < cur_area.left && x1 < cur_area.left) || (x0 >= cur_area.right && x1 >= cur_area.right))
		return false;
	x0 = max(cur_area.left, min(cur_area.right-1, x0));
	x1 = max(cur_area.left, min(cur_area.right-1, x1));
	return true;
}

bool SDraw::DoOps(Rect& r) {
	r.left += cur_area.left;
	r.right += cur_area.left;
	r.top += cur_area.top;
	r.bottom += cur_area.top;
	if (r.right <= cur_area.left || r.left >= cur_area.right ||
		r.bottom <= cur_area.top || r.top >= cur_area.bottom)
		return false;
	return true;
}

Image SDraw::GetImage() {
	RawSysImage* img = new RawSysImage();
	
	int len = GetLength();
	img->data.SetCount(len);
	if (len)
		memcpy(img->data.Begin(), pixels, len);
	img->w = sz.cx;
	img->h = sz.cy;
	img->ch = stride;
	img->pitch = pitch;
	
	return img;
}


void SDraw::StartPage() {TODO}
void SDraw::EndPage() {TODO}
void SDraw::BeginOp() {TODO}
void SDraw::OffsetOp(Point p) {TODO}
bool SDraw::ExcludeClipOp(const Rect& r) {TODO}
bool SDraw::IntersectClipOp(const Rect& r) {TODO}
bool SDraw::IsPaintingOp(const Rect& r) const {TODO}
Rect SDraw::GetPaintRect() const {TODO}
void SDraw::SysDrawImageOp(int x, int y, const Image& img, Color color) {TODO}
void SDraw::SysDrawImageOp(int x, int y, const Image& img, const Rect& src, Color color) {TODO}
void SDraw::DrawDataOp(int x, int y, int cx, int cy, const String& data, const char *id) {TODO}
void SDraw::DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
                           const int *subpolygon_counts, int scc,
                           const int *disjunct_polygon_counts, int dpcc,
                           Color color, int width, Color outline,
                           uint64 pattern, Color doxor) {TODO}
void SDraw::DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color) {TODO}
void SDraw::DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor) {TODO}
void SDraw::DrawDrawingOp(const Rect& target, const Drawing& w) {TODO}
void SDraw::DrawPaintingOp(const Rect& target, const Painting& w) {TODO}
Size SDraw::GetNativeDpi() const {TODO}
void SDraw::BeginNative() {TODO}
void SDraw::EndNative() {TODO}
int  SDraw::GetCloffLevel() const {TODO}
void SDraw::Escape(const String& data) {TODO}
Color SDraw::GetDefaultInk() const {TODO}

SImageDraw& SImageDraw::Alpha() {
	TODO
}

END_UPP_NAMESPACE
