#include "ProtoVM.h"


ENode& Pcb::AddNode(String name) {
	return Add<ElectricNode>(name);
}

ElcBase& Pcb::AddReferenceSingle(ElcBase& n, int pin_i) {
	TODO
}

void Pcb::Attach(ElectricNodeBase& from, ElectricNodeBase& to) {
	LOG((String)"from " + from.GetDynamicName() + " to " + to.GetDynamicName());
	ASSERT(!from.IsEmpty() && !to.IsEmpty());
	ASSERT(&from != &to);
	
	if (from.IsTrivialSourceDefault() && to.IsTrivialSinkDefault()) {
		ElectricNodeBase::Connector& src = from.GetTrivialSource();
		ElectricNodeBase::Connector& sink = to.GetTrivialSink();
		
		if (!src.IsConnectable())
			throw Exc((String)"source is not connectable, from " + from.GetDynamicName() + " to " + to.GetDynamicName());
		
		if (!sink.IsConnectable())
			throw Exc((String)"sink is not connectable, from " + from.GetDynamicName() + " to " + to.GetDynamicName());
		
		src.links << &sink;
		sink.links << &src;
	}
	else {
		TODO
	}
	
}
