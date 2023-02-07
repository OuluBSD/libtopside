#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


ProgPainter::ProgPainter(Size sz, ProgPainter& p, DrawCommand& begin, DrawCommand& end)
	: sz(sz), begin(&begin), end(&end)
{
	prev = p.cur ? p.cur : p.begin;
	next = p.end;
	begin.prev = prev;
	end.next = next;
	prev->next = &begin;
	next->prev = &end;
}

ProgPainter::ProgPainter(Size sz, DrawCommand& prev, DrawCommand& begin, DrawCommand& end, DrawCommand& next) : 
	sz(sz), prev(&prev), begin(&begin), end(&end), next(&next)
{
	
}

Size ProgPainter::GetPageSize() const {
	return sz;
}

void ProgPainter::DrawLineOp(int x1, int y1, int x2, int y2, int width, Color color) {
	DrawLine(x1,y1,x2,y2,width,RGBA(color));
}

void ProgPainter::DrawRectOp(int x, int y, int cx, int cy, Color color) {
	DrawRect(x,y,cx,cy,RGBA(color));
}

void ProgPainter::DrawTextOp(int x, int y, int angle, const wchar *text, Font font,
	                    Color ink, int n, const int *dx) {
	DrawText(x, y, WString(text).ToString(), font, RGBA(ink));
}

void ProgPainter::DrawPolyPolylineOp(const Point *vertices, int vertex_count,
                                const int *counts, int count_count,
                                int width, Color color, Color doxor) {
	DrawPolyline(vertices, vertex_count, width, color);
}

bool ProgPainter::ClipOp(const Rect& r) {
	Offset(r);
	return true;
}

void ProgPainter::EndOp() {
	End();
}




DrawCommand& ProgPainter::CreateCommand() {
	DrawCommand* cmd = &DrawCommandCache::Local().CreateCommand();
	cmd->prev = cur;
	if (cur)
		cur->next = cmd;
	cur = cmd;
	if (!cur_begin)
		cur_begin = cur;
	return *cur;
}

void ProgPainter::SetSize(Size sz) {
	this->sz = sz;
	
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_META_SIZE;
	cmd.i[0] = sz.cx;
	cmd.i[1] = sz.cy;
}

void ProgPainter::CtrlDrawBegin(hash_t h) {
	BindWindow(h);
	SetSize(sz);
}

void ProgPainter::CtrlDrawEnd() {
	UnbindWindow();
}

void ProgPainter::BindWindow(hash_t h) {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_BIND_WINDOW;
	cmd.hash = h;
}

void ProgPainter::UnbindWindow() {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_UNBIND_WINDOW;
}

void ProgPainter::DrawLine(int x0, int y0, int x1, int y1, int line_width, RGBA c) {
	if (line_width <= 0) return;
	
	if (line_width == 1) {
		DrawCommand& cmd = CreateCommand();
		cmd.type = DRAW_LINE;
		cmd.i[0] = x0;
		cmd.i[1] = y0;
		cmd.i[2] = x1;
		cmd.i[3] = y1;
		cmd.clr = c;
	}
	else {
		Point a(x0, y0), b(x1, y1);
		Point off = GetPointOffsets(a, b, line_width);
		Point p0a(a.x - off.x, a.y - off.y);
		Point p1a(b.x - off.x, b.y - off.y);
		Point p0b(a.x + off.x, a.y + off.y);
        Point p1b(b.x + off.x, b.y + off.y);
        
		DrawCommand& cmd = CreateCommand();
		cmd.type = DRAW_TRIANGLES;
		cmd.triangles.SetCount(2*2*3);
		cmd.clr = c;
		
		
		double signed_area = GetSignedArea(p0a, p1a, p0b);
		if (signed_area >= 0) {
			cmd.triangles[(0 + 0)*2 + 0] = p0a.x;
			cmd.triangles[(0 + 0)*2 + 1] = p0a.y;
			cmd.triangles[(0 + 1)*2 + 0] = p1a.x;
			cmd.triangles[(0 + 1)*2 + 1] = p1a.y;
			cmd.triangles[(0 + 2)*2 + 0] = p0b.x;
			cmd.triangles[(0 + 2)*2 + 1] = p0b.y;
			cmd.triangles[(3 + 0)*2 + 0] = p0b.x;
			cmd.triangles[(3 + 0)*2 + 1] = p0b.y;
			cmd.triangles[(3 + 1)*2 + 0] = p1a.x;
			cmd.triangles[(3 + 1)*2 + 1] = p1a.y;
			cmd.triangles[(3 + 2)*2 + 0] = p1b.x;
			cmd.triangles[(3 + 2)*2 + 1] = p1b.y;
		}
		else {
			cmd.triangles[(0 + 0)*2 + 0] = p0a.x;
			cmd.triangles[(0 + 0)*2 + 1] = p0a.y;
			cmd.triangles[(0 + 1)*2 + 0] = p0b.x;
			cmd.triangles[(0 + 1)*2 + 1] = p0b.y;
			cmd.triangles[(0 + 2)*2 + 0] = p1a.x;
			cmd.triangles[(0 + 2)*2 + 1] = p1a.y;
			cmd.triangles[(3 + 0)*2 + 0] = p0b.x;
			cmd.triangles[(3 + 0)*2 + 1] = p0b.y;
			cmd.triangles[(3 + 1)*2 + 0] = p1b.x;
			cmd.triangles[(3 + 1)*2 + 1] = p1b.y;
			cmd.triangles[(3 + 2)*2 + 0] = p1a.x;
			cmd.triangles[(3 + 2)*2 + 1] = p1a.y;
		}
	}
}

void ProgPainter::DrawImage(int x, int y, Image img, byte alpha) {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_IMAGE;
	cmd.i[0] = x;
	cmd.i[1] = y;
	cmd.img = img;
	//cmd.img.MakeSysAccel();
	cmd.clr.a = (byte)(alpha / 255.0);
}

void ProgPainter::DrawRect(Rect r, RGBA clr) {
	DrawRect(r.left, r.top, r.Width(), r.Height(), clr);
}

void ProgPainter::DrawRect(int x, int y, int w, int h, RGBA clr) {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_RECT;
	cmd.i[0] = x;
	cmd.i[1] = y;
	cmd.i[2] = x+w;
	cmd.i[3] = y+h;
	cmd.clr = clr;
}

void ProgPainter::DrawText(int x, int y, String txt, Font fnt, RGBA clr) {
	if (txt.GetCount() == 0 || fnt.IsNullInstance())
		return;
	
	#if IS_UPP_CORE
	TODO
	#else
	SysColor c;
	#if 0
	c.r = (byte)(clr.r * 255.0);
	c.g = (byte)(clr.g * 255.0);
	c.b = (byte)(clr.b * 255.0);
	c.a = 255;
	#else
	c = clr;
	#endif
	Image img = RenderTextBlended(fnt, txt.Begin(), c);
	if (img.IsEmpty()) {
		DLOG("Couldn't render text");
		return;
	}
	
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_IMAGE;
	cmd.i[0] = x;
	cmd.i[1] = y;
	cmd.img = img;
	cmd.clr.a = clr.a;
	#endif
}

void ProgPainter::DrawPolyline(const Point* pts, int pt_count, int line_width, RGBA c) {
	ASSERT(pt_count >= 3);
	DrawCommand& cmd = CreateCommand();
	cmd.clr = c;
	
	static thread_local Vector<Pointf> tmp1; // can't inherit Geometry to headers
	
	if (line_width == 1) {
		cmd.type = DRAW_POLYLINE;
		cmd.i[0] = line_width;
		cmd.pts.SetCount(pt_count);
		memcpy(cmd.pts.Begin(), pts, pt_count * sizeof(Point));
	}
	else {
		
		tmp0.SetCount(pt_count-1);
		tmp1.SetCount(0);
		angles.SetCount(pt_count-1);
		const Point* a = NULL;
		const Point* b = &pts[0];
		for(int i = 0; i < pt_count-1; i++) {
			a = b;
			b = &pts[i+1];
			tmp0[i] = GetPointOffsets(*a, *b, line_width);
			
			double dx = b->x - a->x;
			double dy = b->y - a->y;
			double theta = atan(dy / dx) * 360 / (2*M_PI);
			if (dx < 0)
				theta *= -1;
			angles[i] = theta;
		}
		a = NULL;
		b = &pts[0];
		const Point* c = &pts[1];
		double a0, a1 = angles[0];
		Point* o0, *o1 = &tmp0[0];
		
		// Loop "left side"
		for(int i = 0; i < angles.GetCount()-1; i++) {
			a = b;
			b = c;
			c = &pts[i+2];
			a0 = a1;
			a1 = angles[i+1];
			double diff = a1 - a0;
			
			o0 = o1;
			o1 = &tmp0[i+1];
			
			Pointf al	(a->x - o0->x, a->y - o0->y);
			Pointf b0l(b->x - o0->x, b->y - o0->y);
			Pointf b1l(b->x - o1->x, b->y - o1->y);
			Pointf cl	(c->x - o1->x, c->y - o1->y);
			
			if (!i)
				tmp1.Add(al);
			
			if (diff == 0) {
				tmp1.Add(b0l);
			}
			else if (diff > 0) {
				Pointf is = Intersect(al, b0l, b1l, cl);
				tmp1.Add(is);
			}
			else {
				tmp1.Add(b0l);
				tmp1.Add(b1l);
			}
			
			if (i == angles.GetCount()-2)
				tmp1.Add(cl);
		}
		
		// Loop "right side" in reverse
		a = &pts[angles.GetCount()-1];
		b = &pts[angles.GetCount()];
		c = NULL;
		a0 = angles[angles.GetCount()-1];
		o0 = &tmp0[angles.GetCount()-1];
		for (int i = angles.GetCount()-2; i >= 0; i--) {
			c = b;
			b = a;
			a = &pts[i];
			a1 = a0;
			a0 = angles[i];
			double diff = a1 - a0;
			o1 = o0;
			o0 = &tmp0[i];
			
			Pointf ar	(a->x + o0->x, a->y + o0->y);
			Pointf b0r	(b->x + o0->x, b->y + o0->y);
			Pointf b1r	(b->x + o1->x, b->y + o1->y);
			Pointf cr	(c->x + o1->x, c->y + o1->y);
			
			if (i == angles.GetCount()-2)
				tmp1.Add(cr);
			
			if (diff == 0) {
				tmp1.Add(b0r);
			}
			else if (diff < 0) {
				Pointf is = Intersect(ar, b0r, b1r, cr);
				tmp1.Add(is);
			}
			else {
				tmp1.Add(b1r);
				tmp1.Add(b0r);
			}
			
			if (!i)
				tmp1.Add(ar);
		}
		
		cmd.type = DRAW_TRIANGLES;
		TriangulatePointf::Process(tmp1, cmd.triangles);
		
		//cmd.type = DRAW_POLYLINE;
		//cmd.pts <<= tmp1;
	}
}

void ProgPainter::DrawPolygon(const Vector<Point>& pts, RGBA c) {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_TRIANGLES;
	cmd.clr = c;
	
	TODO //Triangulate::Process(pts, cmd.triangles);
}

void ProgPainter::Offset(const Rect& r) {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_OFFSET;
	cmd.i[0] = r.left;
	cmd.i[1] = r.top;
	cmd.i[2] = r.right;
	cmd.i[3] = r.bottom;
}

void ProgPainter::WindowOffset(const Rect& r) {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_WINDOW_OFFSET;
	cmd.i[0] = r.left;
	cmd.i[1] = r.top;
	cmd.i[2] = r.right;
	cmd.i[3] = r.bottom;
}

void ProgPainter::End() {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_END;
}

void ProgPainter::WindowEnd() {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_WINDOW_END;
}


void ProgPainter::Attach(DrawCommand& begin, DrawCommand& end) {
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

void ProgPainter::AppendPick(DrawCommand* begin, DrawCommand* end) {
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

DrawCommand* ProgPainter::GetBegin() const {
	return begin;
}

DrawCommand* ProgPainter::GetEnd() const {
	return end;
}

void ProgPainter::Dump() {
	if (!begin) {
		LOG("<no draw commands>");
	}
	else {
		DrawCommand* it = begin;
		int i = 0;
		while (it) {
			LOG(i++ << ": " << it->ToString());
			if (it == end)
				break;
			it = it->next;
		}
	}
}

void ProgPainter::Link() {
	ASSERT(prev != begin && next != end);
	DrawCommand* free_begin = NULL;
	DrawCommand* free_end = NULL;
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
		DrawCommand* free = free_begin;
		while (free && free != free_end) {
			if (free->is_cached)
				DrawCommandCache::Local().Return(free);
			free = free->next;
		}
	}
	
	ASSERT(begin->next != begin);
}

void ProgPainter::Clear() {
	DrawCommand* free_begin = NULL;
	DrawCommand* free_end = NULL;
	if (begin->next != end) {
		free_begin = begin->next;
		free_end = end->prev;
	}
	
	if (free_begin) {
		DrawCommand* free = free_begin;
		while (free && free != free_end) {
			if (free->is_cached)
				DrawCommandCache::Local().Return(free);
			free = free->next;
		}
		begin->next = 0;
		end->prev = 0;
	}
}

bool ProgPainter::ClipoffOp(const Rect& r) {TODO}
dword ProgPainter::GetInfo() const {TODO}
void ProgPainter::BeginOp() {TODO}
void ProgPainter::OffsetOp(Point p) {TODO}
bool ProgPainter::ExcludeClipOp(const Rect& r) {TODO}
bool ProgPainter::IntersectClipOp(const Rect& r) {TODO}
bool ProgPainter::IsPaintingOp(const Rect& r) const {TODO}
void ProgPainter::DrawPolyPolyPolygonOp(const Point *vertices, int vertex_count,
                                   const int *subpolygon_counts, int scc,
                                   const int *disjunct_polygon_counts, int dpcc,
                                   Color color, int width, Color outline,
                                   uint64 pattern, Color doxor) {TODO}
void ProgPainter::DrawArcOp(const Rect& rc, Point start, Point end, int width, Color color) {TODO}
void ProgPainter::DrawEllipseOp(const Rect& r, Color color, int pen, Color pencolor) {TODO}





double TriangulatePointf::Area(const Vector<Pointf> &contour) {
	int n = contour.GetCount();
	
	double A=0.0f;
	
	for (int p=n-1,q=0; q<n; p=q++) {
		A+= contour[p].x * contour[q].y - contour[q].x * contour[p].y;
	}
	
	return A*0.5f;
}

/*
  InsideTriangle decides if a point P is Inside of the triangle
  defined by A, B, C.
*/
bool TriangulatePointf::InsideTriangle(double Ax, double Ay,
		double Bx, double By,
		double Cx, double Cy,
		double Px, double Py)
        
{
	double ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
	double cCROSSap, bCROSScp, aCROSSbp;
	
	ax = Cx - Bx;
	ay = Cy - By;
	bx = Ax - Cx;
	by = Ay - Cy;
	cx = Bx - Ax;
	cy = By - Ay;
	apx= Px - Ax;
	apy= Py - Ay;
	bpx= Px - Bx;
	bpy= Py - By;
	cpx= Px - Cx;
	cpy= Py - Cy;
	
	aCROSSbp = ax*bpy - ay*bpx;
	cCROSSap = cx*apy - cy*apx;
	bCROSScp = bx*cpy - by*cpx;
	
	return ((aCROSSbp >= 0.0f) && (bCROSScp >= 0.0f) && (cCROSSap >= 0.0f));
};

bool TriangulatePointf::Snip(const Vector<Pointf> &contour,int u,int v,int w,int n,int *V) {
	int p;
	double Ax, Ay, Bx, By, Cx, Cy, Px, Py;
	
	Ax = contour[V[u]].x;
	Ay = contour[V[u]].y;
	
	Bx = contour[V[v]].x;
	By = contour[V[v]].y;
	
	Cx = contour[V[w]].x;
	Cy = contour[V[w]].y;
	
	if (EPSILON > (((Bx-Ax)*(Cy-Ay)) - ((By-Ay)*(Cx-Ax))))
		return false;
		
	for (p=0;p<n;p++) {
		if ((p == u) || (p == v) || (p == w))
			continue;
			
		Px = contour[V[p]].x;
		
		Py = contour[V[p]].y;
		
		if (InsideTriangle(Ax,Ay,Bx,By,Cx,Cy,Px,Py))
			return false;
	}
	
	return true;
}

bool TriangulatePointf::Process(const Vector<Pointf> &contour, Vector<float> &result) {
	/* allocate and initialize list of Vertices in polygon */
	result.SetCount(0);
	
	int n = contour.GetCount();
	
	if (n < 3)
		return false;
		
	Vector<int> V;
	V.SetCount(n);
	
	/* we want a counter-clockwise polygon in V */
	
	if (0.0f < Area(contour))
		for (int v=0; v<n; v++)
			V[v] = v;
	else
		for (int v=0; v<n; v++)
			V[v] = (n-1)-v;
			
	int nv = n;
	
	/*  remove nv-2 Vertices, creating 1 triangle every time */
	int count = 2*nv;   /* error detection */
	
	for (int m=0, v=nv-1; nv>2;) {
		/* if we loop, it is probably a non-simple polygon */
		if (0 >= (count--)) {
			//** TriangulatePointf: ERROR - probable bad polygon!
			return false;
		}
		
		/* three consecutive vertices in current polygon, <u,v,w> */
		int u = v  ;
		
		if (nv <= u)
			u = 0;     /* previous */
			
		v = u+1;
		
		if (nv <= v)
			v = 0;     /* new v    */
			
		int w = v+1;
		
		if (nv <= w)
			w = 0;     /* next     */
			
		if (Snip(contour,u,v,w,nv,V.Begin())) {
			int a,b,c,s,t;
			
			/* true names of the vertices */
			a = V[u];
			b = V[v];
			c = V[w];
			
			/* output Triangle */
			#if 0
			tri2& tri = result.Add();
			tri.a = contour[a];
			tri.b = contour[b];
			tri.c = contour[c];
			#else
			const auto& aa = contour[a];
			const auto& bb = contour[b];
			const auto& cc = contour[c];
			result.Add(aa.x);
			result.Add(aa.y);
			result.Add(bb.x);
			result.Add(bb.y);
			result.Add(cc.x);
			result.Add(cc.y);
			#endif
			
			m++;
			
			/* remove v from remaining polygon */
			
			for (s=v,t=v+1;t<nv;s++,t++)
				V[s] = V[t];
				
			nv--;
			
			/* resest error detection counter */
			count = 2*nv;
		}
	}
	
	
	
	return true;
}

Pointf GetPointOffsets(const Pointf& a, const Pointf& b, double width) {
	double dx = b.x - a.x;
	double dy = b.y - a.y;
	double len = sqrt(dx * dx + dy * dy);
	double scale = width / (2 * len);
	return Pointf(-scale * dy, scale * dx);
}


NAMESPACE_TOPSIDE_END
