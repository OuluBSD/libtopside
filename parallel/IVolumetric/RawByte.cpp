#include "IVolumetric.h"

#if (defined flagLINUX) || (defined flagFREEBSD)


NAMESPACE_PARALLEL_BEGIN

bool VolRawByte::StaticSource_Initialize(NativeStaticSource& dev, AtomBase& a, const Script::WorldState& ws) {
	
	dev.vflip = false;
	
	TODO
}

bool VolRawByte::StaticSource_PostInitialize(NativeStaticSource& dev, AtomBase& a) {
	TODO
}

bool VolRawByte::StaticSource_Start(NativeStaticSource& dev, AtomBase& a) {
	TODO
}

void VolRawByte::StaticSource_Stop(NativeStaticSource& dev, AtomBase& a) {
	TODO
}

void VolRawByte::StaticSource_Uninitialize(NativeStaticSource& dev, AtomBase& a) {
	TODO
}

bool VolRawByte::StaticSource_Send(NativeStaticSource& dev, AtomBase& a, PacketValue& out) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

