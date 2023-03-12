#include "ProtoVM.h"

NAMESPACE_TOPSIDE_BEGIN


Pin::Pin() {
	AddBidirectional("bi");
	
}

Pin& Pin::SetReference(bool is_high) {
	is_ref_volt = true;
	this->is_high = is_high;
	Clear();
	AddBidirectional("0").SetMultiConn();
	return *this;
}







FlipFlopJK::FlipFlopJK() {
	AddSink("Ck");
	AddSource("~Pr").SetMultiConn();
	AddSource("~Clr").SetMultiConn();
	AddSource("D").SetMultiConn();
	AddSource("~Q").SetMultiConn();
	
}




Crystal::Crystal() {
	AddSink("I");
	AddSource("O").SetMultiConn();
	
}

ElcNor::ElcNor() {
	AddSink("I0");
	AddSink("I1");
	AddSource("C").SetMultiConn();
	
}

ElcNand::ElcNand() {
	AddSink("I0");
	AddSink("I1");
	AddSource("O").SetMultiConn();
	
}

ElcNot::ElcNot() {
	AddSink("I");
	AddSource("O").SetMultiConn();
	
}

ElcCapacitor::ElcCapacitor() {
	AddSink("I");
	AddSource("O").SetMultiConn();
	
}


NAMESPACE_TOPSIDE_END
