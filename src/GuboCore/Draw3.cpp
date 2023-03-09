#include "GuboCore.h"

NAMESPACE_TOPSIDE_BEGIN


ProgDraw3::ProgDraw3() /*: fb(state), shader(state)*/ {
	//Create(Size(16,16));
}

ProgDraw3::ProgDraw3(Volf sz) /*: fb(state), shader(state)*/ {
	Create(sz);
}

ProgDraw3::ProgDraw3(float w, float h, float d) /*: fb(state), shader(state)*/ {
	Create(Volf(w,h,d));
}

Volf ProgDraw3::GetFrameSize() const {
	TODO
	//return state.size;
}

void ProgDraw3::Realize(Volf sz){
	if (d.IsEmpty() || d->GetPageSize() != sz)
		Create(sz);
	
	d->Clear();
}

void ProgDraw3::Create(Volf sz){
	Clear();
	//state.size = sz;
	
	LinkRender();
	
	d = new ProgPainter3(sz, cmd_screen_begin, render_begin, render_end, cmd_screen_end);
	
	d->Init(sz);
	
	DrawProxy3::SetTarget(&*d);
}

void ProgDraw3::Create(Volf sz, DrawCommand& sub_begin, DrawCommand& sub_end) {
	Clear();
	//state.size = sz;
	
	LinkRender();
	
	sub_begin.prev = &cmd_screen_begin;
	sub_end.next = &cmd_screen_end;
	cmd_screen_begin.next = &sub_begin;
	cmd_screen_end.prev = &sub_end;
	
	d = new ProgPainter3(sz, cmd_screen_begin, sub_begin, sub_end, cmd_screen_end);
	
}

void ProgDraw3::LinkRender() {
	cmd_screen_begin.next = &render_begin;
	render_begin.prev = &cmd_screen_begin;
	cmd_screen_end.prev = &render_end;
	render_end.next = &cmd_screen_end;
}

void ProgDraw3::Clear(){
	d.Clear();
	cmd_screen_begin.next = &cmd_screen_end;
	cmd_screen_begin.prev = 0;
	cmd_screen_end.next = 0;
	cmd_screen_end.prev = &cmd_screen_begin;
}

String ProgDraw3::Dump() const {
	return cmd_screen_begin.GetQueueString();
}

void ProgDraw3::Finish() {
	if (d)
		d->Link();
}

ProgDraw3::operator Image() const {
	TODO
}

ProgPainter3& ProgDraw3::GetPainter() {
	ASSERT(d);
	return *d;
}

void ProgDraw3::DetachTo(ProgPainter3& pp) {
	if (cmd_screen_begin.next)
		pp.AppendPick(cmd_screen_begin.next, cmd_screen_end.prev);
}

#if 0

Size ProgDraw3::GetPageSize() const {
	if (!d.IsEmpty())
		return d->GetPageSize();
	return Size(0,0);
}

Size ProgDraw3::GetPageDimensions() {
	return GetPageSize(); // call virtual
}

void ProgDraw3::SetDimensions(const Size& sz) {
	SetSize(sz); // call virtual
}

void ProgDraw3::SetSize(Size sz) {
	d->SetSize(sz);
}

void ProgDraw3::DrawLineOp(int x1, int y1, int x2, int y2, float width, Color color) {
	ASSERT(d);
	d->DrawLine(x1, y1, x2, y2, width, color);
}

void ProgDraw3::DrawCubfOp(float x, float y, float z, int cx, int cy, Color color) {
	d->DrawCubf(x, y, cx, cy, color);
}

void ProgDraw3::DrawTextOp(float x, float y, float z, int angle, const wchar *text, Font font,
	                     Color ink, int n, const int *dx) {
	d->DrawTextOp(x, y, angle, text, font, ink, n, dx);
}

void ProgDraw3::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
                                 const int *counts, int count_count,
                                 float width, Color color, Color doxor) {
	d->DrawPolyPolylineOp(
		vertices, vertex_count,
		counts, count_count,
		width, color, doxor);
}

bool ProgDraw3::ClipOp(const Cubf& r) {
	TODO
}

void ProgDraw3::EndOp() {
	d->End();
}

void ProgDraw3::DrawImage(float x, float y, float z, Image img, byte alpha) {
	TODO
}

Draw& ProgDraw3::Alpha() {
	TODO
}

bool ProgDraw3::ClipoffOp(const Cubf& r) {
	TODO
}

dword ProgDraw3::GetInfo() const {
	TODO
}

void ProgDraw3::BeginOp() {
	TODO
}

void ProgDraw3::OffsetOp(Point p) {
	TODO
}

bool ProgDraw3::ExcludeClipOp(const Cubf& r) {
	TODO
}

bool ProgDraw3::IntersectClipOp(const Cubf& r) {
	TODO
}

bool ProgDraw3::IsPaintingOp(const Cubf& r) const {
	TODO
}

void ProgDraw3::DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
                                   const int *subpolygon_counts, int scc,
                                   const int *disjunct_polygon_counts, int dpcc,
                                   Color color, float width, Color outline,
                                   uint64 pattern, Color doxor) {
	TODO
}

void ProgDraw3::DrawArcOp(const Cubf& rc, Point start, Point end, float width, Color color) {
	TODO
}

void ProgDraw3::DrawEllipseOp(const Cubf& r, Color color, float pen, Color pencolor) {
	TODO
}

#endif




NAMESPACE_TOPSIDE_END
