#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


GeomInteraction2D::GeomInteraction2D() {
	ignore_mouse = false;
	hidden = false;
	
	cmd_begin.next = &cmd_frame;
	cmd_frame.prev = &cmd_begin;
	cmd_frame.next = &cmd_pre;
	cmd_pre.prev = &cmd_frame;
	cmd_pre.next = &cmd_post;
	cmd_post.prev = &cmd_pre;
	cmd_post.next = &cmd_end;
	cmd_end.prev = &cmd_post;
}

bool GeomInteraction2D::Is2D() const {
	return true;
}

GeomInteraction2D* GeomInteraction2D::Get2D() {
	return this;
}

Image GeomInteraction2D::FrameMouseEvent(int event, Point p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

Image GeomInteraction2D::MouseEvent(int event, Point p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

void GeomInteraction2D::MouseEnter(Point frame_p, dword keyflags) {
	if (do_debug_draw)
		Refresh();
}

Image GeomInteraction2D::CursorImage(Point p, dword keyflags) {
	return DefaultImages::Arrow;
}

int GeomInteraction2D::GetCount() const {
	return sub.GetCount();
}

GeomInteraction2D* GeomInteraction2D::operator[](int i) {
	return CastPtr<GeomInteraction2D>(sub[i]);
}

bool GeomInteraction2D::MouseMoveInFrame(Point pt, dword keyflags) {
	MouseMove(pt, keyflags);
	return true;
}

void GeomInteraction2D::DeepMouseMoveInFrame(Point pt, dword keyflags) {
	for(int i = sub.GetCount()-1; i >= 0; i--) {
		GeomInteraction2D* c = sub[i]->Get2D();
		if (!c) continue;
		
		if (c->has_mouse_deep) {
			Point p0(	pt.x - frame_r.left,
						pt.y - frame_r.top);
			c->DeepMouseMove(p0, keyflags);
		}
	}
}

bool GeomInteraction2D::DeepMouseMove(const Point& pt, dword keyflags) {
	int deep_count = 0;
	for(int i = sub.GetCount()-1; i >= 0; i--) {
		GeomInteraction2D* c = sub[i]->Get2D();
		if (!c) continue;
		
		if (c->HasMouseDeep()) {
			if (deep_count)
				c->DeepMouseLeave();
			else
				deep_count++;
		}
	}
	ASSERT(deep_count <= 1);
	
	if (GetCaptured()) {
		if (has_mouse) {
			MouseMoveInFrame(pt, keyflags);
			return true;
		}
		else if (has_mouse_deep) {
			DeepMouseMoveInFrame(pt, keyflags);
			return true;
		}
		return false;
	}
	else {
		return MouseMoveInFrame(pt, keyflags);
	}
	return false;
}

Point GeomInteraction2D::GetContentPoint(const Point& pt) {
	Point ctl = frame_r.TopLeft();
	return pt - ctl;
}

bool GeomInteraction2D::DeepMouse(int mouse_code, const Point& pt, dword keyflags) {
	if (GetCaptured()) {
		if (has_mouse) {
			Point cpt = GetContentPoint(pt);
			
			switch (mouse_code) {
				case MOUSE_LEFTDOWN: LeftDown(cpt, keyflags); break;
				case MOUSE_LEFTDOUBLE: LeftDouble(cpt, keyflags); break;
				case MOUSE_LEFTTRIPLE: LeftTriple(cpt, keyflags); break;
				case MOUSE_LEFTDRAG: LeftDrag(cpt, keyflags); break;
				case MOUSE_LEFTHOLD: LeftHold(cpt, keyflags); break;
				case MOUSE_LEFTREPEAT: LeftRepeat(cpt, keyflags); break;
				case MOUSE_LEFTUP: LeftUp(cpt, keyflags); break;
				case MOUSE_RIGHTDOWN: RightDown(cpt, keyflags); break;
				case MOUSE_RIGHTDOUBLE: RightDouble(cpt, keyflags); break;
				case MOUSE_RIGHTTRIPLE: RightTriple(cpt, keyflags); break;
				case MOUSE_RIGHTDRAG: RightDrag(cpt, keyflags); break;
				case MOUSE_RIGHTHOLD: RightHold(cpt, keyflags); break;
				case MOUSE_RIGHTREPEAT: RightRepeat(cpt, keyflags); break;
				case MOUSE_RIGHTUP: RightUp(cpt, keyflags); break;
				case MOUSE_MIDDLEDOWN: MiddleDown(cpt, keyflags); break;
				case MOUSE_MIDDLEDOUBLE: MiddleDouble(cpt, keyflags); break;
				case MOUSE_MIDDLETRIPLE: MiddleTriple(cpt, keyflags); break;
				case MOUSE_MIDDLEDRAG: MiddleDrag(cpt, keyflags); break;
				case MOUSE_MIDDLEHOLD: MiddleHold(cpt, keyflags); break;
				case MOUSE_MIDDLEREPEAT: MiddleRepeat(cpt, keyflags); break;
				case MOUSE_MIDDLEUP: MiddleUp(cpt, keyflags); break;
			}
			return true;
		}
		else if (has_mouse_deep) {
			if (MouseEventInFrameCaptured(mouse_code, pt, keyflags))
				return true;
			
			Point cpt = GetContentPoint(pt);
			for(int i = sub.GetCount()-1; i >= 0; i--) {
				GeomInteraction2D* c = sub[i]->Get2D();
				if (c->has_mouse_deep)
					c->DeepMouse(mouse_code, cpt, keyflags);
			}
			return true;
		}
		return false;
	}
	else {
		return MouseEventInFrame(mouse_code, pt, keyflags);
	}
}

bool GeomInteraction2D::DeepMouseWheel(const Point& pt, int zdelta, dword keyflags) {
	if (GetCaptured()) {
		if (has_mouse) {
			ASSERT(this == GetCaptured());
			Point cpt = GetContentPoint(pt);
			MouseWheel(cpt, zdelta, keyflags);
			return true;
		}
		else if (has_mouse_deep) {
			Point cpt = GetContentPoint(pt);
			for(int i = sub.GetCount()-1; i >= 0; i--) {
				GeomInteraction2D* c = sub[i]->Get2D();
				if (c->has_mouse_deep)
					c->DeepMouseWheel(cpt, zdelta, keyflags);
			}
			
			return true;
		}
		return false;
	}
	else {
		MouseWheelInFrame(pt, zdelta, keyflags);
		return true;
	}
}

bool GeomInteraction2D::MouseWheelInFrame(Point pt, int zdelta, dword keyflags) {
	Point cpt = GetContentPoint(pt);
	if (!frame_r.Contains(cpt))
		return false;
	for(int i = sub.GetCount()-1; i >= 0; i--) {
		GeomInteraction2D* c = sub[i]->Get2D();
		if (c && c->DeepMouseWheel(cpt, zdelta, keyflags))
			return true;
	}
	MouseWheel(cpt, zdelta, keyflags);
	return true;
}


bool GeomInteraction2D::Redraw(bool only_pending) {
	bool did_draw = false;
	bool was_pending_fx_redraw = pending_fx_redraw;
	bool frame = IsGeomDrawBegin();
	bool draw_begin = false;
	Size sz = GetFrameSize();
	
	if (pending_fx_redraw) {
		ASSERT(cmd_begin.prev);
		ASSERT(cmd_frame.next);
		ProgPainter fx(sz, *cmd_begin.prev, cmd_begin, cmd_frame, *cmd_frame.next);
		
		if (frame) {
			fx.CtrlDrawBegin((hash_t)this);
			draw_begin = true;
		}
		
		fx.WindowOffset(frame_r);
		
		fx.Link();
		
		pending_fx_redraw = false;
		did_draw = true;
	}
	
	
	
	
	if (pending_redraw) {
		ASSERT(cmd_frame.prev);
		ASSERT(cmd_pre.next);
		ProgPainter pre(sz, *cmd_frame.prev, cmd_frame, cmd_pre, *cmd_pre.next);
		
		bool frame = IsGeomDrawBegin();
		if (frame && !draw_begin) {
			pre.CtrlDrawBegin((hash_t)this);
			draw_begin = true;
		}
		
		PaintPreFrame(pre);
		Paint(pre);
		PaintDebug(pre);
		
		if (draw_begin && !pending_redraw)
			pre.CtrlDrawEnd();
		
		pre.Link();
	}
	
	
	for(int i = 0; i < sub.GetCount(); i++) {
		GeomInteraction* c = sub[i];
		ASSERT(c);
		did_draw = c->Redraw(only_pending) || did_draw;
	}
	
	
	if (pending_redraw) {
		ASSERT(cmd_post.prev);
		ASSERT(cmd_end.next);
		ProgPainter post(sz, *cmd_post.prev, cmd_post, cmd_end, *cmd_end.next);
		
		PaintPostFrame(post);
		post.WindowEnd();
		
		if (draw_begin) post.CtrlDrawEnd();
		
		post.Link();
		
		did_draw = true;
		pending_redraw = false;
	}
	
	return did_draw;
}

NAMESPACE_TOPSIDE_END
