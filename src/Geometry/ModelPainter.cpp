#include "Geometry.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN


ModelPainter::ModelPainter(Volf sz, ModelPainter& p, DrawCommand& begin, DrawCommand& end)
	: sz(sz), begin(&begin), end(&end)
{
	prev = p.cur ? p.cur : p.begin;
	next = p.end;
	begin.prev = prev;
	end.next = next;
	prev->next = &begin;
	next->prev = &end;
}

ModelPainter::ModelPainter(Volf sz, DrawCommand& prev, DrawCommand& begin, DrawCommand& end, DrawCommand& next) : 
	sz(sz), prev(&prev), begin(&begin), end(&end), next(&next)
{
	
}

void ModelPainter::SetSize(Volf v) {
	this->sz = v;
	
	TODO
	/*
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_META_SIZE3;
	cmd.i[0] = v.cx;
	cmd.i[1] = v.cy;
	cmd.i[2] = v.cz;
	*/
}

Volf ModelPainter::GetPageSize() const {
	return sz;
}

void ModelPainter::DrawLineOp(float x1, float y1, float z1, float x2, float y2, float z2, float width, Color color) {
	DrawLine(x1,y1,z1,x2,y2,z2,width,RGBA(color));
}

void ModelPainter::DrawCuboidOp(float x, float y, float z, float cx, float cy, float cz, Color color) {
	DrawCuboid(x,y,z,cx,cy,cz,RGBA(color));
}

void ModelPainter::DrawTextOp(float x, float y, float z, float angle, const wchar *text, Font font,
	                          Color ink, int n, const float *dx) {
	DrawText(x, y, z, WString(text).ToString(), font, RGBA(ink));
}

void ModelPainter::DrawPolyPolylineOp(const vec3 *vertices, int vertex_count,
                                      const int *counts, int count_count,
                                      float width, Color color, Color doxor) {
	DrawPolyline(vertices, vertex_count, width, color);
}

bool ModelPainter::ClipOp(const Cubf& r) {
	Offset(r);
	return true;
}

void ModelPainter::EndOp() {
	End();
}




DrawCommand& ModelPainter::CreateCommand() {
	DrawCommand* cmd = &DrawCommandCache::Local().CreateCommand();
	cmd->prev = cur;
	if (cur)
		cur->next = cmd;
	cur = cmd;
	if (!cur_begin)
		cur_begin = cur;
	return *cur;
}

void ModelPainter::CtrlDrawBegin(hash_t h) {
	BindWindow(h);
	SetSize(sz);
}

void ModelPainter::CtrlDrawEnd() {
	UnbindWindow();
}

void ModelPainter::BindWindow(hash_t h) {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_BIND_WINDOW;
	cmd.hash = h;
}

void ModelPainter::UnbindWindow() {
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_UNBIND_WINDOW;
}

void ModelPainter::DrawLine(float x0, float y0, float z0, float x1, float y1, float z1, float line_width, RGBA c) {
	TODO
	#if 0
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
		cmd.triangles.SetCount(2);
		cmd.clr = c;
		
		TODO
		/*
		double signed_area = GetSignedArea(p0a, p1a, p0b);
		if (signed_area >= 0) {
			cmd.triangles[0].Set(p0a, p1a, p0b);
			cmd.triangles[1].Set(p0b, p1a, p1b);
		}
		else {
			cmd.triangles[0].Set(p0a, p0b, p1a);
			cmd.triangles[1].Set(p0b, p1b, p1a);
		}*/
	}
	#endif
}

void ModelPainter::DrawImage(float x, float y, float z, Image img, byte alpha) {
	TODO
	#if 0
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_IMAGE;
	cmd.i[0] = x;
	cmd.i[1] = y;
	cmd.img = img;
	//cmd.img.MakeSysAccel();
	cmd.clr.a = (byte)(alpha / 255.0);
	#endif
}

void ModelPainter::DrawCuboid(Cubf r, RGBA clr) {
	DrawCuboid(r.left, r.top, r.near, r.Width(), r.Height(), r.Depth(), clr);
}

void ModelPainter::DrawCuboid(float x, float y, float z, float w, float h, float d, RGBA clr) {
	TODO
	#if 0
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_CUBF;
	cmd.i[0] = x;
	cmd.i[1] = y;
	cmd.i[2] = z;
	cmd.i[3] = x+w;
	cmd.i[4] = y+h;
	cmd.i[5] = z+d;
	cmd.clr = clr;
	#endif
}

void ModelPainter::DrawText(float x, float y, float z, String txt, Font fnt, RGBA clr) {
	TODO
	#if 0
	if (txt.GetCount() == 0 || fnt.IsNullInstance())
		return;
	
	#if IS_UPP_CORE
	TODO
	#else
	SysColor c;
	c.r = (byte)(clr.r * 255.0);
	c.g = (byte)(clr.g * 255.0);
	c.b = (byte)(clr.b * 255.0);
	c.a = 255;
	RawSysImage* surf = fnt.GetSysFont()->RenderTextBlended(txt.Begin(), c);
	if (!surf) {
		#if HAVE_SDL2
		DLOG("Couldn't render text: " << SDL_GetError());
		#else
		DLOG("Couldn't render text");
		#endif
		return;
	}
	
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_IMAGE;
	cmd.i[0] = x;
	cmd.i[1] = y;
	cmd.img = Image(surf);
	//cmd.img.MakeSysAccel();
	cmd.clr.a = clr.a;
	#endif
	#endif
}

void ModelPainter::DrawPolyline(const vec3* pts, int pt_count, float line_width, RGBA c) {
	TODO
	#if 0
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
	#endif
}

void ModelPainter::DrawPolygon(const Vector<vec3>& pts, RGBA c) {
	TODO
	#if 0
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_TRIANGLES;
	cmd.clr = c;
	
	TODO //Triangulate::Process(pts, cmd.triangles);
	#endif
}

void ModelPainter::Offset(const Cubf& r) {
	TODO
	#if 0
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_OFFSET;
	cmd.i[0] = r.left;
	cmd.i[1] = r.top;
	cmd.i[2] = r.right;
	cmd.i[3] = r.bottom;
	#endif
}

void ModelPainter::WindowOffset(const Cubf& r) {
	TODO
	#if 0
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_WINDOW_OFFSET;
	cmd.i[0] = r.left;
	cmd.i[1] = r.top;
	cmd.i[2] = r.right;
	cmd.i[3] = r.bottom;
	#endif
}

void ModelPainter::End() {
	TODO
	#if 0
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_END;
	#endif
}

void ModelPainter::WindowEnd() {
	TODO
	#if 0
	DrawCommand& cmd = CreateCommand();
	cmd.type = DRAW_WINDOW_END;
	#endif
}


void ModelPainter::Attach(DrawCommand& begin, DrawCommand& end) {
	TODO
	#if 0
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
	#endif
}

void ModelPainter::AppendPick(DrawCommand* begin, DrawCommand* end) {
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

DrawCommand* ModelPainter::GetBegin() const {
	return begin;
}

DrawCommand* ModelPainter::GetEnd() const {
	return end;
}

void ModelPainter::Dump() {
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

void ModelPainter::Link() {
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

void ModelPainter::Clear() {
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


NAMESPACE_TOPSIDE_END

#endif
