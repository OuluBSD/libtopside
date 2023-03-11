#include "GuboCore.h"
#include <ParallelLib/ParallelLib.h>

NAMESPACE_TOPSIDE_BEGIN


#if 0
void SurfaceFrame::FramePaint(Draw& draw, const Rect& r) {}

void SurfaceFrame::FrameAdd(Surface& ctrl) {}

void SurfaceFrame::FrameRemove() {}

int SurfaceFrame::OverPaint() const {
	return 0;
}
#endif


void SurfaceFrame::SetCapture() {
	if (!ctrl) return;
	SetCaptured(this);
	ctrl->SetCapture();
}

void SurfaceFrame::ReleaseCapture() {
	if (!ctrl) return;
	SetCaptured(NULL);
	ctrl->ReleaseCapture();
}

SurfaceFrame* SurfaceFrame::GetCaptured() {
	TODO
	/*
	if (!ctrl) return NULL;
	return ctrl->GetWindows()->GetFrameCaptured();*/
}

SurfaceFrame* SurfaceFrame::GetWithMouse() {
	TODO
	/*
	if (!ctrl) return NULL;
	return ctrl->GetWindows()->GetFrameWithMouse();*/
}

void SurfaceFrame::SetCaptured(SurfaceFrame* c) {
	TODO
	/*
	ctrl->GetWindows()->SetFrameCaptured(c);*/
}

void SurfaceFrame::SetWithMouse(SurfaceFrame* c) {
	TODO
	/*
	ctrl->GetWindows()->SetFrameWithMouse(c);*/
}



int       Surface::LoopLevel;
Surface     *Surface::LoopSurface;
int64     Surface::EventLoopNo;



Surface::Surface() {
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

void Surface::Add(GeomInteraction2D& c) {
	GeomInteraction2D::Add(c);
}

void Surface::Add(Surface& c) {
	GeomInteraction2D::Add(c);
}

void Surface::AddChild(Surface* c) {
	GeomInteraction2D::AddSub(c);
}

Surface* Surface::GetLastChild() {
	return CastPtr<Surface>(sub.Top());
}

void Surface::RemoveChild(Surface* c) {
	GeomInteraction2D::RemoveSub(c);
}

Surface* Surface::GetParent() {
	if (!owner)
		return 0;
	return CastPtr<Surface>(owner);
}

Surface* Surface::GetIndexChild(int i) {
	return CastPtr<Surface>(sub[i]);
}

int Surface::GetChildCount() const {
	return sub.GetCount();
}

#if 0
TopSurface* Surface::GetTopSurface() {
	Surface* c = this;
	while (c) {
		Surface* p = c->GetParent();
		if (p) {
			c = p;
			if (p->IsCaptureRoot())
				break;
		}
		else
			break;
	}
	if (c) {
		TopSurface* tc = CastPtr<TopSurface>(c);
		ASSERT(tc);
		return tc;
	}
	return 0;
}
#else
TopSurface* Surface::GetTopSurface() {
	Surface* c = this;
	while (c) {
		Surface* par = c->GetParent();
		if (!par) {
			TopSurface* tw = CastPtr<TopSurface>(c);
			return tw;
		}
		c = par;
	}
	return 0;
}
#endif

void Surface::SetRect(const Rect& r) {
	SetFrameRect(r);
	SetPendingRedrawDeep();
}

void Surface::SetFrameBox(const Rect& r) {
	this->frame_r = r;
	/*SetPendingEffectRedraw();
	if (parent) {
		parent->SetPendingLayout();
		Geom2DComponent* w = GetWindow();
		if (w)
			w->SetPendingLayout();
	}*/
}

Size Surface::GetContentSize() const {
	return content_r.GetSize();
}

void Surface::SetContentRect(const Rect& r) {
	content_r = r;
}

Rect Surface::GetContentRect() const {
	ASSERT(frame_r.Contains(content_r));
	return content_r;
}

Point Surface::GetContentPoint(const Point& pt) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	return cpt;
}

void Surface::MouseMoveInFrameContent(Point pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point fpt = pt - ftl;
	Rect r(frame_r.GetSize());
	SurfaceFrame* last_fitting = NULL;
	Rect fitting_rect;
	for(int i = 0; i < frames.GetCount(); i++) {
		SurfaceFrame* f = frames[i];
		if (r.Contains(fpt)) {
			last_fitting = f;
			fitting_rect = r;
		}
		f->FrameLayout(r);
	}
	if (last_fitting) {
		Surface* with_mouse = GetWithMouse();
		if (with_mouse) {
			with_mouse->has_mouse = false;
			with_mouse->MouseLeave();
			SetWithMouse(NULL);
		}
		SurfaceFrame* f = last_fitting;
		Point fitting_pt = fpt - fitting_rect.TopLeft();
		if (!f->has_mouse) {
			SurfaceFrame* frame_with_mouse = GetFrameWithMouse();
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

void Surface::DeepMouseMoveInFrameContent(Point pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	
	if (GetFrameCaptured()) {
		Rect r(frame_r.GetSize());
		SurfaceFrame* last_fitting = NULL;
		Rect fitting_rect;
		for(int i = 0; i < frames.GetCount(); i++) {
			SurfaceFrame* f = frames[i];
			if (f == GetFrameCaptured()) {
				last_fitting = f;
				fitting_rect = r;
				break;
			}
			f->FrameLayout(r);
		}
		if (last_fitting) {
			SurfaceFrame* f = last_fitting;
			Point fitting_pt = fpt - fitting_rect.TopLeft();
			f->MouseMove(fitting_pt, keyflags);
			return;
		}
	}
}

bool Surface::MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	
	SurfaceFrame* frame_captured = GetFrameCaptured();
	if (frame_captured) {
		Rect r(frame_r.GetSize());
		SurfaceFrame* last_fitting = NULL;
		Rect fitting_rect;
		for(int i = 0; i < frames.GetCount(); i++) {
			SurfaceFrame* f = frames[i];
			if (f == frame_captured) {
				last_fitting = f;
				fitting_rect = r;
				break;
			}
			f->FrameLayout(r);
		}
		if (last_fitting) {
			SurfaceFrame* f = last_fitting;
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

void Surface::MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point fpt = pt - ftl;
	Rect r(frame_r.GetSize());
	SurfaceFrame* last_fitting = NULL;
	Rect fitting_rect;
	for(int i = 0; i < frames.GetCount(); i++) {
		SurfaceFrame* f = frames[i];
		if (r.Contains(fpt)) {
			last_fitting = f;
			fitting_rect = r;
		}
		f->FrameLayout(r);
	}
	if (last_fitting) {
		Surface* with_mouse = GetWithMouse();
		if (with_mouse) {
			with_mouse->has_mouse = false;
			with_mouse->MouseLeave();
			with_mouse = NULL;
			SetWithMouse(NULL);
		}
		SurfaceFrame* f = last_fitting;
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

void Surface::MouseLeaveFrame() {
	SurfaceFrame* frame_with_mouse = GetFrameWithMouse();
	if (frame_with_mouse) {
		frame_with_mouse->has_mouse = false;
		frame_with_mouse->MouseLeave();
		SetFrameWithMouse(NULL);
	}
}

bool Surface::MouseWheelInFrameContent(Point pt, int zdelta, dword keyflags) {
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
		SurfaceFrame* last_fitting = NULL;
		Rect fitting_rect;
		for(int i = 0; i < frames.GetCount(); i++) {
			SurfaceFrame* f = frames[i];
			if (r.Contains(fpt)) {
				last_fitting = f;
				fitting_rect = r;
			}
			f->FrameLayout(r);
		}
		if (last_fitting) {
			Surface* with_mouse = GetWithMouse();
			if (with_mouse) {
				with_mouse->has_mouse = false;
				with_mouse->MouseLeave();
				with_mouse = NULL;
				SetWithMouse(NULL);
			}
			SurfaceFrame* f = last_fitting;
			Point fitting_pt = fpt - fitting_rect.TopLeft();
			if (!f->has_mouse) {
				SurfaceFrame* frame_with_mouse = GetFrameWithMouse();
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

void Surface::SetFocus() {
	Surface* tw = GetTopSurface();
	if (tw) tw->DeepUnfocus();
	
	has_focus = true;
	has_focus_deep = true;
	GotFocus();
	
	Surface* c = GetParent();
	while (c) {
		c->has_focus_deep = true;
		c->ChildGotFocus();
		c = c->GetParent();
	}
	
	GeomInteraction::SetFocus();
}

void Surface::Refresh() {
	GeomInteraction2D::Refresh();
}

void Surface::DeepUnfocus() {
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
			Surface* c = GetIndexChild(i);
			if (c->HasFocusDeep()) {
				c->DeepUnfocus();
				break;
			}
		}
	}
}



bool Surface::IsSurface() const {
	return true;
}

Surface* Surface::GetCaptured() {
	Surface* top = GetTopSurface();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetCaptured();
		Surface* c = CastPtr<Surface>(gi);
		return c;
	}
	return 0;
}

Surface* Surface::GetWithMouse() {
	Surface* top = GetTopSurface();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetWithMouse();
		Surface* c = CastPtr<Surface>(gi);
		return c;
	}
	return 0;
}

void Surface::SetCaptured(Surface* c) {
	Surface* top = GetTopSurface();
	if (top)
		top->SetCaptured(c);
}

void Surface::SetWithMouse(Surface* c) {
	Gu::SurfaceManager* wm = CastPtr<Gu::SurfaceManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetWithMouse(c);
}

SurfaceFrame* Surface::GetFrameCaptured() {
	SurfaceFrame* f = 0;
	Gu::SurfaceManager* wm = CastPtr<Gu::SurfaceManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<SurfaceFrame>(wm->GetFrameCaptured());
	return f;
}

SurfaceFrame* Surface::GetFrameWithMouse() {
	SurfaceFrame* f = 0;
	Gu::SurfaceManager* wm = CastPtr<Gu::SurfaceManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<SurfaceFrame>(wm->GetFrameWithMouse());
	return f;
}

void Surface::SetFrameCaptured(SurfaceFrame* c) {
	Gu::SurfaceManager* wm = CastPtr<Gu::SurfaceManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameCaptured(c);
}

void Surface::SetFrameWithMouse(SurfaceFrame* c) {
	Gu::SurfaceManager* wm = CastPtr<Gu::SurfaceManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameWithMouse(c);
}




void Surface::DeepFrameLayout() {
	Size sz(frame_r.GetSize());
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		SurfaceFrame& f = *frames[i];
		f.FrameLayout(new_content_r);
	}
	content_r = new_content_r;
}


Rect Surface::GetWorkArea() const {
	TODO
}


bool Surface::ReleaseSurfaceCapture() {
	TODO
	/*GuiLock __;
	LLOG("ReleaseSurfaceCapture");
	if(captureSurface) {
		captureSurface->CancelMode();
		Surface *w = captureSurface->GetTopSurface();
		captureSurface = NULL;
		CheckMouseSurface();
		if(w->HasWndCapture()) {
			w->ReleaseWndCapture();
			return true;
		}
	}
	return false;*/
}

Surface* Surface::GetCaptureSurface() {
	TODO
}

void Surface::Update() {
	SetModify();
	Updated();
}

void Surface::PaintPreFrame(ProgPainter& pp) {
	Size sz = GetFrameSize();
	ASSERT(!sz.IsEmpty());
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		SurfaceFrame& f = *frames[i];
		f.FramePaint(pp, new_content_r);
		f.FrameLayout(new_content_r);
	}
	if (frames.GetCount())
		pp.Clipoff(new_content_r);
	content_r = new_content_r;
}

void Surface::PaintPostFrame(ProgPainter& pp) {
	if (frames.GetCount())
		pp.End();
}

void Surface::PaintDebug(ProgPainter& pp) {
	Size sz = GetFrameSize();
	Rect new_content_r(sz);
	if (do_debug_draw) {
		if (has_mouse) {
			RGBA c = RGBAC(255, 0, 0, 125);
			pp.DrawRect(new_content_r.GetSize(), c);
		}
		else {
			RGBA c(RandomColor(64, 128));
			c.a = 127;
			pp.DrawRect(new_content_r.GetSize(), c);
		}
	}
}

/*Absolute2DInterface* Surface::GetAbsolute2D() {
	TopSurface* tw = GetTopSurface();
	if (!tw)
		return 0;
	Absolute2DInterface* iface = tw->GetTarget();
	return iface;
}*/

void Surface::EventLoop() {
	TODO
}

void Surface::EventLoopIteration(void*) {
	TODO
}

void Surface::PaintAll(bool b) {
	TODO
}



void Surface::InitFB() {
	TODO
}

void Surface::ExitFB() {
	TODO
}

void Surface::SetDesktopSize(Size sz) {
	TODO
}



NAMESPACE_TOPSIDE_END
