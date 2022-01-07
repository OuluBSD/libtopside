#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(MidiFile, Mif, m) {
	IfaceLib::Add(this);
	
	COLOR(114, 157, 142)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(MidiFile) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(MidiFile)
		NATIVE_CLASS(Process)
		//UTIL_CLASS()
		
		FUNCTION1R(CreateMidiFile, bool, NativeMidiFile&)
		FUNCTION1V(ClearMidiFile, NativeMidiFile&)
		
	}
	
}


NAMESPACE_PLAN_END
