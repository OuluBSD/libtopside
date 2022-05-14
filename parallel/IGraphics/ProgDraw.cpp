#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN




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
	TODO
	//return state.size;
}

void ProgDraw::Create(Size sz){
	Clear();
	//state.size = sz;
	d = new ProgPainter(cmd_screen_begin, render_begin, render_end, cmd_screen_end);
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

Draw& ProgDraw::Alpha() {
	TODO
}

ProgPainter& ProgDraw::GetProgPainter() {
	ASSERT(d);
	return *d;
}


NAMESPACE_PARALLEL_END

