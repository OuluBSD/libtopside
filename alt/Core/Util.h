#ifndef _CoreAlt_Util_h_
#define _CoreAlt_Util_h_

NAMESPACE_UPP_BEGIN

void Panic(String s);
void Assert(bool b, String s="Assertion failed");
void AssertFalse(bool b, String s="Assertion failed");

#undef PANIC
#define PANIC(msg) Panic(msg); UNREACHABLE

template <class T>
T& PtrRef(T* o, String throw_msg) {
	if (!o) Throw(throw_msg);
	return *o;
}

MultiStream& LogMulti();
Stream& VppLog();
Stream& LogFile();
Stream& Cout();
Stream& Cerr();
Stream& Cin();

inline String ReadStdIn() {return Cin().GetLine();}

void SetExeFilePath(String s);
String GetExeFilePath();
String GetHomeDir();
String ConfigFile(String file_name);
String GetFileName(String path);
String GetFileTitle(String path);
String GetFileDirectory(String path);
String AppendFileName(String a, String b);
String GetParentDirectory(String path, int steps=1);
String GetFileExt(String path);
void RealizeDirectory(String dir);
void DeleteFile(String path);

inline bool IsFin(float f)	{return ::isfinite(f);}
inline bool IsNaN(double d)	{return std::isnan(d);}
inline bool IsInf(double d)	{return std::isinf(d);}
inline bool IsFin(double d)	{return !IsNaN(d) && !IsInf(d);}




void ParseCommandLine(int argc, const char** argv);
void ParseCommandLine(const char* cmdline);
const Vector<String>& CommandLine();
int GetExitCode();
void SetExitCode(int i);
void Exit(int i);
void SetCoreArg(String key, String value);
String GetExeDirFile(String filename);
String GetEnv(String id);
void ReadCoreCmdlineArgs();
void SetDataPath(String path);
String GetDataDirectory();
String GetDataFile(String filename);
bool FileExists(String path);
bool DirectoryExists(String path);
String FindLocalFile(String filename);
void AddLocalFileDirectory(String dir);
bool IsVerbose();
void SetVerbose(bool b=true);

#if defined flagWIN32 && defined flagGUI
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




struct Uuid {
	uint64 v[2];

	Uuid() {}

	hash_t GetHashValue() const { CombineHash ch; ch.Put64(v[0]); ch.Put64(v[1]); return ch;}

	void     New();
	
	String ToString() const;
	static Uuid Create() { Uuid uuid; uuid.New(); return uuid; }
};




class FindFile {
	
	
public:
	typedef FindFile CLASSNAME;
	FindFile();
	
	bool Search(String path);
	bool Next();
	
	bool IsDirectory() const;
	String GetPath() const;
	String GetName() const;
};




void BZ2Decompress(Stream& out, Stream& in);
void BZ2Compress(Stream& out, Stream& in);
String BZ2Compress(Stream& in);
String BZ2Decompress(Stream& in);
String BZ2Compress(const void *data, int64 len);
String BZ2Decompress(const void *data, int64 len);
String BZ2Compress(const String& data);
String BZ2Decompress(const String& data);

String MD5String(String s);
String HexEncode(String s);




class NoCopy {
private:
	NoCopy(const NoCopy&);
	void operator=(const NoCopy&);
public:
	NoCopy() {}
};



bool Load(Callback1<Stream&> x, Stream& s);
void Store(Callback1<Stream&> x, Stream& s);
String GetGlobalConfigData(const char* name);
void SetGlobalConfigData(const char* name, String data);
bool LoadFromGlobal(Callback1<Stream&> x, const char *name);
void StoreToGlobal(Callback1<Stream&> x, const char *name);


String GetHomeDirectory();
String GetHomeDirFile(const char *fp);

void AppInit__(int argc, const char** argv);
void AppExit__();


template <class T>
void Zero(T& obj) {
	::memset(&obj, 0, sizeof(obj));
}




NAMESPACE_UPP_END

#endif
