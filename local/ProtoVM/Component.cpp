#include "ProtoVM.h"


Pin::Pin() {
	AddBidirectional("bi");
	
}

Pin& Pin::SetReference(double voltage) {
	is_ref_volt = true;
	this->voltage = voltage;
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
	AddSink("A");
	AddSink("B");
	AddSource("C");
	
}

ElcNand::ElcNand() {
	AddSink("A");
	AddSink("B");
	AddSource("C");
	
}

ElcNot::ElcNot() {
	AddSink("I");
	AddSource("O");
	
}

ElcCapacitor::ElcCapacitor() {
	AddSink("I");
	AddSource("O");
	
}
