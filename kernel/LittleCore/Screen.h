#ifndef _LittleCore_Screen_h_
#define _LittleCore_Screen_h_


class Screen {
	
public:
	typedef Screen CLASSNAME;
	Screen() {}
	virtual ~Screen() {}
	
	
	virtual void MoveCursor() {}
	virtual void Scroll() {};
	virtual void Put(dword d, int count) {};		// Write a single character out to the screen.
	virtual void Clear() {};			// Clear the screen to all black.
	virtual void Write(const char *c) {};	// Output a null-terminated ASCII string to the monitor.
	virtual void WriteN(const char *c, int n) {};
	virtual void WriteDec(int i) {};
	virtual void WriteHexPtr(void* p) {};
	virtual void WriteHexInt(size_t i) {};
	virtual void NewLine() {};
	
	void WriteHex(size_t i) {return WriteHexInt(i);}
	void WriteHex(void* p) {return WriteHexPtr(p);}
	
};


#endif
