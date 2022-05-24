#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Synth, Syn, Y) {
	IfaceLib::Add(this);
	
	COLOR(200, 179, 81)
	DEPENDENCY(ParallelLib)
	//DEPENDENCY(IMedia)
	HAVE_IS_READY
	
	PKG_IFACE {
		//NATIVE_CLASS(Camera)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(Instrument) {
			NATIVE_INHERIT(Instrument, dev)
			
			//METHOD1R(CreateWebcam, bool, NativeWebcam& this)
			//METHOD1V(ClearWebcam, NativeWebcam& this)
			
			
		}
	}
	
	VENDOR(Fluidsynth) {
		VENDOR_ENABLED_FLAG(FLUIDSYNTH)
		//ENDOR_CLASS(Camera, void*)
		
		v->AddStruct("NativeInstrument")
			.Add("settings",		"fluid_settings_t*")
			.Add("synth",			"fluid_synth_t*")
			.Add("adriver",			"fluid_audio_driver_t*")
			.Add("sfont_id",		"int")
			.Add("sf_loaded",		"bool")
		;
	
	}
	
	
	
}


NAMESPACE_PLAN_END
