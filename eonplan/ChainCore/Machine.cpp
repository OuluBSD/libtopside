#include "ChainCore.h"

Machine::Machine() {
	
}

void Machine::Init() {
	Stream s;
	s.m = this;
	
	Serialize(s);
	
}

void Machine::OnChain(Chain& c) {
	
	LOG("TODO Machine::OnChain");
	
}

