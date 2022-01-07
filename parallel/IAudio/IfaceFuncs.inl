// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

int GetSinkDeviceCount();
int GetSourceDeviceCount();
bool CreateSinkDevice(int, NativeSinkDevice&);
bool CreateSourceDevice(int, NativeSourceDevice&);
void ClearSinkDevice(NativeSinkDevice&);
void ClearSourceDevice(NativeSourceDevice&);
bool SetSinkCallback(void*, SinkCallbackFn);
bool SetSourceCallback(void*, SourceCallbackFn);
int GetSinkFormatCount(NativeSinkDevice&);
int GetSourceFormatCount(NativeSourceDevice&);
bool GetSinkFormat(NativeSinkDevice&, int, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float);
bool GetSourceFormat(NativeSinkDevice&, int, int& channels, int& samplerate, int& bytes, bool& is_signed, bool& is_float);
