// This file have been generated automatically.
// DO NOT MODIFY THIS FILE!
// Last export: 25.3.25 19:11:33

bool CreateRunner(NativeRunner&);
void ClearRunner(NativeRunner&);
bool CreateThread(NativeRunner&, NativeThread&);
void ClearThread(NativeThread&);
bool Run(NativeThread&, String filepath, String script, const StringMap* args);
void Stop(NativeThread&);
bool IsRunning(NativeThread&);
