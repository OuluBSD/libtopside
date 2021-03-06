#include "IfaceLib.h"

NAMESPACE_PLAN_BEGIN



PKG(Audio, Aud, A) {
	IfaceLib::Add(this);
	
	COLOR(226, 212, 0)
	DEPENDENCY(ParallelLib)
	HAVE_NEGOTIATE_FORMAT
	
	PKG_IFACE {
		NATIVE_CLASS(SinkDevice)
		NATIVE_CLASS(SourceDevice)
		//UTIL_CLASS()
		
	}
	
	NAMESPACE {
		CLASS(SinkDevice) {
			NATIVE_INHERIT(SinkDevice, dev)
			
			METHOD0R(GetSinkDeviceCount, int)
			METHOD2R(CreateSinkDevice, bool, int sink_i, NativeSinkDevice& this)
			METHOD1V(ClearSinkDevice, NativeSinkDevice& this)
			METHOD2R(SetSinkCallback, bool, void* data, DataCallbackFn cb)
			METHOD1R(GetSinkFormatCount, int, NativeSinkDevice& this)
			METHOD7R(GetSinkFormat, bool, NativeSinkDevice& this, int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float);
		}
		CLASS(SourceDevice) {
			NATIVE_INHERIT(SourceDevice, dev)
			
			METHOD0R(GetSourceDeviceCount, int)
			METHOD2R(CreateSourceDevice, bool, int sink_i, NativeSourceDevice& this)
			METHOD1V(ClearSourceDevice, NativeSourceDevice& this)
			METHOD2R(SetSourceCallback, bool, void* data, DataCallbackFn cb)
			METHOD1R(GetSourceFormatCount, int, NativeSourceDevice& this)
			METHOD7R(GetSourceFormat, bool, NativeSourceDevice& this, int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float);
		}
	}
	
	VENDOR(Portaudio) {
		const char* builtin = "defined flagBUILTIN_PORTAUDIO | (defined flagWIN32 & defined flagMSC)";
		DEPENDENCY_("BUILTIN_PORTAUDIO | (WIN32&MSC)", ports/portaudio)
		LIBRARY("!(BUILTIN_PORTAUDIO | (WIN32&MSC))", portaudio)
		
		VENDOR_ENABLED_FLAG(LINUX)
		VENDOR_ENABLED_FLAG(FREEBSD)
		VENDOR_ENABLED_FLAG(WIN32)
		VENDOR_INCLUDE(builtin, ports/portaudio/portaudio.h)
		VENDOR_INCLUDE(builtin, ports/portaudio/pa_types.h)
		VENDOR_INCLUDE("", portaudio.h)
		VENDOR_HEADER_REQUIRES_INCLUDES
		VENDOR_CLASS(SinkDevice, PaStream*)
		VENDOR_CLASS(SourceDevice, PaStream*)
		
		
	}
	
	
}


NAMESPACE_PLAN_END
