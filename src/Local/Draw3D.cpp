#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


#if IS_UPP_CORE
Color DefaultInk() {
	struct SpecialColor : Color {
		SpecialColor(dword d) {color = d;}
	};
	return SpecialColor(254);
}
#endif


Draw3::~Draw3() {
	
}

Color Draw3::GetDefaultInk() const
{
	dword w = GetInfo();
	if(w & DRAWING)
		return DefaultInk();
	if(w & DOTS)
		return Black();
	return SColorText();
}

void Draw3::DrawEllipse(float x, float y, float z, float cx, float cy, float cz, Color color,
		             int pen, Color pencolor) {
	TODO
}

#if 0

void Draw3::DrawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) {
	DrawLineOp(x1, y1, x2, y2, width, color);
}

void Draw3::DrawText(float x, float y, float z, const String& text, Font font, Color ink, const int *dx) {
	WString ws(ToWString(text));
	DrawTextOp(x, y, z, 0, ws.Begin(), font, ink, 0, dx);
}

void Draw3::DrawText(float x, float y, float z, const char* text, Font font, Color ink, const int *dx) {
	DrawText(x, y, z, String(text), font, ink, dx);
}
	          
void Draw3::DrawText(float x, float y, float z, const WString& text, Font font, Color ink, const int *dx) {
	DrawText(x, y, z, text.ToString(), font, ink, dx);
}

void Draw3::DrawBox(float x, float y, float z, float cx, float cy, float cz, Color color) {
	DrawBoxOp(x, y, z, cx, cy, cz, color);
}

void Draw3::DrawBox(const Cubf& cub, Color color) {
	DrawBoxOp(cub.top, cub.top, cub.Width(), cub.Height(), color);
}

void Draw3::DrawBox(ts::Cubf_<int> const&, ts::Color) {
	TODO
}

void Draw3::DrawPolyline(const Point3f *vertices, int count, float width, Color color, Color doxor) {
	DrawPolyPolylineOp(vertices, count, &count, 1, width, color, doxor);
}

void Draw3::DrawPolyline(const Vector<Point3f>& vertices, float width, Color color, Color doxor) {
	int count = vertices.GetCount();
	DrawPolyPolylineOp(vertices.Begin(), count, &count, 1, width, color, doxor);
}

void Draw3::DrawImage(float x, float y, float z, const Image& img) {
	DrawImage(x, y, z, img, 255);
}

void Draw3::DrawImage(float x, float y, float z, const Image& img, const Cubf& src) {
	TODO
}

void Draw3::DrawImage(float x, float y, float z, float cx, float cy, float cz, const Image& img) {
	TODO
}

void Draw3::DrawPolygon(const Vector<Point3f>& vertices, Color color, float width, Color outline, uint64 pattern, Color doxor) {
	int tris = vertices.GetCount() / 3;
	for(int i = 0; i < tris; i++) {
		int off = i * 3;
		const Point3f& a = vertices[off + 0];
		const Point3f& b = vertices[off + 1];
		const Point3f& c = vertices[off + 2];
		DrawTriangle(a, b, c, color);
	}
}

void Draw3::DrawEllipse(const Cubf& r, Color color, int pen, Color pencolor) {
	TODO
}

void Draw3::DrawEllipse(float x, float y, float z, float cx, float cy, float cz, Color color, int pen, Color pencolor) {
	TODO
}

#endif


void Draw3::DrawText(float x, float y, float z, const wchar *text, Font font,
                    Color ink, int n, const int *dx)
{
	DrawText(x, y, z, 0, text, font, ink, n, dx);
}

// ---------------------------

void Draw3::DrawText(float x, float y, float z, int angle, const WString& text, Font font,
                    Color ink, const int *dx)
{
	DrawText(x, y, z, angle, text.Begin(), font, ink, text.GetLength(), dx);
}

void Draw3::DrawText(float x, float y, float z, const WString& text, Font font, Color ink, const int *dx)
{
	DrawText(x, y, z, 0, text, font, ink, dx);
}

void Draw3::DrawText(float x, float y, float z, int angle, const wchar *text, Font font,
		          Color ink, int n, const int *dx) {
	TODO
}

// ---------------------------

void Draw3::DrawText(float x, float y, float z, int angle, const char *text, byte charset, Font font,
                    Color ink, int n, const int *dx)
{
	TODO //DrawText(x, y, z, angle, TextUnicode(text, n, charset, font), font, ink, dx);
}

void Draw3::DrawText(float x, float y, float z, const char *text, byte charset, Font font,
                    Color ink, int n, const int *dx)
{
	DrawText(x, y, z, 0, text, charset, font, ink, n, dx);
}

// ---------------------------

void Draw3::DrawText(float x, float y, float z, int angle, const char *text,
                    Font font, Color ink, int n, const int *dx)
{
	TODO //DrawText(x, y, z, angle, text, CHARSET_DEFAULT, font, ink, n, dx);
}

void Draw3::DrawText(float x, float y, float z, const char *text, Font font,
                    Color ink, int n, const int *dx)
{
	TODO //DrawText(x, y, z, text, CHARSET_DEFAULT, font, ink, n, dx);
}

// ---------------------------

void Draw3::DrawText(float x, float y, float z, int angle, const String& text, Font font,
                    Color ink, const int *dx)
{
	DrawText(x, y, z, angle, text, font, ink, text.GetLength(), dx);
}

void Draw3::DrawText(float x, float y, float z, const String& text, Font font, Color ink, const int *dx)
{
	TODO //WString h = TextUnicode(text, text.GetLength(), CHARSET_DEFAULT, font);
	//DrawText(x, y, z, h, font, ink, h.GetLength(), dx);
}

void Draw3::DrawPolyline(const Point3f *vertices, int count,
                        float width, Color color, Color doxor)
{
	DrawPolyPolyline(vertices, count, &count, 1, width, color, doxor);
}

void Draw3::DrawPolyline(const Vector<Point3f>& vertices,
                        float width, Color color, Color doxor)
{
	DrawPolyline(vertices.Begin(), vertices.GetCount(), width, color, doxor);
}

void Draw3::DrawBox(const Cubf& cub, Color color)
{
	DrawBox(cub.left, cub.top, cub.near, cub.GetWidth(), cub.GetHeight(), cub.GetDepth(), color);
}

void Draw3::DrawBox(float x, float y, float z, float cx, float cy, float cz, Color color)
{
	DrawBoxOp(x, y, z, cx, cy, cz, color);
}

void Draw3::DrawLine(Point3f p1, Point3f p2, float width, Color color)
{
	DrawLine(p1.x, p1.y, p2.x, p2.y, width, color);
}

void Draw3::DrawLine(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color)
{
	DrawLineOp(x1, y1, z1, x2, y2, z2, width, ResolveInk(color));
}

Volf Draw3::GetPageSize() const
{
	return Volf(FLT_MAX / 2, FLT_MAX / 2, -FLT_MAX / 2);
}

void Draw3::StartPage() {}
void Draw3::EndPage() {}

Cubf Draw3::GetPaintCubf() const
{
	return Cubf(-(FLT_MAX / 2), -(FLT_MAX / 2), -(FLT_MAX / 2), FLT_MAX / 2, FLT_MAX / 2, FLT_MAX / 2);
}

void Draw3::SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, Color color)
{
	NEVER();
}

void Draw3::SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, const Rect& src, Color color)
{
	TODO/*if(src == Cubf(img.GetSize()))
		SysDrawImageOp(x, y, z, img, color);
	else {
		Clipoff(x, y, z, src.GetWidth(), src.GetHeight());
		SysDrawImageOp(-src.left, -src.top, -src.near, img, color);
		End();
	}*/
}

void Draw3::DrawImageOp(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Rect& src, Color color)
{
	TODO
}

void Draw3::DrawDataOp(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *id)
{
	TODO
}

void Draw3::DrawDrawingOp(const Cubf& target, const Drawing& w) {
	TODO
}

void Draw3::DrawPaintingOp(const Cubf& target, const Painting& pw) {
	TODO
}

Volf Draw3::GetNativeDpi() const { return Volf(96, 96, 96); }

void Draw3::BeginNative() {}
void Draw3::EndNative() {}
int Draw3::GetCloffLevel() const { return 0; }
void Draw3::Escape(const String& data) {}

void Draw3::DrawImage(float x, float y, float z, const Image& img)
{
	TODO
	/*Volf sz = img.GetSize();
	DrawImageOp(x, y, z, sz.cx, sz.cy, img, img.GetSize(), Null);*/
}

bool Draw3::Clipoff(float x, float y, float z, float cx, float cy, float cz) {
	return Clipoff(CubfC(x,y,z,cx,cy,cz));
}

bool Draw3::Clip(float x, float y, float z, float cx, float cy, float cz) {
	return Clip(CubfC(x,y,z,cx,cy,cz));
}
void Draw3::DrawPolyPolyline(const Point3f *vertices, int vertex_count,
                            const int *counts, int count_count,
                            float width, Color color, Color doxor)
{
	DrawPolyPolylineOp(vertices, vertex_count, counts, count_count, width,
	                   ResolveInk(color), doxor);
}




dword DrawProxy3::GetInfo() const
{
	return ptr->GetInfo();
}

Volf DrawProxy3::GetPageSize() const
{
	return ptr->GetPageSize();
}

void DrawProxy3::StartPage()
{
	ptr->StartPage();
}

void DrawProxy3::EndPage()
{
	ptr->EndPage();
}

void DrawProxy3::BeginOp()
{
	ptr->BeginOp();
}

void DrawProxy3::EndOp()
{
	ptr->EndOp();
}

void DrawProxy3::OffsetOp(Point3f p)
{
	ptr->OffsetOp(p);
}

bool DrawProxy3::ClipOp(const Cubf& r)
{
	return ptr->ClipOp(r);
}

bool DrawProxy3::ClipoffOp(const Cubf& r)
{
	return ptr->ClipoffOp(r);
}

bool DrawProxy3::ExcludeClipOp(const Cubf& r)
{
	return ptr->ExcludeClipOp(r);
}

bool DrawProxy3::IntersectClipOp(const Cubf& r)
{
	return ptr->IntersectClipOp(r);
}

bool DrawProxy3::IsPaintingOp(const Cubf& r) const
{
	return ptr->IsPaintingOp(r);
}

Cubf DrawProxy3::GetPaintCubf() const
{
	return ptr->GetPaintCubf();
}

void DrawProxy3::DrawBoxOp(float x, float y, float z, float cx, float cy, float cz, Color color)
{
	ptr->DrawBoxOp(x, y, z, cx, cy, cz, color);
}

void DrawProxy3::SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, Color color)
{
	ptr->SysDrawImageOp(x, y, z, imgsz, img, color);
}

void DrawProxy3::SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, const Rect& src, Color color)
{
	ptr->SysDrawImageOp(x, y, z, imgsz, img, src, color);
}

void DrawProxy3::DrawImageOp(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Rect& src, Color color)
{
	ptr->DrawImageOp(x, y, z, cx, cy, cz, img, src, color);
}

void DrawProxy3::DrawDataOp(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *id)
{
	ptr->DrawDataOp(x, y, z, cx, cy, cz, data, id);
}

void DrawProxy3::DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color)
{
	ptr->DrawLineOp(x1, y1, x1, x2, y2, z2, width, color);
}

void DrawProxy3::DrawPolyPolylineOp(const Point3f *vertices, int vertex_count, const int *counts,
                                   int count_count, float width, Color color, Color doxor)
{
	ptr->DrawPolyPolylineOp(vertices, vertex_count, counts, count_count, width, color, doxor);
}

void DrawPolyPolyline(const Vector<Point3f>& vertices, const Vector<int>& counts,
		                  float width, Color color, Color doxor) {
	TODO
}
	
void DrawProxy3::DrawPolyPolyPolygonOp(const Point3f *vertices, int vertex_count, const int *subpolygon_counts,
                                      int scc, const int *disjunct_polygon_counts, int dpcc, Color color,
                                      float width, Color outline, uint64 pattern, Color doxor)
{
	ptr->DrawPolyPolyPolygonOp(vertices, vertex_count, subpolygon_counts, scc, disjunct_polygon_counts,
	                           dpcc, color, width, outline, pattern, doxor);
}

void DrawProxy3::DrawArcOp(const Cubf& rc, Point3f start, Point3f end, float width, Color color)
{
	ptr->DrawArcOp(rc, start, end, width, color);
}

void DrawProxy3::DrawEllipseOp(const Cubf& r, Color color, float pen, Color pencolor)
{
	ptr->DrawEllipseOp(r, color, pen, pencolor);
}

void DrawProxy3::DrawTextOp(float x, float y, float z, int angle, const wchar *text, Font font, Color ink, int n, const int *dx)
{
	ptr->DrawTextOp(x, y, z, angle, text, font, ink, n, dx);
}

void DrawProxy3::DrawDrawingOp(const Cubf& target, const Drawing& w)
{
	ptr->DrawDrawingOp(target, w);
}

void DrawProxy3::DrawPaintingOp(const Cubf& target, const Painting& w)
{
	ptr->DrawPaintingOp(target, w);
}

Volf DrawProxy3::GetNativeDpi() const
{
	return ptr->GetNativeDpi();
}

void DrawProxy3::BeginNative()
{
	ptr->BeginNative();
}

void DrawProxy3::EndNative()
{
	ptr->EndNative();
}

int DrawProxy3::GetCloffLevel() const
{
	return ptr->GetCloffLevel();
}

void DrawProxy3::Escape(const String& data)
{
	ptr->Escape(data);
}









dword NilDraw3::GetInfo() const { return DOTS; }
Volf NilDraw3::GetPageSize() const { return Volf(0, 0, 0); }
void NilDraw3::BeginOp() {}
void NilDraw3::EndOp() {}
void NilDraw3::OffsetOp(Point3f p) {}
bool NilDraw3::ClipOp(const Cubf& r) { return false; }
bool NilDraw3::ClipoffOp(const Cubf& r) { return false; }
bool NilDraw3::ExcludeClipOp(const Cubf& r) { return false; }
bool NilDraw3::IntersectClipOp(const Cubf& r) { return false; }
bool NilDraw3::IsPaintingOp(const Cubf& r) const { return false; }
Cubf NilDraw3::GetPaintCubf() const { return Cubf(0, 0, 0, 0); }
void NilDraw3::DrawBoxOp(float x, float y, float z, float cx, float cy, float cz, Color color) {}
void NilDraw3::DrawImageOp(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Cubf& src, Color color) {}
void NilDraw3::DrawDataOp(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *id) {}
void NilDraw3::DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) {}
void NilDraw3::DrawPolyPolylineOp(const Point3f *vertices, int vertex_count, const int *counts, int count_count, float width, Color color, Color doxor) {}
void NilDraw3::DrawPolyPolyPolygonOp(const Point3f *vertices, int vertex_count, const int *subpolygon_counts, int scc, const int *disjunct_polygon_counts, int dpcc, Color color, float width, Color outline, uint64 pattern, Color doxor) {}
void NilDraw3::DrawArcOp(const Cubf& rc, Point3f start, Point3f end, float width, Color color) {}
void NilDraw3::DrawEllipseOp(const Cubf& r, Color color, int pen, Color pencolor) {}
void NilDraw3::DrawTextOp(float x, float y, float z, int angle, const wchar *text, Font font, Color ink, int n, const int *dx) {}
void NilDraw3::DrawDrawingOp(const Cubf& target, const Drawing& w) {}
void NilDraw3::DrawPaintingOp(const Cubf& target, const Painting& w) {}



NAMESPACE_TOPSIDE_END
