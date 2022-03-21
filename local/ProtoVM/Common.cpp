#include "ProtoVM.h"


ElectricNodeBase::ElectricNodeBase() {
	
}

ElectricNodeBase& ElectricNodeBase::operator>>(ElectricNodeBase& b) {
	pcb->Attach(*this, b);
	return b;
}

ElectricNodeBase& ElectricNodeBase::operator[](String code) {
	int i = 0;
	for (Connector& c : conns) {
		if (c.name == code) {
			
			// create reference node to pcb
			return pcb->AddReferenceSingle(*this, i);
		}
		i++;
	}
	
	THROW(Exc("did not find pin " + code + " in " + GetDynamicName()));
}

ElectricNodeBase& ElectricNodeBase::operator[](int i) {
	TODO
}

bool ElectricNodeBase::IsTrivialSourceDefault() const {
	return (bi_count + src_count) == 1;
}

bool ElectricNodeBase::IsTrivialSinkDefault() const {
	return (bi_count + sink_count) == 1;
}

ElectricNodeBase::Connector& ElectricNodeBase::GetTrivialSource() {
	ASSERT(IsTrivialSourceDefault());
	for (Connector& c : conns)
		if (c.is_src)
			return c;
	Panic("internal error");
	NEVER();
}

ElectricNodeBase::Connector& ElectricNodeBase::GetTrivialSink() {
	ASSERT(IsTrivialSinkDefault());
	for (Connector& c : conns)
		if (c.is_sink)
			return c;
	Panic("internal error");
	NEVER();
}

ElectricNodeBase::Connector& ElectricNodeBase::AddBidirectional(String name) {
	Connector& conn = conns.Add();
	conn.name = name;
	conn.is_sink = conn.is_src = true;
	bi_count++;
	return conn;
}

ElectricNodeBase::Connector& ElectricNodeBase::AddSource(String name) {
	Connector& conn = conns.Add();
	conn.name = name;
	conn.is_src = true;
	src_count++;
	return conn;
}

ElectricNodeBase::Connector& ElectricNodeBase::AddSink(String name) {
	Connector& conn = conns.Add();
	conn.name = name;
	conn.is_sink = true;
	sink_count++;
	return conn;
}
















ElectricNode::ElectricNode() {
	AddBidirectional("A").SetMultiConn();
}


