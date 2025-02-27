#include "Local.h"
#include <SerialLib/SerialLib.h>

#ifdef VIRTUALGUI

NAMESPACE_UPP

#define LLOG(x)  // LOG(x)

void GatherWindowTree(Ctrl *w, const Vector<Ctrl *>& ws, Vector<Ctrl *>& es);

void TopWindow::SyncFrameRect(const Rect& r)
{
	frame->SetClient(r);
}

void TopWindow::DestroyFrame()
{
	if(frame->IsOpen())
		frame->DestroyWnd();
}

void TopWindow::GripResize()
{
	frame->GripResize();
}

void TopWindow::SyncSizeHints()
{
	SyncCaption();
}

void TopWindow::SyncTitle()
{
	SyncCaption();
}

void TopWindow::SyncCaption()
{
	GuiLock __;
	frame->title = title.ToString();
	frame->minsize = minsize;
	frame->close.Show(!noclosebox);
	frame->maximize.Show(maximizebox);
	frame->sizeable = sizeable;
	frame->RefreshLayout();
	frame->Refresh();
	frame->close ^= [=] { WhenClose(); };
	frame->icon = icon;
	frame->Enable(IsEnabled());
}

void TopWindow::OnClose() {
	WhenClose();
}

void TopWindow::State(int reason)
{
	SyncCaption();
}

void TopWindow::SyncRect()
{
	frame->SyncBox();
	Rect r = frame->GetClient();
	if(r != GetRect())
		SetRect(r);
}

void TopWindow::Open(Ctrl *owner)
{
	GuiLock __;
	LLOG("Open " << Upp::Name(owner));
	Rect r = GetRect();
	if(r.IsEmpty())
		SetRect(GetDefaultWindowRect());
	else
	if(r.left == 0 && r.top == 0) {
		if(owner && center == 1)
			SetRect(owner->GetRect().CenterRect(r.GetSize()));
		else
		if(center)
			SetRect(GetWorkArea().CenterRect(r.GetSize()));
	}
	frame->SetClient(GetRect());
	frame->window = this;
	frame->PopUp(owner, false, true);
	PopUp(frame, false, true);
	popup = false;
	if(fullscreen)
		SetRect(GetWorkArea());
	else
		SetRect(frame->GetClient());
	SyncCaption();
	if(state == MAXIMIZED)
		frame->Maximize();
}

void TopWindow::Open()
{
	Open(GetActiveCtrl());
}

void TopWindow::OpenMain()
{
	Open(NULL);
}

void TopWindow::Minimize(bool effect)
{
//	state = MINIMIZED;
}

TopWindow& TopWindow::FullScreen(bool b)
{
	fullscreen = true;
	return *this;
}

void TopWindow::Maximize(bool effect)
{
	state = MAXIMIZED;
	frame->Maximize();
}

void TopWindow::Overlap(bool effect)
{
	GuiLock __;
	state = OVERLAPPED;
	frame->Overlap();
}

TopWindow& TopWindow::TopMost(bool b, bool stay_top)
{
	GuiLock __;
	return *this;
}

bool TopWindow::IsTopMost() const
{
	return true;
}

void TopWindow::GuiPlatformConstruct()
{
	CreateGeom2DComponent();
}

void TopWindow::GuiPlatformDestruct()
{
	delete frame;
}

void TopWindow::SerializePlacement(Stream& s, bool reminimize)
{
	GuiLock __;
}

void TopWindow::FocusEvent() {
	Panic("TODO");
}

void TopWindow::CreateGeom2DComponent() {
	using namespace Ecs;
	using namespace Parallel;
	
	#if IS_UPP_CORE
	Machine& mach = GetActiveMachine();
	WindowSystemRef wins = mach.Get<TS::Parallel::WindowSystem>();
	WindowManager& mgr = wins->GetActiveScope();
	mgr.AddInterface(*this);
	#endif
}


END_UPP_NAMESPACE

#endif
