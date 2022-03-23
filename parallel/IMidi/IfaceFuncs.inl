// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 23.3.23 18:44:22

int GetSinkDeviceCount();
int GetSourceDeviceCount();
bool CreateSinkDevice(int, NativeSinkDevice&);
bool CreateSourceDevice(int, NativeSourceDevice&);
void ClearSinkDevice(NativeSinkDevice&);
void ClearSourceDevice(NativeSourceDevice&);
bool PollSink(NativeSinkDevice&, NativeEvent&);
bool PollSource(NativeSinkDevice&, NativeEvent&);
