#include "EditorBase.h"


NAMESPACE_TOPSIDE_BEGIN


EditorBase::EditorBase() {
	Title("Editor");
	Sizeable().MaximizeBox().MinimizeBox();
	//Maximize();
	
	AddFrame(main_menu);
	
	Add(hsplit.Horz().SizePos());
	hsplit << lbar << editor_bottom;
	hsplit.SetPos(1700);
	
	editor_bottom.Vert();
	editor_bottom << hsplit_code.Horz() << bottom;
	editor_bottom.SetPos(8000);
	bottom.SetFrame(btabs);
	bottom.Add(console.SizePos().SetFrame(NullFrame()));
	bottom.Add(error.SizePos().SetFrame(NullFrame()));
	bottom.Add(ffound.SizePos().SetFrame(NullFrame()));
	bottom.Add(calc.SizePos().SetFrame(NullFrame()));
	btabs <<= THISBACK(SyncBottom);
	BTabs();
	SwapBottom();
	
	SetupError(error, "Message");
	error.AddIndex("NOTES");
	error.ColumnWidths("207 41 834");
	error.WhenBar = THISBACK(ErrorMenu);
	
	SetupError(ffound, "Source");
	ffound.ColumnWidths("207 41 834");
	ffound.ColumnAt(0).SetDisplay(Single<FoundFileDisplay>());
	ffound.ColumnAt(2).SetDisplay(Single<FoundDisplay>());
	ffound.WhenBar = THISBACK(FFoundMenu);
	
	error.WhenSel = THISBACK(SelError);
	error.WhenLeftClick = THISBACK(ShowError);
	ffound.WhenSel = ffound.WhenLeftClick = THISBACK(ShowFound);
	
	ff.WhenSearch = THISBACK(DoFindInFiles);
	
	hsplit_code << left << right;
	
	
	PostCallback(THISBACK(SetMenu));
	
}

EditorBase::~EditorBase() {
	ClearExt();
}

void EditorBase::ClearCtrls() {
	while (this->lbar.GetChildCount())  this->lbar .RemoveChild(this->lbar .GetIndexChild(0));
	while (this->left.GetChildCount())  this->left .RemoveChild(this->left .GetIndexChild(0));
	while (this->right.GetChildCount()) this->right.RemoveChild(this->right.GetIndexChild(0));
}

void EditorBase::ClearExt() {
	if (active_ext) {
		active_ext->Deactivate();
		active_ext->base = 0;
		active_ext = 0;
	}
}

void EditorBase::SetExt(EditorExtension& prj_ext) {
	ClearCtrls();
	ClearExt();
	ASSERT(prj_ext.base == 0);
	prj_ext.base = this;
	active_ext = &prj_ext;
	active_ext->Activate();
}

void EditorBase::SetCtrls(Ctrl& lbar, Ctrl& left, Ctrl& right) {
	ClearCtrls();
	
	this->lbar.Add(lbar.SizePos());
	this->left.Add(left.SizePos());
	this->right.Add(right.SizePos());
}

void EditorBase::OnMessage(ProcMsg e) {
	lock.Enter();
	errors.Add(e);
	lock.Leave();
	
	GuiLock __;
	SyncBottom();
	
	Color bg = White();
	if (e.severity == PROCMSG_ERROR)			bg = Color(255, 182, 176);
	else if (e.severity == PROCMSG_WARNING)		bg = Color(255, 255, 180);
	
	ErrorInfo ei;
	ei.file = e.file;
	ei.lineno = e.line;
	ei.linepos = e.col;
	ei.kind = e.severity;
	ei.message = e.msg;
	
	error.Add(e.file, e.line, AttrText(e.GetSeverityString() + ": " + e.msg).NormalPaper(bg), RawToValue(ei));
}

void EditorBase::FocusLine(ArrayCtrl* list) {
	
}

void EditorBase::Execute() {
	state = COMPILING;
	ProcessCompiling();
	
}

void EditorBase::DebugFile() {
	state = COMPILING;
	ProcessCompiling();
	
}

void EditorBase::StopDebug() {
	
}

void EditorBase::Continue() {
	
}

bool EditorBase::IsRunning() {
	return state == DEBUGGING || state == RUNNING;
}

bool EditorBase::IsPaused() {
	return state == PAUSED;
}

void EditorBase::FindInFiles(bool b) {
	
}

bool EditorBase::HotKey(dword key) {
	if (key == K_ESCAPE) {SwapBottom(); return true;}
	if (key == K_F5) {
		
		if (!IsRunning()) {
			DebugFile(); return true;
		}
		else if (IsPaused()) {
			Continue(); return true;
		}
		else {
			StopDebug(); return true;
		}
	}
	if (key == (K_CTRL | K_F5) ) {Execute(); return true;}
	if (key == (K_CTRL | K_SHIFT | K_F)) {FindInFiles(0); return true;}
	if (key == (K_CTRL | K_SHIFT | K_R)) {FindInFiles(1); return true;}
	//if (key == (K_CTRL | K_SHIFT | K_W)) {CloseTab(); return true;}
	//if (key == (K_CTRL | K_ALT   | K_W)) {CloseAllTabs(); return true;}
	//if (key == (K_CTRL | K_ALT | K_LEFT)) {PreviousTab(); return true;}
	//if (key == (K_CTRL | K_ALT | K_RIGHT)) {NextTab(); return true;}
	/*if (key == K_F2) {SwitchPreviewMode(); return true;}
	if (key == (K_CTRL | K_1)) {SetPreviewMode(PREV_MAIN);   return true;}
	if (key == (K_CTRL | K_2)) {SetPreviewMode(PREV_HSPLIT); return true;}
	if (key == (K_CTRL | K_3)) {SetPreviewMode(PREV_TOPWND); return true;}
	if (key == (K_CTRL | K_4)) {SetPreviewMode(PREV_HIDDEN); return true;}
	if (key == (K_CTRL | K_J)) {path.SetEdit(); return true;}*/
	
	if (active_ext && active_ext->HotKey(key))
		return true;
	
	return false;
}

void EditorBase::ProcessCompiling() {
	{
		GuiLock __;
		error.Clear();
		btabs.SetCursor(2);
		SyncBottom();
	}
	
	if (active_ext)
		active_ext->Save();
	
	TODO
}

void EditorBase::SetProject(UppProject& p, const UppAssembly& as, UppAssemblyData& asd) {
	this->as = &as;
	this->asd = &asd;
	prj = &p;
	prj->GetRecursiveUses(rec_uses, asd);
}

	

NAMESPACE_TOPSIDE_END
