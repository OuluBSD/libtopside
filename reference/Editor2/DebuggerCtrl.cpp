#include "DebuggerCtrl.h"


DebuggerCtrl::DebuggerCtrl() {
/*	Add(tabs.VSizePos().HSizePos());
	
	//tabs.Add(threads, "Threads");
	tabs.Add(callstack, "Calls");
	tabs.Add(callstack);
	tabs.Add(locals, "Locals");
	tabs.Add(locals);
	tabs.Add(thisclass, "This");
	tabs.Add(thisclass);
	tabs.Add(watches, "Watches");
	tabs.Add(watches);
	

	callstack.AddColumn("Frame");
	callstack.AddColumn("PrvFrame");
	callstack.AddColumn("Self");
	callstack.AddColumn("Return");
	callstack.AddColumn("Start");*/
	
}


void DebuggerCtrl::RefreshDisassembly() {
/*	callstack.Clear();
	uint32 fp = arm.reg[11];
	uint32 *frame;
    //GuiPrint("Frame     PrvFrame Self     Return   Start\n");
    do {
        GuiPrint("%08X:", fp);
        frame = (uint32*) VirtMemPtr(fp - 12, 16);
        if (!frame) {
            GuiPrint(" invalid address\n");
            break;
        }
        GuiPrint(" %08X %08X %08X %08X\n", frame[0], frame[1], frame[2], frame[3]);
        callstack.Add(Format("%08X", (int64)fp), Format("%08X", (int64)frame[0]), Format("%08X", (int64)frame[1]), Format("%08X", (int64)frame[2]), Format("%08X", (int64)frame[3]));
        if (frame[0] <= fp) // don't get stuck in infinite loop :) 
            break;
        fp = frame[0];
    } while (frame[2] != 0);*/
}

