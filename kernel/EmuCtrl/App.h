#ifndef _EmuCtrl_App_h_
#define _EmuCtrl_App_h_


#define KB_QUEUE_LENGTH 16

class EmuApp;

class EmuScreen : public Ctrl {
	EmuApp& app;
	
	// State
	Size grid;
	Color bg, fg;
	Font fnt;
	
	
	TimeCallback tc;
	
protected:
	friend class EmuApp;
	VirtualScreen vscr;
	
public:
	typedef EmuScreen CLASSNAME;
	EmuScreen(EmuApp& a);
	
	void Paint(Draw& d) override;
	void Put(dword d, int count=1);
	void NewLine();
	void ClearScreen();
	void PostRefresh() {PostCallback(THISBACK(Refresh0));}
	void Refresh0() {Refresh();}
	
	Size GetPreferredSize() const;
	
	bool Key(dword key, int count) override;
	
};

class EmuApp : public TopWindow, public Screen {
	bool running = false, stopped = false;
	
	
protected:
	friend class EmuScreen;
	
	EmuScreen scr;
	
public:
	typedef EmuApp CLASSNAME;
	EmuApp();
	~EmuApp();
	
	void OnClose();
	void Data();
	void Init();
	void Start();
	void Stop() {running = false; while (!stopped) Sleep(10);}
	void EmuProcess();
	void RefreshOutput();
	
	
};


#endif
