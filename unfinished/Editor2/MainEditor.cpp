#include "MainEditor.h"
#include "ProjectManager.h"
#include "BuilderCtrl.h"
#include "WrapperWizard.h"


IDE::IDE() : terminal(this), navigator(this), assist(this) {
	project = 0;
	
	LoadThis();
	LoadHistory();
	
	Title("Editor");
	Sizeable(true);
	Zoomable(true);
	MinimizeBox();
	MaximizeBox();
	Maximize(1);
	
	Add(run_horz_split.VSizePos().HSizePos());
	
	
	build_mode.Add("Debug");
	build_mode.Add("Optimal");
	build_mode.Add("Speed");
	build_mode.Add("Size");
	
	
	run_horz_split << main_vert_split;
	
	//run_horz_split.SetPos(1500, 0);
	//run_horz_split.SetPos(10000-1500*1.15, 1);
	run_horz_split.SetPos(0, 0);
	run_horz_split.SetPos(10000, 1);
	
	main_vert_split.Set(main_horz_split, terminal);
	main_vert_split.Vert();
	//main_vert_split.SetPos(8000);
	main_vert_split.SetPos(10000);
	
	main_horz_split.Horz();
	main_horz_split << navigator << editor << assist;
	main_horz_split.SetPos(1500, 0);
	main_horz_split.SetPos(10000-1500*1.15, 1);
	
	AddFrame(menu);
	AddFrame(tool);
	
	menu.Set(THISBACK(MainBar));
	tool.Set(THISBACK(ToolBar));
	
	editor.WhenCtrlClick = THISBACK(WhenEditorCtrlClick);
	
	navigator.WhenSelectFile = THISBACK(SelectFile);
	
	terminal.WhenSelectFile = THISBACK(SelectFile);
	terminal.WhenSelectFilePos = THISBACK(SelectFilePos);
	
	package_configurations.WhenAction = THISBACK(UpdateHistory);
	build_methods.WhenAction = THISBACK(UpdateHistory);
	build_mode.WhenAction = THISBACK(UpdateHistory);
	
	
	RefreshPackageConfigurations();
	RefreshBuilderMethods();
}

IDE::~IDE() {
	
}


/*void IDE::Status(const String& s) {
	status.Temporary(s, 5000);
}
*/
void IDE::Serialize(Stream& s) {
	s % default_path % recent_projects;
}

void IDE::StoreThis() {
	StoreToFile(*this, ConfigFile("ide.bin"));
}

void IDE::LoadThis() {
	LoadFromFile(*this, ConfigFile("ide.bin"));
}










void IDE::WhenEditorCursor(String path, int line, int column) {
	Translation::Cursor cur = project->GetTranslator().GetCursor(path, line, column);
	assist.SetCursor(path, line, column, cur);
	navigator.SetLine(line);
}

void IDE::WhenEditorCtrlClick(String path, int line, int column) {
	Translation::Cursor cur = project->GetTranslator().GetCursor(path, line, column);
	////Status("Clicked: " + path + ":" + IntStr(line) + ":" + IntStr(column) + " = " + cur.GetDisplayName());
	//assist.SetCursor(path, line, column, cur);
	//navigator.SetLine(line);
	
	String variable = editor.GetOpenEditor().GetVariable(line, column);
	if (!variable.GetCount()) 
		return;
	
	LOG(cur.GetTreeString());
	for (int i=0; i < 3; i++) {
		if (cur.IsDefinition()) {
			cur = cur.GetType().GetSourceType().GetTypeDeclaration(); // ei GetReferenced()
		}
		else if (cur.IsFunctionDecl() || cur.IsConstructor() || cur.IsDestructor() || cur.IsCXXMethod()) {
			cur = cur.GetDefinition();
		}
		else if (cur.IsReference() || cur.IsMemberRef() || cur.IsTypeRef()) {
			cur = cur.GetReferenced();
		}
		else if (cur.IsTypedefDecl()) {
			cur = cur.GetType().GetSourceType().GetTypeDeclaration();
		}
		else if (cur.IsClassDecl()) {
			cur = cur.GetType().GetSourceType().GetTypeDeclaration();
		} 
		else if (cur.IsCompoundStmt()) {
			cur = cur.GetSemanticParent();//.GetSubMatch(line, column);
			//LOG(cur.GetTreeString());
			cur = cur.FindName(variable);
			//continue;
		}
		else if (cur.IsDeclRefExpr()) {
			cur = cur.GetReferenced();
		}
		else if (cur.IsDeclStmt()) {
			cur = cur.GetReferenced();
		}
		else {
			int kind = cur.GetKind();
			LOG("Unknown cursor");
		}
		break;
	}
	
	Translation::Location loc = cur.GetLocation();
	loc.GetValues(path, line, column);
	if (path != "")
		editor.OpenAndSelect(path, line, column);
}

void IDE::Find() {
	if (editor.IsOpenEditor())
		editor.GetOpenEditor().FindReplace(1, 1, 0);
}

void IDE::SwitchManagerVisibility() {
	if (main_vert_split.GetPos() == 10000)
		main_vert_split.SetPos(7500);
	else
		main_vert_split.SetPos(10000);
}


int AppendJScript(Translation::Cursor cur, String& out) {
	int kind = cur.GetKind();
	
	int count = out.GetCount();
	// out << "|-" << 
	// GetKind() << ", " << 
	// GetName() << ", " << 
	// GetType().GetResultType().GetName() << ", " << 
	// GetDisplayName() <<  "\n";
	
	String name = cur.GetName();
	String resname = cur.GetType().GetResultType().GetName();
	String disname = cur.GetDisplayName();
	
	if (kind == CXCursor_VarDecl) {
		out << "var " <<  disname << " = ";
		if (name == "UPP::String")	out += "\"\"";
		else if (name == "int")		out += "0";
		else if (name == "double")	out += "0.0";
		else if (name == "float")	out += "0.0";
		else out += "unknown_class";
		out += ";\n";
	}
	else if (kind == CXCursor_FunctionDecl) {
		int count = cur.GetCount();
		if (count >= 2) {
			out << "// c++: " << resname << " " << disname << "\n";
			int a = disname.Find("(");
			ASSERT(a != -1);
			String fn = disname.Left(a);
			out << "function " << fn << "(";
			for(int i = 1; i < count-1; i++) {
				String arg = cur[i].GetDisplayName();
				if (i > 1) out << ", ";
				out << arg;
			}
			out << ") {\n";
			if (AppendJScript(cur[count-1], out))
				out << ";\n";
			out << "}\n";
		}
	}
	else if (kind == CXCursor_CallExpr) {
		int count = cur.GetCount();
		if (name == "UPP::String" && disname == "operator<<" && count == 4) {
			String a = cur[0].GetDisplayName();
			String b = cur[2].GetDisplayName();
			out << a << " = " << a << ".concat(" << b << ")";
		} else {
			out << disname << "(";
			int count = cur.GetCount();
			for(int i = 0; i < count; i++) {
				if (i > 0) out << ", ";
				AppendJScript(cur[i], out);
			}
			out << ")";
		}
	}
	else if (kind == CXCursor_ForStmt) {
		out << "for (";
		int count = cur.GetCount();
		ASSERT(count == 4);
		for(int i = 0; i < 3; i++) {
			if (i) out << "; ";
			AppendJScript(cur[i], out);
		}
		out << ") {\n";
		AppendJScript(cur[3], out);
		out << "}\n";
	}
	else if (cur.IsDefinition()) {
		cur.GetType().GetSourceType().GetTypeDeclaration(); // ei GetReferenced()
	}
	else if (cur.IsFunctionDecl() || cur.IsConstructor() || cur.IsDestructor() || cur.IsCXXMethod()) {
		cur.GetDefinition();
	}
	else if (cur.IsReference() || cur.IsMemberRef() || cur.IsTypeRef()) {
		cur.GetReferenced();
	}
	else if (cur.IsTypedefDecl()) {
		cur.GetType().GetSourceType().GetTypeDeclaration();
	}
	else if (cur.IsClassDecl()) {
		cur.GetType().GetSourceType().GetTypeDeclaration();
	} 
	else if (cur.IsCompoundStmt()) {
		//cur.GetSemanticParent();//.GetSubMatch(line, column);
		//LOG(cur.GetTreeString());
		//cur.FindName(variable);
		//continue;
	}
	else if (cur.IsDeclRefExpr()) {
		cur.GetReferenced();
	}
	else if (cur.IsDeclStmt()) {
		cur.GetReferenced();
	}
	else {
		int kind = cur.GetKind();
		//LOG("Unknown cursor");
		
	}
	
	for(int i = 0; i < cur.GetCount(); i++) {
		AppendJScript(cur[i], out);
	}
	
	return out.GetCount() - count;
}














void IDE::MainBar(Bar& bar)
{
	bar.Add("File", THISBACK(File));
	bar.Add("View", THISBACK(View));
	bar.Add("Project", THISBACK(Project));
	bar.Add("Build", THISBACK(Build));
	bar.Add("Debug", THISBACK(Debug));
	bar.Add("Setup", THISBACK(Setup));
}



void IDE::File(Bar& bar) {
	bar.Add("Set main package...", THISBACK(SetMainPackage));
	bar.Separator();
	bar.Add("Save", THISBACK(Save)).Key(K_CTRL | K_S);
	bar.Separator();
	bar.Add("Exit", THISBACK(Exit));
}

void IDE::View(Bar& bar) {
	bar.Add("Select left tab", callback(&editor, &Editor::SelectLeft)).Key(K_CTRL_LEFT);
	bar.Add("Select right tab", callback(&editor, &Editor::SelectRight)).Key(K_CTRL_RIGHT);
	bar.Add("Close tab", callback(&editor, &Editor::CloseSelected)).Key(K_CTRL_W);
	bar.Add("Close all tab", callback(&editor, &Editor::CloseAllTabs)).Key(K_CTRL_E);
	bar.Separator();
	bar.Add("Find", THISBACK(Find)).Key(K_CTRL_F);
	//bar.Separator();
	//bar.Add("Assist", THISBACK(PopupAssist)).Key(K_CTRL|K_SPACE);
	bar.Add("Switch terminal visibility", THISBACK(SwitchManagerVisibility)).Key(K_ESCAPE);
}

void IDE::Project(Bar& bar) {
	bar.Add("Wrapper Wizard", THISBACK(WrapperWizard)).Key(K_W|K_CTRL|K_ALT);
}

void IDE::Build(Bar& bar) {
	bar.Add("Build", THISBACK(Make)).Key(K_F7);
	bar.Add("BuildAll", THISBACK(BuildAllProject));
	bar.Separator();
	bar.Add("Find next error", THISBACK(FindNextError));
	bar.Add("Find previous error", THISBACK(FindPreviousError));
	
}



void IDE::Debug(Bar& bar) {
	//bar.Add("Start/Stop", THISBACK(Restart));
	bar.Add("Debug", THISBACK(StartDebug)).Key(K_F5);
	bar.Add("Break now", THISBACK(BreakNow)).Key(K_F12);
	bar.Add("Step into", THISBACK(StepInto)).Key(K_F11);
	bar.Add("Step over", THISBACK(StepOver)).Key(K_F10);
	bar.Add("Step out", THISBACK(StepOut)).Key(K_SHIFT_F11);
	bar.Add("Run to", THISBACK(RunTo));
	bar.Add("Run", THISBACK(Continue));
	
	/*
	bar.Add("Run", Imgs::Start(), THISBACK(RunPackage)).Key(K_F4);
	bar.Add("Pause", Imgs::Pause(), THISBACK(Pause)).Key(K_F5);
	bar.Add("Stop", Imgs::Stop(), THISBACK(Stop)).Key(K_F6);
	bar.Add("Build method", Imgs::BuildMethod(), THISBACK(BuildMethod));
	*/
}


void IDE::Setup(Bar& bar) {
	bar.Add("Build methods..", THISBACK(BuildMethods));
}






















void IDE::RefreshPackageConfigurations() {
	
}

void IDE::RefreshBuilderMethods() {
	int c = build_methods.Get();
	build_methods.Clear();
	for(int i = 0; i < GetBuilder().GetBuilderMethodCount(); i++) {
		BuilderMethod& bm = GetBuilder().GetBuilder(i);
		build_methods.Add(bm.name);
	}
}

void IDE::ToolBar(Bar& bar) {
	bar.Add(package_configurations, 200);
	bar.Add(build_methods, 100);
	bar.Add(build_mode, 100);
}

void IDE::ShowTerminal() {
	main_vert_split.SetPos(7500);
}

void IDE::HideTerminal() {
	main_vert_split.SetPos(10000);
}

void IDE::BuildProject() {
	ProjectManager& pman = GetProjectManager();
	ShowTerminal();
	terminal.BeginBuild();
	terminal.BuilderOutput("Building " + project->GetOpenPackage().name + "\n");
	BuildPackage();
}

void IDE::BuildAllProject() {
	ShowTerminal();
	terminal.BeginBuild();
	//???
	BuildPackage();
}

void IDE::FindNextError() {
	
}

void IDE::FindPreviousError() {
	
}

void IDE::SetMainPackage() {
	
}

void IDE::Save() {
	editor.StoreCurrentFile();
}


void IDE::Exit() {
	Close();Close();
}

void IDE::WrapperWizard() {
	class WrapperWizard ww(this);
	ww.Run();
}
/*
void IDE::PopupAssist() {
	CodeEditor& edit = decomp.GetOpenEditor();
	Rect r = edit.GetLineScreenRect(edit.GetCursorLine());
	Point pt = r.TopLeft();
	pt.y += r.GetHeight();
	Point pt2 = edit.GetCaretPoint();
	assist.SetRect(pt.x + pt2.x, pt.y, 200, 100);
	if (!assist.IsOpen())
		assist.Ctrl::PopUp(GetParent(), false, true, true);	
}
*/
void IDE::Restart() {
	
}

void IDE::EnterDebugger() {
	
}






void IDE::BreakNow() {
	
}


void IDE::StartDebug() {
	
}

void IDE::StepInto() {
	
}

void IDE::StepOver() {
	
}

void IDE::StepOut() {
	
}

void IDE::RunTo() {
	
}

void IDE::Continue() {
	
}


void IDE::StartDebugger() {
	
}





void IDE::StoreHistory() {
	StoreToFile(histories, ConfigFile("History.bin"));
}

void IDE::LoadHistory() {
	LoadFromFile(histories, ConfigFile("History.bin"));
}

void IDE::UpdateHistory() {
	ProjectManager& pman = GetProjectManager();
	PackageHistory& ph = GetOpenHistory();
	ph.open_tabs.Clear();
	for(int i = 0; i < editor.GetCount(); i++) {
		EditorOpenTab& o = ph.open_tabs.Add();
		o.path = editor.GetPath(i);
		CodeEditor& ce = editor.GetEditor(i);
		o.line = ce.GetLine(ce.GetCursor());
		o.col  = ce.GetCursor() - ce.GetPos(ce.GetLine(ce.GetCursor()));
	}
	ph.selected_tab = editor.GetOpenTab();
	LOG("UpdateHistory open_tabs: " << ph.open_tabs.GetCount());
	
	ph.package_configuration = project->FindPackageConfiguration(package_configurations.Get());
	ph.build_method = GetBuilder().FindBuildMethod(build_methods.Get());
	ph.build_mode = GetBuilder().FindBuildMode(build_mode.Get());
	
	GetBuilder().SetCurrentBuilder(ph.build_method);
	GetBuilder().SetCurrentMode(ph.build_mode);
	
	StoreHistory();
}

PackageHistory& IDE::GetOpenHistory() {
	ProjectManager& pman = GetProjectManager();
	Package& p = project->GetOpenPackage();
	String prj_name = p.nest + DIR_SEPS + p.name;
	int i = histories.Find(prj_name);
	if (i == -1) return histories.Add(prj_name);
	return histories[i];
}

/*void IDE::SetMethod(int id) {
	PackageHistory& ph = GetOpenHistory();
	ph.build_method = id;
	terminal.Log("", "Set builder method to " + GetBuilder().GetBuilder(id).name);
	UpdateHistory();
}*/

void IDE::SetCompiled(String path, unsigned hash) {
	PackageHistory& oh = GetOpenHistory();
	int i = oh.compiled.Find(path);
	if (i == -1) oh.compiled.Add(path, hash);
	else oh.compiled[i] = hash;
}

void IDE::GetCompiled(String path, unsigned* hash) {
	PackageHistory& oh = GetOpenHistory();
	int i = oh.compiled.Find(path);
	if (i == -1) *hash = 0;
	else *hash = oh.compiled[i];
}

void IDE::Make() {
	if (status != STATUS_EDITING) {
		terminal.Log("Make", "Can't make because not editing");
	}
	else builder_thrd.Run(THISBACK(TryBuildPackage));
}

void IDE::Rebuild() {
	GetOpenHistory().compiled.Clear();
	Make();
}

void IDE::RunPackage() {
	if (status == STATUS_EDITING) {
		builder_thrd.Run(THISBACK(Start));
	}
	else if (status == STATUS_DEBUGBREAK) {
		ASSERT(dbg.IsPaused());
		ChangeStatus(STATUS_DEBUGGING);
		dbg.Start();
	}
	else terminal.Log("Dbg", "Can't run because not editing"); 
}

void IDE::ChangeStatus(int status_code) {
	LOG("Status code: " << IntStr(status_code));
	
	switch (status_code) {
		case STATUS_DEBUGGING:
		case STATUS_DEBUGBREAK:
		case STATUS_EDITING:
			terminal.SetSkipDuplicateLog(0);
			break;
		case STATUS_COMPILING:
		case STATUS_LINKING:
			terminal.SetSkipDuplicateLog(1);
	}
	status = status_code;
}

int IDE::BuildPackage() {
	int r;
	terminal.ClearLog();
	
	editor.StoreAllFiles();
	
	ChangeStatus(STATUS_COMPILING);
	GetBuilder().SetCurrentBuilder(GetOpenHistory().build_method);
	r = GetBuilder().CompileProject(*project);
	if (r==0) {
		ChangeStatus(STATUS_LINKING);
		r = GetBuilder().LinkProject();
	}
	ChangeStatus(STATUS_EDITING);
	UpdateHistory();
	return r;
}

void IDE::LoadProject(class Project& prj) {
	this->project = &prj;
	
	ProjectManager& pman = GetProjectManager();
	
	// Open project's cache
	NodeCache& nc = prj.GetCache();
	Assembly& as = prj.GetOpenAssembly();
	Package& pkg = prj.GetOpenPackage();
	String prj_name = as.name + "__" + pkg.name;
	nc.SetProjectName(prj_name);
	nc.LoadThis();
	ASSERT(nc.GetProject().GetString() == prj_name);
	//nc.Dump();
	
	prj.RefreshCache();
	
	navigator.RefreshFiles();
	
	open_package = "";
	
	PackageHistory& ph = GetOpenHistory();
	LOG("Previous open tabs count=" << ph.open_tabs.GetCount());
	for(int i = 0; i < ph.open_tabs.GetCount(); i++) {
		EditorOpenTab& tab = ph.open_tabs[i];
		editor.OpenAndSelect(tab.path, tab.line, tab.col);
	}
	if (ph.selected_tab >= 0 && ph.selected_tab < ph.open_tabs.GetCount())
		editor.Select(ph.open_tabs[ph.selected_tab].path);

	package_configurations.Set( prj.GetPackageConfiguration( ph.package_configuration ) );
	build_methods.Set( GetBuilder().GetBuildMethod( ph.build_method ) );
	build_mode.Set( GetBuilder().GetBuildMode( ph.build_mode ) );
	
	GetBuilder().SetCurrentBuilder(ph.build_method);
	GetBuilder().SetCurrentMode(ph.build_mode);
	
	status = STATUS_EDITING;
	
}

void IDE::BuildMethods() {
	BuilderCtrl bctrl;
	bctrl.SetBuilder(GetBuilder());
	bctrl.Run();
	GetBuilder().StoreThis();
	RefreshBuilderMethods();
}

void IDE::Start() {
	int r;
	r = BuildPackage();
	if (r) return;
	
	ChangeStatus(STATUS_DEBUGGING);
	
	main_vert_split.SetPos(7000);
	
	terminal.ClearLog();
	terminal.ClearProgramOutput();
	
	ProjectManager& pman = GetProjectManager();
	dbg.Init(GetBuilder().GetExePath(project->GetOpenPackage()));
	dbg.Start();
	
}

void IDE::Pause() {
	//kesc.Pause();
	dbg.Pause();
}

void IDE::Stop() {
	terminal.info.log.Clear();
	terminal.info.calls.Clear();
	dbg.Stop();
}






String SelectFileSaveAs(const char *types, String old_path)
{
	//FileSel& fs = GFileSel();
	FileSel fs;
	//LoadFromGlobal(fs, "GlobalFileSelector");
	fs.ClearTypes();
	fs.Types(types);
	fs.Set(old_path);
	bool b = fs.ExecuteSaveAs();
	//StoreToGlobal(fs, "GlobalFileSelector");
	return b ? ~fs : String::GetVoid();
}

String SelectFileOpen(const char *types, String old_path)
{
	//FileSel& fs = GFileSel();
	FileSel fs;
	//LoadFromGlobal(fs, "GlobalFileSelector");
	fs.ClearTypes();
	fs.Types(types);
	fs.Set(old_path);
	bool b = fs.ExecuteOpen();
	//StoreToGlobal(fs, "GlobalFileSelector");
	return b ? ~fs : String::GetVoid();
}




