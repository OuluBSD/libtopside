#ifndef _CommandBridge_CommandBridge_h
#define _CommandBridge_CommandBridge_h

#include <CtrlLib/CtrlLib.h>
#include <TabBar/TabBar.h>
#include <Terminal/Terminal.h>
#include <PtyProcess/PtyProcess.h>
using namespace Upp;

#ifdef flagHAVE_FTP
#include <Ftp/Ftp.h>
#endif

#define KEYGROUPNAME "AK"
#define KEYNAMESPACE AKKeys
#define KEYFILE      <CommandBridge/CommandBridge.key>
#include             <CtrlLib/key_header.h>

using namespace AKKeys;

#include "Images.h"
#include "Console.h"
#include "Terminal.h"

class TrayApp : public TrayIcon {
	
	bool is_exit;
	
public:
	typedef TrayApp CLASSNAME;

	TrayApp();
	
	bool IsExit() const {return is_exit;}
	void Exit() {is_exit = true; Break();}
	void Close() {Break();}
	
	virtual void LeftDouble();
	virtual void LeftDown();
	virtual void Menu(Bar& bar);
};


class CommandBridge : public TopWindow {
	MenuBar						menu;
	
protected:
	ArrayMap<int, Console>		cons;
	ArrayMap<int, TerminalTab>	terms;
	TabBar						tabs;
	double						alpha = 0.9;
	int							id_counter;
	bool						def_terminal = true;
	
	void ShowTabId(int i);
	void ShowTab();
	
public:
	typedef CommandBridge CLASSNAME;
	CommandBridge();
	
	Console& NewConsole();
	TerminalTab& NewTerminal();
	Console* GetActiveConsole();
	TerminalTab* GetActiveTerminal();
	void SetSemiTransparent();
	void Quit() {PostClose();}
	void AddConsole() {NewConsole();}
	void AddTerminal() {NewTerminal();}
	void AddDefault() {if (def_terminal) AddTerminal(); else AddConsole();}
	void CloseTab();
	void CloseTabId(int id);
	void PreviousTab();
	void NextTab();
	void TabClosed(Value tab);
	void MainMenu(Bar& menu);
	void AppMenu(Bar& menu);
	void ViewMenu(Bar& menu);
	void SetupMenu(Bar& menu);
	void RefreshMenu();
	void SetLang(int lang);
	void RefreshTitle(int id);
	void RefreshTitle1(String title, int id);
	void ViewChange(int id);
	void RemoveId(int id);
	
	virtual bool Key(dword key, int count);

	void PostClose() {PostCallback(THISBACK(Close0));}
	void Close0() {Close();}
	void PostTopMost() {PostCallback(THISBACK(TopMost0));}
	void TopMost0();
	void SetLayout();
	void PostSetLayout() {PostCallback(THISBACK(SetLayout));}
	void PostSetSemiTransparent() {PostCallback(THISBACK(SetSemiTransparent));}
	
};

#endif
