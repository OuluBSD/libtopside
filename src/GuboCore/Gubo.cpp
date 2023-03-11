#include "GuboCore.h"
#include <GuboLib/GuboLib.h>


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


#if 0
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

#endif

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

/*void Gubo::SetRect(const Rect& r) {
	SetFrameRect(r);
	SetPendingRedrawDeep();
}*/

void Gubo::SetFrameBox(const Cubf& r) {
	this->frame = r;
	/*SetPendingEffectRedraw();
	if (parent) {
		parent->SetPendingLayout();
		Geom3DComponent* w = GetWindow();
		if (w)
			w->SetPendingLayout();
	}*/
}

Volf Gubo::GetContentSize() const {
	return content.GetSize();
}

void Gubo::SetContentBox(const Cubf& r) {
	content = r;
}

Cubf Gubo::GetContentBox() const {
	ASSERT(frame.Contains(content));
	return content;
}

Point3f Gubo::GetContentPoint(const Point3f& pt) {
	Point3f ftl = frame.FirstCorner();
	Point3f ctl = content.FirstCorner();
	Point3f fpt = pt - ftl;
	Point3f cpt = fpt - ctl;
	return cpt;
}

void Gubo::MouseMoveInFrameContent(Point3f pt, dword keyflags) {
	Point3f ftl = frame.FirstCorner();
	Point3f fpt = pt - ftl;
	Cubf r(frame.GetSize());
	GuboFrame* last_fitting = NULL;
	Cubf fitting_rect;
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
		Point3f fitting_pt = fpt - fitting_rect.FirstCorner();
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

void Gubo::DeepMouseMoveInFrameContent(Point3f pt, dword keyflags) {
	Point3f ftl = frame.FirstCorner();
	Point3f ctl = content.FirstCorner();
	Point3f fpt = pt - ftl;
	
	if (GetFrameCaptured()) {
		Cubf r(frame.GetSize());
		GuboFrame* last_fitting = NULL;
		Cubf fitting_rect;
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
			Point3f fitting_pt = fpt - fitting_rect.FirstCorner();
			f->MouseMove(fitting_pt, keyflags);
			return;
		}
	}
}

bool Gubo::MouseEventInFrameCaptured(int mouse_code, const Point3f& pt, dword keyflags) {
	Point3f ftl = frame.FirstCorner();
	Point3f ctl = content.FirstCorner();
	Point3f fpt = pt - ftl;
	Point3f cpt = fpt - ctl;
	
	GuboFrame* frame_captured = GetFrameCaptured();
	if (frame_captured) {
		Cubf r(frame.GetSize());
		GuboFrame* last_fitting = NULL;
		Cubf fitting_rect;
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
			Point3f fitting_pt = fpt - fitting_rect.FirstCorner();
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

void Gubo::MouseEventInFrameContent(int mouse_code, const Point3f& pt, dword keyflags) {
	Point3f ftl = frame.FirstCorner();
	Point3f fpt = pt - ftl;
	Cubf r(frame.GetSize());
	GuboFrame* last_fitting = NULL;
	Cubf fitting_rect;
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
		Point3f fitting_pt = fpt - fitting_rect.FirstCorner();
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

bool Gubo::MouseWheelInFrameContent(Point3f pt, int zdelta, dword keyflags) {
	Point3f ftl = frame.FirstCorner();
	Point3f ctl = content.FirstCorner();
	Point3f fpt = pt - ftl;
	Point3f cpt = fpt - ctl;
	
	if (content.Contains(fpt)) {
		for(int i = sub.GetCount()-1; i >= 0; i--) {
			GeomInteraction3D* c = sub[i]->Get3D();
			if (c->DeepMouseWheel(cpt, zdelta, keyflags))
				return true;
		}
		MouseWheel(cpt, zdelta, keyflags);
	}
	else {
		Cubf r(frame.GetSize());
		GuboFrame* last_fitting = NULL;
		Cubf fitting_rect;
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
			Point3f fitting_pt = fpt - fitting_rect.FirstCorner();
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
	
	TODO
	/*Absolute3DInterface* aw = GetAbsolute3D();
	if (aw)
		aw->SetPendingPartialRedraw();*/
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
	Gu::GuboManager* wm = CastPtr<Gu::GuboManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetWithMouse(c);
}

GuboFrame* Gubo::GetFrameCaptured() {
	GuboFrame* f = 0;
	Gu::GuboManager* wm = CastPtr<Gu::GuboManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<GuboFrame>(wm->GetFrameCaptured());
	return f;
}

GuboFrame* Gubo::GetFrameWithMouse() {
	GuboFrame* f = 0;
	Gu::GuboManager* wm = CastPtr<Gu::GuboManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<GuboFrame>(wm->GetFrameWithMouse());
	return f;
}

void Gubo::SetFrameCaptured(GuboFrame* c) {
	Gu::GuboManager* wm = CastPtr<Gu::GuboManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameCaptured(c);
}

void Gubo::SetFrameWithMouse(GuboFrame* c) {
	Gu::GuboManager* wm = CastPtr<Gu::GuboManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameWithMouse(c);
}




void Gubo::DeepFrameLayout() {
	Volf sz(frame.GetSize());
	Cubf new_content(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		GuboFrame& f = *frames[i];
		f.FrameLayout(new_content);
	}
	content = new_content;
}


Cubf Gubo::GetWorkArea() const {
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

void Gubo::PaintPreFrame(ProgPainter3& pp) {
	Volf sz = GetFrameSize();
	ASSERT(!sz.IsEmpty());
	Cubf new_content(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		GuboFrame& f = *frames[i];
		f.FramePaint(pp, new_content);
		f.FrameLayout(new_content);
	}
	if (frames.GetCount())
		pp.Clipoff(new_content);
	content = new_content;
}

void Gubo::PaintPostFrame(ProgPainter3& pp) {
	if (frames.GetCount())
		pp.End();
}

void Gubo::PaintDebug(ProgPainter3& pp) {
	Volf sz = GetFrameSize();
	Cubf new_content(sz);
	if (do_debug_draw) {
		if (has_mouse) {
			RGBA c = RGBAC(255, 0, 0, 125);
			pp.DrawBox(new_content.GetSize(), c);
		}
		else {
			RGBA c(RandomColor(64, 128));
			c.a = 127;
			pp.DrawBox(new_content.GetSize(), c);
		}
	}
}

/*Absolute3DInterface* Gubo::GetAbsolute3D() {
	TopSurface* tw = GetTopSurface();
	if (!tw)
		return 0;
	Absolute3DInterface* iface = tw->GetTarget();
	return iface;
}*/



NAMESPACE_TOPSIDE_END

