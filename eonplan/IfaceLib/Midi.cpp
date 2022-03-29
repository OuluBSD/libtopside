#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Midi, Mid, M) {
	IfaceLib::Add(this);
	
	COLOR(198, 85, 150)
	DEPENDENCY(ParallelLib)
	
	PKG_IFACE {
		NATIVE_CLASS(SinkDevice)
		NATIVE_CLASS(SourceDevice)
		NATIVE_CLASS(Event)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(MidiSinkDevice) {
			NATIVE_INHERIT(SinkDevice, dev)
			
			METHOD0R(GetSinkDeviceCount, int)
			METHOD2R(CreateSinkDevice, bool, int dev_i, NativeSinkDevice& this)
			METHOD1V(ClearSinkDevice, NativeSinkDevice& this)
			METHOD2R(PollSink, bool, NativeSinkDevice& this, NativeEvent& ev)
			
		}
		CLASS(MidiSourceDevice) {
			NATIVE_INHERIT(SourceDevice, dev)
			
			METHOD0R(GetSourceDeviceCount, int)
			METHOD2R(CreateSourceDevice, bool, int dev_i, NativeSourceDevice& this)
			METHOD1V(ClearSourceDevice, NativeSourceDevice& this)
			METHOD2R(PollSource, bool, NativeSourceDevice& this, NativeEvent& ev)
			
		}
	}
	
	
	VENDOR(Portmidi) {
		
	}
	
	
}


NAMESPACE_PLAN_END
