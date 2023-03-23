#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


ProgDraw::ProgDraw() /*: fb(state), shader(state)*/ {
	Create(0,Size(16,16));
}

ProgDraw::ProgDraw(void* hash, Size sz) /*: fb(state), shader(state)*/ {
	Create(hash, sz);
}

ProgDraw::ProgDraw(void* hash, int w, int h) /*: fb(state), shader(state)*/ {
	Create(hash, Size(w,h));
}

Size ProgDraw::GetFrameSize() const {
	TODO
	//return state.size;
}

void ProgDraw::Realize(void* hash, Size sz){
	if (d.IsEmpty() || d->GetPageSize() != sz)
		Create(hash, sz);
	
	d->Clear();
}

void ProgDraw::Create(void* hash, Size sz){
	Clear();
	//state.size = sz;
	
	LinkRender();
	
	d = new ProgPainter(hash, sz, cmd_screen_begin, render_begin, render_end, cmd_screen_end);
	
	d->Init(sz);
	
	DrawProxy::SetTarget(&*d);
}

void ProgDraw::Create(void* hash, Size sz, DrawCommand& sub_begin, DrawCommand& sub_end) {
	Clear();
	//state.size = sz;
	
	LinkRender();
	
	sub_begin.prev = &cmd_screen_begin;
	sub_end.next = &cmd_screen_end;
	cmd_screen_begin.next = &sub_begin;
	cmd_screen_end.prev = &sub_end;
	
	d = new ProgPainter(hash, sz, cmd_screen_begin, sub_begin, sub_end, cmd_screen_end);
	
}

void ProgDraw::LinkRender() {
	cmd_screen_begin.next = &render_begin;
	render_begin.prev = &cmd_screen_begin;
	cmd_screen_end.prev = &render_end;
	render_end.next = &cmd_screen_end;
}

void ProgDraw::Clear(){
	d.Clear();
	cmd_screen_begin.next = &cmd_screen_end;
	cmd_screen_begin.prev = 0;
	cmd_screen_end.next = 0;
	cmd_screen_end.prev = &cmd_screen_begin;
}

String ProgDraw::Dump() const {
	return cmd_screen_begin.GetQueueString();
}

void ProgDraw::Finish() {
	if (d)
		d->Link();
}

ProgDraw::operator Image() const {
	TODO
}

ProgPainter& ProgDraw::GetPainter() {
	ASSERT(d);
	return *d;
}

void ProgDraw::DetachTo(ProgPainter& pp) {
	if (cmd_screen_begin.next)
		pp.AppendPick(cmd_screen_begin.next, cmd_screen_end.prev);
}

#if 0

Size ProgDraw::GetPageSize() const {
	if (!d.IsEmpty())
		return d->GetPageSize();
	return Size(0,0);
}

Size ProgDraw::GetPageDimensions() {
	return GetPageSize(); // call virtual
}

void ProgDraw::SetDimensions(const Size& sz) {
	SetSize(sz); // call virtual
}

void ProgDraw::SetSize(Size sz) {
	d->SetSize(sz);
}

void ProgDraw::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	ASSERT(d);
	d->DrawLine(x1, y1, x2, y2, width, color);
}

void ProgDraw::DrawRectOp(int x, int y, int cx, int cy, Color color) {
	d->DrawRect(x, y, cx, cy, color);
}

void ProgDraw::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
	                     Color ink, int n, const int *dx) {
	d->DrawTextOp(x, y, angle, text, font, ink, n, dx);
}

void ProgDraw::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
                                 const int *counts, int count_count,
                                 int width, Color color, Color doxor) {
	d->DrawPolyPolylineOp(
		vertices, vertex_count,
		counts, count_count,
		width, color, doxor);
}

bool ProgDraw::ClipOp(const Rect& r) {
	TODO
}

void ProgDraw::EndOp() {
	d->End();
}

void ProgDraw::DrawImage(int x, int y, Image img, byte alpha) {
	TODO
}

Draw& ProgDraw::Alpha() {
	TODO
}

bool ProgDraw::ClipoffOp(const Rect& r) {
	TODO
}

dword ProgDraw::GetInfo() const {
	TODO
}

void ProgDraw::BeginOp() {
	TODO
}

void ProgDraw::OffsetOp(Point p) {
	TODO
}

bool ProgDraw::ExcludeClipOp(const Rect& r) {
	TODO
}

bool ProgDraw::IntersectClipOp(const Rect& r) {
	TODO
}

bool ProgDraw::IsPaintingOp(const Rect& r) const {
	TODO
}

void ProgDraw::DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
                                   const int *subpolygon_counts, int scc,
                                   const int *disjunct_polygon_counts, int dpcc,
                                   Color color, int width, Color outline,
                                   uint64 pattern, Color doxor) {
	TODO
}

void ProgDraw::DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color) {
	TODO
}

void ProgDraw::DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor) {
	TODO
}

#endif



NAMESPACE_TOPSIDE_END
