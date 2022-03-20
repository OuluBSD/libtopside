#include "ProtoVM.h"


ElectricNodeBase::ElectricNodeBase() {
	
}

ElectricNodeBase& ElectricNodeBase::operator>>(ElectricNodeBase& b) {
	pcb->Attach(*this, b);
	return *this;
}

ElectricNodeBase& ElectricNodeBase::operator[](String code) {
	TODO
}

ElectricNodeBase& ElectricNodeBase::operator[](int i) {
	TODO
}

