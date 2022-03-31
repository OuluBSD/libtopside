// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 2022.3.31 14:22:11

static bool SinkDevice_Initialize(NativeSinkDevice& dev, AtomBase&, const Script::WorldState&);
static bool SinkDevice_Start(NativeSinkDevice& dev);
static void SinkDevice_Stop(NativeSinkDevice& dev);
static void SinkDevice_Uninitialize(NativeSinkDevice& dev);
static bool SinkDevice_ProcessPacket(NativeSinkDevice& dev, PacketValue& v);

static int SinkDevice_GetSinkDeviceCount();
static bool SinkDevice_CreateSinkDevice(int sink_i, NativeSinkDevice& o);
static void SinkDevice_ClearSinkDevice(NativeSinkDevice& o);
static bool SinkDevice_SetSinkCallback(void* data, DataCallbackFn cb);
static int SinkDevice_GetSinkFormatCount(NativeSinkDevice& o);
static bool SinkDevice_GetSinkFormat(NativeSinkDevice& o, int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float);
	
static bool SourceDevice_Initialize(NativeSourceDevice& dev, AtomBase&, const Script::WorldState&);
static bool SourceDevice_Start(NativeSourceDevice& dev);
static void SourceDevice_Stop(NativeSourceDevice& dev);
static void SourceDevice_Uninitialize(NativeSourceDevice& dev);
static bool SourceDevice_ProcessPacket(NativeSourceDevice& dev, PacketValue& v);

static int SourceDevice_GetSourceDeviceCount();
static bool SourceDevice_CreateSourceDevice(int sink_i, NativeSourceDevice& o);
static void SourceDevice_ClearSourceDevice(NativeSourceDevice& o);
static bool SourceDevice_SetSourceCallback(void* data, DataCallbackFn cb);
static int SourceDevice_GetSourceFormatCount(NativeSourceDevice& o);
static bool SourceDevice_GetSourceFormat(NativeSourceDevice& o, int ch_i, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float);
	
