#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(MidiFile, Mif, m) {
	IfaceLib::Add(this);
	
	COLOR(114, 157, 142)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(MidiFile)
		NATIVE_CLASS(Process)
		//UTIL_CLASS()
		
		
	}
	
	NAMESPACE {
		CLASS(MidiFile) {
			NATIVE_INHERIT(MidiFile, file)
			
			METHOD1R(CreateMidiFile, bool, NativeMidiFile& this)
			METHOD1V(ClearMidiFile, NativeMidiFile& this)
		}
	}
	
}


NAMESPACE_PLAN_END
