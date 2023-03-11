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
	l.UpdateProcess();
	
	RunInitOps();
	
	return true;
}

bool Machine::RunInitOps() {
	for (const ProcessOp& op : l.init_ops) {
		switch (op.type) {
			break;
			
		default: TODO
		}
	}
	return true;
}

bool Machine::RunRtOps() {
	for (const ProcessOp& op : l.rt_ops) {
		switch (op.type) {
		case ProcessType::BIT_READ:
		case ProcessType::BIT_WRITE:
		case ProcessType::BIT_RW:
			ASSERT(op.processor);
			if (!op.processor->Process(op.type, op.mem_bits, op.id, *op.dest, op.dest_id)) {
				LOG("error: processing failed in " << op.processor->GetClassName());
				return false;
			}
			break;
			
		case ProcessType::BYTE_READ:
		case ProcessType::BYTE_WRITE:
		case ProcessType::BYTE_RW:
			ASSERT(op.processor);
			if (!op.processor->Process(op.type, op.mem_bytes, op.id, *op.dest, op.dest_id)) {
				LOG("error: processing failed in " << op.processor->GetClassName());
				return false;
			}
			break;
			
		default:
			TODO
			break;
			
		}
	}
	return true;
}

bool Machine::Tick() {
	for (Pcb& pcb : pcbs) {
		if (!pcb.Tick())
			return false;
	}
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
