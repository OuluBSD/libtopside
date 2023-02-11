#include "IGraphics.h"


NAMESPACE_PARALLEL_BEGIN


DrawProg::DrawProg() {
	
}

void DrawProg::SkipWindowCommands(bool b) {
	skip_window_commands = b;
}

void DrawProg::Process(const DrawCommand* begin, const DrawCommand* end) {
	typedef void (DrawProg::*FnPtr)(const DrawCommand&);
	static FnPtr ptrs[DRAW_CMD_COUNT];
	static bool has_ptrs;
	if (!has_ptrs) {
		memset(ptrs, 0, sizeof(ptrs));
		ptrs[DRAW_BIND_WINDOW] = &DrawProg::BindWindow;
		ptrs[DRAW_UNBIND_WINDOW] = &DrawProg::UnbindWindow;
		ptrs[DRAW_LINE] = &DrawProg::DrawLine;
		ptrs[DRAW_TEXT] = &DrawProg::DrawText;
		ptrs[DRAW_IMAGE] = &DrawProg::DrawImage;
		ptrs[DRAW_IMAGE_SIZED] = &DrawProg::DrawImageOp;
		ptrs[DRAW_RECT] = &DrawProg::DrawRect;
		ptrs[DRAW_TRIANGLES] = &DrawProg::DrawTriangles;
		ptrs[DRAW_POLYLINE] = &DrawProg::DrawPolyline;
		ptrs[DRAW_CLIPOFF] = &DrawProg::Clipoff;
		ptrs[DRAW_OFFSET] = &DrawProg::DrawOffset;
		ptrs[DRAW_OFFSET_POINT] = &DrawProg::DrawOffsetPoint;
		ptrs[DRAW_END] = &DrawProg::DrawEnd;
		ptrs[DRAW_WINDOW_OFFSET] = &DrawProg::DrawWindowOffset;
		ptrs[DRAW_WINDOW_END] = &DrawProg::DrawWindowEnd;
		has_ptrs = true;
	}
	
	const DrawCommand* cmd = begin;
	while (cmd) {
		if (cmd->type >= DRAW_BEGIN && cmd->type < DRAW_CMD_COUNT) {
			ASSERT(ptrs[cmd->type]);
			(*this.*ptrs[cmd->type])(*cmd);
		}
		
		ASSERT(cmd->next != cmd);
		cmd = cmd->next;
		if (cmd == end || !cmd)
			break;
		if (cmd && cmd->next && cmd->next->prev != cmd) {
			LOG("DrawProg::Process: error: command chain duplex breakage");
			break; // failsafe break
		}
	}
}

void DrawProg::BindWindow(const DrawCommand& cmd) {
	ASSERT_(bind_win_count == 0, "Window have been bound already. DrawCommand program is invalid.");
	bind_win_count++;
}

void DrawProg::UnbindWindow(const DrawCommand& cmd) {
	bind_win_count--;
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

void DrawProg::DrawText(const DrawCommand& cmd) {
	int x = cmd.i[0];
	int y = cmd.i[1];
	((Draw*)this)->DrawText(
		x,y,
		cmd.txt,
		cmd.fnt,
		cmd.clr);
}

void DrawProg::DrawImage(const DrawCommand& cmd) {
	int x0 = cmd.i[0];
	int y0 = cmd.i[1];
	((Draw*)this)->DrawImage(
		x0, y0,
		cmd.img);
}

void DrawProg::DrawImageOp(const DrawCommand& cmd) {
	#if IS_UPP_CORE
	int x = cmd.i[0];
	int y = cmd.i[1];
	int cx = cmd.i[2];
	int cy = cmd.i[3];
	((Draw*)this)->DrawImageOp(
		x, y,
		cx, cy,
		cmd.img,
		cmd.crop,
		cmd.clr);
	
	#if 0
	// Dump images
	hash_t h = cmd.img.GetHashValue();
	String out = ConfigFile(IntStr64(h) + ".png");
	if (!FileExists(out)) {
		PNGEncoder png;
		png.SaveFile(out, cmd.img);
		LOG("Saved file: " << out);
	}
	#endif
	
	#else
	TODO
	#endif
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

void DrawProg::Clipoff(const DrawCommand& cmd) {
	Rect r {cmd.i[0], cmd.i[1], cmd.i[2], cmd.i[3]};
	#if IS_UPP_CORE
	((Draw*)this)->Clipoff(r);
	#else
	((Draw*)this)->ClipoffOp(r); // this is probably wrong
	#endif
}

void DrawProg::DrawOffset(const DrawCommand& cmd) {
	Rect r {cmd.i[0], cmd.i[1], cmd.i[2], cmd.i[3]};
	((Draw*)this)->ClipOp(r);
}

void DrawProg::DrawOffsetPoint(const DrawCommand& cmd) {
	Point pt {cmd.i[0], cmd.i[1]};
	((Draw*)this)->OffsetOp(pt);
}

void DrawProg::DrawWindowOffset(const DrawCommand& cmd) {
	if (skip_window_commands)
		return;
	#if IS_UPP_CORE
	Clipoff(cmd);
	#else
	DrawOffset(cmd);
	#endif
}

void DrawProg::DrawEnd(const DrawCommand& cmd) {
	((Draw*)this)->EndOp();
}

void DrawProg::DrawWindowEnd(const DrawCommand& cmd) {
	if (skip_window_commands)
		return;
	((Draw*)this)->EndOp();
}



NAMESPACE_PARALLEL_END

