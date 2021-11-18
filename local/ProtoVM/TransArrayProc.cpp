#include "ProtoVM.h"


void TransArrayProc::InitTest(int i) {
	test = i;
	
	if (test == 0) {
		GridProgrammer prog(grid);
		prog.SetBlockIn(0,0, 0); // connect block(0,0) line 0 channel in (from block (-1,0))
		prog.SetLine(0,0, 0, 0,1,2); // In block(0,0) and line 0: connect ch0 to ch2 with ch1 as trans amp
		prog.SetLine(0,0, 1, 0,1,0);
		
		
		
	}
	else Panic("Invalid test id");
	
}

void TransArrayProc::Tick() {
	if (test >= 0) {
		if (test == 0) {
			if (iter == 0) {
				MemoryProgrammer mprog(grid);
				mprog.SetBit(-1,0,0, true); // set block(-1,0) ch0 value true
				// -> AND output false
			}
			else if (iter == 1) {
				MemoryProgrammer mprog(grid);
				mprog.SetBit(-1,0,1, true);
				// -> AND output false
			}
			else if (iter == 1) {
				MemoryProgrammer mprog(grid);
				mprog.SetBit(-1,0,0, true);
				mprog.SetBit(-1,0,1, true);
				// -> AND output false
			}
		}
	}
	
	TODO
	
	iter++;
}
