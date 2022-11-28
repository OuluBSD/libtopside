#include "CtrlCore.h"
#include <EcsLib/EcsLib.h>

NAMESPACE_UPP


#if 0
void CtrlFrame::FramePaint(Draw& draw, const Rect& r) {}

void CtrlFrame::FrameAdd(Ctrl& ctrl) {}

void CtrlFrame::FrameRemove() {}

int CtrlFrame::OverPaint() const {
	return 0;
}
#endif


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
		if (p) {
			c = p;
			if (p->IsCaptureRoot())
				break;
		}
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

Point Ctrl::GetContentPoint(const Point& pt) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	return cpt;
}

bool Ctrl::MouseMoveInFrame(Point pt, dword keyflags) {
	if (GetCaptured()) {
		ASSERT(this == GetCaptured());
		Point cpt = GetContentPoint(pt);
		MouseMove(cpt, keyflags);
		return true;
	}
	else {
		if (frame_r.Contains(pt)) {
			has_mouse_deep = true;
			
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

void Ctrl::DeepMouseMoveInFrame(Point pt, dword keyflags) {
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
			return;
		}
	}
	
	for(int i = sub.GetCount()-1; i >= 0; i--) {
		GeomInteraction2D* c = sub[i]->Get2D();
		if (!c) continue;
		
		if (c->has_mouse_deep)
			c->DeepMouseMove(cpt, keyflags);
	}
}

bool Ctrl::MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) {
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
	
	return false;
}

bool Ctrl::MouseEventInFrame(int mouse_code, const Point& pt, dword keyflags) {
	if (frame_r.Contains(pt)) {
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

void Ctrl::MouseLeaveFrame() {
	CtrlFrame* frame_with_mouse = GetFrameWithMouse();
	if (frame_with_mouse) {
		frame_with_mouse->has_mouse = false;
		frame_with_mouse->MouseLeave();
		SetFrameWithMouse(NULL);
	}
}

bool Ctrl::MouseWheelInFrame(Point pt, int zdelta, dword keyflags) {
	if (frame_r.Contains(pt)) {
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
	
	GeomInteraction::SetFocus();
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
	
	AbsoluteWindow* aw = GetAbsoluteWindow();
	if (aw)
		aw->SetPendingPartialRedraw();
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



bool Ctrl::IsCtrl() const {
	return true;
}

Ctrl* Ctrl::GetCaptured() {
	Ctrl* top = GetTopCtrl();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetCaptured();
		return gi ? gi->GetCtrl() : 0;
	}
	return 0;
}

Ctrl* Ctrl::GetWithMouse() {
	Ctrl* top = GetTopCtrl();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetWithMouse();
		return gi ? gi->GetCtrl() : 0;
	}
	return 0;
}

void Ctrl::SetCaptured(Ctrl* c) {
	Ctrl* top = GetTopCtrl();
	if (top)
		top->SetCaptured(c);
}

void Ctrl::SetWithMouse(Ctrl* c) {
	Ctrl* top = GetTopCtrl();
	if (top)
		top->SetWithMouse(c);
}

CtrlFrame* Ctrl::GetFrameCaptured() {
	TODO //return GetWindows()->GetFrameCaptured();
}

CtrlFrame* Ctrl::GetFrameWithMouse() {
	TODO //return GetWindows()->GetFrameWithMouse();
}

void Ctrl::SetFrameCaptured(CtrlFrame* c) {
	TODO //GetWindows()->SetFrameCaptured(c);
}

void Ctrl::SetFrameWithMouse(CtrlFrame* c) {
	TODO //GetWindows()->SetFrameWithMouse(c);
}



void Ctrl::DeepLayout() {
	TODO
	#if 0
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
		SetGeomRect(cr);
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
	#endif
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

void Ctrl::Update() {
	SetModify();
	Updated();
}

void Ctrl::PaintPreFrame(ProgPainter& pp) {
	Size sz = GetFrameSize();
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		CtrlFrame& f = *frames[i];
		f.FramePaint(pp, new_content_r);
		f.FrameLayout(new_content_r);
	}
	if (frames.GetCount())
		pp.Offset(new_content_r);
	content_r = new_content_r;
}

void Ctrl::PaintPostFrame(ProgPainter& pp) {
	if (frames.GetCount())
		pp.End();
}

void Ctrl::PaintDebug(ProgPainter& pp) {
	Size sz = GetFrameSize();
	Rect new_content_r(sz);
	if (do_debug_draw) {
		if (has_mouse) {
			RGBA c{255, 0, 0, 125};
			pp.DrawRect(new_content_r.GetSize(), c);
		}
		else {
			RGBA c(RandomColor(64, 128));
			c.a = 127;
			pp.DrawRect(new_content_r.GetSize(), c);
		}
	}
}

AbsoluteWindow* Ctrl::GetAbsoluteWindow() {
	TODO
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
