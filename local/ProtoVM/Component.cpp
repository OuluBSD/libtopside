#include "ProtoVM.h"


Pin::Pin() {
	AddBidirectional("bi");
	
}

Pin& Pin::SetReference(double voltage) {
	is_ref_volt = true;
	this->voltage = voltage;
	return *this;
}







FlipFlopJK::FlipFlopJK() {
	AddSink("Ck");
	AddSource("~Pr");
	AddSource("~Clr");
	AddSource("D");
	AddSource("~Q");
	
}
