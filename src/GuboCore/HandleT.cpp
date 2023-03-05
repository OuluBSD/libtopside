#include "GuboCore.h"


NAMESPACE_TOPSIDE_BEGIN

void DebugMainLoop();

NAMESPACE_TOPSIDE_END



NAMESPACE_PARALLEL_BEGIN


Image& WindowsImg::close() {
	static Image img;
	if (img.IsEmpty())
		img = StreamRaster::LoadFileAny(RealizeShareFile("imgs" DIR_SEPS "close.png"));
	return img;
}

Image& WindowsImg::maximize() {
	static Image img;
	if (img.IsEmpty())
		img = StreamRaster::LoadFileAny(RealizeShareFile("imgs" DIR_SEPS "maximize.png"));
	return img;
}

Image& WindowsImg::minimize() {
	static Image img;
	if (img.IsEmpty())
		img = StreamRaster::LoadFileAny(RealizeShareFile("imgs" DIR_SEPS "minimize.png"));
	return img;
}

Image& WindowsImg::nwse() {
	static Image img;
	if (img.IsEmpty()) {
		img = StreamRaster::LoadFileAny(RealizeShareFile("imgs" DIR_SEPS "nwse.png"));
		SetCenterHotSpot(img);
	}
	return img;
}

Image& WindowsImg::nesw() {
	static Image img;
	if (img.IsEmpty()) {
		img = StreamRaster::LoadFileAny(RealizeShareFile("imgs" DIR_SEPS "nesw.png"));
		SetCenterHotSpot(img);
	}
	return img;
}

Image& WindowsImg::ns() {
	static Image img;
	if (img.IsEmpty()) {
		img = StreamRaster::LoadFileAny(RealizeShareFile("imgs" DIR_SEPS "ns.png"));
		SetCenterHotSpot(img);
	}
	return img;
}

Image& WindowsImg::ew() {
	static Image img;
	if (img.IsEmpty()) {
		img = StreamRaster::LoadFileAny(RealizeShareFile("imgs" DIR_SEPS "ew.png"));
		SetCenterHotSpot(img);
	}
	return img;
}


template <class Dim>
HandleT<Dim>::HandleT() :
	decor(this)
{
	maximized = false;
	id = -1;
	
	this->Add(decor);
	
	Box box = Dim::GetDefaultHandleDimensions(40);
	this->SetFrameBox(box);
	
}

template <class Dim>
typename Dim::TopContainer* HandleT<Dim>::GetTopContainer() {
	auto* proxy = this->GetLinkedProxy();
	if (!proxy)
		return 0;
	return CastPtr<typename Dim::TopContainer>(proxy);
}

template <class Dim>
void HandleT<Dim>::SetInterface(InterfaceProxy& iface) {
	if (this->GetLinkedProxy()) {
		TODO // clear old
	}
	
	iface.SetTarget(*this);
	
	typename Dim::Interaction* iact = CastPtr<typename Dim::Interaction>(&iface);
	if (iact)
		Dim::Interaction::Add(*iact);
	// --> GetLinkedProxy()
}

template <class Dim>
void HandleT<Dim>::Paint(DrawT& draw) {
	TODO // permanent
}

template <>
void HandleT<Ctx2D>::Paint(DrawT& draw) {
	Color bg = GrayColor(128+64);
	Sz sz(this->GetFrameBox().GetSize());
	draw.DrawRect(sz, bg);
	
	if (!maximized) {
		Color hi = White();
		Color lo = Black();
		draw.DrawLine(0,0,sz.cx-1,0, 1, hi);
		draw.DrawLine(0,0,0,sz.cy-1, 1, hi);
		draw.DrawLine(0,sz.cy-1,sz.cx-1,sz.cy-1, 1, lo);
		draw.DrawLine(sz.cx-1,0,sz.cx-1,sz.cy-1, 1, lo);
	}
}

template <class Dim>
int HandleT<Dim>::GetFrameWidth() const {
	int frame_width = GetScope().GetFrameWidth();
	return maximized ? 0 : frame_width;
}

template <class Dim>
int HandleT<Dim>::GetCornerWidth() const {
	int corner_width = GetScope().GetCornerWidth();
	return maximized ? 0 : corner_width;
}

template <class Dim>
void HandleT<Dim>::Layout() {
	int title_h = 25;
	int border = GetFrameWidth();
	Box handle_box(this->GetFrameBox().GetSize());
	handle_box.left += border;
	handle_box.top += border;
	handle_box.right -= border;
	handle_box.bottom -= border;
	Sz handle_sz = handle_box.GetSize();
	ASSERT(!handle_sz.IsEmpty());
	Box decor_box = handle_box;
	decor_box.bottom = decor_box.top + title_h;
	decor.SetFrameBox(decor_box);
	
	typename Dim::Interaction* iact = CastPtr<typename Dim::Interaction>(this->GetLinkedProxy());
	if (iact) {
		Box content_box = handle_box;
		content_box.top = content_box.top + title_h;
		#if 0
		content_box.top += 5;
		content_box.bottom -= 5;
		content_box.left += 5;
		content_box.right -= 5;
		#endif
		iact->SetFrameBox(content_box);
	}
}

template <class Dim>
int HandleT<Dim>::GetArea(const Pt& pt) {
	int frame_width = GetFrameWidth();
	int corner_width = GetCornerWidth();
	Sz sz = this->GetFrameBox().GetSize();
	
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

template <class Dim>
Image HandleT<Dim>::OverrideCursor(const Image& m) {
	HandleSystem& sys = GetHandleSystem();
	Image cursor;
	if (sys.get_mouse_cursor) {
		cursor = sys.get_mouse_cursor(sys.get_mouse_cursor_arg);
	}
	if (sys.set_mouse_cursor) {
		sys.set_mouse_cursor(sys.set_mouse_cursor_arg, m);
	}
	cursor_overriden = true;
	return cursor;
}

template <class Dim>
Image HandleT<Dim>::DefaultCursor() {
	HandleSystem& sys = GetHandleSystem();
	Image cursor;
	if (sys.get_mouse_cursor) {
		cursor = sys.get_mouse_cursor(sys.get_mouse_cursor_arg);
	}
	if (sys.set_mouse_cursor) {
		sys.set_mouse_cursor(sys.set_mouse_cursor_arg, Image());
	}
	override_area = -1;
	cursor_overriden = false;
	return cursor;
}

template <class Dim>
void HandleT<Dim>::Title(const String& title) {
	decor.SetLabel(title);
}

template <class Dim>
typename Dim::Interface& HandleT<Dim>::Sizeable(bool b) {
	TODO
}

template <class Dim>
typename Dim::Interface& HandleT<Dim>::MaximizeBox(bool b) {
	TODO
}

template <class Dim>
typename Dim::Interface& HandleT<Dim>::MinimizeBox(bool b) {
	TODO
}

template <class Dim>
int HandleT<Dim>::Run(bool appmodal) {
	DebugMainLoop();
	return 0;
}

template <class Dim>
String HandleT<Dim>::GetTitle() const {
	return decor.GetLabel();
}

template <class Dim>
void HandleT<Dim>::SetPendingPartialRedraw() {
	pending_partial_redraw = true;
}

/*template <class Dim>
GeomInteraction* HandleT<Dim>::GetDynamicallyLinked() const {
	auto* abs_proxy = this->GetLinkedProxy();
	if (abs_proxy)
		return abs_proxy->GetInteraction();
	return 0;
}*/

template <class Dim>
ScopeT<Dim>& HandleT<Dim>::GetScope() const {
	ScopeT<Dim>* owner = this->GetParent().Get();
	ASSERT(owner);
	return *owner;
}

template <class Dim>
HandleSystemT<Dim>& HandleT<Dim>::GetHandleSystem() const {
	ScopeT<Dim>* owner0 = this->GetParent().Get();
	ASSERT(owner0);
	HandleSystemT<Dim>* owner1 = owner0->GetParent().Get();
	ASSERT(owner1);
	return *owner1;
}

template <class Dim>
void HandleT<Dim>::Close() {
	Scope& scope = GetScope();
	scope.QueueCloseHandle(id);
}

template <class Dim>
void HandleT<Dim>::Maximize() {
	Scope& scope = GetScope();
	scope.FocusHandlePos(id);
	scope.MaximizeHandle(id);
	maximized = true;
}

template <class Dim>
void HandleT<Dim>::Minimize() {
	Scope& scope = GetScope();
	scope.MinimizeHandle(id);
}

template <class Dim>
void HandleT<Dim>::CloseOthers() {
	Scope& scope = GetScope();
	scope.CloseOthers(id);
}

template <class Dim>
void HandleT<Dim>::SetMaximized(bool b) {
	maximized = b;
}

template <class Dim>
bool HandleT<Dim>::IsMaximized() const {
	return maximized;
}

template <class Dim>
bool HandleT<Dim>::IsActive() const {
	Scope& scope = this->GetScope();
	return scope.IsActiveHandle(id);
}

template <class Dim>
void HandleT<Dim>::StoreRect() {
	stored_box = this->GetFrameBox();
}

template <class Dim>
void HandleT<Dim>::LoadRect() {
	ASSERT(stored_box.bottom && stored_box.right);
	SetFrameBox(stored_box);
}

template <class Dim>
void HandleT<Dim>::ToggleMaximized() {
	if (IsMaximized())
		Restore();
	else
		Maximize();
}

template <class Dim>
bool HandleT<Dim>::IsPendingPartialRedraw() const {
	return pending_partial_redraw;
}

template <class Dim>
void HandleT<Dim>::Restore()
{
	Scope& scope = GetScope();
	scope.RestoreHandle(id);
	scope.FocusHandle(id);
	
	maximized = false;
}

template <class Dim>
void HandleT<Dim>::SetFrameBox(const Box& b) {
	// this method override is for debugging
	Dim::Interaction::SetFrameBox(b);
}

template <class Dim>
void HandleT<Dim>::MoveHandle(Pt pt) {
	Scope& scope = GetScope();
	scope.MoveHandle( pt, id );
}

template <class Dim>
void HandleT<Dim>::CheckMouseBorder(const Pt& pt) {
	int area = GetArea(pt);
	
	switch (area) {
	case TL:
	case BR:
		if (area != override_area) {
			override_area = area;
			this->OverrideCursor(WindowsImg::nwse());
		}
		break;
	case TR:
	case BL:
		if (area != override_area) {
			override_area = area;
			this->OverrideCursor(WindowsImg::nesw());
		}
		break;
	case TOP:
	case BOTTOM:
		if (area != override_area) {
			override_area = area;
			this->OverrideCursor(WindowsImg::ns());
		}
		break;
	case LEFT:
	case RIGHT:
		if (area != override_area) {
			override_area = area;
			this->OverrideCursor(WindowsImg::ew());
		}
		break;
	case CENTER:
	default:
		if (cursor_overriden)
			DefaultCursor();
	}
}

template <class Dim>
bool HandleT<Dim>::DeepMouseMove(const Pt& pt, dword keyflags) {
	Box frame_r = this->GetFrameBox();
	if (frame_r.Contains(pt)) {
		//Box content_r = this->GetContentRect();
		Pt ftl = FirstCorner(frame_r);
		Pt fpt = pt - ftl;
		//Point ctl = content_r.TopLeft();
		//Point cpt = fpt - ctl;
		CheckMouseBorder(fpt);
	}
	
	return Interaction::DeepMouseMove(pt, keyflags);
}

template <class Dim>
void HandleT<Dim>::MouseMove(Pt pt, dword keyflags) {
	if (is_resizing) {
		if (used_momentum) {
			resize_start_pt = GetGlobalMouse();
			used_momentum = false;
		}
		resize_diff = GetGlobalMouse() - resize_start_pt;
		DoResize();
	}
	CheckMouseBorder(pt);
}

template <class Dim>
GeomInteraction* HandleT<Dim>::GetProxy() const {
	auto proxy = this->GetLinkedProxy();
	return CastPtr<GeomInteraction>(proxy);
}

template <class Dim>
void HandleT<Dim>::MouseLeave() {
	ReleaseResize();
	
	if (cursor_overriden)
		DefaultCursor();
}

template <class Dim>
void HandleT<Dim>::DeepMouseLeave() {
	if (cursor_overriden)
		DefaultCursor();
}

template <class Dim>
typename Dim::Pt HandleT<Dim>::GetGlobalMouse() const {
	return GetScope().GetGlobalMouse();
}

template <class Dim>
void HandleT<Dim>::CaptureResize(const Pt& p) {
	int area = GetArea(p);
	if (area != CENTER) {
		is_resizing = true;
		resize_start_pt = GetGlobalMouse();
		resize_area = GetArea(p);
		resize_start_r = this->GetFrameBox();
		this->SetCapture();
	}
}

template <class Dim>
void HandleT<Dim>::ReleaseResize() {
	if (is_resizing) {
		this->ReleaseCapture();
		is_resizing = false;
	}
}

template <class Dim>
void HandleT<Dim>::LeftDown(Pt p, dword keyflags) {
	CaptureResize(p);
	
}

template <class Dim>
void HandleT<Dim>::LeftUp(Pt p, dword keyflags) {
	ReleaseResize();
	
}

template <class Dim>
void HandleT<Dim>::ContinueGlobalMouseMomentum() {
	if (is_resizing) {
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
		resize_start_r = this->GetFrameBox();
		DoResize();
		used_momentum = true;
	}
}

template <class Dim>
void HandleT<Dim>::DoResize() {
	Box new_frame_r = resize_start_r;
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
	
	this->SetFrameBox(new_frame_r);
	this->Refresh();
}
















template <class Dim>
GeomDecorationT<Dim>::GeomDecorationT(Handle* h) {
	handle = h;
	
	close->SetImage(WindowsImg::close());
	maximize->SetImage(WindowsImg::maximize());
	minimize->SetImage(WindowsImg::minimize());
	
	this->Add(close.TopPos(3, 19).RightPos(3, 19));
	this->Add(maximize.TopPos(3, 19).RightPos(3+22, 19));
	this->Add(minimize.TopPos(3, 19).RightPos(3+22+19, 19));
	
	close->WhenAction = callback(h, &Handle::Close);
	maximize->WhenAction = callback(h, &Handle::ToggleMaximized);
	minimize->WhenAction = callback(h, &Handle::Minimize);
	
}

template <class Dim>
void GeomDecorationT<Dim>::Paint(DrawT& draw) {
	TODO // permanent
}

template <>
void GeomDecorationT<Ctx2D>::Paint(DrawT& id) {
	Size sz(GetFrameSize());
	ASSERT(!sz.IsEmpty());
	
	Color left, right;
	ASSERT(handle);
	if (!handle) return;
	if (handle->IsActive()) {
		left = Color(0, 64, 128);
		right = Color(57, 141, 195);
	} else {
		left = GrayColor();
		right = GrayColor(195);
	}
	
	if (this->do_debug_draw) {
		if (has_mouse) {
			RGBA c = RGBAC(255, 0, 0, 125);
			id.DrawRect(sz, c);
		}
		else {
			RGBA c(RandomColor(64, 128));
			c.a = 127;
			id.DrawRect(sz, c);
		}
	}
	else
		id.DrawRect(0, 0, sz.cx, sz.cy, left);
	
	id.DrawText(7, 4, label, StdFont(15), Black());
	id.DrawText(6, 3, label, StdFont(15), White());
	
	Color tl = GrayColor(128+64+32);
	Color br = GrayColor(128-64-32);
	
	id.DrawLine(0,0, sz.cx-1, 0, 1, tl);
	id.DrawLine(0,0, 0, sz.cy-1, 1, tl);
	id.DrawLine(sz.cx-1, sz.cy-1, sz.cx-1, 0, 1, br);
	id.DrawLine(sz.cx-1, sz.cy-1, 0, sz.cy-1, 1, br);
	
}

template <class Dim>
void GeomDecorationT<Dim>::LeftDown(Pt p, dword keyflags) {
	left_down = true;
	left_down_pt = p;
	this->SetCapture();
	
	handle->FocusEvent();
}

template <class Dim>
void GeomDecorationT<Dim>::LeftDouble(Pt p, dword keyflags) {
	handle->ToggleMaximized();
}

template <class Dim>
void GeomDecorationT<Dim>::LeftUp(Pt p, dword keyflags) {
	left_down = false;
	this->ReleaseCapture();
	
}

template <class Dim>
void GeomDecorationT<Dim>::MouseMove(Pt p, dword keyflags) {
	ASSERT(this->has_mouse);
	if (left_down) {
		handle->MoveHandle(p - left_down_pt);
	}
	#if 0
	if (this->do_debug_draw) {
		this->Refresh();
	}
	#endif
}

template <class Dim>
void GeomDecorationT<Dim>::MouseEnter(Pt frame_p, dword keyflags) {
	LOG("GeomDecorationT<Dim>::MouseEnter");
	this->Refresh();
}

template <class Dim>
void GeomDecorationT<Dim>::MouseLeave() {
	LOG("GeomDecorationT<Dim>::MouseLeave");
	this->Refresh();
}

template <class Dim>
void GeomDecorationT<Dim>::RightDown(Pt p, dword keyflags) {
	MenuBar::Execute(THISBACK(LocalMenu));
}

template <class Dim>
void GeomDecorationT<Dim>::LocalMenu(Bar& bar) {
	bar.Add("Maximize / Restore", callback(handle, &HandleT<Dim>::Maximize));
	bar.Add("Minimize", callback(handle, &HandleT<Dim>::Minimize));
	bar.Separator();
	bar.Add("Close", callback(handle, &HandleT<Dim>::Close));
}


HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(HandleT)
HANDLETYPE_EXCPLICIT_INITIALIZE_CLASS(GeomDecorationT)

NAMESPACE_PARALLEL_END
