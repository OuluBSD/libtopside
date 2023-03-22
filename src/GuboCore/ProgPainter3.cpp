#include "GuboCore.h"

NAMESPACE_TOPSIDE_BEGIN

ProgPainter3::ProgPainter3(Volf sz, ProgPainter3& p, DrawCommand3& begin, DrawCommand3& end) {
	prev = p.cur ? p.cur : p.begin;
	next = p.end;
	begin.prev = prev;
	end.next = next;
	prev->next = &begin;
	next->prev = &end;
}

ProgPainter3::ProgPainter3(Volf sz, DrawCommand3& prev, DrawCommand3& begin, DrawCommand3& end, DrawCommand3& next) :
	prev(&prev), begin(&begin), end(&end), next(&next)
{
	SDraw3::Init(sz);
	
}

void ProgPainter3::Clear() {
	DrawCommand3* free_begin = NULL;
	DrawCommand3* free_end = NULL;
	if (begin->next != end) {
		free_begin = begin->next;
		free_end = end->prev;
	}
	
	if (free_begin) {
		DrawCommand3* free = free_begin;
		while (free && free != free_end) {
			if (free->is_cached)
				DrawCommand3Cache::Local().Return(free);
			free = free->next;
		}
		begin->next = 0;
		end->prev = 0;
	}
	
	cur = 0;
	cur_begin = 0;
}

void ProgPainter3::WindowOffset(const Cubf& r) {
	Clipoff(r);
}

void ProgPainter3::WindowEnd() {
	End();
}

DrawCommand3& ProgPainter3::CreateCommand() {
	DrawCommand3* cmd = &DrawCommand3Cache::Local().CreateCommand();
	cmd->prev = cur;
	if (cur)
		cur->next = cmd;
	cur = cmd;
	if (!cur_begin)
		cur_begin = cur;
	return *cur;
}

DrawCommand3* ProgPainter3::GetCurrentBegin() const {
	return cur_begin;
}

DrawCommand3* ProgPainter3::GetBegin() const {
	return begin;
}

DrawCommand3* ProgPainter3::GetEnd() const {
	return end;
}

void ProgPainter3::Link() {
	ASSERT(prev != begin && next != end);
	DrawCommand3* free_begin = NULL;
	DrawCommand3* free_end = NULL;
	if (begin->next != end) {
		free_begin = begin->next;
		free_end = end->prev;
	}
	if (!cur) {
		end->prev = begin;
		begin->next = end;
	}
	else {
		end->prev = cur;
		cur->next = end;
		cur_begin->prev = begin;
		begin->next = cur_begin;
	}
	end->next = next;
	begin->prev = prev;
	next->prev = end;
	prev->next = begin;
	if (free_begin) {
		DrawCommand3* free = free_begin;
		while (free && free != free_end) {
			if (free->is_cached)
				DrawCommand3Cache::Local().Return(free);
			free = free->next;
		}
	}
	
	ASSERT(begin->next != begin);
}

void ProgPainter3::Dump() {
	if (!begin) {
		LOG("<no draw commands>");
	}
	else {
		DrawCommand3* it = begin;
		int i = 0;
		while (it) {
			LOG(i++ << ": " << it->ToString());
			if (it == end)
				break;
			it = it->next;
		}
	}
}

void ProgPainter3::Attach(DrawCommand3& begin, DrawCommand3& end) {
	if (this->begin->next == &begin && this->end->prev == &end) {
		cur = 0;
		cur_begin = 0;
		return;
	}
	
	if (cur) {
		ASSERT_(0, "TODO this doesn't seem to make sense... workaround: remove added commands before this attach");
	}
	else {
		ASSERT(this->begin && this->end);
		begin.prev = this->begin;
		this->begin->next = &begin;
		end.next = this->end;
		this->end->prev = &end;
		cur = &end;
		cur_begin = &begin;
	}
}

void ProgPainter3::AppendPick(DrawCommand3* begin, DrawCommand3* end) {
	ASSERT(begin && end);
	
	if (cur) {
		end->next = cur->next;
		ASSERT(end->next);
		end->next->prev = end;
		cur->next = begin;
		begin->prev = cur;
		cur = end;
	}
	else {
		ASSERT(this->begin && this->end);
		begin->prev = this->begin;
		this->begin->next = begin;
		end->next = this->end;
		this->end->prev = end;
		cur = end;
		cur_begin = begin;
	}
}

void ProgPainter3::SetSize(Volf sz) {
	#if IS_UPP_CORE
	this->sz = sz;
	#endif
	
	Init(sz);
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_SET_SIZE;
	cmd.sz = sz;
}

void ProgPainter3::BindWindow(hash_t h) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_BIND_WINDOW;
	cmd.hash = h;
}

void ProgPainter3::UnbindWindow() {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_UNBIND_WINDOW;
}

void ProgPainter3::CtrlDrawBegin(hash_t h) {
	BindWindow(h);
	SetSize(sz);
}

void ProgPainter3::CtrlDrawEnd() {
	UnbindWindow();
}

dword ProgPainter3::GetInfo() const {
	return SDraw3::GetInfo();
}

Volf ProgPainter3::GetPageSize() const {
	ASSERT(!sz.IsEmpty());
	return sz;
}

void ProgPainter3::StartPage() {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_START_PAGE;
}

void ProgPainter3::EndPage() {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_END_PAGE;
}

void ProgPainter3::BeginOp() {
	SDraw3::BeginOp();
	
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_BEGIN_OP;
}

void ProgPainter3::EndOp() {
	SDraw3::EndOp();
	
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_END_OP;
}

void ProgPainter3::OffsetOp(Point3f p) {
	SDraw3::OffsetOp(p);
	
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_OFFSET_OP;
	cmd.pt = p;
}

bool ProgPainter3::ClipOp(const Cubf& r) {
	SDraw3::ClipOp(r);
	
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_CLIP_OP;
	cmd.r = r;
	return true;
}

bool ProgPainter3::ClipoffOp(const Cubf& r) {
	SDraw3::ClipoffOp(r);
	
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_CLIPOFF_OP;
	cmd.r = r;
	return true;
}

bool ProgPainter3::ExcludeClipOp(const Cubf& r) {
	SDraw3::ExcludeClipOp(r);
	
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_EXCLUDE_CLIP_OP;
	cmd.r = r;
	return true;
}

bool ProgPainter3::IntersectClipOp(const Cubf& r) {
	SDraw3::IntersectClipOp(r);
	
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_INTERSECT_CLIP_OP;
	cmd.r = r;
	return true;
}

bool ProgPainter3::IsPaintingOp(const Cubf& r) const {
	return SDraw3::IsPaintingOp(r); // is return true
}

Cubf ProgPainter3::GetPaintCubf() const {
	return Cubf(sz);
}

void ProgPainter3::DrawBoxOp(float x, float y, float z, float cx, float cy, float cz, Color color) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_BOX_OP;
	cmd.pt.x = x;
	cmd.pt.y = y;
	cmd.pt.z = z;
	cmd.sz.cx = cx;
	cmd.sz.cy = cy;
	cmd.sz.cz = cz;
	cmd.color = color;
}

void ProgPainter3::SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, Color color) {
	SysDrawImageOp(x, y, z, imgsz, img, img.GetSize(), color);
}

void ProgPainter3::SysDrawImageOp(float x, float y, float z, Sizef imgsz, const Image& img, const Rect& src, Color color) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_SYSDRAW_IMAGE_OP;
	cmd.pt = Point3f(x,y,z);
	cmd.img = img;
	cmd.r = Volf(imgsz.cx, imgsz.cy, 0.01);
	cmd.rect = src;
	cmd.color = color;
}

void ProgPainter3::DrawImageOp(float x, float y, float z, float cx, float cy, float cz, const Image& img, const Rect& src, Color color) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_IMAGE_OP;
	cmd.pt = Point3f(x,y,z);
	cmd.sz = Volf(cx,cy,cy);
	cmd.img = img;
	cmd.rect = src;
	cmd.color = color;
}

void ProgPainter3::DrawDataOp(float x, float y, float z, float cx, float cy, float cz, const String& data, const char *id) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_DATA_OP;
	cmd.pt = Point3f(x,y,z);
	cmd.sz = Volf(cx,cy,cy);
	cmd.txt = data;
	cmd.id = id;
}

void ProgPainter3::DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_LINE_OP;
	cmd.pt = Point3f(x1,y1,z1);
	cmd.pt2 = Point3f(x2,y2,z2);
	cmd.width = width;
	cmd.color = color;
}

void ProgPainter3::DrawPolyPolylineOp(const Point3f *vertices, int vertex_count,
						const int *counts, int count_count,
						float width, Color color, Color doxor) {
	if (vertex_count <= 0 || count_count <= 0)
		return;
	
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_POLY_POLYLINE_OP;
	cmd.points.SetCount(vertex_count);
	cmd.ints.SetCount(count_count);
	memcpy(cmd.points.Begin(), vertices, sizeof(Point) * vertex_count);
	memcpy(cmd.ints.Begin(), counts, sizeof(int) * count_count);
	cmd.width = width;
	cmd.color = color;
	cmd.doxor = doxor;
}

void ProgPainter3::DrawPolyPolyPolygonOp(const Point3f *vertices, int vertex_count,
							const int *subpolygon_counts, int scc,
							const int *disjunct_polygon_counts, int dpcc,
							Color color, float width, Color outline,
							uint64 pattern, Color doxor) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_POLY_POLY_POLYGON_OP;
	cmd.points.SetCount(vertex_count);
	cmd.subpolygon_counts.SetCount(scc);
	cmd.disjunct_polygon_counts.SetCount(dpcc);
	memcpy(cmd.points.Begin(), vertices, sizeof(Point) * vertex_count);
	memcpy(cmd.subpolygon_counts.Begin(), subpolygon_counts, sizeof(int) * scc);
	memcpy(cmd.disjunct_polygon_counts.Begin(), disjunct_polygon_counts, sizeof(int) * dpcc);
	cmd.color = color;
	cmd.width = width;
	cmd.outline = outline;
	cmd.pattern = pattern;
	cmd.doxor = doxor;
}

void ProgPainter3::DrawArcOp(const Cubf& rc, Point3f start, Point3f end, float width, Color color) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_ARC_OP;
	cmd.r = rc;
	cmd.pt = start;
	cmd.pt2 = end;
	cmd.width = width;
	cmd.color = color;
}

void ProgPainter3::DrawEllipseOp(const Cubf& r, Color color, float pen, Color pencolor) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_ELLIPSE_OP;
	cmd.r = r;
	cmd.color = color;
	cmd.width = pen;
	cmd.outline = pencolor;
}

void ProgPainter3::DrawTextOp(float x, float y, float z, int angle, const wchar *text, Font font,
				Color ink, int n, const int *dx) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_TEXT_OP;
	cmd.pt = Point3f(x,y,z);
	cmd.angle = angle;
	cmd.wtxt = WString(text);
	cmd.fnt = font;
	cmd.color = ink;
	cmd.ints.SetCount(n);
	if (dx) {
		TODO
		/// not right... what dx is? //memcpy(cmd.ints.Begin(), dx, sizeof(int) * n);
	}
}

void ProgPainter3::DrawDrawingOp(const Cubf& target, const Drawing& w) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_DRAWING_OP;
	cmd.r = target;
	#if IS_UPP_CORE
	cmd.value = w;
	#else
	TODO
	#endif
}

void ProgPainter3::DrawPaintingOp(const Cubf& target, const Painting& w) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_PAINTING_OP;
	cmd.r = target;
	#if IS_UPP_CORE
	cmd.value = w;
	#else
	TODO
	#endif
}

Volf ProgPainter3::GetNativeDpi() const {
	return Volf(96,96,96);
}

void ProgPainter3::BeginNative() {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_BEGIN_NATIVE;
}

void ProgPainter3::EndNative() {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_END_NATIVE;
}

int ProgPainter3::GetCloffLevel() const {
	return 0;
}

void ProgPainter3::Escape(const String& data) {
	DrawCommand3& cmd = CreateCommand();
	cmd.type = DRAW3_ESCAPE;
	cmd.txt = data;
}


NAMESPACE_TOPSIDE_END
