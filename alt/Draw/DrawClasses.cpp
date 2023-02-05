#include "Draw.h"

NAMESPACE_UPP


Color DefaultInk() {
	TODO
}






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

void Draw::DrawPolygon(const Vector<Point>& vertices, Color color, int width, Color outline, uint64 pattern, Color doxor) {
	int tris = vertices.GetCount() / 3;
	for(int i = 0; i < tris; i++) {
		int off = i * 3;
		const Point& a = vertices[off + 0];
		const Point& b = vertices[off + 1];
		const Point& c = vertices[off + 2];
		DrawTriangle(a, b, c, color);
	}
}

void Draw::DrawEllipse(const Rect& r, Color color, int pen, Color pencolor) {
	TODO
}

void Draw::DrawEllipse(int x, int y, int cx, int cy, Color color, int pen, Color pencolor) {
	TODO
}







void DrawProxy::SetSize(Size sz) {
	if (ptr)
		return ptr->SetSize(sz);
}

Size DrawProxy::GetPageSize() const {
	return ptr->GetPageSize();
}

void DrawProxy::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	ptr->DrawLineOp(x1, y1, x2, y2, width, color);
}

void DrawProxy::DrawRectOp(int x, int y, int cx, int cy, Color color) {
	ptr->DrawRectOp(x, y, cx, cy, color);
}

void DrawProxy::DrawTextOp(int x, int y, int angle, const wchar *text, Font font, Color ink, int n, const int *dx) {
	ptr->DrawTextOp(x, y, angle, text, font, ink, n, dx);
}

void DrawProxy::DrawPolyPolylineOp(const Point *vertices, int vertex_count, const int *counts,
		int count_count, int width, Color color, Color doxor) {
	ptr->DrawPolyPolylineOp(vertices, vertex_count, counts, count_count, width, color, doxor);
}

bool DrawProxy::ClipOp(const Rect& r) {
	return ptr->ClipOp(r);
}

void DrawProxy::EndOp() {
	ptr->EndOp();
}

void DrawProxy::DrawImage(int x, int y, Image img, byte alpha) {
	ptr->DrawImage(x, y, img, alpha);
}

void DrawProxy::DrawTriangle(Point a, Point b, Point c, RGBA clr) {
	ptr->DrawTriangle(a, b, c, clr);
}

bool DrawProxy::ClipoffOp(const Rect& r) {
	return ptr->ClipoffOp(r);
}

dword DrawProxy::GetInfo() const {
	return ptr->GetInfo();
}

void DrawProxy::BeginOp() {
	ptr->BeginOp();
}

void DrawProxy::OffsetOp(Point p) {
	ptr->OffsetOp(p);
}

bool DrawProxy::ExcludeClipOp(const Rect& r) {
	return ExcludeClipOp(r);
}

bool DrawProxy::IntersectClipOp(const Rect& r) {
	return IntersectClipOp(r);
}

bool DrawProxy::IsPaintingOp(const Rect& r) const {
	return IsPaintingOp(r);
}

void DrawProxy::DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
                                   const int *subpolygon_counts, int scc,
                                   const int *disjunct_polygon_counts, int dpcc,
                                   Color color, int width, Color outline,
                                   uint64 pattern, Color doxor) {
	DrawPolyPolyPolygonOp(
		vertices,
		vertex_count,
		subpolygon_counts,
		scc,
		disjunct_polygon_counts,
		dpcc,
		color,
		width,
		outline,
		pattern,
		doxor);
}

void DrawProxy::DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color) {
	DrawArcOp(rc, start, end, width, color);
}

void DrawProxy::DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor) {
	DrawEllipseOp(r, color, pen, pencolor);
}



END_UPP_NAMESPACE
