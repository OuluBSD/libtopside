#ifndef _LittleCore_VirtualScreen_h_
#define _LittleCore_VirtualScreen_h_


class VirtualScreen : public Screen {
	
public:
	byte* mem = 0;
	uint16 cursor_x = 0, cursor_y = 0;
	uint16 cursorLocation = 0;
	int stride = 0, pitch = 0, sz = 0;
	int width = 0, height= 0;
	
public:
	VirtualScreen();
	~VirtualScreen();
	
	bool Init(int w=80, int h=24);
	void Free();
	
	void MoveCursor() override;
	void Scroll() override;
	void Put(dword d, int count=1) override;			// Write a single character out to the screen.
	void Clear() override;				// Clear the screen to all black.
	void Write(const char *c) override;	// Output a null-terminated ASCII string to the monitor.
	void WriteN(const char *c, int n) override;
	void WriteDec(int i) override;
	void WriteHexPtr(void* p) override;
	void WriteHexInt(size_t i) override;
	void NewLine() override;
	
};


#endif
