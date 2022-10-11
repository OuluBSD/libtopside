#include "ProtoVM.h"




bool Machine::Init() {
	
	// Check that all pins are connected
	for (Pcb& pcb : pcbs) {
		if (!pcb.IsAllConnected()) {
			LOG("Pcb \"" + pcb.GetName() + "\" not fully connected");
			return false;
		}
	}
	LOG("Machine::Init: all pcbs fully connected!");
	
	LinkMap l;
	for (Pcb& pcb : pcbs) {
		pcb.GetLinks(l.links);
	}
	
	l.UpdateLinkLayers();
	
	
	TODO
	
	return true;
}

void Machine::Tick() {
	TODO
}

Pcb& Machine::AddPcb() {
	Pcb& p = pcbs.Add();
	p.mach = this;
	return p;
}
