// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 23.3.23 18:44:22

bool CreateVirtualMachine(NativeVirtualMachine&);
void ClearVirtualMachine(NativeVirtualMachine&);
bool CreateThread(NativeVirtualMachine&, NativeThread&);
void ClearThread(NativeThread&);
bool Run(NativeThread&, String filepath, String script, const StringMap* args);
void Stop(NativeThread&);
bool IsRunning(NativeThread&);
