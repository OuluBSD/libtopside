#include "CtrlCore.h"
#include <ParallelLib/ParallelLib.h>

NAMESPACE_UPP

Ptr<Ctrl> Ctrl::focusCtrl;
Ptr<Ctrl> Ctrl::captureCtrl;
int64     Ctrl::EndSessionLoopNo;
bool      Ctrl::ignoreclick;



bool ThreadHasGuiLock();





bool      Ctrl::do_debug_draw;
int       Ctrl::LoopLevel;
Ctrl     *Ctrl::LoopCtrl;
int64     Ctrl::EventLoopNo;



Ctrl::Ctrl() {
	inloop = false;
	wantfocus = false;
	/*has_focus = false;
	has_focus_deep = false;
	has_mouse = false;
	has_mouse_deep = false;
	pending_fx_redraw = true;
	pending_redraw = true;
	pending_layout = true;*/
	modify = false;
	
}

/*void Ctrl::Add(GeomInteraction2D& c) {
	GeomInteraction2D::Add(c);
}*/

void Ctrl::Add(Ctrl& c) {
	TODO //GeomInteraction::Add(c);
}

void Ctrl::AddChild(Ctrl* c) {
	TODO //GeomInteraction::AddSub(c);
}

Ctrl* Ctrl::GetLastChild() {
	TODO //return CastPtr<Ctrl>(sub.Top());
}

void Ctrl::RemoveChild(Ctrl* c) {
	TODO //GeomInteraction2D::RemoveSub(c);
}

Ctrl* Ctrl::GetParent() {
	TODO /*if (!owner)
		return 0;
	return CastPtr<Ctrl>(owner);*/
}

Ctrl* Ctrl::GetTopCtrl() {
	TODO
	/*Ctrl* c = this;
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
	return c;*/
}

Ctrl* Ctrl::GetIndexChild(int i) {
	TODO //return CastPtr<Ctrl>(sub[i]);
}

int Ctrl::GetChildCount() const {
	TODO //return sub.GetCount();
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
	TODO //SetFrameRect(r);
	//SetPendingRedrawDeep();
}

void Ctrl::SetRect(int x, int y, int cx, int cy) {
	SetRect(RectC(x,y,cx,cy));
}

void Ctrl::SetFrameBox(const Rect& r) {
	TODO //this->frame_r = r;
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
	TODO //
	/*ASSERT(frame_r.Contains(content_r));
	return content_r;*/
}

Point Ctrl::GetContentPoint(const Point& pt) {
	TODO
	/*Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	return cpt;*/
}

void Ctrl::MouseMoveInFrameContent(Point pt, dword keyflags) {
	TODO
	/*Point ftl = frame_r.TopLeft();
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
	}*/
}

void Ctrl::DeepMouseMoveInFrameContent(Point pt, dword keyflags) {
	TODO
	/*Point ftl = frame_r.TopLeft();
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
	}*/
}

bool Ctrl::MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) {
	TODO
	/*Point ftl = frame_r.TopLeft();
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
	
	return false;*/
}

void Ctrl::MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags) {
	TODO //
	/*Point ftl = frame_r.TopLeft();
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
	}*/
}

void Ctrl::MouseLeaveFrame() {
	TODO //
	/*CtrlFrame* frame_with_mouse = GetFrameWithMouse();
	if (frame_with_mouse) {
		frame_with_mouse->has_mouse = false;
		frame_with_mouse->MouseLeave();
		SetFrameWithMouse(NULL);
	}*/
}

bool Ctrl::MouseWheelInFrameContent(Point pt, int zdelta, dword keyflags) {
	TODO //
	/*Point ftl = frame_r.TopLeft();
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
	return false;*/
}

void Ctrl::SetFocus() {
	TODO //
	/*Ctrl* tw = GetTopCtrl();
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
	
	GeomInteraction::SetFocus();*/
}

void Ctrl::Refresh() {
	TODO //GeomInteraction2D::Refresh();
}

void Ctrl::RefreshFrame() {
	TODO //RefreshFrame(Rect(GetRect().Size()).Inflated(overpaint));
}

void Ctrl::RefreshFrame(const Rect& r) {
	TODO //
	/*if(!top) {
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
	}*/
}

void Ctrl::DeepUnfocus() {
	TODO //
	/*if (has_focus) {
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
	}*/
}



bool Ctrl::IsCtrl() const {
	return true;
}

Ctrl* Ctrl::GetCaptured() {
	TODO //
	/*Ctrl* top = GetTopCtrl();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetCaptured();
		Ctrl* c = CastPtr<Ctrl>(gi);
		return c;
	}
	return 0;*/
}

Ctrl* Ctrl::GetWithMouse() {
	TODO //
	/*Ctrl* top = GetTopCtrl();
	if (top && top->IsCaptureRoot()) {
		GeomInteraction* gi = top->GetWithMouse();
		Ctrl* c = CastPtr<Ctrl>(gi);
		return c;
	}
	return 0;*/
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
	TODO //if (!GetFrameBox().IsEmpty())
	//	DeepLayout();
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
	TODO //
	/*CtrlFrame* f = 0;
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<CtrlFrame>(wm->GetFrameCaptured());
	return f;*/
}

CtrlFrame* Ctrl::GetFrameWithMouse() {
	TODO //
	/*CtrlFrame* f = 0;
	Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		f = CastPtr<CtrlFrame>(wm->GetFrameWithMouse());
	return f;*/
}

void Ctrl::SetFrameCaptured(CtrlFrame* c) {
	TODO //
	/*Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameCaptured(c);*/
}

void Ctrl::SetFrameWithMouse(CtrlFrame* c) {
	TODO //
	/*Parallel::WindowManager* wm = CastPtr<Parallel::WindowManager>(GetGeomDrawBegin());
	if (wm)
		wm->SetFrameWithMouse(c);*/
}




void Ctrl::DeepFrameLayout() {
	TODO //
	/*Size sz(frame_r.GetSize());
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		CtrlFrame& f = *frames[i];
		f.FrameLayout(new_content_r);
	}
	content_r = new_content_r;*/
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
	TODO //
	/*SetModify();
	Updated();*/
}

void Ctrl::PaintPreFrame(ProgPainter& pp) {
	TODO //
	/*Size sz = GetFrameSize();
	ASSERT(!sz.IsEmpty());
	Rect new_content_r(sz);
	for(int i = 0; i < frames.GetCount(); i++) {
		CtrlFrame& f = *frames[i];
		f.FramePaint(pp, new_content_r);
		f.FrameLayout(new_content_r);
	}
	if (frames.GetCount())
		pp.Clipoff(new_content_r);
	content_r = new_content_r;*/
}

void Ctrl::PaintPostFrame(ProgPainter& pp) {
	if (frames.GetCount())
		pp.End();
}

void Ctrl::PaintDebug(ProgPainter& pp) {
	TODO //
	/*Size sz = GetFrameSize();
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
	}*/
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
	TODO //SetPendingRedraw();
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
	TODO //SetPendingRedraw();
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

Ctrl& Ctrl::BottomPosZ(int i, int size) {
	pos.htype = LogPos::BOTTOM;
	pos.b = i;
	pos.h = size;
	return *this;
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

bool Ctrl::Is2D() const {
	return true;
}

Ctrl* Ctrl::Get2D() {
	return this;
}

Image Ctrl::FrameMouseEvent(int event, Point p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

Image Ctrl::MouseEvent(int event, Point p, int zdelta, dword keyflags) {
	return DefaultImages::Arrow;
}

void Ctrl::MouseEnter(Point frame_p, dword keyflags) {
	if (do_debug_draw)
		Refresh();
}

Image Ctrl::CursorImage(Point p, dword keyflags) {
	return DefaultImages::Arrow;
}

Rect Ctrl::GetRect() const {
	TODO
}

Size Ctrl::GetSize() const {
	TODO
}

bool Ctrl::HasMouse() const {
	TODO
}

String Ctrl::GetDesc() const {
	TODO
}

void Ctrl::Updated() {
	TODO
}

void Ctrl::Layout() {
	TODO
}

void Ctrl::LostFocus() {
	TODO
}

void Ctrl::CancelMode() {
	TODO
}

void Ctrl::Close() {
	TODO
}

void Ctrl::GotFocus() {
	TODO
}

void Ctrl::MouseLeave() {
	TODO
}

bool Ctrl::SetCapture() {
	TODO
}

bool Ctrl::ReleaseCapture() {
	TODO
}

void Ctrl::Show(bool b) {
	TODO
}

bool Ctrl::HasCapture() const {
	TODO
}

bool Ctrl::HotKey(dword key) {
	TODO
}

bool Ctrl::Key(dword key, int count) {
	TODO
}

#if 0
int Ctrl::GetCount() const {
	return sub.GetCount();
}

Ctrl* Ctrl::At(int i) {
	return CastPtr<Ctrl>(sub[i]);
}

bool Ctrl::MouseMoveInFrame(Point pt, dword keyflags) {
	if (HasCapture()) {
		//GeomInteraction* cap = CastPtr<Ctrl>(GetCaptured());
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
					Ctrl* c2 = c->Get2D();
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

void Ctrl::DeepMouseMoveInFrameContent(Point pt, dword keyflags) {
	
}

void Ctrl::MouseEventInFrameContent(int mouse_code, const Point& pt, dword keyflags) {
	
}

bool Ctrl::MouseWheelInFrameContent(Point p, int zdelta, dword keyflags) {
	return false;
}

bool Ctrl::DeepMouseMoveInFrame(Point pt, dword keyflags) {
	Rect content_r = GetContentRect();
	Point ftl = frame_r.TopLeft();
	Point ctl = content_r.TopLeft();
	Point fpt = pt - ftl;
	Point cpt = fpt - ctl;
	
	DeepMouseMoveInFrameContent(pt, keyflags);
	
	for(int i = sub.GetCount()-1; i >= 0; i--) {
		Ctrl* c = sub[i]->Get2D();
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

bool Ctrl::DeepMouseMove(const Point& pt, dword keyflags) {
	int deep_count = 0;
	for(int i = sub.GetCount()-1; i >= 0; i--) {
		Ctrl* c = sub[i]->Get2D();
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
		Ctrl* cap2 = CastPtr<Ctrl>(captured);
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

Rect Ctrl::GetContentRect() const {
	return frame_r.GetSize();
}

Point Ctrl::GetContentPoint(const Point& pt) {
	Point ctl = frame_r.TopLeft();
	return pt - ctl;
}

bool Ctrl::DeepMouseDispatch(int mouse_code, const Point& cpt, dword keyflags) {
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

bool Ctrl::DeepMouse(int mouse_code, const Point& pt, dword keyflags) {
	if (GetCaptured()) {
		#if 1
		Ctrl* c2 = GetCaptured()->Get2D();
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
				Ctrl* c = sub[i]->Get2D();
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

bool Ctrl::DeepMouseWheel(const Point& pt, int zdelta, dword keyflags) {
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
				Ctrl* c = sub[i]->Get2D();
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

bool Ctrl::MouseWheelInFrame(Point pt, int zdelta, dword keyflags) {
	if (frame_r.Contains(pt)) {
		Rect content_r = GetContentRect();
		Point ftl = frame_r.TopLeft();
		Point ctl = content_r.TopLeft();
		Point fpt = pt - ftl;
		Point cpt = fpt - ctl;
		
		if (content_r.Contains(fpt)) {
			for(int i = sub.GetCount()-1; i >= 0; i--) {
				Ctrl* c = sub[i]->Get2D();
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

void Ctrl::SetFrameBox(const Rect& r) {
	#if 0
	GeomInteraction* gi = GetOwner();
	if (gi) {
		Ctrl* gi2 = CastPtr<Ctrl>(gi);
		Rect parent_rect = gi2->GetRect();
		int parent_width = parent_rect.Width();
		ASSERT(r.right <= parent_width);
	}
	#endif
	this->frame_r = r;
	this->SetPendingLayout();
}

bool Ctrl::Redraw(bool only_pending) {
	Ctrl* content = this;
	//Ctrl* linked = CastPtr<Ctrl>(GetDynamicallyLinked());
	/*if (linked) {
		content = linked;
	}*/
	
	bool did_draw = false;
	bool was_pending_fx_redraw = pending_fx_redraw;
	bool frame = IsGeomDrawBegin();
	bool draw_begin = false;
	Size sz = GetFrameSize();
	
	TODO
	#if 0
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
		
		const char* dbg_class_name = GetDynamicName();
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
	#endif
	
	return did_draw;
}

bool Ctrl::MouseEventInFrameCaptured(int mouse_code, const Point& pt, dword keyflags) {
	return false;
}

bool Ctrl::MouseEventInFrame(int mouse_code, const Point& pt, dword keyflags) {
	if (frame_r.Contains(pt)) {
		Rect content_r = GetContentRect();
		Point ftl = frame_r.TopLeft();
		Point ctl = content_r.TopLeft();
		Point fpt = pt - ftl;
		Point cpt = fpt - ctl;
		
		if (content_r.Contains(fpt)) {
			for(int i = sub.GetCount()-1; i >= 0; i--) {
				Ctrl* c = sub[i]->Get2D();
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

void Ctrl::DeepLayout() {
	//Ctrl* linked = CastPtr<Ctrl>(GetDynamicallyLinked());
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
		Ctrl* c2 = c->Get2D();
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

bool Ctrl::Dispatch(const CtrlEvent& e) {
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

Ctrl* Ctrl::GetAbsoluteDrawBegin() {
	GeomInteraction* proxy = FindProxy();
	if (proxy)
		return CastPtr<Ctrl>(proxy);
	return 0;
}

void Ctrl::Refresh() {
	GeomInteraction::Refresh();
	
	Ctrl* proxy = GetAbsoluteDrawBegin();
	if (proxy) {
		TODO
		/*AbsoluteInterface* aiface = CastPtr<AbsoluteInterface>(proxy);
		if (aiface)
			aiface->SetPendingPartialRedraw();*/
	}
}

Point Ctrl::GetFramePointBetween(Ctrl& top_owner, Ctrl& deep_sub, const Point& pt) {
	Point tl_sum(0,0);
	
	// The "deep_sub" node is not counted in, so we consider it's owner only
	GeomInteraction* ds_owner = deep_sub.GetOwner();
	ASSERT(ds_owner); if (!ds_owner) return Point(0,0);
	
	Ctrl* iter = ds_owner->Get2D();
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

#endif

END_UPP_NAMESPACE
