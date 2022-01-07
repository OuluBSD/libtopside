// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

int GetSinkDeviceCount();
int GetSourceDeviceCount();
bool CreateSinkDevice(int, NativeSinkDevice&);
bool CreateSourceDevice(int, NativeSourceDevice&);
void ClearSinkDevice(NativeSinkDevice&);
void ClearSourceDevice(NativeSourceDevice&);
bool PollSink(NativeSinkDevice&, NativeEvent&);
bool PollSource(NativeSinkDevice&, NativeEvent&);
