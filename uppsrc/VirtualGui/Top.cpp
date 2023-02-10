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

void TopWindow::State(int reason)
{
	SyncCaption();
}

void TopWindow::SyncRect()
{
	frame->SyncRect();
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
	frame = new TopWindowFrame;
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

void TopWindow::RunInMachine(bool appmodal) {
	GuiLock __;
	
	// See Ctrl::InitX11 for example code
	
	//VirtualGuiPtr = &gui;
	//Ctrl::InitFB();
	
	//Ctrl::GlobalBackBuffer();
	Ctrl::InitTimer();

	//SetStdFont(ScreenSans(12));
	//ChStdSkin();
	
	//Ctrl::SetDesktopSize(gui.GetSize());
	Font::SetDefaultFont(Arial(12));

	ReSkin();

	GUI_GlobalStyle_Write(GUISTYLE_XP);
	GUI_DragFullWindow_Write(1);
	GUI_PopUpEffect_Write(GUIEFFECT_NONE);
	GUI_DropShadows_Write(0);
	GUI_AltAccessKeys_Write(1);
	GUI_AKD_Conservative_Write(0);

	LLOG("TopWindow::RunInMachine() <- " << typeid(*this).name());
	LLOG("Focus = " << UPP::Name(GetFocusCtrl()));
	if(!IsOpen())
		Open();
	if(!IsVisible()) Show();
	bool pinloop = inloop;
	int  pexitcode = exitcode;
	exitcode = Null;
	Vector<Ctrl *> es;
	if(appmodal)
		es = GetTopCtrls();
	else {
		Vector<Ctrl *> ws = GetTopCtrls();
		for(int i = 0; i < ws.GetCount(); i++)
			if(ws[i]->InLoop())
				es.Add(ws[i]);
		Ctrl *mw = GetMainWindow();
		if(mw) GatherWindowTree(mw, ws, es);
	}
	Vector< Ptr<Ctrl> > disabled = DisableCtrls(es, this);
#ifdef _DEBUG
	for(int d = 0; d < disabled.GetCount(); d++)
		LLOG("DisableCtrls[" << d << "] = " << UPP::Name(disabled[d]));
	LLOG("Running EventLoop in " << UPP::Name(this));
#endif
	TS::DebugMainLoop();
#ifdef _DEBUG
	LLOG("Finished EventLoop in " << UPP::Name(this));
	for(int e = 0; e < disabled.GetCount(); e++)
		LLOG("EnableCtrls[" << e << "] = " << UPP::Name(disabled[e]));
#endif
	EnableCtrls(disabled);
	if(IsNull(exitcode)) {
		WhenClose();
		if(IsNull(exitcode))
			DefaultBreak();
	}
	int q = exitcode;
	inloop = pinloop;
	exitcode = pexitcode;
	LLOG("TopWindow::Run() = " << q << " -> " << typeid(*this).name());
#ifdef GUI_WIN
	LLOG("Focus = " << UPP::Name(GetFocusCtrl()) << ", raw " << (void *)::GetFocus());
#endif
	Ctrl::ExitFB();
}

void TopWindow::CreateGeom2DComponent() {
	using namespace Ecs;
	using namespace Parallel;
	
	Machine& mach = GetActiveMachine();
	WindowSystemRef wins = mach.Get<WindowSystem>();
	WindowManager& mgr = wins->GetActiveScope();
	mgr.AddInterface(*this);
}
END_UPP_NAMESPACE

#endif
