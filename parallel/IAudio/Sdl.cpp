#include "IAudio.h"

#if defined flagSDL


NAMESPACE_PARALLEL_BEGIN

bool AudSdl::SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

void AudSdl::SinkDevice_Start(NativeSinkDevice& dev) {
	TODO
}

void AudSdl::SinkDevice_Stop(NativeSinkDevice& dev) {
	TODO
}

void AudSdl::SinkDevice_Uninitialize(NativeSinkDevice& dev) {
	TODO
}

bool AudSdl::SinkDevice_ProcessPacket(NativeSinkDevice& dev, PacketValue& v) {
	TODO
}

int AudSdl::SinkDevice_GetSinkDeviceCount() {
	TODO
}

bool AudSdl::SinkDevice_CreateSinkDevice(int sink_i, NativeSinkDevice& o) {
	TODO
}

void AudSdl::SinkDevice_ClearSinkDevice(NativeSinkDevice& o) {
	TODO
}

bool AudSdl::SinkDevice_SetSinkCallback(void* data, DataCallbackFn cb) {
	TODO
}

int AudSdl::SinkDevice_GetSinkFormatCount(NativeSinkDevice& o) {
	TODO
}

bool AudSdl::SinkDevice_GetSinkFormat(NativeSinkDevice& o, int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float) {
	TODO
}

bool AudSdl::SourceDevice_Initialize(NativeSourceDevice& dev, AtomBase& a, const Script::WorldState& ws) {
	TODO
}

void AudSdl::SourceDevice_Start(NativeSourceDevice& dev) {
	TODO
}

void AudSdl::SourceDevice_Stop(NativeSourceDevice& dev) {
	TODO
}

void AudSdl::SourceDevice_Uninitialize(NativeSourceDevice& dev) {
	TODO
}

bool AudSdl::SourceDevice_ProcessPacket(NativeSourceDevice& dev, PacketValue& v) {
	TODO
}

int AudSdl::SourceDevice_GetSourceDeviceCount() {
	TODO
}

bool AudSdl::SourceDevice_CreateSourceDevice(int sink_i, NativeSourceDevice& o) {
	TODO
}

void AudSdl::SourceDevice_ClearSourceDevice(NativeSourceDevice& o) {
	TODO
}

bool AudSdl::SourceDevice_SetSourceCallback(void* data, DataCallbackFn cb) {
	TODO
}

int AudSdl::SourceDevice_GetSourceFormatCount(NativeSourceDevice& o) {
	TODO
}

bool AudSdl::SourceDevice_GetSourceFormat(NativeSourceDevice& o, int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float) {
	TODO
}





NAMESPACE_PARALLEL_END
#endif

