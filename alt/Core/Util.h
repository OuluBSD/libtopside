#ifndef _CoreAlt_Util_h_
#define _CoreAlt_Util_h_

NAMESPACE_UPP_BEGIN


void Panic(String s);
void Assert(bool b, String s="Assertion failed");
void AssertFalse(bool b, String s="Assertion failed");

#undef PANIC
#define PANIC(msg) UPP::Panic(msg); UNREACHABLE

template <class T>
T& PtrRef(T* o, String throw_msg) {
	if (!o) Throw(throw_msg);
	return *o;
}





void ParseCommandLine(int argc, const char** argv);
void ParseCommandLine(const char* cmdline);
const Vector<String>& CommandLine();
int GetExitCode();
void SetExitCode(int i);
void Exit();
void Exit(int i);
void SetCoreArg(const String& key, const String& value);
String GetEnv(String id);
void ReadCoreCmdlineArgs();
bool IsVerbose();
void SetVerbose(bool b=true);

#if defined flagWIN32
void SetWin32Instances(HINSTANCE inst, HINSTANCE prev, bool nCmdShow);
HINSTANCE GetWin32Instance();
HINSTANCE GetWin32PrevInstance();
bool GetWin32CmdShow();
#endif

template <class T>
inline T& Single() {
	static T o;
	return o;
}


int64 usecs(int64 prev = 0);
int msecs(int prev = 0);





void BZ2Decompress(Stream& out, Stream& in);
void BZ2Compress(Stream& out, Stream& in);
String BZ2Compress(Stream& in);
String BZ2Decompress(Stream& in);
String BZ2Compress(const void *data, int64 len);
String BZ2Decompress(const void *data, int64 len);
String BZ2Compress(const String& data);
String BZ2Decompress(const String& data);


bool Load(Callback1<Stream&> x, Stream& s);
void Store(Callback1<Stream&> x, Stream& s);
String GetGlobalConfigData(const char* name);
void SetGlobalConfigData(const char* name, String data);
bool LoadFromGlobal(Callback1<Stream&> x, const char *name);
void StoreToGlobal(Callback1<Stream&> x, const char *name);



void AppInit__(int argc, const char** argv);
void AppExit__();


template <class T>
void Zero(T& obj) {
	::memset(&obj, 0, sizeof(obj));
}



inline dword Random() {return (dword)RNG::Local().Random(UINT32_MAX);}
inline void Random64(uint64* t, int n) {return RNG::Local().GetN(t, n);}
inline dword Random(dword n) {return (dword)RNG::Local().Random(n);}
inline uint64 Random64() {return RNG::Local().Get64();}
inline uint64 Random64(uint64 n) {return RNG::Local().Random64(n);}
inline double Randomf() {return RNG::Local().Randomf();}
inline void SeedRandom() {return RNG::Local().Seed();}
inline void SeedRandom(dword seed) {return RNG::Local().Seed(seed);}


NAMESPACE_UPP_END

#endif
