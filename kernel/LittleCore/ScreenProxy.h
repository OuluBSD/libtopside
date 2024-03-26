#ifndef _LittleCore_ScreenProxy_h_
#define _LittleCore_ScreenProxy_h_


class ScreenProxy : public Screen {
	Screen* target = 0;
	
public:
	typedef ScreenProxy CLASSNAME;
	ScreenProxy();
	
	void SetTarget(Screen& s) {target = &s;}
	void MoveCursor() override;
	void Scroll() override;
	void Put(char c) override;			// Write a single character out to the screen.
	void Clear() override;				// Clear the screen to all black.
	void Write(const char *c) override;	// Output a null-terminated ASCII string to the monitor.
	void WriteN(const char *c, int n) override;
	void WriteDec(int i) override;
	void WriteHexPtr(void* p) override;
	void WriteHexInt(size_t i) override;
	void NewLine() override;
	
};


#endif
