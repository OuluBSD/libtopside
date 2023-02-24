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
		//ptrs[DRAW_SET_SIZE] = &DrawProg::SetSize;
		//ptrs[DRAW_IMAGE] = &DrawProg::DrawImage;
		//ptrs[DRAW_CTRL_DRAW_BEGIN] = &DrawProg::CtrlDrawBegin;
		//ptrs[DRAW_CTRL_DRAW_END] = &DrawProg::CtrlDrawEnd;
		//ptrs[DRAW_GET_INFO] = &DrawProg::GetInfo;
		//ptrs[DRAW_GET_PAGE_SIZE] = &DrawProg::GetPageSize;
		ptrs[DRAW_START_PAGE] = &DrawProg::StartPage;
		ptrs[DRAW_END_PAGE] = &DrawProg::EndPage;
		ptrs[DRAW_BEGIN_OP] = &DrawProg::BeginOp;
		ptrs[DRAW_END_OP] = &DrawProg::EndOp;
		ptrs[DRAW_OFFSET_OP] = &DrawProg::OffsetOp;
		ptrs[DRAW_CLIP_OP] = &DrawProg::ClipOp;
		ptrs[DRAW_CLIPOFF_OP] = &DrawProg::ClipoffOp;
		ptrs[DRAW_EXCLUDE_CLIP_OP] = &DrawProg::ExcludeClipOp;
		ptrs[DRAW_INTERSECT_CLIP_OP] = &DrawProg::IntersectClipOp;
		//ptrs[DRAW_IS_PAINTING_OP] = &DrawProg::IsPaintingOp;
		//ptrs[DRAW_GET_PAINT_RECT] = &DrawProg::GetPaintRect;
		ptrs[DRAW_RECT_OP] = &DrawProg::RectOp;
		ptrs[DRAW_SYSDRAW_IMAGE_OP] = &DrawProg::SysdrawImageOp;
		ptrs[DRAW_IMAGE_OP] = &DrawProg::ImageOp;
		ptrs[DRAW_DATA_OP] = &DrawProg::DataOp;
		ptrs[DRAW_LINE_OP] = &DrawProg::LineOp;
		ptrs[DRAW_POLY_POLYLINE_OP] = &DrawProg::PolyPolylineOp;
		ptrs[DRAW_POLY_POLY_POLYGON_OP] = &DrawProg::PolyPolyPolygonOp;
		ptrs[DRAW_ARC_OP] = &DrawProg::ArcOp;
		ptrs[DRAW_ELLIPSE_OP] = &DrawProg::EllipseOp;
		ptrs[DRAW_TEXT_OP] = &DrawProg::TextOp;
		ptrs[DRAW_DRAWING_OP] = &DrawProg::DrawingOp;
		ptrs[DRAW_PAINTING_OP] = &DrawProg::PaintingOp;
		//ptrs[DRAW_GET_NATIVE_DPI] = &DrawProg::GetNativeDpi;
		ptrs[DRAW_BEGIN_NATIVE] = &DrawProg::BeginNative;
		ptrs[DRAW_END_NATIVE] = &DrawProg::EndNative;
		//ptrs[DRAW_GET_CLOFF_LEVEL] = &DrawProg::GetCloffLevel;
		ptrs[DRAW_ESCAPE] = &DrawProg::Escape;
		ptrs[DRAW_BIND_WINDOW] = &DrawProg::BindWindow;
		ptrs[DRAW_UNBIND_WINDOW] = &DrawProg::UnbindWindow;
		
		#if 0
		ptrs[DRAW_LINE] = &DrawProg::DrawLine;
		ptrs[DRAW_TEXT] = &DrawProg::DrawText;
		ptrs[DRAW_IMAGE] = &DrawProg::DrawImage;
		ptrs[DRAW_IMAGE_SIZED] = &DrawProg::DrawImageOp;
		ptrs[DRAW_IMAGEBUFFER] = &DrawProg::DrawImageBuffer;
		ptrs[DRAW_RECT] = &DrawProg::DrawRect;
		ptrs[DRAW_TRIANGLES] = &DrawProg::DrawTriangles;
		ptrs[DRAW_POLYLINE] = &DrawProg::DrawPolyline;
		ptrs[DRAW_CLIPOFF] = &DrawProg::Clipoff;
		ptrs[DRAW_OFFSET] = &DrawProg::DrawOffset;
		ptrs[DRAW_OFFSET_POINT] = &DrawProg::DrawOffsetPoint;
		ptrs[DRAW_END] = &DrawProg::DrawEnd;
		ptrs[DRAW_WINDOW_OFFSET] = &DrawProg::DrawWindowOffset;
		ptrs[DRAW_WINDOW_END] = &DrawProg::DrawWindowEnd;
		#endif
		has_ptrs = true;
	}
	
	const DrawCommand* cmd = begin;
	while (cmd) {
		if (cmd->type > DRAW_NULL && cmd->type < DRAW_CMD_COUNT) {
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
/*
void DrawProg::SetSize(const DrawCommand& cmd) {
	((Draw*)this)->SetSize(
		cmd.sz);
}

void DrawProg::CtrlDrawBegin(const DrawCommand& cmd) {
	((Draw*)this)->CtrlDrawBegin(
		);
}

void DrawProg::CtrlDrawEnd(const DrawCommand& cmd) {
	((Draw*)this)->CtrlDrawEnd(
		);
}

void DrawProg::GetPageSize(const DrawCommand& cmd) {
	((Draw*)this)->GetPageSize(
		);
}
*/
void DrawProg::StartPage(const DrawCommand& cmd) {
	((Draw*)this)->StartPage(
		);
}

void DrawProg::EndPage(const DrawCommand& cmd) {
	((Draw*)this)->EndPage(
		);
}

void DrawProg::BeginOp(const DrawCommand& cmd) {
	((Draw*)this)->BeginOp(
		);
}

void DrawProg::EndOp(const DrawCommand& cmd) {
	((Draw*)this)->EndOp(
		);
}

void DrawProg::OffsetOp(const DrawCommand& cmd) {
	((Draw*)this)->OffsetOp(
		cmd.pt);
}

void DrawProg::ClipOp(const DrawCommand& cmd) {
	((Draw*)this)->ClipOp(
		cmd.r);
}

void DrawProg::ClipoffOp(const DrawCommand& cmd) {
	((Draw*)this)->ClipoffOp(
		cmd.r);
}

void DrawProg::ExcludeClipOp(const DrawCommand& cmd) {
	((Draw*)this)->ExcludeClipOp(
		cmd.r);
}

void DrawProg::IntersectClipOp(const DrawCommand& cmd) {
	((Draw*)this)->IntersectClipOp(
		cmd.r);
}

void DrawProg::RectOp(const DrawCommand& cmd) {
	((Draw*)this)->DrawRectOp(
		cmd.pt.x,
		cmd.pt.y,
		cmd.sz.cx,
		cmd.sz.cy,
		cmd.color);
}

void DrawProg::SysdrawImageOp(const DrawCommand& cmd) {
	((Draw*)this)->SysDrawImageOp(
		cmd.pt.x, cmd.pt.y,
		cmd.img,
		cmd.r,
		cmd.color);
}

void DrawProg::ImageOp(const DrawCommand& cmd) {
	((Draw*)this)->DrawImageOp(
		cmd.pt.x, cmd.pt.y,
		cmd.sz.cx, cmd.sz.cy,
		cmd.img,
		cmd.r,
		cmd.color);
}

void DrawProg::DataOp(const DrawCommand& cmd) {
	((Draw*)this)->DrawDataOp(
		cmd.pt.x, cmd.pt.y,
		cmd.sz.cx, cmd.sz.cy,
		cmd.txt,
		cmd.id);
}

void DrawProg::LineOp(const DrawCommand& cmd) {
	((Draw*)this)->DrawLineOp(
		cmd.pt.x, cmd.pt.y,
		cmd.pt2.x, cmd.pt2.y,
		cmd.width,
		cmd.color
		);
}

void DrawProg::PolyPolylineOp(const DrawCommand& cmd) {
	((Draw*)this)->DrawPolyPolylineOp(
		cmd.points.Begin(), cmd.points.GetCount(),
		cmd.ints.Begin(), cmd.ints.GetCount(),
		cmd.width, cmd.color, cmd.doxor
		);
}

void DrawProg::PolyPolyPolygonOp(const DrawCommand& cmd) {
	((Draw*)this)->DrawPolyPolyPolygonOp(
		cmd.points.Begin(), cmd.points.GetCount(),
		cmd.subpolygon_counts.Begin(), cmd.subpolygon_counts.GetCount(),
		cmd.disjunct_polygon_counts.Begin(), cmd.disjunct_polygon_counts.GetCount(),
		cmd.color, cmd.width, cmd.outline,
		cmd.pattern, cmd.doxor);
}

void DrawProg::ArcOp(const DrawCommand& cmd) {
	((Draw*)this)->DrawArcOp(
		cmd.r,
		cmd.pt,
		cmd.pt2,
		cmd.width,
		cmd.color);
}

void DrawProg::EllipseOp(const DrawCommand& cmd) {
	((Draw*)this)->DrawEllipseOp(
		cmd.r,
		cmd.color,
		cmd.width,
		cmd.outline);
}

void DrawProg::TextOp(const DrawCommand& cmd) {
	((Draw*)this)->DrawTextOp(
		cmd.pt.x, cmd.pt.y,
		cmd.angle,
		cmd.wtxt,
		cmd.fnt,
		cmd.color,
		cmd.ints.GetCount(),
		0);
}

void DrawProg::DrawingOp(const DrawCommand& cmd) {
	#if IS_UPP_CORE
	((Draw*)this)->DrawDrawingOp(
		cmd.r, cmd.value);
	#else
	TODO
	#endif
}

void DrawProg::PaintingOp(const DrawCommand& cmd) {
	#if IS_UPP_CORE
	((Draw*)this)->DrawPaintingOp(
		cmd.r, cmd.value);
	#else
	TODO
	#endif
}

void DrawProg::BeginNative(const DrawCommand& cmd) {
	((Draw*)this)->BeginNative(
		);
}

void DrawProg::EndNative(const DrawCommand& cmd) {
	((Draw*)this)->EndNative(
		);
}

void DrawProg::Escape(const DrawCommand& cmd) {
	((Draw*)this)->Escape(
		cmd.txt);
}

void DrawProg::BindWindow(const DrawCommand& cmd) {
	ASSERT_(bind_win_count == 0, "Window have been bound already. DrawCommand program is invalid.");
	bind_win_count++;
}

void DrawProg::UnbindWindow(const DrawCommand& cmd) {
	bind_win_count--;
}


#if 0


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
	Color clr = cmd.clr.a == 0 ? Color(Null) : Color(cmd.clr);
	((Draw*)this)->DrawImageOp(
		x, y,
		cx, cy,
		cmd.img,
		cmd.crop,
		clr);
	
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

void DrawProg::DrawImageBuffer(const DrawCommand& cmd) {
	Rect r(cmd.i[0], cmd.i[1], cmd.i[2], cmd.i[3]);
	ImageBuffer* ib = (ImageBuffer*)cmd.ptr;
	ASSERT(ib);
	TODO // dead end
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


#endif


NAMESPACE_PARALLEL_END

