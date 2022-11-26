#include "CtrlCore.h"
#include <EcsLib/EcsLib.h>

NAMESPACE_UPP


void CtrlFrame::FramePaint(Draw& draw, const Rect& r) {}
void CtrlFrame::FrameAdd(Ctrl& ctrl) {}
void CtrlFrame::FrameRemove() {}
int CtrlFrame::OverPaint() const { return 0; }
void CtrlFrame::SetCapture() {
	if (!ctrl) return;
	SetCaptured(this);
	ctrl->SetCapture();
}

void CtrlFrame::ReleaseCapture() {
	if (!ctrl) return;
	SetCaptured(NULL);
	ctrl->ReleaseCapture();
}

CtrlFrame* CtrlFrame::GetCaptured() {
	TODO
	/*
	if (!ctrl) return NULL;
	return ctrl->GetWindows()->GetFrameCaptured();*/
}

CtrlFrame* CtrlFrame::GetWithMouse() {
	TODO
	/*
	if (!ctrl) return NULL;
	return ctrl->GetWindows()->GetFrameWithMouse();*/
}

void CtrlFrame::SetCaptured(CtrlFrame* c) {
	TODO
	/*
	ctrl->GetWindows()->SetFrameCaptured(c);*/
}

void CtrlFrame::SetWithMouse(CtrlFrame* c) {
	TODO
	/*
	ctrl->GetWindows()->SetFrameWithMouse(c);*/
}



int       Ctrl::LoopLevel;
Ctrl     *Ctrl::LoopCtrl;
int64     Ctrl::EventLoopNo;



Ctrl::Ctrl() {
	inloop = false;
	want_focus = false;
	has_focus = false;
	has_focus_deep = false;
	has_mouse = false;
	has_mouse_deep = false;
	pending_fx_redraw = true;
	pending_redraw = true;
	pending_layout = true;
	modify = false;
	
}

void Ctrl::Add(Ctrl& c) {
	GeomInteraction2D::Add(c);
}

void Ctrl::AddChild(Ctrl* c) {
	GeomInteraction2D::AddSub(c);
}

Ctrl* Ctrl::GetLastChild() {
	return CastPtr<Ctrl>(sub.Top());
}

void Ctrl::RemoveChild(Ctrl* c) {
	GeomInteraction2D::RemoveSub(c);
}

Ctrl* Ctrl::GetParent() {
	return CastPtr<Ctrl>(owner);
}

Ctrl* Ctrl::GetTopCtrl() {
	Ctrl* c = this;
	while (c) {
		Ctrl* p = c->GetParent();
		if (p)
			c = p;
		else
			break;
	}
	return c;
}

Ctrl* Ctrl::GetIndexChild(int i) {
	return CastPtr<Ctrl>(sub[i]);
}

int Ctrl::GetChildCount() const {
	return sub.GetCount();
}

TopWindow* Ctrl::GetTopWindow() {
	Ctrl* c = this;
	while (c) {
		Ctrl* par = c->GetParent();
		if (!par) {
			TopWindow* tw = CastPtr<TopWindow>(c);
			return tw;
		}
		c = par;
	}
	return 0;
}

void Ctrl::SetRect(const Rect& r) {
	SetFrameRect(r);
	SetPendingRedrawDeep();
}

void Ctrl::SetFrameRect(const Rect& r) {
	this->frame_r = r;
	/*SetPendingEffectRedraw();
	if (parent) {
		parent->SetPendingLayout();
		CoreWindow* w = GetWindow();
		if (w)
			w->SetPendingLayout();
	}*/
}

void Ctrl::MouseLeaveFrame() {
	CtrlFrame* frame_with_mouse = GetFrameWithMouse();
	if (frame_with_mouse) {
		frame_with_mouse->has_mouse = false;
		frame_with_mouse->MouseLeave();
		SetFrameWithMouse(NULL);
	}
}

void Ctrl::SetFocus() {
	Ctrl* tw = GetTopCtrl();
	if (tw) tw->DeepUnfocus();
	
	has_focus = true;
	has_focus_deep = true;
	GotFocus();
	
	Ctrl* c = GetParent();
	while (c) {
		c->has_focus_deep = true;
		c->ChildGotFocus();
		c = c->GetParent();
	}
}


void Ctrl::SetPendingRedrawDeep() {
	SetPendingEffectRedraw();
	SetPendingRedraw();
	int c = GetChildCount();
	for(int i = 0; i < c; i++) {
		GetIndexChild(i)->SetPendingRedrawDeep();
	}
}

void Ctrl::Refresh() {
	SetPendingRedrawDeep();
	
	AbsoluteWindow* aw = GetAbsoluteWindow()
	if (aw)
		aw->SetPendingPartialRedraw();
}

void Ctrl::PostCallback(Callback cb) {
	SetTimeCallback(1, cb, this);
}

void Ctrl::PostRefresh() {
	PostCallback(THISBACK(Refresh0));
}

void Ctrl::PostLayoutCallback() {
	PostCallback(THISBACK(Layout0));
}

void Ctrl::SetCapture() {
	//SDL_CaptureMouse(SDL_TRUE);
	SetCaptured(this);
}

void Ctrl::ReleaseCapture() {
	//SDL_CaptureMouse(SDL_FALSE);
	SetCaptured(NULL);
}

void Ctrl::DeepUnfocus() {
	if (has_focus) {
		has_focus = false;
		has_focus_deep = false;
		LostFocus();
	}
	else if (has_focus_deep) {
		has_focus_deep = false;
		ChildLostFocus();
		
		int c = GetChildCount();
		for(int i = 0; i < c; i++) {
			Ctrl* c = GetIndexChild(i);
			if (c->HasFocusDeep()) {
				c->DeepUnfocus();
				break;
			}
		}
	}
}

Ctrl& Ctrl::HSizePos(int l, int r) {
	pos.htype = LogPos::HORZ;
	pos.l = l;
	pos.r = r;
	return *this;
}

Ctrl& Ctrl::VSizePos(int t, int b) {
	pos.vtype = LogPos::VERT;
	pos.t = t;
	pos.b = b;
	return *this;
}

Ctrl& Ctrl::BottomPos(int i, int size) {
	pos.vtype = LogPos::BOTTOM;
	pos.b = i;
	pos.h = size;
	return *this;
}

Ctrl& Ctrl::TopPos(int i, int size) {
	pos.vtype = LogPos::TOP;
	pos.t = i;
	pos.h = size;
	return *this;
}

Ctrl& Ctrl::LeftPos(int i, int size) {
	pos.htype = LogPos::LEFT;
	pos.l = i;
	pos.w = size;
	return *this;
}

Ctrl& Ctrl::RightPos(int i, int size) {
	pos.htype = LogPos::RIGHT;
	pos.r = i;
	pos.w = size;
	return *this;
}



bool Ctrl::Redraw(bool only_pending) {
	Size sz(GetFrameSize());
	Rect new_content_r(sz);
	bool did_draw = false;
	
	bool was_pending_fx_redraw = pending_fx_redraw;
	bool frame = IsGeomDrawBegin();
	bool draw_begin = false;
	
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
		
		for(int i = 0; i < frames.GetCount(); i++) {
			CtrlFrame& f = *frames[i];
			f.FramePaint(pre, new_content_r);
			f.FrameLayout(new_content_r);
		}
		
		if (frames.GetCount())
			pre.Offset(new_content_r);
		
		Paint(pre);
		if (do_debug_draw) {
			if (has_mouse) {
				RGBA c{255, 0, 0, 125};
				pre.DrawRect(new_content_r.GetSize(), c);
			}
			else {
				RGBA c(RandomColor(64, 128));
				c.a = 127;
				pre.DrawRect(new_content_r.GetSize(), c);
			}
		}
		
		if (draw_begin && !pending_redraw)
			pre.CtrlDrawEnd();
		
		pre.Link();
		
		content_r = new_content_r;
	}
	
	
	for(int i = 0; i < children.GetCount(); i++) {
		Ctrl* c = children[i];
		ASSERT(c);
		did_draw = c->Redraw(only_pending) || did_draw;
	}
	
	
	if (pending_redraw) {
		ASSERT(cmd_post.prev);
		ASSERT(cmd_end.next);
		ProgPainter post(sz, *cmd_post.prev, cmd_post, cmd_end, *cmd_end.next);
		
		if (frames.GetCount())
			post.End();
		
		post.WindowEnd();
		
		if (draw_begin) post.CtrlDrawEnd();
		
		post.Link();
		
		did_draw = true;
		pending_redraw = false;
	}
	
	return did_draw;
}

Ctrl* Ctrl::GetCaptured() {
	return GetWindows()->GetCaptured();
}
Ctrl* Ctrl::GetWithMouse() {
	return GetWindows()->GetWithMouse();
}
void Ctrl::SetCaptured(Ctrl* c) {
	GetWindows()->SetCaptured(c);
}
void Ctrl::SetWithMouse(Ctrl* c) {
	GetWindows()->SetWithMouse(c);
}
CtrlFrame* Ctrl::GetFrameCaptured() {
	return GetWindows()->GetFrameCaptured();
}
CtrlFrame* Ctrl::GetFrameWithMouse() {
	return GetWindows()->GetFrameWithMouse();
}
void Ctrl::SetFrameCaptured(CtrlFrame* c) {
	GetWindows()->SetFrameCaptured(c);
}
void Ctrl::SetFrameWithMouse(CtrlFrame* c) {
	GetWindows()->SetFrameWithMouse(c);
}



void Ctrl::DeepLayout() {
	Rect prev_frame_r = frame_r;
	
	const LogPos& lp = GetLogPos();
	if ((lp.htype || lp.vtype) && parent) {
		Rect cr = frame_r;
		Rect r(parent->content_r.GetSize());
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
		SetFrameRect0(cr);
	}
	
	Size sz(frame_r.GetSize());
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		CtrlFrame& f = *frames[i];
		f.FrameLayout(new_content_r);
	}
	content_r = new_content_r;
	
	Layout();
	pending_layout = false;
	
	if (!(prev_frame_r == frame_r)) {
		SetPendingEffectRedraw();
		if (!(prev_frame_r.GetSize() == this->frame_r.GetSize()))
			SetPendingRedraw();
	}
	

	for(int i = 0; i < children.GetCount(); i++) {
		Ctrl& c = *children[i];
		c.DeepLayout();
	}
	
	
	PostLayout();
}

bool Ctrl::DeepKey(dword key, int count) {
	if (HasFocus()) {
		return Key(key, count);
	}
	else {
		for(int i = 0; i < children.GetCount(); i++) {
			Ctrl& c = *children[i];
			if (c.HasFocusDeep())
				return c.DeepKey(key, count);
		}
		return false;
	}
}

bool Ctrl::DeepMouseMove(const Point& pt, dword keyflags) {
	int deep_count = 0;
	for(int i = children.GetCount()-1; i >= 0; i--) {
		Ctrl* c = children[i];
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
			ASSERT(this == GetCaptured());
			Point ftl = frame_r.TopLeft();
			Point ctl = content_r.TopLeft();
			Point fpt = pt - ftl;
			Point cpt = fpt - ctl;
			
			MouseMove(cpt, keyflags);
			
			return true;
		}
		else if (has_mouse_deep) {
			Point ftl = frame_r.TopLeft();
			Point ctl = content_r.TopLeft();
			Point fpt = pt - ftl;
			Point cpt = fpt - ctl;
			
			if (GetFrameCaptured()) {
				Rect r(frame_r.GetSize());
				CtrlFrame* last_fitting = NULL;
				Rect fitting_rect;
				for(int i = 0; i < frames.GetCount(); i++) {
					CtrlFrame* f = frames[i];
					if (f == GetFrameCaptured()) {
						last_fitting = f;
						fitting_rect = r;
						break;
					}
					f->FrameLayout(r);
				}
				if (last_fitting) {
					CtrlFrame* f = last_fitting;
					Point fitting_pt = fpt - fitting_rect.TopLeft();
					f->MouseMove(fitting_pt, keyflags);
					return true;
				}
			}
			
			for(int i = children.GetCount()-1; i >= 0; i--) {
				Ctrl* c = children[i];
				if (c->has_mouse_deep)
					c->DeepMouseMove(cpt, keyflags);
			}
			return true;
		}
		return false;
	}
	else {
		#if 0
		{
			Point ftl = frame_r.TopLeft();
			Point fpt = pt - ftl;
			Point ctl = content_r.TopLeft();
			Point cpt = fpt - ctl;
			
			for(int i = children.GetCount()-1; i >= 0; i--) {
				Ctrl* c = children[i];
				if (CastPtr<Button>(c) && c->frame_r.Contains(cpt)) {
					LOG("");
				}
			}
		}
		#endif
		if (frame_r.Contains(pt)) {
			has_mouse_deep = true;
			
			Point ftl = frame_r.TopLeft();
			Point fpt = pt - ftl;
			Point ctl = content_r.TopLeft();
			Point cpt = fpt - ctl;
			
			if (content_r.Contains(fpt)) {
				bool found = false;
				for(int i = children.GetCount()-1; i >= 0; i--) {
					Ctrl* c = children[i];
					if (found) {
						if (c->has_mouse_deep) {
							c->DeepMouseLeave();
							break;
						}
					}
					else if (c->DeepMouseMove(cpt, keyflags)) {
						found = true;
					}
				}
				
				if (!found) {
					CtrlFrame* frame_with_mouse = GetFrameWithMouse();
					if (frame_with_mouse) {
						frame_with_mouse->has_mouse = false;
						frame_with_mouse->MouseLeave();
						SetFrameWithMouse(NULL);
					}
					
					if (!has_mouse) {
						if (GetCaptured()) {ASSERT(GetCaptured() == this);}
						
						Ctrl* with_mouse = GetWithMouse();
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
				Rect r(frame_r.GetSize());
				CtrlFrame* last_fitting = NULL;
				Rect fitting_rect;
				for(int i = 0; i < frames.GetCount(); i++) {
					CtrlFrame* f = frames[i];
					if (r.Contains(fpt)) {
						last_fitting = f;
						fitting_rect = r;
					}
					f->FrameLayout(r);
				}
				if (last_fitting) {
					Ctrl* with_mouse = GetWithMouse();
					if (with_mouse) {
						with_mouse->has_mouse = false;
						with_mouse->MouseLeave();
						SetWithMouse(NULL);
					}
					CtrlFrame* f = last_fitting;
					Point fitting_pt = fpt - fitting_rect.TopLeft();
					if (!f->has_mouse) {
						CtrlFrame* frame_with_mouse = GetFrameWithMouse();
						if (frame_with_mouse) {
							frame_with_mouse->has_mouse = false;
							frame_with_mouse->MouseLeave();
						}
						f->has_mouse = true;
						SetFrameWithMouse(f);
						
						f->MouseEnter(fitting_pt, keyflags);
					}
					f->MouseMove(fitting_pt, keyflags);
				}
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

bool Ctrl::DeepMouse(int mouse_code, const Point& pt, dword keyflags) {
	if (GetCaptured()) {
		if (has_mouse) {
			Point ftl = frame_r.TopLeft();
			Point ctl = content_r.TopLeft();
			Point fpt = pt - ftl;
			Point cpt = fpt - ctl;
			
			
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
			Point ftl = frame_r.TopLeft();
			Point ctl = content_r.TopLeft();
			Point fpt = pt - ftl;
			Point cpt = fpt - ctl;
			
			CtrlFrame* frame_captured = GetFrameCaptured();
			if (frame_captured) {
				Rect r(frame_r.GetSize());
				CtrlFrame* last_fitting = NULL;
				Rect fitting_rect;
				for(int i = 0; i < frames.GetCount(); i++) {
					CtrlFrame* f = frames[i];
					if (f == frame_captured) {
						last_fitting = f;
						fitting_rect = r;
						break;
					}
					f->FrameLayout(r);
				}
				if (last_fitting) {
					CtrlFrame* f = last_fitting;
					Point fitting_pt = fpt - fitting_rect.TopLeft();
					switch (mouse_code) {
						case MOUSE_LEFTDOWN: f->LeftDown(fitting_pt, keyflags); break;
						case MOUSE_LEFTDOUBLE: f->LeftDouble(fitting_pt, keyflags); break;
						case MOUSE_LEFTTRIPLE: f->LeftTriple(fitting_pt, keyflags); break;
						case MOUSE_LEFTDRAG: f->LeftDrag(fitting_pt, keyflags); break;
						case MOUSE_LEFTHOLD: f->LeftHold(fitting_pt, keyflags); break;
						case MOUSE_LEFTREPEAT: f->LeftRepeat(fitting_pt, keyflags); break;
						case MOUSE_LEFTUP: f->LeftUp(fitting_pt, keyflags); break;
						case MOUSE_RIGHTDOWN: f->RightDown(fitting_pt, keyflags); break;
						case MOUSE_RIGHTDOUBLE: f->RightDouble(fitting_pt, keyflags); break;
						case MOUSE_RIGHTTRIPLE: f->RightTriple(fitting_pt, keyflags); break;
						case MOUSE_RIGHTDRAG: f->RightDrag(fitting_pt, keyflags); break;
						case MOUSE_RIGHTHOLD: f->RightHold(fitting_pt, keyflags); break;
						case MOUSE_RIGHTREPEAT: f->RightRepeat(fitting_pt, keyflags); break;
						case MOUSE_RIGHTUP: f->RightUp(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEDOWN: f->MiddleDown(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEDOUBLE: f->MiddleDouble(fitting_pt, keyflags); break;
						case MOUSE_MIDDLETRIPLE: f->MiddleTriple(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEDRAG: f->MiddleDrag(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEHOLD: f->MiddleHold(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEREPEAT: f->MiddleRepeat(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEUP: f->MiddleUp(fitting_pt, keyflags); break;
					}
					return true;
				}
			}
			
			for(int i = children.GetCount()-1; i >= 0; i--) {
				Ctrl* c = children[i];
				if (c->has_mouse_deep)
					c->DeepMouse(mouse_code, cpt, keyflags);
			}
			return true;
		}
		return false;
	}
	else {
		if (frame_r.Contains(pt)) {
			Point ftl = frame_r.TopLeft();
			Point ctl = content_r.TopLeft();
			Point fpt = pt - ftl;
			Point cpt = fpt - ctl;
			
			if (content_r.Contains(fpt)) {
				for(int i = children.GetCount()-1; i >= 0; i--) {
					Ctrl* c = children[i];
					if (c->DeepMouse(mouse_code, cpt, keyflags))
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
				Rect r(frame_r.GetSize());
				CtrlFrame* last_fitting = NULL;
				Rect fitting_rect;
				for(int i = 0; i < frames.GetCount(); i++) {
					CtrlFrame* f = frames[i];
					if (r.Contains(fpt)) {
						last_fitting = f;
						fitting_rect = r;
					}
					f->FrameLayout(r);
				}
				if (last_fitting) {
					Ctrl* with_mouse = GetWithMouse();
					if (with_mouse) {
						with_mouse->has_mouse = false;
						with_mouse->MouseLeave();
						with_mouse = NULL;
						SetWithMouse(NULL);
					}
					CtrlFrame* f = last_fitting;
					Point fitting_pt = fpt - fitting_rect.TopLeft();
					if (!f->has_mouse) {
						ASSERT(!with_mouse);
						f->has_mouse = true;
						SetFrameWithMouse(f);
						
						f->MouseEnter(fitting_pt, keyflags);
					}
					switch (mouse_code) {
						case MOUSE_LEFTDOWN: f->LeftDown(fitting_pt, keyflags); break;
						case MOUSE_LEFTDOUBLE: f->LeftDouble(fitting_pt, keyflags); break;
						case MOUSE_LEFTTRIPLE: f->LeftTriple(fitting_pt, keyflags); break;
						case MOUSE_LEFTDRAG: f->LeftDrag(fitting_pt, keyflags); break;
						case MOUSE_LEFTHOLD: f->LeftHold(fitting_pt, keyflags); break;
						case MOUSE_LEFTREPEAT: f->LeftRepeat(fitting_pt, keyflags); break;
						case MOUSE_LEFTUP: f->LeftUp(fitting_pt, keyflags); break;
						case MOUSE_RIGHTDOWN: f->RightDown(fitting_pt, keyflags); break;
						case MOUSE_RIGHTDOUBLE: f->RightDouble(fitting_pt, keyflags); break;
						case MOUSE_RIGHTTRIPLE: f->RightTriple(fitting_pt, keyflags); break;
						case MOUSE_RIGHTDRAG: f->RightDrag(fitting_pt, keyflags); break;
						case MOUSE_RIGHTHOLD: f->RightHold(fitting_pt, keyflags); break;
						case MOUSE_RIGHTREPEAT: f->RightRepeat(fitting_pt, keyflags); break;
						case MOUSE_RIGHTUP: f->RightUp(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEDOWN: f->MiddleDown(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEDOUBLE: f->MiddleDouble(fitting_pt, keyflags); break;
						case MOUSE_MIDDLETRIPLE: f->MiddleTriple(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEDRAG: f->MiddleDrag(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEHOLD: f->MiddleHold(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEREPEAT: f->MiddleRepeat(fitting_pt, keyflags); break;
						case MOUSE_MIDDLEUP: f->MiddleUp(fitting_pt, keyflags); break;
					}
				}
			}
			
			return true;
		}
		return false;
	}
}

bool Ctrl::DeepMouseWheel(const Point& pt, int zdelta, dword keyflags) {
	if (GetCaptured()) {
		if (has_mouse) {
			ASSERT(this == GetCaptured());
			Point ftl = frame_r.TopLeft();
			Point ctl = content_r.TopLeft();
			Point cpt = pt - ftl - ctl;
			
			MouseWheel(cpt, zdelta, keyflags);
			return true;
		}
		else if (has_mouse_deep) {
			Point ftl = frame_r.TopLeft();
			Point ctl = content_r.TopLeft();
			Point cpt = pt - ftl - ctl;
			
			for(int i = children.GetCount()-1; i >= 0; i--) {
				Ctrl* c = children[i];
				if (c->has_mouse_deep)
					c->DeepMouseWheel(cpt, zdelta, keyflags);
			}
			
			return true;
		}
		return false;
	}
	else {
		if (frame_r.Contains(pt)) {
			Point ftl = frame_r.TopLeft();
			Point ctl = content_r.TopLeft();
			Point fpt = pt - ftl;
			Point cpt = fpt - ctl;
			
			if (content_r.Contains(fpt)) {
				for(int i = children.GetCount()-1; i >= 0; i--) {
					Ctrl* c = children[i];
					if (c->DeepMouseWheel(cpt, zdelta, keyflags))
						return true;
				}
				MouseWheel(cpt, zdelta, keyflags);
			}
			else {
				Rect r(frame_r.GetSize());
				CtrlFrame* last_fitting = NULL;
				Rect fitting_rect;
				for(int i = 0; i < frames.GetCount(); i++) {
					CtrlFrame* f = frames[i];
					if (r.Contains(fpt)) {
						last_fitting = f;
						fitting_rect = r;
					}
					f->FrameLayout(r);
				}
				if (last_fitting) {
					Ctrl* with_mouse = GetWithMouse();
					if (with_mouse) {
						with_mouse->has_mouse = false;
						with_mouse->MouseLeave();
						with_mouse = NULL;
						SetWithMouse(NULL);
					}
					CtrlFrame* f = last_fitting;
					Point fitting_pt = fpt - fitting_rect.TopLeft();
					if (!f->has_mouse) {
						CtrlFrame* frame_with_mouse = GetFrameWithMouse();
						if (frame_with_mouse) {
							frame_with_mouse->has_mouse = false;
							frame_with_mouse->MouseLeave();
						}
						f->has_mouse = true;
						SetFrameWithMouse(f);
						
						f->MouseEnter(fitting_pt, keyflags);
					}
					f->MouseWheel(fitting_pt, zdelta, keyflags);
				}
			}
			return true;
		}
		return false;
	}
}


Rect Ctrl::GetWorkArea() const {
	TODO
}


bool Ctrl::ReleaseCtrlCapture() {
	TODO
	/*GuiLock __;
	LLOG("ReleaseCtrlCapture");
	if(captureCtrl) {
		captureCtrl->CancelMode();
		Ctrl *w = captureCtrl->GetTopCtrl();
		captureCtrl = NULL;
		CheckMouseCtrl();
		if(w->HasWndCapture()) {
			w->ReleaseWndCapture();
			return true;
		}
	}
	return false;*/
}

Ctrl* Ctrl::GetCaptureCtrl() {
	TODO
}

Image Ctrl::DefaultCursor() {
	LOG("TODO Ctrl::DefaultCursor");
	return Image();
}

void Ctrl::Update() {
	SetModify();
	Updated();
}

bool Ctrl::IsModified() const {
	GuiLock __;
	return modify;
}

void Ctrl::SetModify() {
	GuiLock __;
	modify = true;
}

void Ctrl::ClearModify() {
	GuiLock __;
	modify = false;
}










Bar::Item::Item() {
	
}

Bar::Item::~Item() {
	
}

Bar::Item& Bar::Item::Text(const char *text) {
	TODO
}

Bar::Item& Bar::Item::Key(dword key) {
	TODO
}

Bar::Item& Bar::Item::Repeat(bool repeat) {
	TODO
}

Bar::Item& Bar::Item::Image(const class Image& img) {
	TODO
}

Bar::Item& Bar::Item::Check(bool check) {
	TODO
}

Bar::Item& Bar::Item::Radio(bool check) {
	TODO
}

Bar::Item& Bar::Item::Enable(bool _enable) {
	TODO
}

Bar::Item& Bar::Item::Bold(bool bold) {
	TODO
}

Bar::Item& Bar::Item::Tip(const char *tip) {
	TODO
}

Bar::Item& Bar::Item::Help(const char *help) {
	TODO
}

Bar::Item& Bar::Item::Topic(const char *topic) {
	TODO
}

Bar::Item& Bar::Item::Description(const char *desc) {
	TODO
}

void Bar::Item::FinalSync() {
	TODO
}

Bar::Item& Bar::Item::Label(const char *text) {
	TODO
}

Bar::Item& Bar::Item::RightLabel(const char *text) {
	TODO
}

Bar::Item& Bar::Item::Key(KeyInfo& (*key)()) {
	TODO
}


END_UPP_NAMESPACE
