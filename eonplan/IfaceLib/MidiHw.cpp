#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(MidiHw, Mid, M) {
	IfaceLib::Add(this);
	
	COLOR(198, 85, 150)
	DEPENDENCY(ParallelLib)
	HAVE_IS_READY
	
	PKG_IFACE {
		//NATIVE_CLASS(Camera)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(Source) {
			NATIVE_INHERIT(Source, dev)
			
			//METHOD1R(CreateWebcam, bool, NativeWebcam& this)
			//METHOD1V(ClearWebcam, NativeWebcam& this)
			
			
		}
	}
	
	VENDOR(Portmidi) {
		VENDOR_ENABLED_FLAG(PORTMIDI)
		//ENDOR_CLASS(Camera, void*)
		
		v->AddStruct("NativeSource")
			.Add("info",		"const PmDeviceInfo*")
			.Add("in_queue",	"PmQueue*")
			.Add("id",			"int")
			.Add("midi_in",		"PmStream*")
		;
	
	}
	
}


NAMESPACE_PLAN_END
