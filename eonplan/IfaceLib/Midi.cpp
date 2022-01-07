#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Midi, Mid, M) {
	IfaceLib::Add(this);
	
	COLOR(198, 85, 150)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(MidiSinkDevice) {
			
		}
		CLASS(MidiSourceDevice) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(SinkDevice)
		NATIVE_CLASS(SourceDevice)
		NATIVE_CLASS(Event)
		//UTIL_CLASS()
		
		FUNCTION0R(GetSinkDeviceCount,   int)
		FUNCTION0R(GetSourceDeviceCount, int)
		FUNCTION2R(CreateSinkDevice,   bool, int, NativeSinkDevice&)
		FUNCTION2R(CreateSourceDevice, bool, int, NativeSourceDevice&)
		FUNCTION1V(ClearSinkDevice,   NativeSinkDevice&)
		FUNCTION1V(ClearSourceDevice, NativeSourceDevice&)
		
		FUNCTION2R(PollSink,   bool, NativeSinkDevice&, NativeEvent&)
		FUNCTION2R(PollSource, bool, NativeSinkDevice&, NativeEvent&)
		
	}
	
	
	VENDOR(Portmidi) {
		
	}
	
	
}


NAMESPACE_PLAN_END
