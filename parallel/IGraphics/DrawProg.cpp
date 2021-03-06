#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN


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
		if (cmd && cmd->next && cmd->next->prev != cmd)
			break; // failsafe break
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
	int triangles_count = cmd.triangles.GetCount() / 6;
	const float* f = cmd.triangles.Begin();
	for(int i = 0; i < triangles_count; i++) {
		v << Point(f[0], f[1])
		  << Point(f[2], f[3])
		  << Point(f[4], f[5]);
		((Draw*)this)->DrawPolygon(v, cmd.clr);
		f += 6;
	}
}

void DrawProg::DrawPolyline(const DrawCommand& cmd) {
	((Draw*)this)->DrawPolyline(cmd.pts, 1, cmd.clr);
}

void DrawProg::DrawPolygon(const DrawCommand& cmd) {
	((Draw*)this)->DrawPolygon(cmd.pts, cmd.clr);
}

void DrawProg::DrawOffset(const DrawCommand& cmd) {
	Rect r {cmd.i[0], cmd.i[1], cmd.i[2], cmd.i[3]};
	((Draw*)this)->ClipOp(r);
}

void DrawProg::DrawEnd(const DrawCommand& cmd) {
	((Draw*)this)->EndOp();
}



NAMESPACE_PARALLEL_END

