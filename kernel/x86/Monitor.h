#ifndef MONITOR_H
#define MONITOR_H



struct Monitor : Screen {
	uint16 *video_memory;
	uint8 cursor_x, cursor_y;
	uint16 cursorLocation;
	
	int Init();
	
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


#define PANIC(x) MON.Write("\n --> "); \
	MON.Write(__FILE__); MON.Write(":"); \
	MON.WriteDec(__LINE__); MON.Write(" "); \
	MON.Write(x); while(1);

#define MON global->monitor

#define KDUMPI(x) MON.Write(#x ": "); MON.WriteDec(x);            MON.Write("\n");
#define KDUMPH(x) MON.Write(#x ": "); MON.WriteHexInt((size_t)x); MON.Write("\n");

#endif
