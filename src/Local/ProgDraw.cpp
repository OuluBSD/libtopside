#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


ProgDraw::ProgDraw() /*: fb(state), shader(state)*/ {
	
}

ProgDraw::ProgDraw(Size sz) /*: fb(state), shader(state)*/ {
	Create(sz);
}

ProgDraw::ProgDraw(int w, int h) /*: fb(state), shader(state)*/ {
	Create(Size(w,h));
}

Size ProgDraw::GetFrameSize() const {
	TODO
	//return state.size;
}

Size ProgDraw::GetPageSize() const {
	if (!d.IsEmpty())
		return d->GetPageSize();
	return Size(0,0);
}

Size ProgDraw::GetPageDimensions() {
	return GetPageSize(); // call virtual
}

void ProgDraw::Create(Size sz){
	Clear();
	//state.size = sz;
	
	LinkRender();
	
	d = new ProgPainter(sz, cmd_screen_begin, render_begin, render_end, cmd_screen_end);
}

void ProgDraw::Create(Size sz, DrawCommand& sub_begin, DrawCommand& sub_end) {
	Clear();
	//state.size = sz;
	
	LinkRender();
	
	sub_begin.prev = &cmd_screen_begin;
	sub_end.next = &cmd_screen_end;
	cmd_screen_begin.next = &sub_begin;
	cmd_screen_end.prev = &sub_end;
	
	d = new ProgPainter(sz, cmd_screen_begin, sub_begin, sub_end, cmd_screen_end);
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

ProgPainter& ProgDraw::GetPainter() {
	ASSERT(d);
	return *d;
}

void ProgDraw::DetachTo(ProgPainter& pp) {
	if (cmd_screen_begin.next)
		pp.AppendPick(cmd_screen_begin.next, cmd_screen_end.prev);
}


NAMESPACE_TOPSIDE_END
