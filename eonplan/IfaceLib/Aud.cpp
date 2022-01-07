#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Audio, Aud, A) {
	IfaceLib::Add(this);
	
	COLOR(226, 212, 0)
	DEPENDENCY(Local)
	
	NAMESPACE {
		CLASS(AudioSinkDevice) {
			
		}
		CLASS(AudioSourceDevice) {
			
		}
	}
	
	PKG_IFACE {
		NATIVE_CLASS(SinkDevice)
		NATIVE_CLASS(SourceDevice)
		//UTIL_CLASS()
		
		FUNCTION0R(GetSinkDeviceCount,   int)
		FUNCTION0R(GetSourceDeviceCount, int)
		FUNCTION2R(CreateSinkDevice,   bool, int, NativeSinkDevice&)
		FUNCTION2R(CreateSourceDevice, bool, int, NativeSourceDevice&)
		FUNCTION1V(ClearSinkDevice,   NativeSinkDevice&)
		FUNCTION1V(ClearSourceDevice, NativeSourceDevice&)
		
		FUNCTION2R(SetSinkCallback,   bool, void*, SinkCallbackFn)
		FUNCTION2R(SetSourceCallback, bool, void*, SourceCallbackFn)
		
		FUNCTION1R(GetSinkFormatCount,   int, NativeSinkDevice&)
		FUNCTION1R(GetSourceFormatCount, int, NativeSourceDevice&)
		FUNCTION7R(GetSinkFormat,   bool, NativeSinkDevice&, int, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float);
		FUNCTION7R(GetSourceFormat, bool, NativeSinkDevice&, int, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float);
		
	}
	
	
	VENDOR(Sdl) {
		
	}
	
	VENDOR(Portaudio) {
		
	}
	
	
}


NAMESPACE_PLAN_END
