#ifndef _EmuCtrl_App_h_
#define _EmuCtrl_App_h_


class EmuApp : public TopWindow {
	bool running = false, stopped = false;
	
	DocEdit log;
	WString output;
	
public:
	typedef EmuApp CLASSNAME;
	EmuApp();
	
	void Data();
	void Init();
	void Start();
	void EmuProcess();
	void RefreshOutput();
	
	void MoveCursor();
	void Scroll();
	void Put(char c);
	void Clear();
	void Write(const char *c);
	void WriteDec(int i);
	void WriteHexPtr(void* p);
	void WriteHexInt(size_t i);
	void NewLine();
	
	
	
};


#endif
