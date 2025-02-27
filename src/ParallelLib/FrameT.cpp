#include "ParallelLib.h"

#ifdef flagGUI

NAMESPACE_PARALLEL_BEGIN

#define LLOG(x)  // LOG(x)
#define LDUMP(x) //DDUMP(x)


template <class Dim>
FrameT<Dim>::FrameT() {
	TODO
}

	
#if IS_UPP_CORE
template <>
FrameT<CtxUpp2D>::FrameT() {
	//geom.SetTargetCtrl(*this);
	
	close.SetImage(FBImg::close());
	close.EdgeStyle();
	Add(close);
	maximize.SetImage(FBImg::maximize());
	maximize.EdgeStyle();
	Add(maximize);
	maximize <<= THISBACK(ToggleMaximize);
	maximized = false;
	sizeable = false;
	holding = false;
}

template <>
Size FrameT<CtxUpp2D>::GetFrameSize() const {
	return Ctrl::GetSize();
}

template <>
Rect FrameT<CtxUpp2D>::GetFrameBox() const {
	return Ctrl::GetRect();
}

template <>
void FrameT<CtxUpp2D>::SetFrameBox(Box b) {
	Ctrl::SetRect(b);
}

template <>
Rect FrameT<CtxUpp2D>::Margins() const
{
	return maximized ? Rect(0,0,0,0) : ChMargins(FBImg::border());
}

template <>
void FrameT<CtxUpp2D>::Paint(DrawT& w) {
	#if 1
	//const Ctrl& window = frame->GetScope().GetCtrl();
	Size sz = Ctrl::GetSize();
	Box m = Margins();
	int c = GetStdFontCy() + 4;
	ChPaintEdge(w, sz, FBImg::border());
	ChPaint(w, m.left, m.top, sz.cx - m.left - m.right, GetStdFontCy() + 4,
	        window->IsForeground() ? FBImg::title() : FBImg::bgtitle());
	int tx = m.left + 2;
	int tcx = sz.cx - m.left - m.right - 4 - c * (close.IsShown() + maximize.IsShown());
	if(!IsNull(icon)) {
		Image h = icon;
		if(h.GetWidth() > c || h.GetHeight() > c)
			h = Rescale(h, GetFitSize(h.GetSize(), Size(c)));
		w.DrawImage(tx, m.top + 2, h);
		tx += c;
		tcx -= c;
	}
	DrawTextEllipsis(w, tx, m.top + 2, tcx, title, "..", StdFont(), SColorHighlightText());
	#else
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
	#endif
}
#endif

template <class Dim>
typename Dim::TopContainer* FrameT<Dim>::GetTopContainer() {
	return window;
}

template <class Dim>
typename Dim::Sz FrameT<Dim>::GetFrameSize() const {
	return Dim::Container::GetFrameSize();
}

template <class Dim>
typename Dim::Box FrameT<Dim>::GetFrameBox() const {
	return Dim::Container::GetFrameBox();
}

template <class Dim>
void FrameT<Dim>::SetFrameBox(Box b) {
	Dim::Container::SetFrameBox(b);
}

template <class Dim>
void FrameT<Dim>::SetScope(Scope* s) {
	scope = s;
	close.WhenPush = THISBACK(Close);
	maximize.WhenPush = THISBACK(ToggleMaximized);
	minimize.WhenPush = THISBACK(Minimize);
}

template <class Dim>
ScopeT<Dim>& FrameT<Dim>::GetWorkArea() {
	return *scope;
}

template <class Dim>
void FrameT<Dim>::SyncBox()
{
	if(maximized) {
		Sz sz = GetWorkArea().GetSize();
		if(this->GetFrameBox().GetSize() != sz)
			this->SetFrameBox(sz);
	}
}

template <class Dim>
void FrameT<Dim>::Maximize()
{
	if(!maximized && maximize.IsShown()) {
		maximized = true;
		overlapped = this->GetFrameBox();
		this->SetFrameBox(GetWorkArea().GetSize());
		maximize.SetImage(FBImg::overlap());
	}
}

template <class Dim>
void FrameT<Dim>::Overlap()
{
	if(maximized && maximize.IsShown()) {
		maximized = false;
		this->SetFrameBox(overlapped);
		maximize.SetImage(FBImg::maximize());
	}
}

template <class Dim>
void FrameT<Dim>::ToggleMaximize()
{
	if(maximized)
		Overlap();
	else
		Maximize();
}

template <class Dim>
typename Dim::Box FrameT<Dim>::Margins() const
{
	TODO
}

template <class Dim>
void FrameT<Dim>::Paint(DrawT& draw) {
	TODO // permanent
}

template <class Dim>
void FrameT<Dim>::Layout() {
	Sz sz = this->GetFrameSize();
	Box m = Margins();
	int c = GetStdFontCy() + 4;
	int x = sz.cx - m.right;
	if(close.IsShown())
		close.SetRect(x -= c, m.top, c, c);
	if(maximize.IsShown())
		maximize.SetRect(x -= c, m.top, c, c);
}

template <class Dim>
typename Dim::Box FrameT<Dim>::GetClient() const
{
	Box r = this->GetFrameBox();
	Box m = Margins();
	r.left += m.left;
	r.right -= m.right;
	r.top += m.top;
	r.bottom -= m.bottom;
	r.top += GetStdFontCy() + 4;
	return r;
}

template <class Dim>
typename Dim::Box FrameT<Dim>::ComputeClient(Box r)
{
	TODO
}

template <class Dim>
void FrameT<Dim>::SetClient(Box r)
{
	this->SetFrameBox(ComputeClient(r));
}

template <class Dim>
typename Dim::Pt FrameT<Dim>::GetDragMode(Pt p) {
	TODO
}

template <class Dim>
void FrameT<Dim>::StartDrag()
{
	TODO
}

template <class Dim>
void FrameT<Dim>::GripResize()
{
	dir = Dim::UnitPoint();
	StartDrag();
}

template <class Dim>
void FrameT<Dim>::LeftDown(Pt p, dword keyflags) {
	#if 1
	dir = GetDragMode(p);
	StartDrag();
	#else
	left_down = true;
	left_down_pt = p;
	this->SetCapture();
	handle->FocusEvent();
	#endif
}

template <class Dim>
void FrameT<Dim>::CancelMode()
{
	holding = false;
}

template <class Dim>
void FrameT<Dim>::LeftUp(Pt p, dword keyflags) {
	#if 1
	holding = false;
	#else
	left_down = false;
	this->ReleaseCapture();
	#endif
}

template <class Dim>
void FrameT<Dim>::Hold()
{
	if(this->Container::HasCapture()) {
		if(this->HasMouse() && GetMouseLeft() && holding)
			StartDrag();
		this->ReleaseCapture();
		holding = false;
	}
}
/*
template <class Dim>
void FrameT<Dim>::LeftHold(Point p, dword keyflags)
{
	if(HasCapture() || FullWindowDrag)
		return;
	dir = GetDragMode(p);
	if(!dir.x && !dir.y)
		StartDrag();
}
*/
template <class Dim>
void FrameT<Dim>::LeftDouble(Pt p, dword keyflags) {
	#if 1
	ToggleMaximize();
	//IgnoreMouseUp();
	#else
	handle->ToggleMaximized();
	#endif
}

template <class Dim>
void FrameT<Dim>::MouseMove(Pt, dword keyflags) {
	TODO
}

template <class Dim>
Image FrameT<Dim>::GetDragImage(Pt dir)
{
	#if IS_UPP_CORE
	static Image (*im[9])() =
	#else
	static const Image& (*im[9])() =
	#endif
	{
		Image::SizeTopLeft,  Image::SizeLeft,  Image::SizeBottomLeft,
		Image::SizeTop,      Image::Arrow,     Image::SizeBottom,
		Image::SizeTopRight, Image::SizeRight, Image::SizeBottomRight,
	};
	int pos = (dir.x + 1) * 3 + (dir.y + 1);
	return (*im[pos])();
}

template <class Dim>
Image FrameT<Dim>::CursorImage(Pt p, dword)
{
	if(!sizeable)
		return Image::Arrow();
	return GetDragImage(this->HasCapture() ? dir : GetDragMode(p));
}

template <class Dim>
void FrameT<Dim>::MouseEnter(Pt frame_p, dword keyflags) {
	LOG("FrameT<Dim>::MouseEnter");
	this->Refresh();
}

template <class Dim>
void FrameT<Dim>::MouseLeave() {
	LOG("FrameT<Dim>::MouseLeave");
	this->Refresh();
}

template <class Dim>
void FrameT<Dim>::RightDown(Pt p, dword keyflags) {
	#if IS_UPP_CORE
	MenuBar::Execute(THISBACK(LocalMenu));
	#endif
}

template <class Dim>
void FrameT<Dim>::LocalMenu(Bar& bar) {
	bar.Add("Maximize / Restore", THISBACK(Maximize));
	bar.Add("Minimize", THISBACK(Minimize));
	bar.Separator();
	bar.Add("Close", THISBACK(Close));
}

/*template <class Dim>
typename Dim::Interaction& FrameT<Dim>::GetInteraction() {
	TODO
}

template <>
typename Ctx2D::Interaction& FrameT<CtxUpp2D>::GetInteraction() {
	return geom;
}

template <>
typename Ctx3D::Interaction& FrameT<Ctx3D>::GetInteraction() {
	return *this;
}*/

template <class Dim>
void FrameT<Dim>::ToggleMaximized() {
	if (IsMaximized())
		Restore();
	else
		Maximize();
}

template <class Dim>
void FrameT<Dim>::Minimize() {
	Scope& scope = GetScope();
	scope.MinimizeHandle(id);
}

template <class Dim>
void FrameT<Dim>::Restore()
{
	Scope& scope = GetScope();
	scope.RestoreHandle(id);
	scope.FocusHandle(id);
	
	maximized = false;
}

template <class Dim>
void FrameT<Dim>::Close() {
	Scope& scope = GetScope();
	scope.QueueCloseHandle(id);
}

#if 0
template <class Dim>
void FrameT<Dim>::Maximize() {
	Scope& scope = GetScope();
	scope.FocusHandlePos(id);
	scope.MaximizeHandle(id);
	maximized = true;
}

template <class Dim>
void FrameT<Dim>::Minimize() {
	Scope& scope = GetScope();
	scope.MinimizeHandle(id);
}

template <class Dim>
void FrameT<Dim>::CloseOthers() {
	Scope& scope = GetScope();
	scope.CloseOthers(id);
}

#endif

#if IS_UPP_CORE

template <>
void FrameT<CtxUpp2D>::StartDrag()
{
	if(maximized)
		return;
	if(!sizeable && (dir.x || dir.y))
		return;
	this->Ctrl::SetCapture();
	startrect = this->GetFrameBox();
	startpos = GetMousePos();
	LLOG("START DRAG ---------------");
}

template <>
Point FrameT<CtxUpp2D>::GetDragMode(Pt p)
{
	Sz sz = this->GetFrameSize();
	Box m = ChMargins(FBImg::border());
	Point dir;
	dir.y = p.y < m.top ? -1 : p.y > sz.cy - m.top ? 1 : 0;
	dir.x = p.x < m.left ? -1 : p.x > sz.cx - m.right ? 1 : 0;
	return dir;
}

template <>
Rect FrameT<CtxUpp2D>::ComputeClient(Rect r)
{
	Rect m = Margins();
	r.left -= m.left;
	r.right += m.right;
	r.top -= m.top;
	r.bottom += m.bottom;
	r.top -= GetStdFontCy() + 4;
	return r;
}

template <>
void FrameT<CtxUpp2D>::MouseMove(Pt, dword keyflags) {
	#if 1
	LDUMP(HasWndCapture());
	LDUMP(HasCapture());
	if(!this->HasCapture() || holding)
		return;
	ASSERT(scope);
	Sz msz = ComputeClient(minsize).GetSize();
	Pt p = GetMousePos() - startpos;
	Box r = startrect;
	if(dir.x == -1)
		r.left = min(r.left + p.x, startrect.right - msz.cx);
	if(dir.x == 1)
		r.right = max(r.right + p.x, startrect.left + msz.cx);
	if(dir.y == -1)
		r.top = min(r.top + p.y, startrect.bottom - msz.cy);
	if(dir.y == 1)
		r.bottom = max(r.bottom + p.y, startrect.top + msz.cy);
	if(dir.y == 0 && dir.x == 0)
		r.Offset(p);
	this->SetFrameBox(r);
	#else
	ASSERT(this->has_mouse);
	if (left_down) {
		handle->MoveHandle(p - left_down_pt);
	}
	#if 0
	if (this->do_debug_draw) {
		this->Refresh();
	}
	#endif
	#endif
}

#endif

PLIB_TYPE_EXCPLICIT_INITIALIZE_CLASS(FrameT)


NAMESPACE_PARALLEL_END

#endif
