#include "GuboCore.h"

NAMESPACE_TOPSIDE_BEGIN


void SDraw3::Init(const Cubf& r) {
	this->sz = r.GetSize();
	this->sz.cx += max(0.0f, r.left);
	this->sz.cy += max(0.0f, r.top);
	this->sz.cz += max(0.0f, r.near);
	
	cur_area = r;
	ops.Clear();
	ops.Add().cur_area = r;
	
	/*Point tl = r.TopLeft();
	if (tl.x != 0 || tl.y != 0)
		Offset(tl);*/
	
}
NAMESPACE_TOPSIDE_END

#include "GuboCore.h"

NAMESPACE_TOPSIDE_BEGIN


dword SDraw3::GetInfo() const { return 0; }


void SDraw3::Finish() {
	ASSERT(ops.GetCount() == 1);
	ops.Clear();
}

Volf SDraw3::GetPageSize() const {
	return sz;
}

void SDraw3::DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) {
	if (width == 1) {
		if (x1 == x2 && y1 == y2 && z1 == z2)
			SDraw3::DrawPixel(x1, GetHeight() - 1 - y1, z1, color);
		else
			SDraw3::DrawLine(x1, y1, z1, x2, y2, z2, color);
	}
	else {
		TODO
	}
}

void SDraw3::DrawBoxOp(float x, float y, float z, float cx, float cy, float cz, Color color) {
	float w = GetWidth();
	float h = GetHeight();
	float d = GetDepth();
	float x0 = max(0.0f, min(w-1, x));
	float x1 = max(0.0f, min(w-1, x+cx));
	float y0 = max(0.0f, min(h-1, y));
	float y1 = max(0.0f, min(h-1, y+cy));
	float z0 = max(0.0f, min(d-1, z));
	float z1 = max(0.0f, min(d-1, z+cz));
	
	TODO
	//for(int y = y0; y <= y1; y++)
	//	DrawHLine(x0, x1, y, color);
}

void SDraw3::DrawTextOp(float x, float y, float z, int angle, const wchar *text, Font font,
	            Color ink, int n, const int *dx) {
	// TODO: improve and take other params into acoount
	String s = WString(text).ToString();
	Image img = RenderTextBlended(font, s, ink);
	DrawImageOp(x, y, z, img.GetWidth(), img.GetHeight(), 0.01, img, img.GetSize(), Color());
}

void SDraw3::DrawPolyPolylineOp(const Point3f *vertices, int vertex_count,
                        const int *counts, int count_count,
                        float width, Color color, Color doxor) {
	if (width <= 1) {
	    const Point3f *it = vertices;
		for(int i = 0; i < count_count; i++) {
			int count = counts[i];
			if (count >= 2) {
				const Point3f* end = it + count;
				Point3f a = *it++;
				while (it != end) {
					Point3f b = *it++;
					DrawLine(a.x, a.y, a.z, b.x, b.y, b.z, color);
					Swap(a, b);
				}
			}
		}
	}
	else {
		TODO
	}
}

bool SDraw3::ClipoffOp(const Cubf& r0) {
	ASSERT(!cur_area.IsEmpty());
	Cubf r = r0;
	r.left = max(0.f, r.left);
	r.right = max(0.f, r.right);
	r.top = max(0.f, r.top);
	r.bottom = max(0.f, r.bottom);
	
	Cubf new_area = CubfC(
		cur_area.left + r.left,
		cur_area.top + r.top,
		cur_area.near + r.near,
		r.GetWidth(),
		r.GetHeight(),
		r.GetDepth());
	
	new_area.left = min(cur_area.right, new_area.left);
	new_area.right = min(cur_area.right, new_area.right);
	new_area.top = min(cur_area.bottom, new_area.top);
	new_area.bottom = min(cur_area.bottom, new_area.bottom);
	
	Op& o = ops.Add();
	o.cur_area = cur_area;
	cur_area = new_area;
	
	return new_area.GetWidth() > 0 && new_area.GetHeight() > 0;
}

bool SDraw3::ClipOp(const Cubf& r0) {
	return true;
}

void SDraw3::EndOp() {
	Op& o = ops.Top();
	cur_area = o.cur_area;
	ops.SetCount(ops.GetCount()-1);
}

void SDraw3::DrawImageOp(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Rect& src, Color color) {
	byte alpha = 255;
	Size sz = img.GetSize();
	Cubf r = CubfC(x, y, z, sz.cx, sz.cy, 0.01);
	if (!DoOps(r))
		return;
	
	float x0 = x, y0 = y, z0 = z;
	DoOpsX(x0);
	DoOpsY(y0);
	DoOpsY(z0);
	
	
	TODO
	#if 0
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
	#endif
}

#if 0
void SDraw3::DrawTriangle(Point a, Point b, Point c, RGBA clr) {
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

byte* SDraw3::GetIterator(float x, float y, float z) {
	ASSERT(pixels);
	if (!pixels) return 0;
	return &pixels[x * stride + y * pitch];
}

void SDraw3::Zero() {
	if (pixels)
		memset(pixels, 0, GetLength());
}

void SDraw3::SwapRG() {
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

void SDraw3::DrawPixel0(byte* data, int stride, int pitch, float x, float y, float z, Color color) {
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

#endif

byte SDraw3::AtRGBA(RGBA rgba, int i) {
	ASSERT(i >= 0 && i < 4);
	switch (i) {
		case 0: return rgba.r;
		case 1: return rgba.g;
		case 2: return rgba.b;
		case 3: return rgba.a;
	}
	return 0;
}


void SDraw3::DrawPixel(float x, float y, float z, Color color) {
	if (!DoOpsX(x) || !DoOpsY(y) || !DoOpsY(z))
		return;
	
	TODO
	/*float width = GetWidth();
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
	}*/
}
/*
void SDraw3::DrawHLine(int x0, int x1, int y, Color color) {
	if (!DoOpsHorz(x0, x1) || !DoOpsY(y))
		return;
	
	if (x0 > x1) Swap(x0, x1);
	
	float width = GetWidth();
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
*/
bool SDraw3::DoOpsX(float& x) {
	x += cur_area.left;
	return x < cur_area.right && x >= cur_area.left;
}

bool SDraw3::DoOpsY(float& y) {
	y += cur_area.top;
	return y < cur_area.bottom && y >= cur_area.top;
}

bool SDraw3::DoOpsZ(float& z) {
	z += cur_area.near;
	return z < cur_area.far && z >= cur_area.near;
}

bool SDraw3::DoOps(Cubf& r) {
	r.left += cur_area.left;
	r.right += cur_area.left;
	r.top += cur_area.top;
	r.bottom += cur_area.top;
	if (r.right <= cur_area.left || r.left >= cur_area.right ||
		r.bottom <= cur_area.top || r.top >= cur_area.bottom)
		return false;
	return true;
}


void SDraw3::StartPage() {TODO}
void SDraw3::EndPage() {TODO}
void SDraw3::BeginOp() {TODO}
void SDraw3::OffsetOp(Point3f p) {TODO}
bool SDraw3::ExcludeClipOp(const Cubf& r) {TODO}
bool SDraw3::IntersectClipOp(const Cubf& r) {TODO}
bool SDraw3::IsPaintingOp(const Cubf& r) const {TODO}
Cubf SDraw3::GetPaintCubf() const {TODO}
void SDraw3::SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, Color color) {TODO}
void SDraw3::SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, const Rect& src, Color color) {TODO}
void SDraw3::DrawDataOp(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *id) {TODO}
void SDraw3::DrawPolyPolyPolygonOp(const Point3f *vertices, int vertex_count,
                           const int *subpolygon_counts, int scc,
                           const int *disjunct_polygon_counts, int dpcc,
                           Color color, float width, Color outline,
                           uint64 pattern, Color doxor) {TODO}
void SDraw3::DrawArcOp(const Cubf& rc, Point3f start, Point3f end, float width, Color color) {TODO}
void SDraw3::DrawEllipseOp(const Cubf& r, Color color, float pen, Color pencolor) {TODO}
void SDraw3::DrawDrawingOp(const Cubf& target, const Drawing& w) {TODO}
void SDraw3::DrawPaintingOp(const Cubf& target, const Painting& w) {TODO}
Volf SDraw3::GetNativeDpi() const {TODO}
void SDraw3::BeginNative() {TODO}
void SDraw3::EndNative() {TODO}
int  SDraw3::GetCloffLevel() const {TODO}
void SDraw3::Escape(const String& data) {TODO}


NAMESPACE_TOPSIDE_END
