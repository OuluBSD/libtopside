#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Synth, Syn, Y) {
	IfaceLib::Add(this);
	
	COLOR(200, 179, 81)
	DEPENDENCY(ParallelLib)
	DEPENDENCY(SoftInstru)
	DEPENDENCY_("FLUIDSYNTH", ports/fluidlite)
	//DEPENDENCY(IMedia)
	//LIBRARY("POSIX", fluidsynth)
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
	
	VENDOR(Soft) {
		VENDOR_INCLUDE("", SoftInstru/SoftInstru.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		
		v->AddStruct("NativeInstrument")
			.Add("instrument",		"SoftInstru::Instrument")
			.Add("sf_loaded",		"bool")
			.Add("sample_rate",		"int")
		;
	
	}
	
	VENDOR(Fluidsynth) {
		VENDOR_ENABLED_FLAG(FLUIDSYNTH)
		//VENDOR_CLASS(Camera, void*)
		VENDOR_INCLUDE("", ports/fluidlite/fluidlite.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		
		v->AddStruct("NativeInstrument")
			.Add("settings",		"fluid_settings_t*")
			.Add("synth",			"fluid_synth_t*")
			.Add("sfont_id",		"int")
			.Add("sf_loaded",		"bool")
			.Add("sample_rate",		"int")
			.Add("buffer",			"Vector<float>")
			.Add("dry",				"Vector<float*>")
			.Add("fx",				"Vector<float*>")
			.Add("flag",			"RunningFlag")
			.Add("packets",			"Array<Vector<byte>>")
			.Add("lock",			"Mutex")
		;
	
	}
	
	
	
}


NAMESPACE_PLAN_END
