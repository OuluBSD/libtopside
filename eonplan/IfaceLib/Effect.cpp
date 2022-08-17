#include "IfaceLib.h"


NAMESPACE_PLAN_BEGIN


PKG(Effect, Fx, X) {
	IfaceLib::Add(this);
	
	COLOR(28, 255, 150)
	DEPENDENCY(AudioCore)
	DEPENDENCY(ParallelLib)
	//LIBRARY("POSIX", )
	HAVE_IS_READY
	//HAVE_UPDATE
	HAVE_RECV_FINALIZE
	
	PKG_IFACE {
		//NATIVE_CLASS(Camera)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(Effect) {
			NATIVE_INHERIT(Effect, dev)
			
			//METHOD1R(CreateWebcam, bool, NativeWebcam& this)
			//METHOD1V(ClearWebcam, NativeWebcam& this)
			
			
		}
	}
	
	VENDOR(AudioCore) {
		VENDOR_INCLUDE("", AudioCore/AudioCore.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		
		v->AddStruct("NativeEffect")
			.Add("effect",			"One<Audio::Effect>")
			.Add("channel_count",	"int")
			.Add("sample_rate",		"int")
			.Add("last_audio_in",	"Packet")
		;
	
	}
}

NAMESPACE_PLAN_END
