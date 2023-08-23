#ifndef _Emu_Monitor_h_
#define _Emu_Monitor_h_

struct Monitor {
	uint16 *video_memory;
	uint8 cursor_x, cursor_y;
	uint16 cursorLocation;
	
	int Init();
	
	void MoveCursor();
	void Scroll();
	void Put(char c);		// Write a single character out to the screen.
	void Clear();			// Clear the screen to all black.
	Monitor& Write(const char *c);	// Output a null-terminated ASCII string to the monitor.
	Monitor& WriteDec(int i);
	Monitor& WriteHex(void* p);
	Monitor& WriteHex(uint32 i);
	Monitor& NewLine();
};

#define MON global->monitor

#define KDUMPI(x) MON.Write(#x ": ").WriteDec(x).Write("\n");
#define KDUMPH(x) MON.Write(#x ": ").WriteHex((uint32)x).Write("\n");


#endif
