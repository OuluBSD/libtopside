#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


bool Pcb::Tick() {
	for (ElectricNodeBase& n : nodes) {
		if (!n.Tick()) {
			LOG("error: component " << n.GetClassName() << "(" << n.GetName() << ") failed");
			return false;
		}
	}
	return true;
}

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
	
	LOG((String)"from " + a + "(" + an + ") to " + b + "(" + bn + ")");
	ASSERT(!from.IsEmpty() && !to.IsEmpty());
	ASSERT(&from != &to);
	int aw = from.GetPinWidth();
	int bw = to.GetPinWidth();
	bool atriv = from.IsTrivialSourceDefault();
	bool btriv = to.IsTrivialSinkDefault();
	bool atrivr = from.IsTrivialSourceDefaultRange();
	bool btrivr = to.IsTrivialSinkDefaultRange();
	
	Pin* src_pin = CastPtr<Pin>(&from);
	Pin* sink_pin = CastPtr<Pin>(&to);
	ASSERT(!src_pin || !src_pin->is_ref_volt || !src_pin->is_high);
	ASSERT(!sink_pin || !sink_pin->is_ref_volt || sink_pin->is_high);
	
	
	if (atriv && btriv) {
		ElectricNodeBase::Connector& src = from.GetTrivialSource();
		ElectricNodeBase::Connector& sink = to.GetTrivialSink();
		
		if (!src.IsConnectable())
			throw Exc((String)"source is not connectable, from " + a + " to " + b);
		
		if (!sink.IsConnectable())
			throw Exc((String)"sink is not connectable, from " + a + " to " + b);
		
		ASSERT(sink.is_sink && src.is_src);
		src.links.Add().conn = &sink;
		sink.links.Add().conn = &src;
	}
	else if (aw == bw && atrivr && btrivr) {
		for(int i = 0; i < aw; i++) {
			ElectricNodeBase::Connector& src = from.Get(i);
			ElectricNodeBase::Connector& sink = to.Get(i);
			
			if (!src.IsConnectable())
				throw Exc((String)"source is not connectable, from " + a + " to " + b);
			
			if (!sink.IsConnectable())
				throw Exc((String)"sink is not connectable, from " + a + " to " + b);
			
			ASSERT(sink.is_sink && src.is_src);
			src.links.Add().conn = &sink;
			sink.links.Add().conn = &src;
		}
	}
	else /*if (aw != bw && aw && bw)*/ {
		int pin_width = min(aw, bw);
		//int a_off = from.GetPinBegin();
		//int b_off = to.GetPinBegin();
		for(int i = 0; i < pin_width; i++) {
			ElectricNodeBase::Connector& src = from.Get(i);
			ElectricNodeBase::Connector& sink = to.Get(i);
			
			if (!src.IsConnectable())
				throw Exc((String)"source is not connectable, from " + a + " to " + b);
			
			if (!sink.IsConnectable())
				throw Exc((String)"sink is not connectable, from " + a + " to " + b);
			
			ASSERT(sink.is_sink && src.is_src);
			src.links.Add().conn = &sink;
			sink.links.Add().conn = &src;
		}
	}
	
}

void Pcb::GetLinks(Array<Link>& links) {
	
	for (ElectricNodeBase& n : nodes) {
		for (ElectricNodeBase::Connector& from : n.conns) {
			for (ElectricNodeBase::CLink& from_clink : from.links) {
				if (from_clink.link != 0)
					continue;
				
				ElectricNodeBase::Connector& to = *from_clink.conn;
				ElectricNodeBase::CLink* to_clink = 0;
				for (ElectricNodeBase::CLink& clink : to.links) {
					if (clink.conn == &from)
						to_clink = &clink;
				}
				ASSERT(to_clink);
				ASSERT(to.base != &n);
				
				Pin* src_pin = CastPtr<Pin>(&n);
				Pin* sink_pin = CastPtr<Pin>(to.base);
				bool src_is_sink = src_pin && src_pin->is_ref_volt && src_pin->is_high;
				bool sink_is_src = sink_pin && sink_pin->is_ref_volt && !sink_pin->is_high;
				bool src_is_src = src_pin && src_pin->is_ref_volt && !src_pin->is_high;
				bool sink_is_sink = sink_pin && sink_pin->is_ref_volt && sink_pin->is_high;
				
				if (src_pin && src_pin->is_ref_volt && sink_pin && sink_pin->is_ref_volt && src_pin->is_high == sink_pin->is_high) {
					Panic("internal error");
				}
					
				Link& l = links.Add();
				if (from.is_src && from.is_sink && !to.is_src) {
					l.sink = &to;
					l.src = &from;
				}
				else if (!src_is_src && !sink_is_sink && (src_is_sink || sink_is_src || from.is_sink || to.is_src)) {
					l.sink = &from;
					l.src = &to;
				}
				else {
					l.sink = &to;
					l.src = &from;
				}
				ASSERT(l.sink->is_sink && l.src->is_src);
				
				Pin* test_src_pin = CastPtr<Pin>(l.src->base);
				ASSERT(!test_src_pin || !test_src_pin->is_ref_volt || !test_src_pin->is_high);
				
				from_clink.link = &l;
				to_clink->link = &l;
			}
		}
	}
	
	
	
}


NAMESPACE_TOPSIDE_END
