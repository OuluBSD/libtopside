#include "Draw.h"

NAMESPACE_UPP




Draw::~Draw() {
	
}

Color Draw::GetDefaultInk() const
{
	dword w = GetInfo();
	if(w & DRAWING)
		return DefaultInk();
	if(w & DOTS)
		return Black();
	return SColorText();
}

void Draw::DrawEllipse(int x, int y, int cx, int cy, Color color,
		             int pen, Color pencolor) {
	TODO
}

#if 0

void Draw::DrawLine(int x1, int y1, int x2, int y2, int width, Color color) {
	DrawLineOp(x1, y1, x2, y2, width, color);
}

void Draw::DrawText(int x, int y, const String& text, Font font, Color ink, const int *dx) {
	WString ws(ToWString(text));
	DrawTextOp(x, y, 0, ws.Begin(), font, ink, 0, dx);
}

void Draw::DrawText(int x, int y, const char* text, Font font, Color ink, const int *dx) {
	DrawText(x, y, String(text), font, ink, dx);
}
	          
void Draw::DrawText(int x, int y, const WString& text, Font font, Color ink, const int *dx) {
	DrawText(x, y, text.ToString(), font, ink, dx);
}

void Draw::DrawRect(int x, int y, int cx, int cy, Color color) {
	DrawRectOp(x, y, cx, cy, color);
}

void Draw::DrawRect(const Rect& rect, Color color) {
	DrawRectOp(rect.top, rect.top, rect.Width(), rect.Height(), color);
}

void Draw::DrawRect(ts::Rect_<int> const&, ts::Color) {
	TODO
}

void Draw::DrawPolyline(const Point *vertices, int count, int width, Color color, Color doxor) {
	DrawPolyPolylineOp(vertices, count, &count, 1, width, color, doxor);
}

void Draw::DrawPolyline(const Vector<Point>& vertices, int width, Color color, Color doxor) {
	int count = vertices.GetCount();
	DrawPolyPolylineOp(vertices.Begin(), count, &count, 1, width, color, doxor);
}

void Draw::DrawImage(int x, int y, const Image& img) {
	DrawImage(x, y, img, 255);
}

void Draw::DrawImage(int x, int y, const Image& img, const Rect& src) {
	TODO
}

void Draw::DrawImage(int x, int y, int cx, int cy, const Image& img) {
	TODO
}

void Draw::DrawEllipse(const Rect& r, Color color, int pen, Color pencolor) {
	TODO
}

void Draw::DrawEllipse(int x, int y, int cx, int cy, Color color, int pen, Color pencolor) {
	TODO
}

#endif

void Draw::DrawPolygon(const Vector<Point>& vertices, Color color, int width, Color outline, uint64 pattern, Color doxor) {
	int tris = vertices.GetCount() / 3;
	for(int i = 0; i < tris; i++) {
		int off = i * 3;
		const Point& a = vertices[off + 0];
		const Point& b = vertices[off + 1];
		const Point& c = vertices[off + 2];
		TODO //DrawTriangle(a, b, c, color);
	}
}


void Draw::DrawText(int x, int y, const wchar *text, Font font,
                    Color ink, int n, const int *dx)
{
	DrawText(x, y, 0, text, font, ink, n, dx);
}

// ---------------------------

void Draw::DrawText(int x, int y, int angle, const WString& text, Font font,
                    Color ink, const int *dx)
{
	DrawText(x, y, angle, ~text, font, ink, text.GetLength(), dx);
}

void Draw::DrawText(int x, int y, const WString& text, Font font, Color ink, const int *dx)
{
	DrawText(x, y, 0, text, font, ink, dx);
}

void Draw::DrawText(int x, int y, int angle, const wchar_t *text, Font font,
		          Color ink, int n, const int *dx) {
	TODO
}

// ---------------------------

void Draw::DrawText(int x, int y, int angle, const char *text, byte charset, Font font,
                    Color ink, int n, const int *dx)
{
	TODO //DrawText(x, y, angle, TextUnicode(text, n, charset, font), font, ink, dx);
}

void Draw::DrawText(int x, int y, const char *text, byte charset, Font font,
                    Color ink, int n, const int *dx)
{
	DrawText(x, y, 0, text, charset, font, ink, n, dx);
}

// ---------------------------

void Draw::DrawText(int x, int y, int angle, const char *text,
                    Font font, Color ink, int n, const int *dx)
{
	TODO //DrawText(x, y, angle, text, CHARSET_DEFAULT, font, ink, n, dx);
}

void Draw::DrawText(int x, int y, const char *text, Font font,
                    Color ink, int n, const int *dx)
{
	TODO //DrawText(x, y, text, CHARSET_DEFAULT, font, ink, n, dx);
}

// ---------------------------

void Draw::DrawText(int x, int y, int angle, const String& text, Font font,
                    Color ink, const int *dx)
{
	DrawText(x, y, angle, text, font, ink, text.GetLength(), dx);
}

void Draw::DrawText(int x, int y, const String& text, Font font, Color ink, const int *dx)
{
	//WString h = TextUnicode(text, text.GetLength(), CHARSET_DEFAULT, font);
	WString h = text.ToWString();
	DrawTextOp(x, y, 0, h.Begin(), font, ink, h.GetLength(), dx);
}

void Draw::DrawPolyline(const Point *vertices, int count,
                        int width, Color color, Color doxor)
{
	DrawPolyPolyline(vertices, count, &count, 1, width, color, doxor);
}

void Draw::DrawPolyline(const Vector<Point>& vertices,
                        int width, Color color, Color doxor)
{
	DrawPolyline(vertices.Begin(), vertices.GetCount(), width, color, doxor);
}

void Draw::DrawRect(const Rect& rect, Color color)
{
	DrawRect(rect.left, rect.top, rect.GetWidth(), rect.GetHeight(), color);
}

void Draw::DrawRect(int x, int y, int cx, int cy, Color color)
{
	DrawRectOp(x, y, cx, cy, color);
}

void Draw::DrawLine(Point p1, Point p2, int width, Color color)
{
	DrawLine(p1.x, p1.y, p2.x, p2.y, width, color);
}

void Draw::DrawLine(int x1, int y1, int x2, int y2, int width, Color color)
{
	DrawLineOp(x1, y1, x2, y2, width, ResolveInk(color));
}

Size Draw::GetPageSize() const
{
	return Size(INT_MAX / 2, INT_MAX / 2);
}

void Draw::StartPage() {}
void Draw::EndPage() {}

Rect Draw::GetPaintRect() const
{
	return Rect(-(INT_MAX / 2), -(INT_MAX / 2), INT_MAX / 2, INT_MAX / 2);
}

void Draw::SysDrawImageOp(int x, int y, const Image& img, Color color)
{
	NEVER();
}

void Draw::SysDrawImageOp(int x, int y, const Image& img, const Rect& src, Color color)
{
	if(src == Rect(img.GetSize()))
		SysDrawImageOp(x, y, img, color);
	else {
		Clipoff(x, y, src.GetWidth(), src.GetHeight());
		SysDrawImageOp(-src.left, -src.top, img, color);
		End();
	}
}

void Draw::DrawImageOp(int x, int y, int cx, int cy, const Image& img, const Rect& src, Color color)
{
	TODO
}

void Draw::DrawDataOp(int x, int y, int cx, int cy, const String& data, const char *id)
{
	TODO
}

void Draw::DrawDrawingOp(const Rect& target, const Drawing& w) {
	TODO
}

void Draw::DrawPaintingOp(const Rect& target, const Painting& pw) {
	TODO
}

Size Draw::GetNativeDpi() const { return Size(96, 96); }

void Draw::BeginNative() {}
void Draw::EndNative() {}
int Draw::GetCloffLevel() const { return 0; }
void Draw::Escape(const String& data) {}

void Draw::DrawImage(int x, int y, const Image& img)
{
	Size sz = img.GetSize();
	DrawImageOp(x, y, sz.cx, sz.cy, img, img.GetSize(), Null);
}

bool Draw::Clipoff(int x, int y, int cx, int cy) {
	return Clipoff(RectC(x,y,cx,cy));
}

bool Draw::Clip(int x, int y, int cx, int cy) {
	return Clip(RectC(x,y,cx,cy));
}
void Draw::DrawPolyPolyline(const Point *vertices, int vertex_count,
                            const int *counts, int count_count,
                            int width, Color color, Color doxor)
{
	DrawPolyPolylineOp(vertices, vertex_count, counts, count_count, width,
	                   ResolveInk(color), doxor);
}




dword DrawProxy::GetInfo() const
{
	return ptr->GetInfo();
}

Size DrawProxy::GetPageSize() const
{
	return ptr->GetPageSize();
}

void DrawProxy::StartPage()
{
	ptr->StartPage();
}

void DrawProxy::EndPage()
{
	ptr->EndPage();
}

void DrawProxy::BeginOp()
{
	ptr->BeginOp();
}

void DrawProxy::EndOp()
{
	ptr->EndOp();
}

void DrawProxy::OffsetOp(Point p)
{
	ptr->OffsetOp(p);
}

bool DrawProxy::ClipOp(const Rect& r)
{
	return ptr->ClipOp(r);
}

bool DrawProxy::ClipoffOp(const Rect& r)
{
	return ptr->ClipoffOp(r);
}

bool DrawProxy::ExcludeClipOp(const Rect& r)
{
	return ptr->ExcludeClipOp(r);
}

bool DrawProxy::IntersectClipOp(const Rect& r)
{
	return ptr->IntersectClipOp(r);
}

bool DrawProxy::IsPaintingOp(const Rect& r) const
{
	return ptr->IsPaintingOp(r);
}

Rect DrawProxy::GetPaintRect() const
{
	return ptr->GetPaintRect();
}

void DrawProxy::DrawRectOp(int x, int y, int cx, int cy, Color color)
{
	ptr->DrawRectOp(x, y, cx, cy, color);
}

void DrawProxy::SysDrawImageOp(int x, int y, const Image& img, Color color)
{
	ptr->SysDrawImageOp(x, y, img, color);
}

void DrawProxy::SysDrawImageOp(int x, int y, const Image& img, const Rect& src, Color color)
{
	ptr->SysDrawImageOp(x, y, img, src, color);
}

void DrawProxy::DrawImageOp(int x, int y, int cx, int cy, const Image& img, const Rect& src, Color color)
{
	ptr->DrawImageOp(x, y, cx, cy, img, src, color);
}

void DrawProxy::DrawDataOp(int x, int y, int cx, int cy, const String& data, const char *id)
{
	ptr->DrawDataOp(x, y, cx, cy, data, id);
}

void DrawProxy::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color)
{
	ptr->DrawLineOp(x1, y1, x2, y2, width, color);
}

void DrawProxy::DrawPolyPolylineOp(const Point *vertices, int vertex_count, const int *counts,
                                   int count_count, int width, Color color, Color doxor)
{
	ptr->DrawPolyPolylineOp(vertices, vertex_count, counts, count_count, width, color, doxor);
}

void DrawPolyPolyline(const Vector<Point>& vertices, const Vector<int>& counts,
		                  int width, Color color, Color doxor) {
	TODO
}
	
void DrawProxy::DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count, const int *subpolygon_counts,
                                      int scc, const int *disjunct_polygon_counts, int dpcc, Color color,
                                      int width, Color outline, uint64 pattern, Color doxor)
{
	ptr->DrawPolyPolyPolygonOp(vertices, vertex_count, subpolygon_counts, scc, disjunct_polygon_counts,
	                           dpcc, color, width, outline, pattern, doxor);
}

void DrawProxy::DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color)
{
	ptr->DrawArcOp(rc, start, end, width, color);
}

void DrawProxy::DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor)
{
	ptr->DrawEllipseOp(r, color, pen, pencolor);
}

void DrawProxy::DrawTextOp(int x, int y, int angle, const wchar *text, Font font, Color ink, int n, const int *dx)
{
	ptr->DrawTextOp(x, y, angle, text, font, ink, n, dx);
}

void DrawProxy::DrawDrawingOp(const Rect& target, const Drawing& w)
{
	ptr->DrawDrawingOp(target, w);
}

void DrawProxy::DrawPaintingOp(const Rect& target, const Painting& w)
{
	ptr->DrawPaintingOp(target, w);
}

Size DrawProxy::GetNativeDpi() const
{
	return ptr->GetNativeDpi();
}

void DrawProxy::BeginNative()
{
	ptr->BeginNative();
}

void DrawProxy::EndNative()
{
	ptr->EndNative();
}

int DrawProxy::GetCloffLevel() const
{
	return ptr->GetCloffLevel();
}

void DrawProxy::Escape(const String& data)
{
	ptr->Escape(data);
}









dword NilDraw::GetInfo() const { return DOTS; }
Size NilDraw::GetPageSize() const { return Size(0, 0); }
void NilDraw::BeginOp() {}
void NilDraw::EndOp() {}
void NilDraw::OffsetOp(Point p) {}
bool NilDraw::ClipOp(const Rect& r) { return false; }
bool NilDraw::ClipoffOp(const Rect& r) { return false; }
bool NilDraw::ExcludeClipOp(const Rect& r) { return false; }
bool NilDraw::IntersectClipOp(const Rect& r) { return false; }
bool NilDraw::IsPaintingOp(const Rect& r) const { return false; }
Rect NilDraw::GetPaintRect() const { return Rect(0, 0, 0, 0); }
void NilDraw::DrawRectOp(int x, int y, int cx, int cy, Color color) {}
void NilDraw::DrawImageOp(int x, int y, int cx, int cy, const Image& img, const Rect& src, Color color) {}
void NilDraw::DrawDataOp(int x, int y, int cx, int cy, const String& data, const char *id) {}
void NilDraw::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {}
void NilDraw::DrawPolyPolylineOp(const Point *vertices, int vertex_count, const int *counts, int count_count, int width, Color color, Color doxor) {}
void NilDraw::DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count, const int *subpolygon_counts, int scc, const int *disjunct_polygon_counts, int dpcc, Color color, int width, Color outline, uint64 pattern, Color doxor) {}
void NilDraw::DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color) {}
void NilDraw::DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor) {}
void NilDraw::DrawTextOp(int x, int y, int angle, const wchar *text, Font font, Color ink, int n, const int *dx) {}
void NilDraw::DrawDrawingOp(const Rect& target, const Drawing& w) {}
void NilDraw::DrawPaintingOp(const Rect& target, const Painting& w) {}





void DrawTextEllipsis(Draw& w, int x, int y, int cx, const wchar *text, const char *ellipsis,
				      Font font, Color ink, int n)
{
	TODO
}

void DrawTextEllipsis(Draw& w, int x, int y, int cx, const char *text, const char *ellipsis,
				      Font font, Color ink, int n)
{
	return DrawTextEllipsis(w, x, y, cx, String(text).ToWString(), ellipsis, font, ink, n);
}


void SweepMkImageCache()
{
	TODO //AdjustValueCache();
}

void Subtract(Vector<Rect>& rr, const Rect& sub)
{
	TODO
}


END_UPP_NAMESPACE
