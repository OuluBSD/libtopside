#ifndef _EmuCtrl_App_h_
#define _EmuCtrl_App_h_


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
};

class EmuApp : public TopWindow {
	bool running = false, stopped = false;
	
	
protected:
	friend class EmuScreen;
	
	EmuScreen scr;
	
public:
	typedef EmuApp CLASSNAME;
	EmuApp();
	~EmuApp();
	
	void Data();
	void Init();
	void Start();
	void Stop() {running = false; while (!stopped) Sleep(10);}
	void EmuProcess();
	void RefreshOutput();
	
	void MoveCursor();
	void Scroll();
	void Put(char c);
	void Clear();
	void WriteString(const String& s);
	void Write(const char *c);
	void WriteN(const char *c, int len);
	void WriteDec(int i);
	void WriteHexPtr(void* p);
	void WriteHexInt(size_t i);
	void NewLine();
	
	
	
};


#endif
