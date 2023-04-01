#include "GuboCore.h"


NAMESPACE_TOPSIDE_BEGIN


GeomInteraction3D::GeomInteraction3D() {
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

bool GeomInteraction3D::Is3D() const {
	return true;
}

GeomInteraction3D* GeomInteraction3D::Get3D() {
	return this;
}

void GeomInteraction3D::Add(GeomInteraction& c) {
	if (c.Is3D()) {
		GeomInteraction3D& c2 = *c.Get3D();
		cmd_post.prev = &c2.cmd_end;
		c2.cmd_end.next = &cmd_post;
		if (sub.GetCount()) {
			GeomInteraction3D* top = sub.Top()->Get3D();
			ASSERT(top);
			if (top) {
				c2.cmd_begin.prev = &top->cmd_end;
				top->cmd_end.next = &c2.cmd_begin;
			}
		}
		else {
			c2.cmd_begin.prev = &cmd_pre;
			cmd_pre.next = &c2.cmd_begin;
		}
	}
	
	GeomInteraction::Add(c);
}

bool GeomInteraction3D::RemoveSub(GeomInteraction* c) {
	if (GeomInteraction::RemoveSub(c)) {
		GeomInteraction3D* c0 = c->Get3D();
		if (c0) {
			c0->cmd_end.next->prev = c0->cmd_begin.prev;
			c0->cmd_begin.prev->next = c0->cmd_end.next;
			c0->cmd_end.next = NULL;
			c0->cmd_begin.prev = NULL;
		}
		return true;
	}
	return false;
}

void GeomInteraction3D::Paint(Draw3& d) {
	// pass
	//LOG(GetDynamicName());
}

bool GeomInteraction3D::Redraw(bool only_pending) {
	GeomInteraction3D* content = this;
	//GeomInteraction3D* linked = CastPtr<GeomInteraction3D>(GetDynamicallyLinked());
	/*if (linked) {
		content = linked;
	}*/
	
	bool did_draw = false;
	//bool was_pending_fx_redraw = pending_fx_redraw;
	bool frame = IsGeomDrawBegin();
	bool draw_begin = false;
	Volf sz = GetFrameSize();
	
	if (!IsShown()) {
		ProgPainter3 fast_exit(this, sz, *cmd_begin.prev, cmd_begin, cmd_end, *cmd_end.next);
		fast_exit.Link();
		pending_fx_redraw = false;
		pending_redraw = false;
		return true;
	}
	
	if (pending_fx_redraw) {
		ASSERT(cmd_begin.prev);
		ASSERT(cmd_frame.next);
		ProgPainter3 fx(this, sz, *cmd_begin.prev, cmd_begin, cmd_frame, *cmd_frame.next);
		
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
		ProgPainter3 pre(this, sz, *cmd_frame.prev, cmd_frame, cmd_pre, *cmd_pre.next);
		
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
		ProgPainter3 post(this, sz, *cmd_post.prev, cmd_post, cmd_end, *cmd_end.next);
		
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

GeomInteraction3D* GeomInteraction3D::At(int i) {
	return CastPtr<GeomInteraction3D>(sub[i]);
}

Image GeomInteraction3D::FrameMouseEvent(int event, Point3f p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

Image GeomInteraction3D::MouseEvent(int event, Point3f p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

bool GeomInteraction3D::DeepMouseDispatch(int mouse_code, const Point3f& cpt, dword keyflags) {
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

bool GeomInteraction3D::DeepMouse(int mouse_code, const Point3f& pt, dword keyflags) {
	if (GetCaptured()) {
		GeomInteraction3D* c2 = GetCaptured()->Get3D();
		if (!c2)
			return false;
		Point3f cpt = GetFramePointBetween(*this, *c2, pt);
		return c2->DeepMouseDispatch(mouse_code, cpt, keyflags);
	}
	else {
		return MouseEventInFrame(mouse_code, pt, keyflags);
	}
}

bool GeomInteraction3D::DeepMouseWheel(const Point3f& pt, int zdelta, dword keyflags) {
	if (GetCaptured()) {
		if (has_mouse) {
			ASSERT(this == GetCaptured());
			Point3f cpt = GetContentPoint(pt);
			MouseWheel(cpt, zdelta, keyflags);
			return true;
		}
		else if (has_mouse_deep) {
			Point3f cpt = GetContentPoint(pt);
			for(int i = sub.GetCount()-1; i >= 0; i--) {
				GeomInteraction3D* c = sub[i]->Get3D();
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

bool GeomInteraction3D::MouseMoveInFrame(Point3f pt, dword keyflags) {
	if (IsCaptured()) {
		//GeomInteraction* cap = CastPtr<GeomInteraction3D>(GetCaptured());
		//ASSERT(this == cap);
		Point3f cpt = GetContentPoint(pt);
		MouseMove(cpt, keyflags);
		return true;
	}
	else {
		
		if (frame_r.Contains(pt)) {
			has_mouse_deep = true;
			
			Cubf content_r = GetContentBox();
			Point3f ftl = frame_r.TopLeftNear();
			Point3f fpt = pt - ftl;
			Point3f ctl = content_r.TopLeftNear();
			Point3f cpt = fpt - ctl;
			
			if (content_r.Contains(fpt)) {
				bool found = false;
				for(int i = sub.GetCount()-1; i >= 0; i--) {
					GeomInteraction* c = sub[i];
					GeomInteraction3D* c2 = c->Get3D();
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

void GeomInteraction3D::DeepMouseMoveInFrameContent(Point3f pt, dword keyflags) {
	
}

void GeomInteraction3D::MouseEventInFrameContent(int mouse_code, const Point3f& pt, dword keyflags) {
	
}

bool GeomInteraction3D::MouseEventInFrameCaptured(int mouse_code, const Point3f& pt, dword keyflags) {
	return false;
}

bool GeomInteraction3D::MouseWheelInFrameContent(Point3f p, int zdelta, dword keyflags) {
	return false;
}

bool GeomInteraction3D::DeepMouseMoveInFrame(Point3f pt, dword keyflags) {
	Cubf content_r = GetContentBox();
	Point3f ftl = frame_r.TopLeftNear();
	Point3f ctl = content_r.TopLeftNear();
	Point3f fpt = pt - ftl;
	Point3f cpt = fpt - ctl;
	
	DeepMouseMoveInFrameContent(pt, keyflags);
	
	for(int i = sub.GetCount()-1; i >= 0; i--) {
		GeomInteraction3D* c = sub[i]->Get3D();
		if (!c) continue;
		
		if (c->has_mouse_deep) {
			Point3f p0(	pt.x - frame_r.left,
						pt.y - frame_r.top,
						pt.z - frame_r.near);
			if (c->DeepMouseMove(cpt, keyflags))
				return true;
		}
	}
	return false;
}

bool GeomInteraction3D::DeepMouseMove(const Point3f& pt, dword keyflags) {
	int deep_count = 0;
	for(int i = sub.GetCount()-1; i >= 0; i--) {
		GeomInteraction3D* c = sub[i]->Get3D();
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
		GeomInteraction3D* cap2 = CastPtr<GeomInteraction3D>(captured);
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

Cubf GeomInteraction3D::GetContentBox() const {
	return frame_r.GetSize();
}

Point3f GeomInteraction3D::GetContentPoint(const Point3f& pt) {
	Point3f ctl = frame_r.TopLeftNear();
	return pt - ctl;
}

bool GeomInteraction3D::MouseEventInFrame(int mouse_code, const Point3f& pt, dword keyflags) {
	if (frame_r.Contains(pt)) {
		Cubf content_r = GetContentBox();
		Point3f ftl = frame_r.TopLeftNear();
		Point3f ctl = content_r.TopLeftNear();
		Point3f fpt = pt - ftl;
		Point3f cpt = fpt - ctl;
		
		if (content_r.Contains(fpt)) {
			for(int i = sub.GetCount()-1; i >= 0; i--) {
				GeomInteraction3D* c = sub[i]->Get3D();
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

bool GeomInteraction3D::MouseWheelInFrame(Point3f pt, int zdelta, dword keyflags) {
	if (frame_r.Contains(pt)) {
		Cubf content_r = GetContentBox();
		Point3f ftl = frame_r.TopLeftNear();
		Point3f ctl = content_r.TopLeftNear();
		Point3f fpt = pt - ftl;
		Point3f cpt = fpt - ctl;
		
		if (content_r.Contains(fpt)) {
			for(int i = sub.GetCount()-1; i >= 0; i--) {
				GeomInteraction3D* c = sub[i]->Get3D();
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

void GeomInteraction3D::SetFrameBox(const Cubf& c) {
	this->frame_r = c;
	this->SetPendingLayout();
}

void GeomInteraction3D::MouseEnter(Point3f frame_p, dword keyflags) {
	if (do_debug_draw)
		Refresh();
}

Image GeomInteraction3D::CursorImage(Point3f p, dword keyflags) {
	return DefaultImages::Arrow;
}

bool GeomInteraction3D::Dispatch(const CtrlEvent& e) {
	if (GeomInteraction::Dispatch(e))
		return true;
	
	Point3f pt(e.pt3[0], e.pt3[1], e.pt3[2]);
	
	switch (e.type) {
		case EVENT_SHUTDOWN:
		case EVENT_WINDOW_RESIZE:
			break;
		
		case EVENT_MOUSEMOVE:
			DeepMouseMove(pt, e.value);
			return true;
		
		case EVENT_MOUSEWHEEL:
			DeepMouseWheel(pt, e.n, e.value);
			return true;
		
		case EVENT_MOUSE_EVENT:
			DeepMouse(e.n, pt, e.value);
			return true;
		
		default:
			TODO
			break;
	}
	
	return false;
}

void GeomInteraction3D::Refresh() {
	GeomInteraction::Refresh();
	
	GeomInteraction3D* proxy = GetAbsoluteDrawBegin();
	if (proxy) {
		TopGubo* tw = CastPtr<TopGubo>(proxy);
		if (tw)
			tw->SetPendingPartialRedraw();
	}
}

GeomInteraction3D* GeomInteraction3D::GetAbsoluteDrawBegin() {
	GeomInteraction* proxy = FindProxy();
	if (proxy)
		return CastPtr<GeomInteraction3D>(proxy);
	return 0;
}

GeomInteraction3D& GeomInteraction3D::HSizePos(int l, int r) {
	pos.htype = LogPos::HORZ;
	pos.l = l;
	pos.r = r;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::VSizePos(int t, int b) {
	pos.vtype = LogPos::VERT;
	pos.t = t;
	pos.b = b;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::BottomPos(int i, int size) {
	pos.vtype = LogPos::BOTTOM;
	pos.b = i;
	pos.h = size;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::TopPos(int i, int size) {
	pos.vtype = LogPos::TOP;
	pos.t = i;
	pos.h = size;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::LeftPos(int i, int size) {
	pos.htype = LogPos::LEFT;
	pos.l = i;
	pos.w = size;
	return *this;
}

GeomInteraction3D& GeomInteraction3D::RightPos(int i, int size) {
	pos.htype = LogPos::RIGHT;
	pos.r = i;
	pos.w = size;
	return *this;
}

String GeomInteraction3D::GetDrawCommandString() const {
	const DrawCommand3* it = &cmd_begin;
	int i = 0;
	String s;
	while (it) {
		s << i++ << ": " << it->ToString() << "\n";
		it = it->next;
	}
	return s;
}

void GeomInteraction3D::DumpDrawCommands() const {
	LOG(GetDrawCommandString());
}

void GeomInteraction3D::DeepLayout() {
	//GeomInteraction3D* linked = CastPtr<GeomInteraction3D>(GetDynamicallyLinked());
	Cubf prev_frame_r = frame_r;
	
	DeepFrameLayout();
	
	Layout();
	pending_layout = false;
	
	if (!(prev_frame_r == frame_r)) {
		SetPendingEffectRedraw();
		if (!(prev_frame_r.GetSize() == this->frame_r.GetSize()))
			SetPendingRedraw();
	}
	
	Cubf r = GetContentBox();
	ASSERT(!r.IsEmpty());
	
	for(GeomInteraction* c : sub) {
		GeomInteraction3D* c2 = c->Get3D();
		if (!c2)
			continue;
		
		Cubf cr = r;
	
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
			c2->SetFrameBox(cr);
		}
	}
	
	for(GeomInteraction* c : sub) {
		c->DeepLayout();
	}
	
	//if (linked)
	//	linked->DeepLayoutSub(r);
	
	PostLayout();
}

Point3f GeomInteraction3D::GetFramePointBetween(GeomInteraction3D& top_owner, GeomInteraction3D& deep_sub, const Point3f& pt) {
	Point3f tl_sum(0,0,0);
	
	// The "deep_sub" node is not counted in, so we consider it's owner only
	GeomInteraction* ds_owner = deep_sub.GetOwner();
	ASSERT(ds_owner); if (!ds_owner) return Point3f(0,0,0);
	
	GeomInteraction3D* iter = ds_owner->Get3D();
	ASSERT(iter); if (!iter) return Point3f(0,0,0);
	
	while (iter) {
		if (iter == &top_owner) {
			Point3f diff = pt - tl_sum;
			return diff;
		}
		Cubf frame = iter->GetFrameBox();
		Point3f frame_tl = frame.TopLeftNear();
		tl_sum += frame_tl;
		GeomInteraction* o = iter->GetOwner();
		iter = o ? o->Get3D() : 0;
	}
	ASSERT_(0, "owner is not connected to given object");
	return Point3f(0,0,0);
}



NAMESPACE_TOPSIDE_END
