#include "CtrlCore.h"
#include <ParallelLib/ParallelLib.h>

NAMESPACE_UPP

Ptr<Ctrl> Ctrl::focusCtrl;
Ptr<Ctrl> Ctrl::captureCtrl;
int64     Ctrl::EndSessionLoopNo;
bool      Ctrl::ignoreclick;



bool ThreadHasGuiLock();


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

#if 0
void CtrlFrame::SetWithMouse(CtrlFrame* c) {
	TODO
	/*
	ctrl->GetWindows()->SetFrameWithMouse(c);*/
}
#endif


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

void Ctrl::Add(GeomInteraction2D& c) {
	GeomInteraction2D::Add(c);
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
	if (!owner)
		return 0;
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

void Ctrl::SetRect(int x, int y, int cx, int cy) {
	SetRect(RectC(x,y,cx,cy));
}

void Ctrl::SetFrameBox(const Rect& r) {
	this->frame_r = r;
	/*SetPendingEffectRedraw();
	if (parent) {
		parent->SetPendingLayout();
		Geom2DComponent* w = GetWindow();
		if (w)
			w->SetPendingLayout();
	}*/
}

Size Ctrl::GetContentSize() const {
	return content_r.GetSize();
}

void Ctrl::SetContentRect(const Rect& r) {
	content_r = r;
}

Rect Ctrl::GetContentRect() const {
	ASSERT(frame_r.Contains(content_r));
	return content_r;
}

Point Ctrl::GetContentPoint(const Point& pt) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	return cpt;
}

void Ctrl::MouseMoveInFrameContent(Point pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point fpt = pt - ftl;
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

void Ctrl::DeepMouseMoveInFrameContent(Point pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	
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

void Ctrl::MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags) {
	Point ftl = frame_r.TopLeft();
	Point fpt = pt - ftl;
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

void Ctrl::MouseLeaveFrame() {
	CtrlFrame* frame_with_mouse = GetFrameWithMouse();
	if (frame_with_mouse) {
		frame_with_mouse->has_mouse = false;
		frame_with_mouse->MouseLeave();
		SetFrameWithMouse(NULL);
	}
}

bool Ctrl::MouseWheelInFrameContent(Point pt, int zdelta, dword keyflags) {
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

void Ctrl::Refresh() {
	GeomInteraction2D::Refresh();
}

void Ctrl::RefreshFrame() {
	RefreshFrame(Rect(GetRect().Size()).Inflated(overpaint));
}

void Ctrl::RefreshFrame(const Rect& r) {
	if(!top) {
		Ctrl *parent = GetParent();
		if(InFrame())
			parent->RefreshFrame(r + GetRect().TopLeft());
		else
			parent->Refresh();//r + GetRect().TopLeft());
	}
	else {
		LLOG("WndInvalidateRect: " << r << ' ' << Name());
		LTIMING("RefreshFrame InvalidateRect");
		WndInvalidateRect(r);
	}
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



bool Ctrl::IsCtrl() const {
	return true;
}

Ctrl* Ctrl::GetCaptured() {
	Ctrl* top = GetTopCtrl();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetCaptured();
		Ctrl* c = CastPtr<Ctrl>(gi);
		return c;
	}
	return 0;
}

Ctrl* Ctrl::GetWithMouse() {
	Ctrl* top = GetTopCtrl();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetWithMouse();
		Ctrl* c = CastPtr<Ctrl>(gi);
		return c;
	}
	return 0;
}

void Ctrl::SetCaptured(Ctrl* c) {
	TODO // deprecated
	/*Ctrl* top = GetTopCtrl();
	if (top)
		top->SetCaptured(c);*/
}

void Ctrl::SetWithMouse(Ctrl* c) {
	TODO // deprecated
}

void Ctrl::SyncLayout(int force) {
	if (!GetFrameBox().IsEmpty())
		DeepLayout();
}

Rect Ctrl::GetScreenView() const {
	Rect r = GetScreenRect();
	return GetView() + r.TopLeft();
}

Rect  Ctrl::GetScreenRect() const
{
	GuiLock __;
	Rect r = GetRect();
	Ctrl *parent = GetParent();
	if(parent) {
		Rect pr = inframe ? parent->GetScreenRect() : parent->GetScreenView();
		r = r + pr.TopLeft();
	}
	else
		GuiPlatformGetTopRect(r);
	return r;
}

Rect Ctrl::GetView() const
{
	TODO
	/*GuiLock __;
	int n = GetFrameCount();
	return n == 0 ? Rect(Size(rect.Size())) : Rect(GetFrame0(n - 1).GetView());*/
}


#if 0
void Ctrl::SetWithMouse(Ctrl* c) {
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetWithMouse(c);
}
#endif

CtrlFrame* Ctrl::GetFrameCaptured() {
	CtrlFrame* f = 0;
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<CtrlFrame>(wm->GetFrameCaptured());
	return f;
}

CtrlFrame* Ctrl::GetFrameWithMouse() {
	CtrlFrame* f = 0;
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<CtrlFrame>(wm->GetFrameWithMouse());
	return f;
}

void Ctrl::SetFrameCaptured(CtrlFrame* c) {
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameCaptured(c);
}

void Ctrl::SetFrameWithMouse(CtrlFrame* c) {
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameWithMouse(c);
}




void Ctrl::DeepFrameLayout() {
	Size sz(frame_r.GetSize());
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		CtrlFrame& f = *frames[i];
		f.FrameLayout(new_content_r);
	}
	content_r = new_content_r;
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
	ASSERT(!sz.IsEmpty());
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		CtrlFrame& f = *frames[i];
		f.FramePaint(pp, new_content_r);
		f.FrameLayout(new_content_r);
	}
	if (frames.GetCount())
		pp.Clipoff(new_content_r);
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

#if 0
Absolute2DInterface* Ctrl::GetAbsolute2D() {
	TopWindow* tw = GetTopWindow();
	if (!tw)
		return 0;
	Absolute2DInterface* iface = tw->GetTarget();
	return iface;
}
#endif










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







Tuple<dword, const char *> KeyNames__[ ] = {
	{ K_A, tt_("key\vA") }, { K_B, tt_("key\vB") }, { K_C, tt_("key\vC") }, { K_D, tt_("key\vD") },
	{ K_E, tt_("key\vE") }, { K_F, tt_("key\vF") }, { K_G, tt_("key\vG") }, { K_H, tt_("key\vH") },
	{ K_I, tt_("key\vI") }, { K_J, tt_("key\vJ") }, { K_K, tt_("key\vK") }, { K_L, tt_("key\vL") },
	{ K_M, tt_("key\vM") }, { K_N, tt_("key\vN") }, { K_O, tt_("key\vO") }, { K_P, tt_("key\vP") },
	{ K_Q, tt_("key\vQ") }, { K_R, tt_("key\vR") }, { K_S, tt_("key\vS") }, { K_T, tt_("key\vT") },
	{ K_U, tt_("key\vU") }, { K_V, tt_("key\vV") }, { K_W, tt_("key\vW") }, { K_X, tt_("key\vX") },
	{ K_Y, tt_("key\vY") }, { K_Z, tt_("key\vZ") }, { K_0, tt_("key\v0") }, { K_1, tt_("key\v1") },
	{ K_2, tt_("key\v2") }, { K_3, tt_("key\v3") }, { K_4, tt_("key\v4") }, { K_5, tt_("key\v5") },
	{ K_6, tt_("key\v6") }, { K_7, tt_("key\v7") }, { K_8, tt_("key\v8") }, { K_9, tt_("key\v9") },
	{ K_F1, tt_("key\vF1") }, { K_F2, tt_("key\vF2") }, { K_F3, tt_("key\vF3") }, { K_F4, tt_("key\vF4") },
	{ K_F5, tt_("key\vF5") }, { K_F6, tt_("key\vF6") }, { K_F7, tt_("key\vF7") }, { K_F8, tt_("key\vF8") },
	{ K_F9, tt_("key\vF9") }, { K_F10, tt_("key\vF10") }, { K_F11, tt_("key\vF11") }, { K_F12, tt_("key\vF12") },
	{ K_TAB, tt_("key\vTab") }, { K_SPACE, tt_("key\vSpace") },
	{ K_RETURN, tt_("key\vEnter") }, { K_BACKSPACE, tt_("key\vBackspace") },
	{ K_CAPSLOCK, tt_("key\vCaps Lock") }, { K_ESCAPE, tt_("key\vEsc") },
	{ K_PAGEUP, tt_("key\vPage Up") }, { K_PAGEDOWN, tt_("key\vPage Down") },
	{ K_END, tt_("key\vEnd") }, { K_HOME, tt_("key\vHome") },
	{ K_LEFT, tt_("key\vLeft") }, { K_UP, tt_("key\vUp") },
	{ K_RIGHT, tt_("key\vRight") }, { K_DOWN, tt_("key\vDown") },
	{ K_INSERT, tt_("key\vInsert") }, { K_DELETE, tt_("key\vDelete") },{ K_BREAK, tt_("key\vBreak") },
	{ K_MULTIPLY, tt_("key\vNum[*]") }, { K_ADD, tt_("key\vNum[+]") }, { K_SUBTRACT, tt_("key\vNum[-]") }, { K_DIVIDE, tt_("key\vNum[/]") },
	{ K_ALT_KEY, tt_("key\vAlt") }, { K_SHIFT_KEY, tt_("key\vShift") }, { K_CTRL_KEY, tt_("key\vCtrl") },
	{ K_PLUS, tt_("key\v[+]") }, { K_MINUS, tt_("key\v[-]") }, { K_COMMA, tt_("key\v[,]") }, { K_PERIOD, tt_("key\v[.]") },
	{ K_SEMICOLON, tt_("key\v[;]") }, { K_SLASH, tt_("key\v[/]") }, { K_GRAVE, tt_("key\v[`]") }, { K_LBRACKET, tt_("key\v[[]") },
	{ K_BACKSLASH, tt_("key\v[\\]") }, { K_RBRACKET, tt_("key\v[]]") }, { K_QUOTEDBL, tt_("key\v[']") },
#ifdef GUI_COCOA
	{ K_OPTION_KEY, tt_("key\vOption") },
#endif
	{ IK_DBL_CLICK, tt_("key\v[double-click]") },
	{ (dword)K_MOUSE_FORWARD, tt_("key\v[Forward]") },
	{ (dword)K_MOUSE_BACKWARD, tt_("key\v[Backward]") },
	{ 0, NULL }
};


int Ctrl::GetFrameCount() const {
	return frames.GetCount();
}

Ctrl::Frame& Ctrl::GetFrame0(int i) {
	return frames[i];
}

Ctrl& Ctrl::SetFrame(int i, CtrlFrame& fr) {
	GuiLock __;
	LLOG("SetFrame " << typeid(fr).name());
	while(GetFrameCount() <= i)
		AddFrame(NullFrame());
	Frame& f = GetFrame0(i);
	f.frame->FrameRemove();
	f.frame = &fr;
	fr.FrameAdd(*this);
	SyncLayout();
	RefreshFrame();
	SetPendingRedraw();
	return *this;
}

Ctrl& Ctrl::SetFrame(CtrlFrame& fr) {
	for (Frame& f : frames)
		f.frame->FrameRemove();
	frames.Clear();
	AddFrame(fr);
	return *this;
}

void Ctrl::AddFrame(CtrlFrame& fr) {
	Frame& f = frames.Add();
	f.frame = &fr;
	fr.FrameAdd(*this);
	SyncLayout();
	RefreshFrame();
	SetPendingRedraw();
}

void Ctrl::PostInput()
{
	GuiLock __;
	Ctrl *parent = GetParent();
	if(parent)
		parent->PostInput();
}

void Ctrl::RefreshParentLayout()
{
	Ctrl *parent = GetParent();
	if(parent)
		parent->RefreshLayout();
}

bool Ctrl::IsForeground() const
{
	GuiLock __;
	TODO //return GetTopCtrl()->IsWndForeground();
}

Ctrl* Ctrl::GetFocusCtrl() { return FocusCtrl(); }

Ctrl* Ctrl::GetParent() const {
	TODO
}

bool Ctrl::IsOpen() const
{
	GuiLock __;
	const Ctrl *q = GetTopCtrl();
	return q->isopen && q->IsWndOpen();
}

const Ctrl *Ctrl::GetTopCtrl() const      { return const_cast<Ctrl *>(this)->GetTopCtrl(); }

void Ctrl::Enable(bool aenable) {
	LOG("Ctrl::Enable: skipping");
	/*GuiLock __;
	if(enabled != aenable) {
		enabled = aenable;
		if(top) WndEnable(enabled);
		if(!enabled && GetParent() && HasFocusDeep())
			IterateFocusForward(this, GetTopCtrl());
		RefreshFrame();
		StateH(ENABLE);
		SyncCaret();
	}*/
}

void Ctrl::ClickActivateWnd()
{
	LOG("Ctrl::ClickActivateWnd: skipping");
	/*GuiLock __;
	LLOG("Ctrl::ClickActivateWnd " << Name(this));
	if(this == ~focusCtrlWnd && focusCtrl && focusCtrl->GetTopCtrl() != this) {
		LLOG("Ctrl::ClickActivateWnd -> ActivateWnd");
		ActivateWnd();
	}*/
}


void Ctrl::SetForeground()
{
	LOG("Ctrl::SetForeground: skipping");
	/*GuiLock __;
	GetTopCtrl()->SetWndForeground();*/
}

Image Ctrl::DispatchMouse(int e, Point p, int zd) {
	LOG("Ctrl::DispatchMouse: skipping");
	return Image();
}

void Ctrl::EndIgnore()
{
	LOG("Ctrl::EndIgnore: skipping");
}

bool Ctrl::DispatchKey(dword keycode, int count)
{
	LOG("Ctrl::DispatchKey: skipping");
	return false;
}

void Ctrl::SyncCaret() {
	LOG("Ctrl::SyncCaret: skipping");
}

void Ctrl::DefferedFocusSync()
{
	LOG("Ctrl::DefferedFocusSync: skipping");
}

bool   Ctrl::InLoop() const
{
	GuiLock __;
	return inloop;
}

void Ctrl::TimerProc(double dt)
{
	LOG("Ctrl::TimerProc: skipping");
}

void  Ctrl::AnimateCaret()
{
	LOG("Ctrl::AnimateCaret: skipping");
}

void Ctrl::UpdateArea(SystemDraw& draw, const Rect& clip)
{
	LOG("Ctrl::UpdateArea: skipping");
}

void Ctrl::DeleteTop()
{
	if(top && utop) {
		delete utop;
		utop = nullptr;
		top = false;
	}
}

void Ctrl::ActivateWnd()
{
	LOG("Ctrl::ActivateWnd: skipping");
	/*GuiLock __;
	// notification, don't set physical focus here
	LLOG("ActivateWnd " << Name());
	Ptr<Ctrl> nfocusCtrl = this;
	Ptr<Ctrl> pfocusCtrl = focusCtrl;
	LLOG("About to set focus: " << UPP::Name(nfocusCtrl));
	DoDeactivate(pfocusCtrl, nfocusCtrl);
	focusCtrl = nfocusCtrl;
	focusCtrlWnd = this;
	DoKillFocus(pfocusCtrl, nfocusCtrl);
	DoSetFocus(pfocusCtrl, nfocusCtrl, true);
	LLOG("Focus: " << UPP::Name(focusCtrl) << " FocusWnd:" << UPP::Name(focusCtrlWnd));*/
}

void  Ctrl::SetWndRect(const Rect& r)
{
	TODO
	//LLOG("SetWndRect " << Name() << " rect: " << r << " (Ctrl::GetRect = " << GetRect() << ")");
	//SetPos0(LogPos(PosLeft(r.left, r.Width()), PosTop(r.top, r.Height())), false);
}

String FromSystemCharset(const String& src)
{
	TODO //return FromWin32Charset(src, CP_ACP);
}

void Ctrl::GlobalBackBuffer(bool b)
{
	LOG("Ctrl::GlobalBackBuffer: skipping");
	//GuiLock __;
	//globalbackbuffer = b;
}

void  Ctrl::InitTimer()
{
	LOG("Ctrl::InitTimer: skipping");
	/*Mutex::Lock __(sTimerLock);
	tevents();*/
}

void Ctrl::CloseTopCtrls()
{
	TODO
	/*GuiLock __;
	Vector<Ctrl *> tc = Ctrl::GetTopCtrls();
	for(int i = 0; i < tc.GetCount(); i++)
		tc[i]->Close();*/
}


END_UPP_NAMESPACE
