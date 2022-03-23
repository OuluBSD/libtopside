#include "ProtoVM.h"

bool Pcb::IsAllConnected() const {
	bool r = true;
	for (ElectricNodeBase& n : nodes) {
		String dn = n.GetDynamicName();
		String nn = n.GetName();
		if (nn.GetCount())
			dn += "(" + nn + ")";
		
		if (n.GetPinWidth() == 0) {
			LOG("Pcb::IsAllConnected: no pins in " << dn);
			r = false;
		}
		
		for (ElectricNodeBase::Connector& c : n.conns) {
			if (!c.IsConnected() && c.IsRequired()) {
				LOG("Pcb::IsAllConnected: " << dn << " pin " << c.name << " not connected");
				r = false;
			}
		}
	}
	return r;
}

ENode& Pcb::AddNode(String name) {
	return Add<ElectricNode>(name);
}

ElcBase& Pcb::AddReferenceSingle(ElcBase& n, int pin_i) {
	for (ElectricNodeBase& r : refs) {
		if (r.type == ElcBase::V_PARTIAL && r.ptr == &n && r.ptr_i == pin_i) {
			return r;
		}
	}
	ASSERT(pin_i >= 0 && pin_i < n.conns.GetCount());
	ElcBase::Connector& conn = n.conns[pin_i];
	
	ElectricNodeBase& r = refs.Add();
	r.pcb = this;
	r.type = ElcBase::V_PARTIAL;
	r.ptr = &n;
	r.ptr_i = pin_i;
	r.ptr_conn = &conn;
	return r;
}

ElcBase& Pcb::AddReferenceRange(ElcBase& n, int pin_i, int pin_count) {
	for (ElectricNodeBase& r : refs) {
		if (r.type == ElcBase::V_PARTIAL_RANGE && r.ptr == &n && r.ptr_i == pin_i && r.ptr_n == pin_count) {
			return r;
		}
	}
	ASSERT(pin_i >= 0 && pin_i < n.conns.GetCount());
	ElcBase::Connector& conn = n.conns[pin_i];
	
	ElectricNodeBase& r = refs.Add();
	r.pcb = this;
	r.type = ElcBase::V_PARTIAL_RANGE;
	r.ptr = &n;
	r.ptr_i = pin_i;
	r.ptr_n = pin_count;
	r.ptr_conn = &conn;
	return r;
}

void Pcb::Attach(ElectricNodeBase& from, ElectricNodeBase& to) {
	String an = from.GetName();
	String bn = to.GetName();
	String a = (String)from.GetDynamicName();
	String b = (String)to.GetDynamicName();
	if (an.GetCount()) a += "(" + an + ")";
	if (bn.GetCount()) b += "(" + bn + ")";
	
	LOG((String)"from " + a + " to " + b);
	ASSERT(!from.IsEmpty() && !to.IsEmpty());
	ASSERT(&from != &to);
	int aw = from.GetPinWidth();
	int bw = to.GetPinWidth();
	bool atriv = from.IsTrivialSourceDefault();
	bool btriv = to.IsTrivialSinkDefault();
	bool atrivr = from.IsTrivialSourceDefaultRange();
	bool btrivr = to.IsTrivialSinkDefaultRange();
	
	
	if (atriv && btriv) {
		ElectricNodeBase::Connector& src = from.GetTrivialSource();
		ElectricNodeBase::Connector& sink = to.GetTrivialSink();
		
		if (!src.IsConnectable())
			throw Exc((String)"source is not connectable, from " + a + " to " + b);
		
		if (!sink.IsConnectable())
			throw Exc((String)"sink is not connectable, from " + a + " to " + b);
		
		src.links << &sink;
		sink.links << &src;
	}
	else if (aw == bw && atrivr && btrivr) {
		for(int i = 0; i < aw; i++) {
			ElectricNodeBase::Connector& src = from.Get(i);
			ElectricNodeBase::Connector& sink = to.Get(i);
			
			if (!src.IsConnectable())
				throw Exc((String)"source is not connectable, from " + a + " to " + b);
			
			if (!sink.IsConnectable())
				throw Exc((String)"sink is not connectable, from " + a + " to " + b);
			
			src.links << &sink;
			sink.links << &src;
		}
	}
	else {
		TODO
	}
	
}
