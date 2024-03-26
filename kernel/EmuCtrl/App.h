#ifndef _EmuCtrl_App_h_
#define _EmuCtrl_App_h_


#define KB_QUEUE_LENGTH 16

class EmuApp;

class EmuScreen : public Ctrl {
	EmuApp& app;
	
	// State
	Size scr_txt_sz;
	Size grid;
	Point cur;
	Color bg, fg;
	Font fnt;
	Vector<wchar> scr_txt;
	
	void ResizeTxt(Size sz) {scr_txt_sz = sz; scr_txt.SetCount(sz.cx * sz.cy, 0);}
	
	TimeCallback tc;
public:
	typedef EmuScreen CLASSNAME;
	EmuScreen(EmuApp& a);
	
	void Paint(Draw& d) override;
	void Put(wchar w);
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
	
	void MoveCursor() override;
	void Scroll() override;
	void Put(char c) override;
	void Clear() override;
	void WriteString(const String& s);
	void Write(const char *c) override;
	void WriteN(const char *c, int len) override;
	void WriteDec(int i) override;
	void WriteHexPtr(void* p) override;
	void WriteHexInt(size_t i) override;
	void NewLine() override;
	
	
};


#endif
