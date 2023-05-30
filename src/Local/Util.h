#ifndef _Local_Util_h_
#define _Local_Util_h_

NAMESPACE_TOPSIDE_BEGIN



template <class T> inline T Mid(const T& low, const T& mid, const T& high) {return std::max(std::min(mid, high), low);}

template<class T> inline bool IsPositive(const T& o);
template<>        inline bool IsPositive(const Size& o) {return o.cx > 0 && o.cy > 0;}

int HexDigitAny(int c);

/*
	Heapless Copying
	- normal vector copying "dst_vector <<= src_vector;" causes memory clearing and allocation
		- it is slow and useless if the allocated memory could be reused
	- to copy data with minimum reallocation, use SetCount and just copy values (or memcpy)
*/
template <class T>
inline void CopyHeapless(const T& from, T& to) {
	to.SetCount(from.GetCount());
	for(int i = 0; i < to.GetCount(); i++)
		to[i] = from[i];
}

template <class T>
inline void CopyHeaplessMat(const T& from, T& to) {
	to.SetCount(from.GetCount());
	for(int i = 0; i < to.GetCount(); i++) {
		const auto& from0 = from[i];
		auto& to0 = to[i];
		to0.SetCount(from0.GetCount());
		for(int i = 0; i < to0.GetCount(); i++)
			to0[i] = from0[i];
	}
}

inline void VectorAdd(const Vector<double>& from, Vector<double>& to) {
	ASSERT(from.GetCount() == to.GetCount());
	double* t = to.Begin();
	for(double f : from)
		*(t++) += f;
}

template <class T>
void Resize1D(Vector<T>& vec, int length) {
	vec.SetCount(length);
}

template <class T>
void Resize2D(Vector<Vector<T> >& vec, int width, int height) {
	vec.SetCount(width);
	for(int i = 0; i < vec.GetCount(); i++) {
		vec[i].SetCount(height);
	}
}


template <class T, class Sorter> void RemoveDuplicates(Vector<T>& items, const Sorter& sorter=StdLess<T>()) {
	if (items.GetCount() < 2)
		return;
	Sort(items, sorter);
	MAKE_STATIC_LOCAL(Vector<int>, rem);
	rem.SetCount(0);
	rem.Reserve(items.GetCount());
	T* it = items.Begin();
	T* end = items.End() - 1;
	for(int i = 0; it != end; it++, i++) {
		T& a = it[0];
		T& b = it[1];
		if (a == b)
			rem.Add(i);
	}
	items.Remove(rem);
}

template <class T, class Sorter> void AppendSorted(const Vector<T>& sorted_src_items, Vector<T>& sorted_dst_items, const Sorter& sorter=StdLess<T>()) {
	if (sorted_src_items.IsEmpty())
		return;
	
	T* dst_it  = sorted_dst_items.Begin();
	T* dst_end = sorted_dst_items.End();
	const T* src_it  = sorted_src_items.Begin();
	const T* src_end = sorted_src_items.End();
	
	MAKE_STATIC_LOCAL(Vector<T>, tmp);
	tmp.SetCount(0);
	tmp.Reserve(sorted_dst_items.GetCount() + sorted_src_items.GetCount());
	
	while (src_it != src_end) {
		if (dst_it == dst_end || sorter(*src_it, *dst_it))
			tmp.Add(*src_it++);
		else
			tmp.Add(*dst_it++);
	}
	while (dst_it != dst_end)
		tmp.Add(*dst_it++);
	
	Swap(tmp, sorted_dst_items);
}

template <class T, class Sorter> void AppendSortedNoDuplicates(const Vector<T>& sorted_src_items, Vector<T>& sorted_dst_items, const Sorter& sorter=StdLess<T>()) {
	if (sorted_src_items.IsEmpty())
		return;
	
	T* dst_it  = sorted_dst_items.Begin();
	T* dst_end = sorted_dst_items.End();
	const T* src_it  = sorted_src_items.Begin();
	const T* src_end = sorted_src_items.End();
	
	MAKE_STATIC_LOCAL(Vector<T>, tmp);
	tmp.SetCount(0);
	tmp.Reserve(sorted_dst_items.GetCount() + sorted_src_items.GetCount());
	
	while (src_it != src_end) {
		if (dst_it == dst_end || sorter(*src_it, *dst_it))
			tmp.Add(*src_it++);
		else if (*src_it == *dst_it)
			src_it++;
		else
			tmp.Add(*dst_it++);
	}
	while (dst_it != dst_end)
		tmp.Add(*dst_it++);
	
	ASSERT(tmp.GetCount() >= sorted_dst_items.GetCount());
	Swap(tmp, sorted_dst_items);
}

template <class T, class Sorter> void AppendSortedRemoveDuplicateSource(Vector<T>& sorted_src_items, Vector<T>& sorted_dst_items, const Sorter& sorter=StdLess<T>()) {
	if (sorted_src_items.IsEmpty())
		return;
	
	T* dst_it    = sorted_dst_items.Begin();
	T* dst_end   = sorted_dst_items.End();
	T* src_begin = sorted_src_items.Begin();
	T* src_it    = src_begin;
	T* src_end   = sorted_src_items.End();
	
	MAKE_STATIC_LOCAL(Vector<int>, rem);
	MAKE_STATIC_LOCAL(Vector<T>, tmp);
	rem.SetCount(0);
	rem.Reserve(sorted_src_items.GetCount());
	tmp.SetCount(0);
	tmp.Reserve(sorted_dst_items.GetCount() + sorted_src_items.GetCount());
	
	while (src_it != src_end) {
		if (dst_it == dst_end || sorter(*src_it, *dst_it))
			tmp.Add(*src_it++);
		else if (*src_it == *dst_it)
			rem.Add(src_it++ - src_begin);
		else
			tmp.Add(*dst_it++);
	}
	while (dst_it != dst_end)
		tmp.Add(*dst_it++);
	
	sorted_src_items.Remove(rem);
	Swap(tmp, sorted_dst_items);
}




template <class Stream>
void CopyStreamCont(Array<Stream>& dest, Array<Stream>& src) {
	dest.Clear();
	for(int i = 0; i < src.GetCount(); i++) {
		StreamCopy(dest.Add(), src[i]);
	}
}

bool StreamCopy(Stream& dest, Stream& src);







inline String ChrStr(char c) {String s; s.Cat(c); return s;}
inline String CharStr(char c) {String s; s.Cat(c); return s;}
inline bool IsUpper(char c) {return c >= 'A' && c <= 'Z';}
inline bool IsLower(char c) {return !IsUpper(c);}
bool IsAllSpace(const String& a);
bool IsAllDigit(const String& a);
String CamelToName(String s);
String ToVarName(String s);
String ToCaps(String s);
String EscapeString(String s);
String EscapeCharacter(String s);
String ReadFileName(String s);
String GetLineNumStr(String s, bool from_zero=false);
bool ScanBoolString(const String& s);
String Join(const Vector<int>& v, String join_str);
String CenteredString(const String& s, int lw);
String FormatScientific(double d);

bool IsConstChar(const WString& n, const char* cmp, int cmp_len);
bool IsConstCharEnd(const WString& n, const char* cmp, int cmp_begin, int cmp_len);
bool IsArg(const WString& n, const char* cmp, int cmp_len);


void GetDirectoryFiles(String dir, Index<String>& files);


template <class To, class From>	To Convert(const From& from) {return from;}
template <> inline WString Convert<WString,String>(const String& s) {return s.ToWString();}
template <> inline String Convert<String,WString>(const WString& s) {return s.ToString();}



inline bool operator==(const Vector<byte>& a, const Vector<byte>& b) {
	if (a.GetCount() != b.GetCount()) return false;
	for(int i = 0; i < a.GetCount(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

typedef Vector<double>			BetSize;
typedef Vector<bool>			BoolVec;




void FillVector(Vector<double>& v);
String UpperBegin(String s);

inline int PopCount64(uint64 i) {
	#ifdef flagMSC
	#if CPU_64
	return (int)__popcnt64(i);
	#elif CPU_32
	return __popcnt(i) + __popcnt(i >> 32);
	#endif
	#else
	return (int)__builtin_popcountll(i);
	#endif
}

inline int PopCount32(dword i) {
	#ifdef flagMSC
	return (int)__popcnt64(i);
	#else
	return (int)__builtin_popcountl(i);
	#endif
	
	#if 0
	i -= ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    return (((i + (i >> 4))& 0xF0F0F0F)* 0x1010101) >> 24;
    #endif
}

typedef std::atomic<uint64> Atomic64;



inline int HammingDistance32(int count, const dword* a, const dword* b) {
	if (count <= 0) return 0;
	const dword* end = a + count;
	int distance = 0;
	while(a != end)
		distance += PopCount32(*a++ ^ *b++);
	return distance;
}

inline int HammingDistance64(int count, const uint64* a, const uint64* b) {
	if (count <= 0) return 0;
	const uint64* end = a + count;
	int distance = 0;
	while(a != end)
		distance += PopCount64(*a++ ^ *b++);
	return distance;
}


#if IS_UPP_CORE
inline String GetDataDirectory() {return GetDataFile("");}
#endif
inline String GetDataDirectoryFile(String file) {return AppendFileName(GetDataDirectory(), file);}
void SetSharedDirectory(String d);
String GetSharedDirectory();
String SharedFile(String file);
void RenameFile(String oldpath, String newpath);
void TouchFile(String path);

inline String AppendPosixFilename(const String& a, const String& b) {
	if (a.Right(1) == "/") return a + b;
	else return a + "/" + b;
}







template <class T, int I>
struct DtorValueSetter {
	T& obj;
	DtorValueSetter(T& obj) : obj(obj) {}
	~DtorValueSetter() {obj = I;}
};

typedef DtorValueSetter<bool, 0> FlagDisabler;





bool IsClose(double a, double b);



inline float RandomFloat32() {
	float f;
	do {
		float base = 1.0f + (float)Randomf();
		dword bf = (Random(2) << 31) | (Random(0x100) << 23) | (*(dword*)&base & (0xFFFFFFFF >> (32 - 23)));
		f = *(float*)&bf;
	}
	while (!IsFin(f));
	return f;
}

double FastMultiply(double prev_norm, int64 count, double multiplier);

inline int msb(dword d) {
    int res = 0;
	#ifdef flagGCC
    asm("bsrl %1,%0" : "=r"(res) : "r"(d));
    #else
	while (d >>= 1)
	    res++;
	#endif
	return res;
}










inline void DumpProbVector(const Vector<double>& probs, int steps, int indent=0) {
	double step = 1.0 / (steps + 1);
	String s;
	for(int i = 0; i < steps; i++) {
		double offset = (steps - i) * step;
		s = "";
		for(int j = 0; j < indent; j++)
			s.Cat('\t');
		for(double d : probs)
			s.Cat(d >= offset ? '#' : ' ');
		LOG(s);
	}
}










inline int64 GetCpuTicks() {
	#if MINGWTHREAD
	return clock();
	#elif defined flagWIN32
    return __rdtsc();
    #else
    return clock();
    #endif
}

inline int64 Delay(int64 cpu_ticks) {
	int64 end = GetCpuTicks() + cpu_ticks;
	int64 iters = 0;
	while (GetCpuTicks() < end)
		iters++;
	return iters;
}












template <class T>
inline const T& IndexAdd(Index<T>& idx, const T& o) {
	int id = idx.GetCount();
	idx.Add(o);
	return idx[id];
}

template <class T>
inline const T& IndexFindAdd(Index<T>& idx, const T& o) {
	int id = idx.FindAdd(o);
	return idx[id];
}





// https://software.intel.com/sites/landingpage/IntrinsicsGuide

struct Trans8x16 {
	union {
		uint16 u16[8];
		uint8 u8[16];
		#if CPU_X86
		__m128i m;
		#endif
		uint64 u64[2];
	};
	
	void TransFrom16x8() {
		#if CPU_X86
		__m128i x = m;
	    for (int i = 0; i < 8; ++i) {
	        u16[7-i] = _mm_movemask_epi8(x);
	        x = _mm_slli_epi64(x,1);
	    }
	    #else
	    TODO
	    #endif
	}
	
	void Zero() {u64[0] = 0; u64[1] = 0;}
};

#ifdef flagAVX2
struct Trans8x32 {
	union {
		uint32 u32[8];
		uint8 u8[32];
		#if CPU_X86
		__m256i m;
		#endif
	};
	
	void TransFrom32x8() {
		#if CPU_X86
		__m256i x = m;
	    for (int i = 0; i < 8; ++i) {
	        u32[7-i] = _mm256_movemask_epi8(x);
	        x = _mm256_slli_epi64(x,1);
	    }
	    #else
	    TODO
	    #endif
	}
};
#endif







class RunningFlagSingle {
	bool running = false, stopped = true;
	
public:
	RunningFlagSingle() {}
	bool IsRunning() const {return running;}
	void SetStopped() {stopped = true;}
	void SetNotRunning() {running = false;}
	void Start() {running = true; stopped = false;}
	void Stop();
	
};

struct RunningFlag {
	int sleep_time = 100;
	bool running = false;
	Atomic workers_running;
	
	RunningFlag() {workers_running = 0;}
	void Start(int count) {Stop(); running = true; workers_running = count;}
	void Stop();
	void SetNotRunning() {running = false;}
	void IncreaseRunning() {workers_running++;}
	int DecreaseRunning() {int r = workers_running--; if (workers_running == 0) running = false; return r-1;}
	bool IsRunning() const {return running;}
	void Wait();
};










struct CmdArg {
	char key;
	String desc, value_desc;
	bool has_value;
};

struct CmdInput {
	char key;
	String value;
};

class CommandLineArguments {
	static const int max_inputs = 300;
	static const int max_args = 100;
	
	Array<CmdArg>				args;
	Array<CmdInput>				inputs;
	VectorMap<String,Object>	vars;
	
public:
	CommandLineArguments() {}
	
	void AddArg(char key, const char* desc, bool has_value, String value_desc="value");
	bool Parse();
	void PrintHelp();
	
	int GetInputCount() const {return inputs.GetCount();}
	bool IsArg(char c) const;
	String GetArg(char c) const;
	
	const Array<CmdInput>& GetInputs() const {return inputs;}
	const VectorMap<String,Object>& GetVariables() const {return vars;}
	
};


String FindShareDir();
String ShareDirFile(String file);
String TrimTrailingDirSep(String file);
String RealizeShareFile(String rel_path);




void SetCoutLog();



struct AppFlags {
	
	typedef enum {
		GFX_UNKNOWN,
		GFX_SW,
		GFX_OPENGL,
		GFX_DX12,
		GFX_VULKAN,
		GFX_METAL,
	} GfxMode;
	
	
	
	GfxMode gfx = GFX_OPENGL;
	bool have_ode_physics = false;
	bool is_ogl_ctx_open = false;
	
	bool IsOpenGL() const {return gfx == GFX_OPENGL;}
	bool IsSoftwareRenderer() const {return gfx == GFX_SW;}
	bool HaveOdePhysics() const {return have_ode_physics;}
	bool IsOpenGLContextOpen() const {return is_ogl_ctx_open;}
	
	void SetOpenGLContextOpen(bool b=true) {is_ogl_ctx_open = b;}
	
};

inline AppFlags& GetAppFlags() {return Single<AppFlags>();}
inline bool IsOpenGL() {return GetAppFlags().IsOpenGL();}
inline bool IsOpenGLContextOpen() {return GetAppFlags().IsOpenGLContextOpen();}
void EnableGfxAccelDebugMessages(bool b);
bool IsGfxAccelDebugMessages();




class ErrorReporter : RTTIBase {
	String last_error;
public:
	RTTI_DECL0(ErrorReporter)
	ErrorReporter() {}
	
	void ClearError() {last_error.Clear();}
	void SetError(String s) {last_error = s;}
	bool IsError() const {return !last_error.IsEmpty();}
	String GetError() const {return last_error;}
	
	virtual void Visit(RuntimeVisitor& vis) {}
	
};





struct InternalPacketData : RTTIBase {
	RTTI_DECL0(InternalPacketData)
	
	void*	ptr;
	
	union {
		double	dbl;
		int64	i64;
		int64	pos;
		char	txt[8];
	};
	
	union {
		int32	i32;
		uint32	u32;
		uint32	count;
	};
	
	
	int GetTextLength() const			{return (int)strnlen(txt, 8);}
	String GetText() const				{return String(txt, GetTextLength());}
	#ifdef COMPILER_MSC
	void SetText(const char* s)			{
		for(int i = 0; i < 8; i++) {
			txt[i] = s[i];
			if (!s[i])
				break;
		}
	}
	#else
	void SetText(const char* s)			{strncpy(txt, s, 8);}
	#endif
	bool IsText(const char* s) const	{return strncmp(txt, s, 8) == 0;}
	
	//void ClearLinks() {dev_comp = 0;}
};



// Converts a length in device-independent pixels (DIPs) to a length in physical pixels.
float ConvertDipsToPixels(float dips, float dpi);

void AddLocalFileDirectory(String dir);
String FindLocalFile(String filename);


NAMESPACE_TOPSIDE_END

#endif
