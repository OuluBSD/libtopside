#include <EcsLib/EcsLib.h>


NAMESPACE_UPP


TopWindow::TopWindow() : id(-1) {
	
}

void TopWindow::Init(Oulu::CoreWindow* cw, int id) {
	this->cw = cw;
	this->id = id;
	
	if (title.IsEmpty())
		title = wm->GetTitle(id);
	else
		wm->SetTitle(id, title);
}

void TopWindow::Title(const String& title) {
	this->title = title;
	if (wm)
		wm->SetTitle(id, title);
}

void TopWindow::SetFrameRect(const Rect& r) {
	Ctrl::SetFrameRect(r);
	cw->SetFrameRect(r);
}

int TopWindow::Run(bool appmodal) {
	ASSERT(cw);
	Ctrl::Invalidate();
	cw->Wait();
	return GetExitCode();
	
	/*
	GuiLock __;
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
	
	EventLoop(this);
	
	EnableCtrls(disabled);
	if(IsNull(exitcode)) {
		WhenClose();
		if(IsNull(exitcode))
			DefaultBreak();
	}
	int q = exitcode;
	inloop = pinloop;
	exitcode = pexitcode;
	
	return q;*/
}

END_UPP_NAMESPACE
