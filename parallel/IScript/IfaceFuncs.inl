// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 26.3.26 14:33:33

bool CreateRunner(NativeRunner&);
void ClearRunner(NativeRunner&);
bool CreateThread(NativeRunner&, NativeThread&);
void ClearThread(NativeThread&);
bool Run(NativeThread&, String filepath, String script, const StringMap* args);
void Stop(NativeThread&);
bool IsRunning(NativeThread&);
