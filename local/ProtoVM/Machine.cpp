#include "ProtoVM.h"
#if 0

void InterfaceBus::Attach(Board* b) {
	for (int i = 0; i < IFACE_SLOTS; i++) {
		if (slots[i] == NULL) {
			slots[i] = b;
			b->bus = this;
			b->iface_slot = i;
			return;
		}
	}
	Panic("could not attach board to interface bus");
}


void MemoryBoard::Tick() {
	
}

void DiskControllerBoard::Tick() {
	
}

void VideoBoard::Tick() {
	
}

void ComputerBoard::Tick() {
	
}

void Machine::Tick() {
	//back.Tick();
	ir.Tick();
	mem.Tick();
	disk.Tick();
	video.Tick();
	computer.Tick();
}

#endif
