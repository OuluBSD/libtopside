#ifndef _CommandBridge_Terminal_h_
#define _CommandBridge_Terminal_h_


struct TerminalTab : TerminalCtrl, PtyProcess {
	TimeCallback tc;
	CommandBridge* bridge = 0;
	int id = -1;
	
	
	typedef TerminalTab CLASSNAME;
	TerminalTab();
	bool Do();
	bool Key(dword key, int count) override;
	void Menu(Bar& bar);
	void Process();
	String GetMenuTitle() {return "Terminal";}
	void SetBridge(CommandBridge* bridge, int id) {this->bridge = bridge; this->id = id;}
	
	
};


#endif
