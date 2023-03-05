#include "GuboCore.h"


NAMESPACE_TOPSIDE_BEGIN

bool      Gubo::do_debug_draw;



#if 0
void GuboFrame::FramePaint(Draw& draw, const Rect& r) {}

void GuboFrame::FrameAdd(Gubo& ctrl) {}

void GuboFrame::FrameRemove() {}

int GuboFrame::OverPaint() const {
	return 0;
}
#endif


void GuboFrame::SetCapture() {
	if (!ctrl) return;
	SetCaptured(this);
	ctrl->SetCapture();
}

void GuboFrame::ReleaseCapture() {
	if (!ctrl) return;
	SetCaptured(NULL);
	ctrl->ReleaseCapture();
}

GuboFrame* GuboFrame::GetCaptured() {
	TODO
	/*
	if (!ctrl) return NULL;
	return ctrl->GetWindows()->GetFrameCaptured();*/
}

GuboFrame* GuboFrame::GetWithMouse() {
	TODO
	/*
	if (!ctrl) return NULL;
	return ctrl->GetWindows()->GetFrameWithMouse();*/
}

void GuboFrame::SetCaptured(GuboFrame* c) {
	TODO
	/*
	ctrl->GetWindows()->SetFrameCaptured(c);*/
}

void GuboFrame::SetWithMouse(GuboFrame* c) {
	TODO
	/*
	ctrl->GetWindows()->SetFrameWithMouse(c);*/
}



int       Gubo::LoopLevel;
Gubo     *Gubo::LoopGubo;
int64     Gubo::EventLoopNo;



Gubo::Gubo() {
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

void Gubo::Add(GeomInteraction3D& c) {
	GeomInteraction3D::Add(c);
}

void Gubo::Add(Gubo& c) {
	GeomInteraction3D::Add(c);
}

void Gubo::AddChild(Gubo* c) {
	GeomInteraction3D::AddSub(c);
}

Gubo* Gubo::GetLastChild() {
	return CastPtr<Gubo>(sub.Top());
}

void Gubo::RemoveChild(Gubo* c) {
	GeomInteraction3D::RemoveSub(c);
}

Gubo* Gubo::GetParent() {
	if (!owner)
		return 0;
	return CastPtr<Gubo>(owner);
}

Gubo* Gubo::GetTopGubo() {
	Gubo* c = this;
	while (c) {
		Gubo* p = c->GetParent();
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

Gubo* Gubo::GetIndexChild(int i) {
	return CastPtr<Gubo>(sub[i]);
}

int Gubo::GetChildCount() const {
	return sub.GetCount();
}

TopSurface* Gubo::GetTopSurface() {
	Gubo* c = this;
	while (c) {
		Gubo* par = c->GetParent();
		if (!par) {
			TopSurface* tw = CastPtr<TopSurface>(c);
			return tw;
		}
		c = par;
	}
	return 0;
}

void Gubo::SetRect(const Rect& r) {
	SetFrameRect(r);
	SetPendingRedrawDeep();
}

void Gubo::SetFrameRect(const Rect& r) {
	this->frame_r = r;
	/*SetPendingEffectRedraw();
	if (parent) {
		parent->SetPendingLayout();
		Geom3DComponent* w = GetWindow();
		if (w)
			w->SetPendingLayout();
	}*/
}

Size Gubo::GetContentSize() const {
	return content_r.GetSize();
}

void Gubo::SetContentRect(const Rect& r) {
	content_r = r;
}

Rect Gubo::GetContentRect() const {
	ASSERT(frame_r.Contains(content_r));
	return content_r;
}

Point Gubo::GetContentPoint(const Point& pt) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	return cpt;
}

void Gubo::MouseMoveInFrameContent(Point pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point fpt = pt - ftl;
	Rect r(frame_r.GetSize());
	GuboFrame* last_fitting = NULL;
	Rect fitting_rect;
	for(int i = 0; i < frames.GetCount(); i++) {
		GuboFrame* f = frames[i];
		if (r.Contains(fpt)) {
			last_fitting = f;
			fitting_rect = r;
		}
		f->FrameLayout(r);
	}
	if (last_fitting) {
		Gubo* with_mouse = GetWithMouse();
		if (with_mouse) {
			with_mouse->has_mouse = false;
			with_mouse->MouseLeave();
			SetWithMouse(NULL);
		}
		GuboFrame* f = last_fitting;
		Point fitting_pt = fpt - fitting_rect.TopLeft();
		if (!f->has_mouse) {
			GuboFrame* frame_with_mouse = GetFrameWithMouse();
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

void Gubo::DeepMouseMoveInFrameContent(Point pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	
	if (GetFrameCaptured()) {
		Rect r(frame_r.GetSize());
		GuboFrame* last_fitting = NULL;
		Rect fitting_rect;
		for(int i = 0; i < frames.GetCount(); i++) {
			GuboFrame* f = frames[i];
			if (f == GetFrameCaptured()) {
				last_fitting = f;
				fitting_rect = r;
				break;
			}
			f->FrameLayout(r);
		}
		if (last_fitting) {
			GuboFrame* f = last_fitting;
			Point fitting_pt = fpt - fitting_rect.TopLeft();
			f->MouseMove(fitting_pt, keyflags);
			return;
		}
	}
}

bool Gubo::MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	
	GuboFrame* frame_captured = GetFrameCaptured();
	if (frame_captured) {
		Rect r(frame_r.GetSize());
		GuboFrame* last_fitting = NULL;
		Rect fitting_rect;
		for(int i = 0; i < frames.GetCount(); i++) {
			GuboFrame* f = frames[i];
			if (f == frame_captured) {
				last_fitting = f;
				fitting_rect = r;
				break;
			}
			f->FrameLayout(r);
		}
		if (last_fitting) {
			GuboFrame* f = last_fitting;
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

void Gubo::MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point fpt = pt - ftl;
	Rect r(frame_r.GetSize());
	GuboFrame* last_fitting = NULL;
	Rect fitting_rect;
	for(int i = 0; i < frames.GetCount(); i++) {
		GuboFrame* f = frames[i];
		if (r.Contains(fpt)) {
			last_fitting = f;
			fitting_rect = r;
		}
		f->FrameLayout(r);
	}
	if (last_fitting) {
		Gubo* with_mouse = GetWithMouse();
		if (with_mouse) {
			with_mouse->has_mouse = false;
			with_mouse->MouseLeave();
			with_mouse = NULL;
			SetWithMouse(NULL);
		}
		GuboFrame* f = last_fitting;
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

void Gubo::MouseLeaveFrame() {
	GuboFrame* frame_with_mouse = GetFrameWithMouse();
	if (frame_with_mouse) {
		frame_with_mouse->has_mouse = false;
		frame_with_mouse->MouseLeave();
		SetFrameWithMouse(NULL);
	}
}

bool Gubo::MouseWheelInFrameContent(Point pt, int zdelta, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	
	if (content_r.Contains(fpt)) {
		for(int i = sub.GetCount()-1; i >= 0; i--) {
			GeomInteraction3D* c = sub[i]->Get3D();
			if (c->DeepMouseWheel(cpt, zdelta, keyflags))
				return true;
		}
		MouseWheel(cpt, zdelta, keyflags);
	}
	else {
		Rect r(frame_r.GetSize());
		GuboFrame* last_fitting = NULL;
		Rect fitting_rect;
		for(int i = 0; i < frames.GetCount(); i++) {
			GuboFrame* f = frames[i];
			if (r.Contains(fpt)) {
				last_fitting = f;
				fitting_rect = r;
			}
			f->FrameLayout(r);
		}
		if (last_fitting) {
			Gubo* with_mouse = GetWithMouse();
			if (with_mouse) {
				with_mouse->has_mouse = false;
				with_mouse->MouseLeave();
				with_mouse = NULL;
				SetWithMouse(NULL);
			}
			GuboFrame* f = last_fitting;
			Point fitting_pt = fpt - fitting_rect.TopLeft();
			if (!f->has_mouse) {
				GuboFrame* frame_with_mouse = GetFrameWithMouse();
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
	return false;
}

void Gubo::SetFocus() {
	Gubo* tw = GetTopGubo();
	if (tw) tw->DeepUnfocus();
	
	has_focus = true;
	has_focus_deep = true;
	GotFocus();
	
	Gubo* c = GetParent();
	while (c) {
		c->has_focus_deep = true;
		c->ChildGotFocus();
		c = c->GetParent();
	}
	
	GeomInteraction::SetFocus();
}


void Gubo::SetPendingRedrawDeep() {
	SetPendingEffectRedraw();
	SetPendingRedraw();
	int c = GetChildCount();
	for(int i = 0; i < c; i++) {
		GetIndexChild(i)->SetPendingRedrawDeep();
	}
}

void Gubo::Refresh() {
	SetPendingRedrawDeep();
	
	Absolute3DInterface* aw = GetAbsolute3D();
	if (aw)
		aw->SetPendingPartialRedraw();
}

void Gubo::DeepUnfocus() {
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
			Gubo* c = GetIndexChild(i);
			if (c->HasFocusDeep()) {
				c->DeepUnfocus();
				break;
			}
		}
	}
}



bool Gubo::IsGubo() const {
	return true;
}

Gubo* Gubo::GetCaptured() {
	Gubo* top = GetTopGubo();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetCaptured();
		return gi ? gi->GetGubo() : 0;
	}
	return 0;
}

Gubo* Gubo::GetWithMouse() {
	Gubo* top = GetTopGubo();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetWithMouse();
		return gi ? gi->GetGubo() : 0;
	}
	return 0;
}

void Gubo::SetCaptured(Gubo* c) {
	Gubo* top = GetTopGubo();
	if (top)
		top->SetCaptured(c);
}

void Gubo::SetWithMouse(Gubo* c) {
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetWithMouse(c);
}

GuboFrame* Gubo::GetFrameCaptured() {
	GuboFrame* f = 0;
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<GuboFrame>(wm->GetFrameCaptured());
	return f;
}

GuboFrame* Gubo::GetFrameWithMouse() {
	GuboFrame* f = 0;
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<GuboFrame>(wm->GetFrameWithMouse());
	return f;
}

void Gubo::SetFrameCaptured(GuboFrame* c) {
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameCaptured(c);
}

void Gubo::SetFrameWithMouse(GuboFrame* c) {
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameWithMouse(c);
}




void Gubo::DeepFrameLayout() {
	Size sz(frame_r.GetSize());
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		GuboFrame& f = *frames[i];
		f.FrameLayout(new_content_r);
	}
	content_r = new_content_r;
}


Rect Gubo::GetWorkArea() const {
	TODO
}


bool Gubo::ReleaseGuboCapture() {
	TODO
	/*GuboLock __;
	LLOG("ReleaseGuboCapture");
	if(captureGubo) {
		captureGubo->CancelMode();
		Gubo *w = captureGubo->GetTopGubo();
		captureGubo = NULL;
		CheckMouseGubo();
		if(w->HasWndCapture()) {
			w->ReleaseWndCapture();
			return true;
		}
	}
	return false;*/
}

Gubo* Gubo::GetCaptureGubo() {
	TODO
}

void Gubo::Update() {
	SetModify();
	Updated();
}

void Gubo::PaintPreFrame(ProgPainter& pp) {
	Size sz = GetFrameSize();
	ASSERT(!sz.IsEmpty());
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		GuboFrame& f = *frames[i];
		f.FramePaint(pp, new_content_r);
		f.FrameLayout(new_content_r);
	}
	if (frames.GetCount())
		pp.Offset(new_content_r);
	content_r = new_content_r;
}

void Gubo::PaintPostFrame(ProgPainter& pp) {
	if (frames.GetCount())
		pp.End();
}

void Gubo::PaintDebug(ProgPainter& pp) {
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

Absolute3DInterface* Gubo::GetAbsolute3D() {
	TopSurface* tw = GetTopSurface();
	if (!tw)
		return 0;
	Absolute3DInterface* iface = tw->GetTarget();
	return iface;
}




NAMESPACE_TOPSIDE_END

