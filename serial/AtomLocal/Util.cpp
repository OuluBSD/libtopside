#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN


JoinerBase::JoinerBase() {
	
}

bool JoinerBase::AltInitialize(const Script::WorldState& ws) {
	
	return true;
}

void JoinerBase::AltUninitialize() {
	
}

void JoinerBase::AltForward(FwdScope& fwd) {
	
}



SplitterBase::SplitterBase() {
	
}

bool SplitterBase::AltInitialize(const Script::WorldState& ws) {
	
	return true;
}

void SplitterBase::AltUninitialize() {
	
}

void SplitterBase::AltForward(FwdScope& fwd) {
	
}

	
NAMESPACE_SERIAL_END
