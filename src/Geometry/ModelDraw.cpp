#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


ModelDraw::ModelDraw() /*: fb(state), shader(state)*/ {
	
}

ModelDraw::ModelDraw(Volf sz) /*: fb(state), shader(state)*/ {
	Create(sz);
}

ModelDraw::ModelDraw(float w, float h, float z) /*: fb(state), shader(state)*/ {
	Create(Volf(w,h,z));
}

Volf ModelDraw::GetFrameSize() const {
	TODO
	//return state.size;
}

Volf ModelDraw::GetPageSize() const {
	if (!d.IsEmpty())
		return d->GetPageSize();
	return Volf(0);
}

void ModelDraw::Create(Volf sz){
	Clear();
	//state.size = sz;
	
	LinkRender();
	
	d = new ModelPainter(sz, cmd_screen_begin, render_begin, render_end, cmd_screen_end);
}

void ModelDraw::Create(Volf sz, DrawCommand& sub_begin, DrawCommand& sub_end) {
	Clear();
	//state.size = sz;
	
	LinkRender();
	
	sub_begin.prev = &cmd_screen_begin;
	sub_end.next = &cmd_screen_end;
	cmd_screen_begin.next = &sub_begin;
	cmd_screen_end.prev = &sub_end;
	
	d = new ModelPainter(sz, cmd_screen_begin, sub_begin, sub_end, cmd_screen_end);
}

void ModelDraw::LinkRender() {
	cmd_screen_begin.next = &render_begin;
	render_begin.prev = &cmd_screen_begin;
	cmd_screen_end.prev = &render_end;
	render_end.next = &cmd_screen_end;
}

void ModelDraw::Clear(){
	d.Clear();
	cmd_screen_begin.next = &cmd_screen_end;
	cmd_screen_begin.prev = 0;
	cmd_screen_end.next = 0;
	cmd_screen_end.prev = &cmd_screen_begin;
}

String ModelDraw::Dump() const {
	return cmd_screen_begin.GetQueueString();
}

void ModelDraw::Finish() {
	if (d)
		d->Link();
}

ModelDraw::operator Image() const {
	TODO
}

void ModelDraw::SetSize(Volf sz) {
	d->SetSize(sz);
}

void ModelDraw::DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) {
	ASSERT(d);
	d->DrawLine(x1, y1, z1, x2, y2, z2, width, color);
}

void ModelDraw::DrawCuboidOp(float x, float y, float z, float cx, float cy, float cz, Color color) {
	d->DrawCuboid(x, y, z, cx, cy, cz, color);
}

void ModelDraw::DrawTextOp(float x, float y, float z, float angle, const wchar *text, Font font,
	                     Color ink, int n, const float *dx) {
	d->DrawTextOp(x, y, z, angle, text, font, ink, n, dx);
}

void ModelDraw::DrawPolyPolylineOp(const vec3 *vertices, int vertex_count,
                                 const int *counts, int count_count,
                                 float width, Color color, Color doxor) {
	d->DrawPolyPolylineOp(
		vertices, vertex_count,
		counts, count_count,
		width, color, doxor);
}

bool ModelDraw::ClipOp(const Cubf& r) {
	TODO
}

void ModelDraw::EndOp() {
	d->End();
}

void ModelDraw::DrawImage(float x, float y, float z, Image img, byte alpha) {
	TODO
}

Draw& ModelDraw::Alpha() {
	TODO
}

ModelPainter& ModelDraw::GetPainter() {
	ASSERT(d);
	return *d;
}

void ModelDraw::DetachTo(ModelPainter& pp) {
	if (cmd_screen_begin.next)
		pp.AppendPick(cmd_screen_begin.next, cmd_screen_end.prev);
}


NAMESPACE_TOPSIDE_END
