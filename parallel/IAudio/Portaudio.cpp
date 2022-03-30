#include "IAudio.h"

#if (defined flagLINUX) || (defined flagFREEBSD) || (defined flagWIN32)
NAMESPACE_PARALLEL_BEGIN

bool AudPortaudio::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

void AudPortaudio::SinkDevice_Start(NativeSinkDevice& dev) {
	TODO
}

void AudPortaudio::SinkDevice_Stop(NativeSinkDevice& dev) {
	TODO
}

void AudPortaudio::SinkDevice_Uninitialize(NativeSinkDevice& dev) {
	TODO
}

bool AudPortaudio::SinkDevice_ProcessPacket(NativeSinkDevice& dev, PacketValue& v) {
	TODO
}

int AudPortaudio::SinkDevice_GetSinkDeviceCount() {
	TODO
}

bool AudPortaudio::SinkDevice_CreateSinkDevice(int sink_i, NativeSinkDevice& o) {
	TODO
}

void AudPortaudio::SinkDevice_ClearSinkDevice(NativeSinkDevice& o) {
	TODO
}

bool AudPortaudio::SinkDevice_SetSinkCallback(void* data, DataCallbackFn cb) {
	TODO
}

int AudPortaudio::SinkDevice_GetSinkFormatCount(NativeSinkDevice& o) {
	TODO
}

bool AudPortaudio::SinkDevice_GetSinkFormat(NativeSinkDevice& o, int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float) {
	TODO
}

bool AudPortaudio::SourceDevice_Initialize(NativeSourceDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

void AudPortaudio::SourceDevice_Start(NativeSourceDevice& dev) {
	TODO
}

void AudPortaudio::SourceDevice_Stop(NativeSourceDevice& dev) {
	TODO
}

void AudPortaudio::SourceDevice_Uninitialize(NativeSourceDevice& dev) {
	TODO
}

bool AudPortaudio::SourceDevice_ProcessPacket(NativeSourceDevice& dev, PacketValue& v) {
	TODO
}

int AudPortaudio::SourceDevice_GetSourceDeviceCount() {
	TODO
}

bool AudPortaudio::SourceDevice_CreateSourceDevice(int sink_i, NativeSourceDevice& o) {
	TODO
}

void AudPortaudio::SourceDevice_ClearSourceDevice(NativeSourceDevice& o) {
	TODO
}

bool AudPortaudio::SourceDevice_SetSourceCallback(void* data, DataCallbackFn cb) {
	TODO
}

int AudPortaudio::SourceDevice_GetSourceFormatCount(NativeSourceDevice& o) {
	TODO
}

bool AudPortaudio::SourceDevice_GetSourceFormat(NativeSourceDevice& o, int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

