#include "Terminal.h"
#include "MainEditor.h"



void ColorLabel::SetLabel(const String& s) {
	fg = Black();
	if (s.Compare("note:") > 0) {
		bg = Color(254,255,161);
	}
	else if (s.Compare("error:") > 0) {
		bg = Color(255,161,169);
	}
	else if (s.Compare("warning:") > 0) {
		bg = Color(255,226,161);
	}
	else {
		bg = White();
	}
	label = s;
}

void ColorLabel::Paint(Draw& d) {
	Rect r(GetSize());
	d.DrawRect(r, bg);
	int h = r.Height();
	int font_height = h * 0.7;
	d.DrawText(2, 3, label, SansSerif(font_height), fg);
}

void ColorLabel::LeftDown(Point p, dword keyflags) {
	WhenSelected();
}








bool LogItem::HasLocation() {
	return haslocation;
}

void LogItem::SetError(String where, String what, int line, int col) {
	haslocation = 1;
	this->line = line;
	this->col = col;
	this->where = where;
	this->what = what;
}

void LogItem::SetNormal(String where, String what) {
	this->where = where;
	this->what = what;
}










GdbInfo::GdbInfo() {
	Add(calls.HSizePos().TopPos(0, 30));
	Add(log.HSizePos().VSizePos(30,10));
	Add(prog.HSizePos().BottomPos(0,10));
	
	log.AddColumn("Where");
	log.AddColumn("What");
	log.ColumnWidths("1 4");
	
	prog.Set(0,1);
}










Terminal::Terminal(IDE* ide) : ide(ide) {
	
	Add(main_vert_split.VSizePos().HSizePos());
	
	main_vert_split.Set(main_horz_split, progress);
	main_vert_split.SetPos(9500);
	main_vert_split.Vert();
	
	main_horz_split.Set(output_tab, dbg_tab);
	main_horz_split.Horz();
	
	output_tab.Add(console, "Console");
	output_tab.Add(console);
	output_tab.Add(builder_msg, "Messages");
	output_tab.Add(builder_msg);
	output_tab.Add(builder_log, "Log");
	output_tab.Add(builder_log);
	
	dbg_tab.Add(threads, "Threads");
	dbg_tab.Add(threads);
	dbg_tab.Add(callstack, "Callback");
	dbg_tab.Add(callstack);
	dbg_tab.Add(locals, "Locals");
	dbg_tab.Add(locals);
	dbg_tab.Add(thisclass, "This");
	dbg_tab.Add(thisclass);
	dbg_tab.Add(watches, "Watches");
	dbg_tab.Add(watches);
	
	
	builder_msg.AddColumn("Path");
	builder_msg.AddColumn("Line");
	builder_msg.AddColumn("Col");
	builder_msg.AddColumn("Message");
	builder_msg.ColumnWidths("5 1 1 7");
	builder_msg.WhenCursor = THISBACK(WhenSelectBuilderMessage);
	
	GetBuilder().WhenProgress = THISBACK(Progress);
	GetBuilder().Log = THISBACK(TryLog);
	GetBuilder().WhenLogItem = THISBACK(NewLogItem);
	GetBuilder().CompilerLog = THISBACK(CompilerLog);
	
	skip_log_duplicates = true;
	
	progress.Set(0, 1);
}
	
/*void Terminal::BuilderLogRefresh() {
	builder_log.SetData(project->GetBuildLog());
	builder_log.SetCursor(builder_log.GetLength());
	const Array<BuildLogItem>& items = project->GetBuildLogItems();
	for(int i = builder_msg.GetCount(); i < items.GetCount(); i++) {
		const BuildLogItem& item = items[i];
		builder_msg.Add(item.path, item.line, item.col, "");
		builder_msg.CreateCtrl<ColorLabel>(i, 3, false).WhenSel(THISBACK1(BuildLogSet, i)).SetLabel(item.message);
	}
}
*/

void Terminal::NewLogItem(BuildLogItem item) {
	GuiLock __;
	int i = builder_msg.GetCount();
	builder_msg.Add(item.path, item.line, item.col, "");
	builder_msg.CreateCtrl<ColorLabel>(i, 3, false).WhenSel(THISBACK1(BuildLogSet, i)).SetLabel(item.message);
	items.Add(item);
}

void Terminal::BuildLogSet(int i) {
	builder_msg.SetCursor(i);
}


void Terminal::WhenSelectBuilderMessage() {
	int id = builder_msg.GetCursor();
	if (id < 0) return;
	const BuildLogItem& item = items[id];
	ide->GetEditor().OpenAndSelect(item.path, item.line, item.col);
}

void Terminal::BeginBuild() {
	output_tab.Set(2);
	builder_msg.Clear();
	builder_log.Clear();
	builder_log_content.Clear();
}




bool IsStrInt(const String& s) {
	if (!s.GetCount()) return 0;
	for(int i = 0; i < s.GetCount(); i++)
		if (!IsDigit(s[i])) return 0;
	return 1;
}





void Terminal::ClearLog() {
	GuiLock __;
	logitems.Clear();
	info.log.Clear();
	logpaths.Clear();
	items.Clear();
}

void Terminal::Progress(int actual, int total) {
	GuiLock __;
	info.prog.Set(actual, total);
}

int Terminal::Log(const String& where, const String& what) {
	BuilderOutput(where + ": " + what + "\n");
	if (skip_log_duplicates) for(int i = 0; i < info.log.GetCount(); i++) {
		if (info.log.Get(i,0) == where && info.log.Get(i,1) == what)
			return -1;
	}
	
	int pos = logitems.GetCount();
	LogItem& i = logitems.Add();
	i.SetNormal(where, what);
	
	GuiLock __;
	info.log.Add(where, what);
	info.log.ScrollEnd();
	return pos;
}

void Terminal::CompilerLog(String where, String what, String path) {
	int pos = Log(where, what);
	if (pos != -1)
		logpaths.Add(pos, path);
}

void Terminal::LogError(String where, String what, int line, int col) {
	LogItem& i = logitems.Add();
	i.SetError(where, what, line, col);
	where += " (" + IntStr(line) + ":" + IntStr(col) + ")";
	
	GuiLock __;
	info.log.Add(where, what);
	info.log.ScrollEnd();
}

void Terminal::SelectLogItem() {
	int c = info.log.GetCursor();
	if (c < 0 || c >= logitems.GetCount()) return;
	int i = logpaths.Find(c);
	if (i == -1) return;
	
	String& path = logpaths[i];
	const String& s = logitems[c].Where();
	Vector<String> loc = Split(s, ":");
	c = loc.GetCount();
	
	// Open path in editor
	
	// Is line and column given?
	if (c >= 3 && IsStrInt(loc[c-1]) && IsStrInt(loc[c-2]))
		WhenSelectFilePos(path, StrInt(loc[c-2]), StrInt(loc[c-1])); 
	else if (c == 2 && IsStrInt(loc[c-1]))
		WhenSelectFilePos(path, StrInt(loc[c-1]), 0); 
	else
		WhenSelectFile(path);
}

void Terminal::ProgramOutput(String s) {
	//GuiLock __;
	console.Put(s);
}

void Terminal::ClearProgramOutput() {
	GuiLock __;
	console.Clear();
}

void Terminal::BuilderOutput(String s) {
	builder_log_content += s;
	
	GuiLock __;
	builder_log.SetData(builder_log_content);
}


Console::Console() {
	Add(edit.VSizePos().HSizePos());
	
}

void Console::Put(const String& s) {
	content += s;
	int pos;
	while ((pos = content.Find("\r")) != -1) {
		int a = content.ReverseFind("\n", pos);
		if (a == -1) a = 0;
		else a++;
		content.Remove(a, pos-a+1);
	}
	if (content.GetCount() > 1024)
		content = content.Right(1024);
	edit.SetData(content);
}

