#include "Local.h"


NAMESPACE_TOPSIDE_BEGIN


GeomInteraction2D::GeomInteraction2D() {
	ignore_mouse = false;
	hidden = false;
	pending_redraw = true;
	pending_layout = true;
	pending_fx_redraw = true;
	
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

GeomInteraction2D* GeomInteraction2D::At(int i) {
	return CastPtr<GeomInteraction2D>(sub[i]);
}

bool GeomInteraction2D::MouseMoveInFrame(Point pt, dword keyflags) {
	if (IsCaptured()) {
		//GeomInteraction* cap = CastPtr<GeomInteraction2D>(GetCaptured());
		//ASSERT(this == cap);
		Point cpt = GetContentPoint(pt);
		MouseMove(cpt, keyflags);
		return true;
	}
	else {
		
		if (frame_r.Contains(pt)) {
			has_mouse_deep = true;
			
			Rect content_r = GetContentRect();
			Point ftl = frame_r.TopLeft();
			Point fpt = pt - ftl;
			Point ctl = content_r.TopLeft();
			Point cpt = fpt - ctl;
			
			if (content_r.Contains(fpt)) {
				bool found = false;
				for(int i = sub.GetCount()-1; i >= 0; i--) {
					GeomInteraction* c = sub[i];
					GeomInteraction2D* c2 = c->Get2D();
					if (found) {
						if (c->has_mouse_deep) {
							c->DeepMouseLeave();
							break;
						}
					}
					else if (c2 && c2->DeepMouseMove(cpt, keyflags)) {
						found = true;
					}
				}
				
				if (!found) {
					if (!has_mouse) {
						if (GetCaptured()) {ASSERT(GetCaptured() == this);}
						
						GeomInteraction* with_mouse = GetWithMouse();
						if (with_mouse) {
							with_mouse->has_mouse = false;
							with_mouse->MouseLeave();
						}
						has_mouse = true;
						
						SetWithMouse(this);
						
						MouseEnter(fpt, keyflags);
					}
					MouseMove(cpt, keyflags);
				}
			}
			else {
				MouseMoveInFrameContent(pt, keyflags);
			}
			
			return true;
		}
		else if (has_mouse_deep) {
			DeepMouseLeave();
		}
		else {
			ASSERT(!has_mouse);
		}
	}
	return false;
}

void GeomInteraction2D::DeepMouseMoveInFrameContent(Point pt, dword keyflags) {
	
}

void GeomInteraction2D::MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags) {
	
}

bool GeomInteraction2D::MouseWheelInFrameContent(Point p, int zdelta, dword keyflags) {
	return false;
}

bool GeomInteraction2D::DeepMouseMoveInFrame(Point pt, dword keyflags) {
	Rect content_r = GetContentRect();
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	
	DeepMouseMoveInFrameContent(pt, keyflags);
	
	for(int i = sub.GetCount()-1; i >= 0; i--) {
		GeomInteraction2D* c = sub[i]->Get2D();
		if (!c) continue;
		
		if (c->has_mouse_deep) {
			Point p0(	pt.x - frame_r.left,
						pt.y - frame_r.top);
			if (c->DeepMouseMove(cpt, keyflags))
				return true;
		}
	}
	return false;
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
	
	GeomInteraction* captured = GetCaptured();
	if (captured) {
		GeomInteraction2D* cap2 = CastPtr<GeomInteraction2D>(captured);
		if (cap2) {
			#if 0
			// This is probably not correct, because "has_mouse" must be updated
			ASSERT(cap2->IsCaptured());
			Point cpt = GetFramePointBetween(this, cap2, pt);
			return cap2->MouseMoveInFrame(cpt, keyflags);
			#else
			if (has_mouse) {
				return MouseMoveInFrame(pt, keyflags);
			}
			else if (has_mouse_deep) {
				return DeepMouseMoveInFrame(pt, keyflags);
			}
			#endif
		}
		else {
			TODO // what is this problem?
		}
		
		return false;
	}
	else {
		return MouseMoveInFrame(pt, keyflags);
	}
	return false;
}

Rect GeomInteraction2D::GetContentRect() const {
	return frame_r.GetSize();
}

Point GeomInteraction2D::GetContentPoint(const Point& pt) {
	Point ctl = frame_r.TopLeft();
	return pt - ctl;
}

bool GeomInteraction2D::DeepMouseDispatch(int mouse_code, const Point& cpt, dword keyflags) {
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

bool GeomInteraction2D::DeepMouse(int mouse_code, const Point& pt, dword keyflags) {
	if (GetCaptured()) {
		#if 1
		GeomInteraction2D* c2 = GetCaptured()->Get2D();
		if (!c2)
			return false;
		Point cpt = GetFramePointBetween(*this, *c2, pt);
		return c2->DeepMouseDispatch(mouse_code, cpt, keyflags);
		#else
		
		// THIS ALL IS INCORRECT!!!!! DON'T USE!!!!
		
		// ...it won't ever seek towards captured
		
		// It's not the one "with mouse" if (has_mouse) {
		if (IsCaptured()) {
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
		#endif
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
	if (frame_r.Contains(pt)) {
		Rect content_r = GetContentRect();
		Point ftl = frame_r.TopLeft();
		Point ctl = content_r.TopLeft();
		Point fpt = pt - ftl;
		Point cpt = fpt - ctl;
		
		if (content_r.Contains(fpt)) {
			for(int i = sub.GetCount()-1; i >= 0; i--) {
				GeomInteraction2D* c = sub[i]->Get2D();
				if (c->DeepMouseWheel(cpt, zdelta, keyflags))
					return true;
			}
			MouseWheel(cpt, zdelta, keyflags);
		}
		else {
			MouseWheelInFrameContent(pt, zdelta, keyflags);
		}
		return true;
	}
	return false;
}

void GeomInteraction2D::SetFrameBox(const Rect& r) {
	#if 0
	GeomInteraction* gi = GetOwner();
	if (gi) {
		GeomInteraction2D* gi2 = CastPtr<GeomInteraction2D>(gi);
		Rect parent_rect = gi2->GetRect();
		int parent_width = parent_rect.Width();
		ASSERT(r.right <= parent_width);
	}
	#endif
	this->frame_r = r;
	this->SetPendingLayout();
}

bool GeomInteraction2D::Redraw(bool only_pending) {
	GeomInteraction2D* content = this;
	//GeomInteraction2D* linked = CastPtr<GeomInteraction2D>(GetDynamicallyLinked());
	/*if (linked) {
		content = linked;
	}*/
	
	bool did_draw = false;
	bool was_pending_fx_redraw = pending_fx_redraw;
	bool frame = IsGeomDrawBegin();
	bool draw_begin = false;
	Size sz = GetFrameSize();
	
	if (!IsShown()) {
		ProgPainter fast_exit(sz, *cmd_begin.prev, cmd_begin, cmd_end, *cmd_end.next);
		fast_exit.Link();
		pending_fx_redraw = false;
		pending_redraw = false;
		return true;
	}
	
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
		
		content->PaintPreFrame(pre);
		content->Paint(pre);
		content->PaintDebug(pre);
		
		if (draw_begin && !pending_redraw)
			pre.CtrlDrawEnd();
		
		pre.Link();
	}
	
	
	for(int i = 0; i < content->sub.GetCount(); i++) {
		GeomInteraction* c = content->sub[i];
		ASSERT(c);
		did_draw = c->Redraw(only_pending) || did_draw;
	}
	
	
	if (pending_redraw) {
		ASSERT(cmd_post.prev);
		ASSERT(cmd_end.next);
		ProgPainter post(sz, *cmd_post.prev, cmd_post, cmd_end, *cmd_end.next);
		
		content->PaintPostFrame(post);
		post.WindowEnd();
		
		if (draw_begin) post.CtrlDrawEnd();
		
		post.Link();
		
		did_draw = true;
		pending_redraw = false;
	}
	
	//if (linked)
	//	did_draw = linked->Redraw(only_pending) || did_draw;
	
	return did_draw;
}

bool GeomInteraction2D::MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) {
	return false;
}

bool GeomInteraction2D::MouseEventInFrame(int mouse_code, const Point& pt, dword keyflags) {
	if (frame_r.Contains(pt)) {
		Rect content_r = GetContentRect();
		Point ftl = frame_r.TopLeft();
		Point ctl = content_r.TopLeft();
		Point fpt = pt - ftl;
		Point cpt = fpt - ctl;
		
		if (content_r.Contains(fpt)) {
			for(int i = sub.GetCount()-1; i >= 0; i--) {
				GeomInteraction2D* c = sub[i]->Get2D();
				if (c && c->DeepMouse(mouse_code, cpt, keyflags))
					return true;
			}
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
		}
		else {
			MouseEventInFrameContent(mouse_code, pt, keyflags);
		}
		return true;
	}
	return false;
}

void GeomInteraction2D::DeepLayout() {
	//GeomInteraction2D* linked = CastPtr<GeomInteraction2D>(GetDynamicallyLinked());
	Rect prev_frame_r = frame_r;
	
	DeepFrameLayout();
	
	Layout();
	pending_layout = false;
	
	if (!(prev_frame_r == frame_r)) {
		SetPendingEffectRedraw();
		if (!(prev_frame_r.GetSize() == this->frame_r.GetSize()))
			SetPendingRedraw();
	}
	
	Rect r = GetContentRect();
	ASSERT(!r.IsEmpty());
	
	for(GeomInteraction* c : sub) {
		GeomInteraction2D* c2 = c->Get2D();
		if (!c2)
			continue;
		
		Rect cr = r;
	
		const LogPos& lp = c2->GetLogPos();
		if (lp.htype || lp.vtype) {
			switch (lp.htype) {
				case LogPos::NO_HORZ:	break;
				case LogPos::LEFT:		cr.left = r.left + lp.l;		cr.right = cr.left + lp.w;		break;
				case LogPos::RIGHT:		cr.right = r.right - lp.r;		cr.left = cr.right - lp.w;		break;
				case LogPos::HORZ:		cr.left = r.left + lp.l;		cr.right = r.right - lp.r;		break;
			}
			switch (lp.vtype) {
				case LogPos::NO_VERT:	break;
				case LogPos::TOP:		cr.top = r.top + lp.t;			cr.bottom = cr.top + lp.h;		break;
				case LogPos::BOTTOM:	cr.bottom = r.bottom - lp.b;	cr.top = cr.bottom - lp.h;		break;
				case LogPos::VERT:		cr.top = r.top + lp.t;			cr.bottom = r.bottom - lp.b;	break;
			}
			c2->SetFrameRect(cr);
		}
	}
	
	for(GeomInteraction* c : sub) {
		c->DeepLayout();
	}
	
	//if (linked)
	//	linked->DeepLayoutSub(r);
	
	PostLayout();
}

GeomInteraction2D& GeomInteraction2D::HSizePos(int l, int r) {
	pos.htype = LogPos::HORZ;
	pos.l = l;
	pos.r = r;
	return *this;
}

GeomInteraction2D& GeomInteraction2D::VSizePos(int t, int b) {
	pos.vtype = LogPos::VERT;
	pos.t = t;
	pos.b = b;
	return *this;
}

GeomInteraction2D& GeomInteraction2D::BottomPos(int i, int size) {
	pos.vtype = LogPos::BOTTOM;
	pos.b = i;
	pos.h = size;
	return *this;
}

GeomInteraction2D& GeomInteraction2D::TopPos(int i, int size) {
	pos.vtype = LogPos::TOP;
	pos.t = i;
	pos.h = size;
	return *this;
}

GeomInteraction2D& GeomInteraction2D::LeftPos(int i, int size) {
	pos.htype = LogPos::LEFT;
	pos.l = i;
	pos.w = size;
	return *this;
}

GeomInteraction2D& GeomInteraction2D::RightPos(int i, int size) {
	pos.htype = LogPos::RIGHT;
	pos.r = i;
	pos.w = size;
	return *this;
}

bool GeomInteraction2D::Dispatch(const CtrlEvent& e) {
	if (GeomInteraction::Dispatch(e))
		return true;
	
	switch (e.type) {
		case EVENT_SHUTDOWN:
		case EVENT_WINDOW_RESIZE:
			break;
		
		case EVENT_MOUSEMOVE:
			DeepMouseMove(e.pt, e.value);
			return true;
		
		case EVENT_MOUSEWHEEL:
			DeepMouseWheel(e.pt, e.n, e.value);
			return true;
		
		case EVENT_MOUSE_EVENT:
			DeepMouse(e.n, e.pt, e.value);
			return true;
		
		default:
			TODO
			break;
	}
	
	return false;
}

GeomInteraction2D* GeomInteraction2D::GetAbsoluteDrawBegin() {
	GeomInteraction* proxy = FindProxy();
	if (proxy)
		return CastPtr<GeomInteraction2D>(proxy);
	return 0;
}

void GeomInteraction2D::Refresh() {
	GeomInteraction::Refresh();
	
	GeomInteraction2D* proxy = GetAbsoluteDrawBegin();
	if (proxy) {
		AbsoluteInterface* aiface = CastPtr<AbsoluteInterface>(proxy);
		if (aiface)
			aiface->SetPendingPartialRedraw();
	}
}

Point GeomInteraction2D::GetFramePointBetween(GeomInteraction2D& top_owner, GeomInteraction2D& deep_sub, const Point& pt) {
	Point tl_sum(0,0);
	
	// The "deep_sub" node is not counted in, so we consider it's owner only
	GeomInteraction* ds_owner = deep_sub.GetOwner();
	ASSERT(ds_owner); if (!ds_owner) return Point(0,0);
	
	GeomInteraction2D* iter = ds_owner->Get2D();
	ASSERT(iter); if (!iter) return Point(0,0);
	
	while (iter) {
		if (iter == &top_owner) {
			Point diff = pt - tl_sum;
			return diff;
		}
		Rect frame = iter->GetFrameBox();
		Point frame_tl = frame.TopLeft();
		tl_sum += frame_tl;
		GeomInteraction* o = iter->GetOwner();
		iter = o ? o->Get2D() : 0;
	}
	ASSERT_(0, "owner is not connected to given object");
	return Point(0,0);
}


NAMESPACE_TOPSIDE_END
