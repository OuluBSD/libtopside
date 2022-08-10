#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Synth, Syn, Y) {
	IfaceLib::Add(this);
	
	COLOR(200, 179, 81)
	DEPENDENCY(ParallelLib)
	//DEPENDENCY(IMedia)
	LIBRARY("POSIX", fluidsynth)
	HAVE_IS_READY
	//HAVE_UPDATE
	HAVE_RECV_FINALIZE
	
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
		//VENDOR_CLASS(Camera, void*)
		VENDOR_INCLUDE("", fluidsynth.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		
		v->AddStruct("NativeInstrument")
			.Add("settings",		"fluid_settings_t*")
			.Add("synth",			"fluid_synth_t*")
			.Add("adriver",			"fluid_audio_driver_t*")
			.Add("sfont_id",		"int")
			.Add("sf_loaded",		"bool")
			.Add("sample_rate",		"int")
			.Add("buffer",			"Vector<float>")
			.Add("dry",				"Vector<float*>")
			.Add("fx",				"Vector<float*>")
		;
	
	}
	
	
	
}


NAMESPACE_PLAN_END
