#include <CtrlCore/CtrlCore.h>

#if 0

NAMESPACE_UPP_BEGIN


dword SystemDraw::GetInfo() const {
	return 0;
}

Size SystemDraw::GetPageSize() const {
	return pageSize;
}


void SystemDraw::SetClip() {
	GuiLock __;
	drawingclip = Rect(-(INT_MAX >> 1), -(INT_MAX >> 1), +(INT_MAX >> 1), +(INT_MAX >> 1));
	if(!clip.IsEmpty()) {
		const Vector<Rect>& topclip = clip.Top();
		drawingclip = Rect(0, 0, 0, 0);
		if(!topclip.IsEmpty()) {
			drawingclip = topclip[0];
			for(int i = 1; i < topclip.GetCount(); i++)
				drawingclip |= topclip[i];
		}
		drawingclip -= actual_offset;
	}
}

void SystemDraw::BeginOp() {
	Cloff f = cloff.Top();
	Vector<Rect> newclip;
	newclip <<= clip.Top();
	f.clipi = clip.GetCount();
	clip.Add() = pick(newclip);
	cloff.Add(f);
	
	DrawProxy::BeginOp();
}

void SystemDraw::EndOp() {
	ASSERT(cloff.GetCount());
	cloff.Drop();
	actual_offset = offset[cloff.Top().offseti];
	clip.SetCount(cloff.Top().clipi + 1);
	SetClip();
	
	DrawProxy::EndOp();
}

void SystemDraw::OffsetOp(Point p) {
	Cloff f = cloff.Top();
	f.offseti = offset.GetCount();
	actual_offset += p;
	drawingclip -= p;
	offset.Add(actual_offset);
	cloff.Add(f);
	
	DrawProxy::OffsetOp(p);
}

bool SystemDraw::ClipOp(const Rect& r) {
	Cloff f = cloff.Top();
	bool ch = false;
	Vector<Rect> newclip = Intersect(clip.Top(), r + actual_offset, ch);
	if(ch) {
		f.clipi = clip.GetCount();
		clip.Add() = pick(newclip);
	}
	cloff.Add(f);
	if(ch)
		SetClip();
	bool b = clip.Top().GetCount();
	
	DrawProxy::ClipOp(r);
	return b;
}

bool SystemDraw::ClipoffOp(const Rect& r) {
	
}

bool SystemDraw::ExcludeClipOp(const Rect& r) {
	
}

bool SystemDraw::IntersectClipOp(const Rect& r) {
	
}

bool SystemDraw::IsPaintingOp(const Rect& r) const {
	
}

Rect SystemDraw::GetPaintRect() const {
	
}


void SystemDraw::DrawRectOp(int x, int y, int cx, int cy, Color color) {
	
}

void SystemDraw::SysDrawImageOp(int x, int y, const Image& img, const Rect& src, Color color) {
	
}

void SystemDraw::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	
}


void SystemDraw::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
								const int *counts, int count_count,
								int width, Color color, Color doxor) {
	
}

void SystemDraw::DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
									const int *subpolygon_counts, int scc,
									const int *disjunct_polygon_counts, int dpcc,
									Color color, int width, Color outline,
									uint64 pattern, Color doxor) {
	
}

void SystemDraw::DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color) {
	
}


void SystemDraw::DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor) {
	
}

void SystemDraw::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
						Color ink, int n, const int *dx) {
	
}


Size SystemDraw::GetNativeDpi() const {
	
}

void SystemDraw::BeginNative() {
	
}

void SystemDraw::EndNative() {
	
}


int SystemDraw::GetCloffLevel() const {
	
}


NAMESPACE_UPP_END

#endif
