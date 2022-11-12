#include "Internal.h"

#if HAVE_WINDOWSYSTEM

NAMESPACE_ECS_BEGIN



//Shader CoreWindow::window_shader;



Point CoreWindow::GetGlobalMouse() {
	/*if (!is_global_mouse_override)
		return SDL2::GetGlobalMouse();
	else
		return global_mouse;*/
	TODO
}

void CoreWindow::ResizeFrame::FrameLayout(Rect& r) {
	sz = r.GetSize();
	r.left += frame_width;		r.right -= frame_width;
	r.top += frame_width;		r.bottom -= frame_width;
}

void CoreWindow::ResizeFrame::FramePaint(Draw& w, const Rect& r) {
	Size sz(r.GetSize());
	Color c = !is_active ? Color(255, 64, 64) : Color(0, 0, 255);
	w.DrawRect(r.left, r.top, frame_width, sz.cy, c);
	w.DrawRect(r.right - frame_width, r.top, frame_width, sz.cy, c);
	w.DrawRect(r.left, r.top, sz.cx, frame_width, c);
	w.DrawRect(r.left, r.bottom - frame_width, sz.cx, frame_width, c);
}

void CoreWindow::ResizeFrame::FrameAddSize(Size& sz) {

}

int CoreWindow::ResizeFrame::GetArea(Point pt) {
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

void CoreWindow::ResizeFrame::MouseEnter(Point frame_p, dword keyflags) {

}

void CoreWindow::ResizeFrame::ContinueGlobalMouseMomentum() {
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

void CoreWindow::ResizeFrame::DoResize() {
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

void CoreWindow::ResizeFrame::MouseMove(Point frame_p, dword keyflags) {
	if (is_resizing) {
		CoreWindow* cw = ctrl->GetTopWindow()->GetWindow();
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
				Ctrl::OverrideCursor(WindowsImg::nwse());
				break;
			case TR:
			case BL:
				Ctrl::OverrideCursor(WindowsImg::nesw());
				break;
			case TOP:
			case BOTTOM:
				Ctrl::OverrideCursor(WindowsImg::ns());
				break;
			case LEFT:
			case RIGHT:
				Ctrl::OverrideCursor(WindowsImg::ew());
				break;
		}
	}
}

void CoreWindow::ResizeFrame::MouseLeave() {
	if (is_resizing) ReleaseCapture();
	is_resizing = false;
	Ctrl::DefaultCursor();
}

void CoreWindow::ResizeFrame::LeftDown(Point p, dword keyflags) {
	is_resizing = true;
	resize_start_pt = ctrl->GetWindow()->GetGlobalMouse();
	resize_area = GetArea(p);
	resize_start_r = win->frame_r;
	SetCapture();
}

void CoreWindow::ResizeFrame::LeftUp(Point p, dword keyflags) {
	is_resizing = false;
	ReleaseCapture();
}





CoreWindow::CoreWindow() : stored_rect(0,0,0,0), decor(this) {
	tw = 0;
	resize_frame.win = this;
	SetMaximized(false);
	
	
	/*cmd_screen_begin.next = &cmd_begin;
	cmd_begin.prev = &cmd_screen_begin;
	
	cmd_end.next = &cmd_screen_end;
	cmd_screen_end.prev = &cmd_end;*/
	
	
	AddFrame(resize_frame);
	Add(decor.SizePos());
	SetFrameRect(RectC(0, 0, 320, 240));
	
	close.SetImage(WindowsImg::close());
	maximize.SetImage(WindowsImg::maximize());
	minimize.SetImage(WindowsImg::minimize());
	
	Add(close.TopPos(3, 19).RightPos(3, 19));
	Add(maximize.TopPos(3, 19).RightPos(3+22, 19));
	Add(minimize.TopPos(3, 19).RightPos(3+22+19, 19));
	
	/*decor.WhenWindowMove = Proxy(WhenWindowMove);
	decor.WhenFocus = THISBACK(FocusEvent);
	decor.WhenMaximize = THISBACK(Maximize);
	decor.WhenMinimize = Proxy(WhenMinimize);
	decor.WhenClose = Proxy(WhenClose);
	*/
	close.WhenAction = THISBACK(Close);
	maximize.WhenAction = THISBACK(ToggleMaximized);
	minimize.WhenAction = THISBACK(Minimize);
	
	
	/*shader = Shader::NewDefault();
	if (!shader->IsLoaded()) {
		shader->Load(
			FindLocalFile("shaders" DIR_SEPS "shader->vs"),
			FindLocalFile("shaders" DIR_SEPS "shader->fs"));
	}*/
}

void CoreWindow::SetMaximized(bool b) {
	maximized = b;
	resize_frame.SetActive(!b);
}

void CoreWindow::SetContent(Windows* wins, int id) {
	this->wins = wins;
	this->id = id;
	
	if (tw) {
		Add(tw->VSizePos(24, 1).HSizePos(1, 1));
	
		tw->SetFocus();
	}
	
	if (maximized) {
		maximized = false;
		Maximize();
	}
}

bool CoreWindow::IsActive() const {bool b = false; wins->IsActiveWindow(&b, id); return b;}
void CoreWindow::MoveWindow(Point pt) {wins->MoveWindow(pt, id);}
void CoreWindow::Maximize() {if (wins) {wins->MaximizeWindow(id); wins->FocusWindow(id);} maximized = true;}
void CoreWindow::Restore()  {if (wins) {wins->RestoreWindow(id); wins->FocusWindow(id);} maximized = false;}
void CoreWindow::Minimize() {if (wins) {wins->MinimizeWindow(id); wins->FocusWindow(id);}}
void CoreWindow::Close() {wins->QueueCloseWindow(id);}
void CoreWindow::FocusEvent() {wins->FocusWindow(id); tw->FocusEvent();}
bool CoreWindow::IsCtrlDrawBegin() {return true;}

void CoreWindow::SetFrameRect(const Rect& r) {
	Ctrl::SetFrameRect(r);
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
}

bool CoreWindow::Redraw(bool only_pending) {
	return Ctrl::Redraw(only_pending);
}

void CoreWindow::LeftDown(Point p, dword keyflags) {
	FocusEvent();
	
}

void CoreWindow::ChildGotFocus() {
	FocusEvent();
	
}

void CoreWindow::ChildMouseEvent(Ctrl *child, int event, Point p, int zdelta, dword keyflags) {
	
	if (event == MOUSE_LEFTDOWN) {
		FocusEvent();
	}
	
}

void CoreWindow::Wait() {
	TODO
}














WindowDecoration::WindowDecoration(CoreWindow* win) : win(win) {
	left_down = false;
	
}
	
void WindowDecoration::Paint(Draw& id) {
	Color border_tl = GrayColor(128+64);
	Color border_br = GrayColor(128);
	
	Size sz(GetFrameSize());
	id.DrawRect(sz, White());
	id.DrawLine(0,0, 0, sz.cy-1, 1, border_tl);
	id.DrawLine(0,0, sz.cx-1, 0, 1, border_tl);
	id.DrawLine(sz.cx-1,0, sz.cx-1, sz.cy-1, 1, border_br);
	id.DrawLine(0,sz.cy-1, sz.cx-1, sz.cy-1, 1, border_br);
	
	Color left, right;
	if (CastPtr<CoreWindow>(GetParent())->IsActive()) {
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
	bar.Add("Maximize / Restore", callback(win, &CoreWindow::Maximize));
	bar.Add("Minimize", callback(win, &CoreWindow::Minimize));
	bar.Separator();
	bar.Add("Close", callback(win, &CoreWindow::Close));
}


NAMESPACE_ECS_END

#endif
