#include "Draw.h"


NAMESPACE_UPP

DrawCommand& DrawCommandCache::Get() {
	TODO
}

void DrawCommandCache::Return(DrawCommand* cmd) {
	TODO
}





DrawCommand& SDraw::GetNext() {
	DrawCommand* cmd = &cache->Get();
	cmd->prev = cur;
	if (cur)
		cur->next = cmd;
	cur = cmd;
	if (!cur_begin)
		cur_begin = cur;
	return *cur;
}

void SDraw::DrawLine(int x0, int y0, int x1, int y1, int line_width, RGBA c) {
	if (line_width <= 0) return;
	
	if (line_width == 1) {
		DrawCommand& cmd = GetNext();
		cmd.type = DRAW_LINE;
		cmd.i[0] = x0;
		cmd.i[1] = y0;
		cmd.i[2] = x1;
		cmd.i[3] = y1;
		cmd.clr = c;
	}
	else {
		Pointf a(x0, y0), b(x1, y1);
		Pointf off = GetOffsets(a, b, line_width);
		Pointf p0a(a.x - off.x, a.y - off.y);
		Pointf p1a(b.x - off.x, b.y - off.y);
		Pointf p0b(a.x + off.x, a.y + off.y);
        Pointf p1b(b.x + off.x, b.y + off.y);
        
		DrawCommand& cmd = GetNext();
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
}

void SDraw::DrawImage(int x, int y, Image img, Byte alpha) {
	DrawCommand& cmd = GetNext();
	cmd.type = DRAW_IMAGE;
	cmd.i[0] = x;
	cmd.i[1] = y;
	cmd.img = img;
	cmd.img.MakeSysAccel();
	cmd.clr.a = (byte)(alpha / 255.0);
}

void SDraw::DrawRect(Rect r, RGBA clr) {
	DrawRect(r.left, r.top, r.Width(), r.Height(), clr);
}

void SDraw::DrawRect(int x, int y, int w, int h, RGBA clr) {
	DrawCommand& cmd = GetNext();
	cmd.type = DRAW_RECT;
	cmd.i[0] = x;
	cmd.i[1] = y;
	cmd.i[2] = x+w;
	cmd.i[3] = y+h;
	cmd.clr = clr;
}

void SDraw::DrawText(int x, int y, String txt, Font fnt, RGBA clr) {
	if (txt.GetCount() == 0 || fnt.IsEmpty())
		return;
	
	SysColor c;
	c.r = (byte)(clr.r * 255.0);
	c.g = (byte)(clr.g * 255.0);
	c.b = (byte)(clr.b * 255.0);
	c.a = 255;
	RawSysImage* surf = fnt.GetSysFont()->RenderTextBlended(txt.Begin(), c);
	if (!surf) {
		#ifdef flagSDL2
		DLOG("Couldn't render text: " << SDL_GetError());
		#else
		DLOG("Couldn't render text");
		#endif
		return;
	}
	
	DrawCommand& cmd = GetNext();
	cmd.type = DRAW_IMAGE;
	cmd.i[0] = x;
	cmd.i[1] = y;
	cmd.img = Image(surf);
	cmd.img.MakeSysAccel();
	cmd.clr.a = clr.a;
}

void SDraw::DrawPolyline(const Vector<Pointf>& pts, int line_width, RGBA c) {
	ASSERT(pts.GetCount() >= 3);
	DrawCommand& cmd = GetNext();
	cmd.clr = c;
	
	if (line_width == 1) {
		cmd.type = DRAW_POLYLINE;
		cmd.i[0] = line_width;
		cmd.pts <<= pts;
	}
	else {
		
		tmp0.SetCount(pts.GetCount()-1);
		tmp1.SetCount(0);
		angles.SetCount(pts.GetCount()-1);
		const Pointf* a = NULL;
		const Pointf* b = &pts[0];
		for(int i = 0; i < pts.GetCount()-1; i++) {
			a = b;
			b = &pts[i+1];
			tmp0[i] = GetOffsets(*a, *b, line_width);
			
			double dx = b->x - a->x;
			double dy = b->y - a->y;
			double theta = atan(dy / dx) * 360 / (2*M_PI);
			if (dx < 0)
				theta *= -1;
			angles[i] = theta;
		}
		a = NULL;
		b = &pts[0];
		const Pointf* c = &pts[1];
		double a0, a1 = angles[0];
		Pointf* o0, *o1 = &tmp0[0];
		
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
			Pointf b0l	(b->x - o0->x, b->y - o0->y);
			Pointf b1l	(b->x - o1->x, b->y - o1->y);
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
		
		TODO
		
		#if 0
		cmd.type = DRAW_TRIANGLES;
		Triangulate::Process(tmp1, cmd.triangles);
		#endif
		
		//cmd.type = DRAW_POLYLINE;
		//cmd.pts <<= tmp1;
	}
}

void SDraw::DrawPolygon(const Vector<Pointf>& pts, RGBA c) {
	DrawCommand& cmd = GetNext();
	cmd.type = DRAW_TRIANGLES;
	cmd.clr = c;
	
	TODO //Triangulate::Process(pts, cmd.triangles);
}

void SDraw::Offset(const Rect& r) {
	DrawCommand& cmd = GetNext();
	cmd.type = DRAW_OFFSET;
	cmd.i[0] = r.left;
	cmd.i[1] = r.top;
	cmd.i[2] = r.right;
	cmd.i[3] = r.bottom;
}

void SDraw::End() {
	DrawCommand& cmd = GetNext();
	cmd.type = DRAW_END;
}

void SDraw::Link() {
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
				cache->Return(free);
			free = free->next;
		}
	}
}


END_UPP_NAMESPACE
