#include "IGraphics.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN


DrawProg::DrawProg() {
	
}

void DrawProg::Process(const DrawCommand* ptr) {
	typedef void (DrawProg::*FnPtr)(const DrawCommand&);
	static FnPtr ptrs[DRAW_CMD_COUNT];
	static bool has_ptrs;
	if (!has_ptrs) {
		ptrs[DRAW_LINE] = &DrawProg::DrawLine;
		ptrs[DRAW_IMAGE] = &DrawProg::DrawImage;
		ptrs[DRAW_RECT] = &DrawProg::DrawRect;
		ptrs[DRAW_TRIANGLES] = &DrawProg::DrawTriangles;
		ptrs[DRAW_POLYLINE] = &DrawProg::DrawPolyline;
		ptrs[DRAW_OFFSET] = &DrawProg::DrawOffset;
		ptrs[DRAW_END] = &DrawProg::DrawEnd;
		has_ptrs = true;
	}
	
	const DrawCommand* cmd = ptr;
	while (cmd) {
		if (cmd->type > DRAW_NULL && cmd->type < DRAW_CMD_COUNT)
			(*this.*ptrs[cmd->type])(*cmd);
		
		ASSERT(cmd->next != cmd);
		cmd = cmd->next;
	}
}

void DrawProg::DrawLine(const DrawCommand& cmd) {
	int x0 = cmd.i[0];
	int y0 = cmd.i[1];
	int x1 = cmd.i[2];
	int y1 = cmd.i[3];
	((Draw*)this)->DrawLine(
		x0, y0,
		x1, y1,
		1, cmd.clr);
}

void DrawProg::DrawImage(const DrawCommand& cmd) {
	int x0 = cmd.i[0];
	int y0 = cmd.i[1];
	((Draw*)this)->DrawImage(
		x0, y0,
		cmd.img);
}

void DrawProg::DrawRect(const DrawCommand& cmd) {
	int x0 = cmd.i[0];
	int y0 = cmd.i[1];
	int x1 = cmd.i[2];
	int y1 = cmd.i[3];
	int w = x1-x0;
	int h = y1-y0;
	((Draw*)this)->DrawRect(x0, y0, w, h, cmd.clr);
}

void DrawProg::DrawTriangles(const DrawCommand& cmd) {
	thread_local static Vector<Point> v;
	v.SetCount(0);
	for (const Trif& t : cmd.triangles) {
		v << Point(t.a.x, t.a.y)
		  << Point(t.c.x, t.c.y)
		  << Point(t.b.x, t.b.y);
		((Draw*)this)->DrawPolygon(v, cmd.clr);
	}
}

void DrawProg::DrawPolyline(const DrawCommand& cmd) {
	((Draw*)this)->DrawPolyline(cmd.pts, 1, cmd.clr);
}

void DrawProg::DrawPolygon(const DrawCommand& cmd) {
	((Draw*)this)->DrawPolygon(cmd.pts, cmd.clr);
}

void DrawProg::DrawOffset(const DrawCommand& cmd) {
	TODO
}

void DrawProg::DrawEnd(const DrawCommand& cmd) {
	TODO
}



NAMESPACE_TOPSIDE_END

#endif
