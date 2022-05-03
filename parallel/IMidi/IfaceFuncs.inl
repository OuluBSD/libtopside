// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

static bool MidiSinkDevice_Initialize(NativeSinkDevice& dev, AtomBase&, const Script::WorldState&);
static bool MidiSinkDevice_PostInitialize(NativeSinkDevice& dev, AtomBase&);
static bool MidiSinkDevice_Start(NativeSinkDevice& dev, AtomBase&);
static void MidiSinkDevice_Stop(NativeSinkDevice& dev, AtomBase&);
static void MidiSinkDevice_Uninitialize(NativeSinkDevice& dev, AtomBase&);
static bool MidiSinkDevice_Send(NativeSinkDevice& dev, AtomBase&, PacketValue& out);

static int MidiSinkDevice_GetSinkDeviceCount();
static bool MidiSinkDevice_CreateSinkDevice(int dev_i, NativeSinkDevice& o);
static void MidiSinkDevice_ClearSinkDevice(NativeSinkDevice& o);
static bool MidiSinkDevice_PollSink(NativeSinkDevice& o, NativeEvent& ev);
	
static bool MidiSourceDevice_Initialize(NativeSourceDevice& dev, AtomBase&, const Script::WorldState&);
static bool MidiSourceDevice_PostInitialize(NativeSourceDevice& dev, AtomBase&);
static bool MidiSourceDevice_Start(NativeSourceDevice& dev, AtomBase&);
static void MidiSourceDevice_Stop(NativeSourceDevice& dev, AtomBase&);
static void MidiSourceDevice_Uninitialize(NativeSourceDevice& dev, AtomBase&);
static bool MidiSourceDevice_Send(NativeSourceDevice& dev, AtomBase&, PacketValue& out);

static int MidiSourceDevice_GetSourceDeviceCount();
static bool MidiSourceDevice_CreateSourceDevice(int dev_i, NativeSourceDevice& o);
static void MidiSourceDevice_ClearSourceDevice(NativeSourceDevice& o);
static bool MidiSourceDevice_PollSource(NativeSourceDevice& o, NativeEvent& ev);
	
