#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


bool Machine::Init() {
	
	// Check that all pins are connected
	for (Pcb& pcb : pcbs) {
		if (!pcb.IsAllConnected()) {
			LOG("Pcb \"" + pcb.GetName() + "\" not fully connected");
			return false;
		}
	}
	LOG("Machine::Init: all pcbs fully connected!");
	
	for (Pcb& pcb : pcbs) {
		pcb.GetLinks(l.links);
	}
	
	l.UpdateLinkLayers();
	
	if (!l.UpdateProcess())
		return false;
	
	RunInitOps();
	
	return true;
}

bool Machine::RunInitOps() {
	/*for (const ProcessOp& op : l.init_ops) {
		switch (op.type) {
		default: TODO
		}
		TODO
	}*/
	return true;
}

bool Machine::RunRtOps() {
	int op_i = 0;
	for (const ProcessOp& op : l.rt_ops) {
		switch (op.type) {
		//case ProcessType::READ:
		case ProcessType::WRITE:
			ASSERT(op.processor);
			if (!op.processor->Process(op.type, op.mem_bytes, op.mem_bits, op.id, *op.dest, op.dest_id)) {
				LOG("error: processing failed in " << op.processor->GetClassName());
				return false;
			}
			break;
			
		case ProcessType::TICK:
			if (!op.dest->Tick())
				return false;
			break;
			
		default:
			TODO
			break;
		}
		op_i++;
	}
	return true;
}

bool Machine::Tick() {
	/*for (Pcb& pcb : pcbs) {
		if (!pcb.Tick())
			return false;
	}*/
	if (!RunRtOps())
		return false;
	return true;
}

Pcb& Machine::AddPcb() {
	Pcb& p = pcbs.Add();
	p.mach = this;
	return p;
}


NAMESPACE_TOPSIDE_END
