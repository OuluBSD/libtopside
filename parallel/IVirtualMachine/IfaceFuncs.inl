// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!

bool CreateVirtualMachine(NativeVirtualMachine&);
void ClearVirtualMachine(NativeVirtualMachine&);
bool CreateThread(NativeVirtualMachine&, NativeThread&);
void ClearThread(NativeThread&);
bool Run(NativeThread&, String filepath, String script, const StringMap* args);
void Stop(NativeThread&);
bool IsRunning(NativeThread&);
