#ifndef _Emu_Monitor_h_
#define _Emu_Monitor_h_

class Monitor : public ScreenProxy {
	
};


#define MON global->monitor

#define KDUMPI(x) MON.Write(#x ": ").WriteDec(x).Write("\n");
#define KDUMPH(x) MON.Write(#x ": ").WriteHex((uint32)x).Write("\n");


#endif
