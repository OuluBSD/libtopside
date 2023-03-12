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
	AddSource("~Pr");
	AddSource("~Clr");
	AddSource("D");
	AddSource("~Q");
	
}




Crystal::Crystal() {
	AddSink("I");
	AddSource("O");
	
}

ElcNor::ElcNor() {
	AddSink("I0");
	AddSink("I1");
	AddSource("C");
	
}

ElcNand::ElcNand() {
	AddSink("I0");
	AddSink("I1");
	AddSource("O");
	
}

ElcNot::ElcNot() {
	AddSink("I");
	AddSource("O");
	
}

ElcCapacitor::ElcCapacitor() {
	AddSink("I");
	AddSource("O");
	
}


NAMESPACE_TOPSIDE_END
