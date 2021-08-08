#include "CommandBridge.h"

#define KEYGROUPNAME "AK"
#define KEYNAMESPACE AKKeys
#define KEYFILE      <CommandBridge/CommandBridge.key>
#include             <CtrlLib/key_source.h>

// fix buggy translate in freebsd
#ifdef flagFREEBSD
	#undef t_
	#define t_(x) x
#endif

CommandBridge::CommandBridge() {
	Icon(CommandBridgeImg::icon());
	FrameLess();
	
	id_counter = 0;
	
	AddFrame(menu);
	AddFrame(tabs);
	
	RefreshMenu();
	
	tabs.MinTabCount(0);
	tabs.Crosses();
	tabs.WhenClose << THISBACK(TabClosed);
	tabs.WhenAction << THISBACK(ShowTab);
	
	InitWord();
	PostSetLayout();
	PostSetSemiTransparent();
}

Console& CommandBridge::NewConsole() {
	int id = id_counter++;
	Console& c = cons.Add(id);
	c.SetBridge(this, id);
	c.WhenTitle << THISBACK1(RefreshTitle, id);
	c.WhenViewChange << THISBACK1(ViewChange, id);
	tabs.AddKey(id, "Console", CommandBridgeImg::icon(), Null, true);
	ShowTabId(id);
	return c;
}

TerminalTab& CommandBridge::NewTerminal() {
	int id = id_counter++;
	TerminalTab& c = terms.Add(id);
	c.SetBridge(this, id);
	c.WhenTitle << THISBACK1(RefreshTitle1, id);
	tabs.AddKey(id, "Terminal", CommandBridgeImg::icon(), Null, true);
	ShowTabId(id);
	return c;
}

void CommandBridge::CloseTab() {
	int active = tabs.GetCursor();
	int tab_id = tabs.GetKey(active);
	CloseTabId(tab_id);
}

void CommandBridge::CloseTabId(int id) {
	int active = tabs.GetCursor();
	for(int i = 0; i < tabs.GetCount(); i++) {
		int tab_id = tabs.GetKey(i);
		if (tab_id == id) {
			tabs.Close(i);
			if (tabs.GetCount() == 0)
				tabs.Clear();
			
			int new_active = active < tabs.GetCount() ? active : active - 1;
			int new_id = new_active >= 0 ? (int)tabs.GetKey(new_active) : -1;
			ShowTabId(new_id);
			
			RemoveId(id);
			break;
		}
	}
}

void CommandBridge::PreviousTab() {
	int active = tabs.GetCursor() - 1;
	if (active < 0) active += tabs.GetCount();
	if (active < 0 || active >= tabs.GetCount()) return;
	tabs.SetCursor(active);
}

void CommandBridge::NextTab() {
	int active = tabs.GetCursor() + 1;
	if (active < 0) active += tabs.GetCount();
	if (active < 0 || active >= tabs.GetCount()) return;
	tabs.SetCursor(active);
}

void CommandBridge::ShowTab() {
	int active = tabs.GetCursor();
	if (active < 0 || active >= tabs.GetCount()) return;
	int id = tabs.GetKey(active);
	ShowTabId(id);
	RefreshMenu();
}

void CommandBridge::ShowTabId(int id) {
	for(int i = 0; i < cons.GetCount(); i++)
		RemoveChild(&cons[i]);
	for(int i = 0; i < terms.GetCount(); i++)
		RemoveChild(&terms[i]);
	
	int i;
	if ((i = cons.Find(id)) >= 0) {
		Ctrl& c = cons[i].SizePos();
		Add(c);
		c.SetFocus();
	}
	else if ((i = terms.Find(id)) >= 0) {
		Ctrl& c = terms[i].SizePos();
		Add(c);
		c.SetFocus();
	}
}

void CommandBridge::RemoveId(int id) {
	int i;
	if ((i = cons.Find(id)) >= 0)
		cons.Remove(i);
	else if ((i = terms.Find(id)) >= 0)
		terms.Remove(i);
}

void CommandBridge::TabClosed(Value tab) {
	int i, id = tab;
	
	if ((i = cons.Find(i)) >= 0) {
		RemoveChild(&cons[i]);
		cons.Remove(i);
	}
	if ((i = terms.Find(i)) >= 0) {
		RemoveChild(&terms[i]);
		terms.Remove(i);
	}
	
}

Console* CommandBridge::GetActiveConsole() {
	int active = tabs.GetCursor();
	if (active < 0 || active >= tabs.GetCount()) return 0;
	int i = tabs.GetKey(active);
	int pos = cons.Find(i);
	return pos >= 0 ? &cons[pos] : 0;
}

TerminalTab* CommandBridge::GetActiveTerminal() {
	int active = tabs.GetCursor();
	if (active < 0 || active >= tabs.GetCount()) return 0;
	int i = tabs.GetKey(active);
	int pos = terms.Find(i);
	return pos >= 0 ? &terms[pos] : 0;
}

void CommandBridge::MainMenu(Bar& menu) {
	menu.Add(t_("App"), THISBACK(AppMenu));
	menu.Add(t_("View"), THISBACK(ViewMenu));
	menu.Add(t_("Setup"), THISBACK(SetupMenu));
	
	Console* cons = GetActiveConsole();
	if (cons){
		String cons_menu = cons->GetMenuTitle();
		if (!cons_menu.IsEmpty()) {
			menu.Add(cons_menu, callback(cons, &Console::Menu));
		}
		return;
	}
	
	TerminalTab* term = GetActiveTerminal();
	if (term) {
		String term_menu = term->GetMenuTitle();
		if (!term_menu.IsEmpty()) {
			menu.Add(term_menu, callback(term, &TerminalTab::Menu));
		}
		return;
	}
}

void CommandBridge::SetLang(int lang)
{
	SetLanguage(lang);
	RefreshMenu();
}

void CommandBridge::RefreshTitle(int id) {
	Console& c = cons.Get(id);
	String title = c.GetTitle();
	RefreshTitle1(title, id);
}

void CommandBridge::RefreshTitle1(String title, int id) {
	for(int i = 0; i < tabs.GetCount(); i++) {
		if (tabs.GetKey(i) == id) {
			tabs.SetValue(i, title);
			break;
		}
	}
}

void CommandBridge::ViewChange(int id) {
	int active = tabs.GetCursor();
	if (active < 0 || active >= tabs.GetCount()) return;
	active = tabs.GetKey(active);
	if (active != id) return;
	RefreshMenu();
}

void CommandBridge::RefreshMenu() {
	menu.Clear();
	menu.Set(THISBACK(MainMenu));
}

void CommandBridge::AppMenu(Bar& menu) {
	menu.Add(AK_OPENCONS, THISBACK(AddConsole));
	menu.Add(AK_OPENTERM, THISBACK(AddTerminal));
	menu.Add(AK_QUIT, THISBACK(Quit));
}

void CommandBridge::ViewMenu(Bar& menu) {
	menu.Add(AK_CLOSETAB, THISBACK(CloseTab));
	menu.Add(AK_PREVTAB, THISBACK(PreviousTab));
	menu.Add(AK_NEXTTAB, THISBACK(NextTab));
}

void CommandBridge::SetupMenu(Bar& menu)
{
	menu.Add(AK_ENGLISH, THISBACK1(SetLang, LNGC_('E','N','U','S', CHARSET_UTF8)))
	         .Radio(GetCurrentLanguage() == LNGC_('E','N','U','S', CHARSET_UTF8));
	menu.Add(AK_FINNISH, THISBACK1(SetLang, LNGC_('F','I','F','I', CHARSET_UTF8)))
	         .Radio(GetCurrentLanguage() == LNGC_('F','I','F','I', CHARSET_UTF8));
	menu.Separator();
	menu.Add(AK_KEYS, callback(EditKeys));
}

bool CommandBridge::Key(dword key, int count) {
	if (key == (K_LEFT|K_CTRL)) {
		PreviousTab();
		return true;
	}
	if (key == (K_RIGHT|K_CTRL)) {
		NextTab();
		return true;
	}
	return false;
}

void CommandBridge::TopMost0() {
	TopMost();
	SetLayout();
	SetSemiTransparent();
}

void CommandBridge::SetLayout() {
	Size scr_sz = GetScreenSize();
	SetRect(1, 1, scr_sz.cx - 1, scr_sz.cy * 3 / 5);
}


#if defined flagPOSIX && defined flagX11
void SetSemiTransparent0(double alpha, XDisplay* display, unsigned long win);
#endif

void CommandBridge::SetSemiTransparent() {
	#if defined flagPOSIX && defined flagX11
	SetSemiTransparent0(alpha, Xdisplay, GetWindow());
	#elif defined flagWIN32
	HWND h = GetTopWindow()->GetHWND();
	SetWindowLongA(h, GWL_EXSTYLE, WS_EX_LAYERED);
	SetLayeredWindowAttributes(h, 0, alpha * 255, LWA_ALPHA);
	#endif
}

















TrayApp::TrayApp() {
	Icon(CommandBridgeImg::icon());
	Tip("This is U++ TrayIcon");
	
	is_exit = false;
	
}

void TrayApp::LeftDouble() {
	PromptOK("CommandBridge is running!");
}

void TrayApp::LeftDown() {
	Close();
}

void TrayApp::Menu(Bar& bar) {
	bar.Add("Info..", THISBACK(LeftDouble));
	bar.Separator();
	bar.Add("Exit", THISBACK(Exit));
}
