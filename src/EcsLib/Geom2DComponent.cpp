#include "EcsLib.h"


#if HAVE_WINDOWSYSTEM

NAMESPACE_ECS_BEGIN







//Shader Geom2DComponent::window_shader;

Geom2DComponent::Geom2DComponent() :
	//decor(this),
	stored_rect(0,0,0,0)
{
	//aw = 0;
	//resize_frame.win = this;
	SetMaximized(false);
	
	
	//AddFrame(resize_frame);
	/*Add(decor);
	SetFrameRect(RectC(0, 0, 320, 240));
	
	close.SetImage(WindowsImg::close());
	maximize.SetImage(WindowsImg::maximize());
	minimize.SetImage(WindowsImg::minimize());
	
	Add(close.TopPos(3, 19).RightPos(3, 19));
	Add(maximize.TopPos(3, 19).RightPos(3+22, 19));
	Add(minimize.TopPos(3, 19).RightPos(3+22+19, 19));*/
	
	/*decor.WhenWindowMove = Proxy(WhenWindowMove);
	decor.WhenFocus = THISBACK(FocusEvent);
	decor.WhenMaximize = THISBACK(Maximize);
	decor.WhenMinimize = Proxy(WhenMinimize);
	decor.WhenClose = Proxy(WhenClose);
	*/
	
	/*close.WhenAction = THISBACK(Close);
	maximize.WhenAction = THISBACK(ToggleMaximized);
	minimize.WhenAction = THISBACK(Minimize);
	*/
}

void Geom2DComponent::Etherize(Ether& e) {
	TODO // ptrs & refs
	
	e % stored_rect
	  % id
	  % pending_partial_redraw;
	
	
}

void Geom2DComponent::Initialize() {
	
}

void Geom2DComponent::Uninitialize() {
	transform.Clear();
	transform2d.Clear();
	
	if (linked) linked->Unlink(this);
}

void Geom2DComponent::operator=(const Geom2DComponent& cw) {
	Clear();
	reset_fn = cw.reset_fn;
	SetFrameRect(cw.frame_r);
	if (reset_fn)
		(*this.*reset_fn)();
}

void Geom2DComponent::Clear() {
	//if (!aw) return;
	ClearSub();
	//aw = 0;
	//owned_aw.Clear();
}

/*void Geom2DComponent::Title(String label) {
	decor.SetLabel(label);
}

void Geom2DComponent::StoreRect() {
	stored_rect = GetFrameRect();
}*/

void Geom2DComponent::LoadRect() {
	ASSERT(stored_rect.bottom && stored_rect.right);
	SetFrameRect(stored_rect);
}

void Geom2DComponent::SetStoredRect(Rect r) {
	stored_rect = r;
}

void Geom2DComponent::SetPendingPartialRedraw() {
	pending_partial_redraw = true;
}

int Geom2DComponent::GetId() const {
	return id;
}

Rect Geom2DComponent::GetStoredRect() const {
	return stored_rect;
}

/*String Geom2DComponent::GetTitle() const {
	return decor.GetLabel();
}*/

void Geom2DComponent::Layout() {
	Size sz = frame_r.GetSize();
	ASSERT(!sz.IsEmpty());
	Rect decor_r = RectC(0,0, sz.cx, 20);
	TODO //decor.SetFrameRect(decor_r);
	
}

/*Absolute2DInterface* Geom2DComponent::GetAbsolute2D() {
	return this;
}*/

bool Geom2DComponent::IsMaximized() const {
	return maximized;
}

void Geom2DComponent::ToggleMaximized() {
	if (IsMaximized())
		Restore();
	else
		Maximize();
}

bool Geom2DComponent::IsPendingPartialRedraw() const {
	return pending_partial_redraw;
}

Point Geom2DComponent::GetGlobalMouse() {
	/*if (!is_global_mouse_override)
		return SDL2::GetGlobalMouse();
	else
		return global_mouse;*/
	TODO
}

#if 0

void Geom2DComponent::ResizeFrame::FrameLayout(Rect& r) {
	sz = r.GetSize();
	r.left += frame_width;		r.right -= frame_width;
	r.top += frame_width;		r.bottom -= frame_width;
}

void Geom2DComponent::ResizeFrame::FramePaint(Draw& w, const Rect& r) {
	Size sz(r.GetSize());
	Color c = !is_active ? Color(255, 64, 64) : Color(0, 0, 255);
	w.DrawRect(r.left, r.top, frame_width, sz.cy, c);
	w.DrawRect(r.right - frame_width, r.top, frame_width, sz.cy, c);
	w.DrawRect(r.left, r.top, sz.cx, frame_width, c);
	w.DrawRect(r.left, r.bottom - frame_width, sz.cx, frame_width, c);
}

void Geom2DComponent::ResizeFrame::FrameAddSize(Size& sz) {

}

int Geom2DComponent::ResizeFrame::GetArea(Point pt) {
	if (pt.x < frame_width) {
		if (pt.y < corner_width)
			return TL;
		else if (pt.y >= sz.cy - corner_width)
			return BL;
		else
			return LEFT;
	}
	else if (pt.x >= sz.cx - frame_width) {
		if (pt.y < corner_width)
			return TR;
		else if (pt.y >= sz.cy - corner_width)
			return BR;
		else
			return RIGHT;
	}
	else {
		if (pt.y < frame_width)
			return TOP;
		else if (pt.y >= sz.cy - frame_width)
			return BOTTOM;
		else
			return CENTER;
	}
}

void Geom2DComponent::ResizeFrame::MouseEnter(Point frame_p, dword keyflags) {

}

void Geom2DComponent::ResizeFrame::ContinueGlobalMouseMomentum() {
	if (is_resizing) {
		/*switch (resize_area) {
			case CENTER:
				break;
			case TL:
				if (resize_diff.x > 0) resize_diff.x * -1;
				if (resize_diff.y > 0) resize_diff.y * -1;
				break;
			case TR:
				if (resize_diff.x < 0) resize_diff.x * -1;
				if (resize_diff.y > 0) resize_diff.y * -1;
				break;
			case BL:
				if (resize_diff.x > 0) resize_diff.x * -1;
				if (resize_diff.y < 0) resize_diff.y * -1;
				break;
			case BR:
				if (resize_diff.x < 0) resize_diff.x * -1;
				if (resize_diff.y < 0) resize_diff.y * -1;
				break;
			case TOP:
				if (resize_diff.y > 0) resize_diff.y * -1;
				break;
			case BOTTOM:
				if (resize_diff.y < 0) resize_diff.y * -1;
				break;
			case LEFT:
				if (resize_diff.x > 0) resize_diff.x * -1;
				break;
			case RIGHT:
				if (resize_diff.x < 0) resize_diff.x * -1;
				break;/
		}*/
		/*resize_diff.x = min(max(-1, resize_diff.x), +1);
		resize_diff.y = min(max(-1, resize_diff.y), +1);*/
		int c = 1;
		switch (resize_area) {
			case CENTER:
				break;
			case TL:
				resize_diff.x = -c;
				resize_diff.y = -c;
				break;
			case TR:
				resize_diff.x = +c;
				resize_diff.y = -c;
				break;
			case BL:
				resize_diff.x = -c;
				resize_diff.y = +c;
				break;
			case BR:
				resize_diff.x = +c;
				resize_diff.y = +c;
				break;
			case TOP:
				resize_diff.y = -c;
				break;
			case BOTTOM:
				resize_diff.y = +c;
				break;
			case LEFT:
				resize_diff.x = -c;
				break;
			case RIGHT:
				resize_diff.x = +c;
				break;
		}
		resize_start_pt += resize_diff;
		resize_start_r = win->frame_r;
		DoResize();
		used_momentum = true;
	}
}

void Geom2DComponent::ResizeFrame::DoResize() {
	Rect new_frame_r = resize_start_r;
	switch (resize_area) {
		case CENTER:
			break;
		case TL:
			new_frame_r.left += resize_diff.x;
			new_frame_r.top += resize_diff.y;
			break;
		case TR:
			new_frame_r.right += resize_diff.x;
			new_frame_r.top += resize_diff.y;
			break;
		case BL:
			new_frame_r.left += resize_diff.x;
			new_frame_r.bottom += resize_diff.y;
			break;
		case BR:
			new_frame_r.right += resize_diff.x;
			new_frame_r.bottom += resize_diff.y;
			break;
		case TOP:
			new_frame_r.top += resize_diff.y;
			break;
		case BOTTOM:
			new_frame_r.bottom += resize_diff.y;
			break;
		case LEFT:
			new_frame_r.left += resize_diff.x;
			break;
		case RIGHT:
			new_frame_r.right += resize_diff.x;
			break;
	}
	if (new_frame_r.Width() < 100) new_frame_r.right = new_frame_r.left + 100;
	if (new_frame_r.Height() < 60) new_frame_r.bottom = new_frame_r.top + 60;
	
	win->SetFrameRect(new_frame_r);
	win->SetPendingEffectRedraw();
	win->SetPendingLayout();
	win->SetPendingRedraw();
}

void Geom2DComponent::ResizeFrame::MouseMove(Point frame_p, dword keyflags) {
	if (is_resizing) {
		Geom2DComponent* cw = ctrl->GetTopWindow()->GetAbsolute2D()->GetWindow();
		if (used_momentum) {
			resize_start_pt = cw->GetGlobalMouse();
			used_momentum = false;
		}
		resize_diff = cw->GetGlobalMouse() - resize_start_pt;
		DoResize();
	}
	else {
		int area = GetArea(frame_p);
		
		switch (area) {
			case CENTER:
				break;
			case TL:
			case BR:
				Absolute2D::OverrideCursor(WindowsImg::nwse());
				break;
			case TR:
			case BL:
				Absolute2D::OverrideCursor(WindowsImg::nesw());
				break;
			case TOP:
			case BOTTOM:
				Absolute2D::OverrideCursor(WindowsImg::ns());
				break;
			case LEFT:
			case RIGHT:
				Absolute2D::OverrideCursor(WindowsImg::ew());
				break;
		}
	}
}

void Geom2DComponent::ResizeFrame::MouseLeave() {
	if (is_resizing) ReleaseCapture();
	is_resizing = false;
	Absolute2D::DefaultCursor();
}

void Geom2DComponent::ResizeFrame::LeftDown(Point p, dword keyflags) {
	is_resizing = true;
	resize_start_pt = ctrl->GetWindow()->GetGlobalMouse();
	resize_area = GetArea(p);
	resize_start_r = win->frame_r;
	SetCapture();
}

void Geom2DComponent::ResizeFrame::LeftUp(Point p, dword keyflags) {
	is_resizing = false;
	ReleaseCapture();
}

#endif




void Geom2DComponent::SetMaximized(bool b) {
	maximized = b;
	//resize_frame.SetActive(!b);
}

/*void Geom2DComponent::SetContent(Windows* wins, int id) {
	this->wins = wins;
	this->id = id;
	
	#if 0
	if (proxy) {
		Add(proxy->VSizePos(24, 1).HSizePos(1, 1));
		proxy->SetFocus();
	}
	#endif
	
	if (maximized) {
		maximized = false;
		Maximize();
	}
}*/


bool Geom2DComponent::IsActive() const
{
	TODO
	#if 0
	bool b = false;
	wins->IsActiveWindow ( &b, id );
	return b;
	#endif
}

void Geom2DComponent::MoveWindow ( Point pt )
{
	TODO
	#if 0
	wins->MoveWindow ( pt, id );
	#endif
}

void Geom2DComponent::Maximize()
{
	TODO
	#if 0
	if ( wins )
	{
		wins->MaximizeWindow ( id );
		wins->FocusWindow ( id );
	}

	maximized = true;
	#endif
}

void Geom2DComponent::Restore()
{
	TODO
	#if 0
	if ( wins )
	{
		wins->RestoreWindow ( id );
		wins->FocusWindow ( id );
	}

	maximized = false;
	#endif
}

void Geom2DComponent::Minimize()
{
	TODO
	#if 0
	if ( wins )
	{
		wins->MinimizeWindow ( id );
		wins->FocusWindow ( id );
	}
	#endif
}

/*void Geom2DComponent::Close()
{
	TODO
	#if 0
	wins->QueueCloseWindow ( id );
	#endif
}*/

/*void Geom2DComponent::FocusEvent()
{
	TODO
	#if 0
	wins->FocusWindow ( id );
	this->FocusEvent();
	#endif
}

bool Geom2DComponent::IsGeomDrawBegin()
{
	return true;
}*/


#if 0
void Geom2DComponent::SetFrameRect(const Rect& r) {
	Ctrl* c = GetWindowCtrl();
	if (c)
		c->SetFrameRect(r);
	cw->SetFrameRect(r);
}
#endif

/*void Geom2DComponent::SetFrameRect(const Rect& r) {
	GeomInteraction2D::SetFrameRect(r);
	if (!transform2d.IsEmpty()) {
		transform2d->position[0] = r.left;
		transform2d->position[1] = r.top;
		transform2d->size[0] = r.Width();
		transform2d->size[1] = r.Height();
	}
	if (!transform.IsEmpty()) {
		transform->data.position[0] = r.left;
		transform->data.position[1] = r.top;
		transform->size[0] = r.Width();
		transform->size[1] = r.Height();
	}
}*/

bool Geom2DComponent::Redraw(bool only_pending) {
	return GeomInteraction2D::Redraw(only_pending);
}

void Geom2DComponent::LeftDown(Point p, dword keyflags) {
	TODO //FocusEvent();
	
}

void Geom2DComponent::ChildGotFocus() {
	TODO //FocusEvent();
	
}

void Geom2DComponent::ChildMouseEvent(Ctrl *child, int event, Point p, int zdelta, dword keyflags) {
	
	TODO
	/*if (event == MOUSE_LEFTDOWN) {
		FocusEvent();
	}*/
	
}

void Geom2DComponent::Wait() {
	TODO
}

/*TopWindow* Geom2DComponent::GetTopWindow() const {
	if (!proxy)
		return 0;
	return CastPtr<TopWindow>(proxy);
}*/

void Geom2DComponent::Paint(Draw& id) {
	Size sz(GetFrameSize());
	ASSERT(!sz.IsEmpty());
	
	id.DrawRect(sz, GrayColor(128));
	
}












void Geom2DComponentLink::Etherize(Ether& e) {
	TODO // ptr
}

void Geom2DComponentLink::Initialize() {
	
}

void Geom2DComponentLink::Uninitialize() {
	if (linked) Unlink(linked);
	
}

void Geom2DComponentLink::Link(Geom2DComponent* cw) {
	ASSERT(!linked);
	if (linked) Unlink(linked);
	
	cw->linked = this;
	linked = cw;
}

void Geom2DComponentLink::Unlink() {
	if (linked) Unlink(linked);
}

void Geom2DComponentLink::Unlink(Geom2DComponent* cw) {
	ASSERT(!linked || linked == cw);
	if (linked == cw) {
		linked = 0;
		cw->linked = 0;
		
		EntityRef e = ComponentBase::GetEntity();
		e->Destroy();
	}
}

Geom2DComponent& Geom2DComponentLink::GetWindow() const {
	ASSERT(linked);
	return *linked;
}

	
	











#if 0
WindowDecoration::WindowDecoration(Geom2DComponent* win) : win(win) {
	left_down = false;
	
}
	
void WindowDecoration::Paint(Draw& id) {
	Color border_tl = GrayColor(128+64);
	Color border_br = GrayColor(128);
	
	Size sz(GetFrameSize());
	ASSERT(!sz.IsEmpty());
	
	id.DrawRect(sz, White());
	id.DrawLine(0,0, 0, sz.cy-1, 1, border_tl);
	id.DrawLine(0,0, sz.cx-1, 0, 1, border_tl);
	id.DrawLine(sz.cx-1,0, sz.cx-1, sz.cy-1, 1, border_br);
	id.DrawLine(0,sz.cy-1, sz.cx-1, sz.cy-1, 1, border_br);
	
	Color left, right;
	GeomInteraction* owner = GetOwner();
	Geom2DComponent* cw = CastPtr<Geom2DComponent>(owner);
	ASSERT(cw);
	if (!cw) return;
	if (cw->IsActive()) {
		left = Color(0, 64, 128);
		right = Color(57, 141, 195);
	} else {
		left = GrayColor();
		right = GrayColor(195);
	}
	/*if (sz.cx > 2) {
		// TODO Draw gradient
		for(int i = 0; i < sz.cx; i++) {
			int x = i;
			int alpha = 255 * i / (sz.cx -2);
			Color clr = Blend(left, right, alpha);
			id.DrawLine(i, 0, i, 23, 1, clr);
		}
	}*/
	id.DrawRect(0, 0, sz.cx, 23, left);
	id.DrawText(7, 4, label, StdFont(15), Black());
	id.DrawText(6, 3, label, StdFont(15), White());
	
	Color tl = GrayColor(128+64+32);
	Color br = GrayColor(128-64-32);
	
	id.DrawLine(0,0, sz.cx-1, 0, 1, tl);
	id.DrawLine(0,0, 0, sz.cy-1, 1, tl);
	id.DrawLine(sz.cx-1, sz.cy-1, sz.cx-1, 0, 1, br);
	id.DrawLine(sz.cx-1, sz.cy-1, 0, sz.cy-1, 1, br);
}

void WindowDecoration::LeftDown(Point p, dword keyflags) {
	left_down = true;
	left_down_pt = p;
	SetCapture();
	
	win->FocusEvent();
}

void WindowDecoration::LeftDouble(Point p, dword keyflags) {
	win->ToggleMaximized();
}

void WindowDecoration::LeftUp(Point p, dword keyflags) {
	left_down = false;
	ReleaseCapture();
	
}

void WindowDecoration::MouseMove(Point p, dword keyflags) {
	if (left_down) {
		win->MoveWindow(p - left_down_pt);
	}
}

void WindowDecoration::RightDown(Point p, dword keyflags) {
	MenuBar::Execute(THISBACK(LocalMenu));
}

void WindowDecoration::LocalMenu(Bar& bar) {
	bar.Add("Maximize / Restore", callback(win, &Geom2DComponent::Maximize));
	bar.Add("Minimize", callback(win, &Geom2DComponent::Minimize));
	bar.Separator();
	TODO //bar.Add("Close", callback(win, &Geom2DComponent::Close));
}
#endif


NAMESPACE_ECS_END

#endif
