#ifndef _Local_Compat_h_
#define _Local_Compat_h_


#ifdef flagFREEBSD
extern char **environ;
#endif

#include <optional>

#ifdef UPP_OLD_VERSION
	#ifdef flagGCC
		#include <x86intrin.h> // for rdtsc
	#endif
#endif


#ifdef UPP_VERSION

#if __GNUC__
	#define UNREACHABLE __builtin_unreachable()
#endif

#ifdef _MSC_VER
	#define UNREACHABLE __assume(0)
#endif

#define MemoryCompare memcmp
#define MemoryCopy    memcpy
#define MemoryMove    memmove

#undef TODO
#define MACROSTR(x) #x
#define COUT(x) {::UPP::String ____s; ____s << x; Cout() << ____s << "\n";}
#define COUTLOG(x) {::UPP::String ____s; ____s << x; LOG(____s); Cout() << ____s << "\n";}
#define TODO {Panic("TODO " __FILE__ ":" + UPP::IntStr(__LINE__)); throw UPP::Exc("TODO");}
#define SYNON_UNION_2(type, name0, name1) union {type name0; type name1;};
#define PANIC(msg) Panic(msg); UNREACHABLE

#define RTTI_TYPEIDCLS


NAMESPACE_UPP_BEGIN

#if UPP_OLD_VERSION
typedef unsigned hash_t;
#endif

inline bool IsOctDigit(char c) { return c >= '0' && c <= '7'; }
inline bool IsHexDigit(char c) { return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
inline int GetHexDigit(char c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return 10 + c - 'a';
	if (c >= 'A' && c <= 'F')
		return 10 + c - 'A';
	return 0;
}

inline int OctInt(const char *s) {
	if (!s) return 0;
	while (IsSpace(*s)) s++;
	int n=0, neg=0;
	switch (*s) {
		case '-': neg=1;
		case '+': s++;
	}
	while (*s == '0') s++;
	while (IsOctDigit(*s))
		n = 8*n - (*s++ - '0');
	return neg ? n : -n;
}

inline int HexInt(const char *s) {
	if (!s) return 0;
	while (IsSpace(*s)) s++;
	int n=0, neg=0;
	switch (*s) {
		case '-': neg=1;
		case '+': s++;
	}
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		s += 2;
	while (IsHexDigit(*s))
		n = 16*n - GetHexDigit(*s++);
	return neg ? n : -n;
}

template<class InputIterator, class UnaryPredicate>
InputIterator FindIf(InputIterator first, InputIterator last, UnaryPredicate pred) {
	return std::find_if(first, last, pred);
}

void sSeed(uint64 *s);

inline void GetSysSeedValues(int64* a, int64* b, int64* c) {
	if(a) sSeed((uint64*)a);
	if(b) sSeed((uint64*)b);
	if(c) sSeed((uint64*)c);
}

inline String HexStr(int64 i) {return Format("0x%X", i);}
inline String HexStr(void* i) {return Format("0x%X", (int64)i);}

#if 0
typedef Image RawSysTexture;
#endif

using NullOpt = std::nullopt_t;

#define null_opt std::nullopt

template <class T> using Optional = std::optional<T>;

//template <class T, class ...Args> std::optional<T> MakeOptional(Args... args) {return std::make_optional(args...);}
template <class T> std::optional<T> MakeOptional(const T& o) {return std::make_optional(o);}

NAMESPACE_UPP_END

#include <SharedCore/SharedCore.h>
#include <StaticInterface/DrawBackend.h>

#define CompatFileHandle(x) x



#if !defined(flagGUI)
NAMESPACE_UPP
class Ctrl : public Pte<Ctrl> {
	
public:
	enum {
		UNKNOWN,
		LEFTDOWN,
		LEFTDOUBLE,
		LEFTTRIPLE,
		LEFTDRAG,
		LEFTHOLD,
		LEFTREPEAT,
		LEFTUP,
		RIGHTDOWN,
		RIGHTDOUBLE,
		RIGHTTRIPLE,
		RIGHTDRAG,
		RIGHTHOLD,
		RIGHTREPEAT,
		RIGHTUP,
		MIDDLEDOWN,
		MIDDLEDOUBLE,
		MIDDLETRIPLE,
		MIDDLEDRAG,
		MIDDLEHOLD,
		MIDDLEREPEAT,
		MIDDLEUP,
	};
};

enum {
	K_DELTA        = 0x010000,

	K_ALT          = 0x080000,
	K_SHIFT        = 0x040000,
	K_CTRL         = 0x020000,

	K_KEYUP        = 0x100000,

	K_MOUSEMIDDLE  = 0x200000,
	K_MOUSERIGHT   = 0x400000,
	K_MOUSELEFT    = 0x800000,
	K_MOUSEDOUBLE  = 0x1000000,
	K_MOUSETRIPLE  = 0x2000000,

	K_SHIFT_CTRL = K_SHIFT|K_CTRL,

#ifdef PLATFORM_COCOA
	K_OPTION       = 0x4000000,
#endif

	K_PEN          = 0x8000000,

	IK_DBL_CLICK   = 0x40000001, // this is just to get the info that the entry is equal to dbl-click to the menu
	
	K_MOUSE_FORWARD = 0x80000001,
	K_MOUSE_BACKWARD = 0x80000002,
};

class SystemDraw {
public:
	Size GetPageSize() const {return Size(0,0);}
};

#if UPP_OLD_VERSION
template<> inline hash_t GetHashValue(const float& a)         { return memhash(&a, sizeof(a)); }
#endif



END_UPP_NAMESPACE
#endif


NAMESPACE_UPP

inline bool IsBinDigit(int c) { return c == '0' || c == '1'; }
inline bool IsHexDigit(int c) { return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
inline int GetHexDigit(int c) {
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return 10 + c - 'a';
	if (c >= 'A' && c <= 'F')
		return 10 + c - 'A';
	return 0;
}
inline int GetBinDigit(int c) {
	if (c == '0' || c == '1')
		return c - '0';
	return 0;
}
inline int64 BinInt64(const char *s) {
	if (!s) return 0;
	while (IsSpace(*s)) s++;
	int64 n=0, neg=0;
	switch (*s) {
		case '-': neg=1;
		case '+': s++;
	}
	if (s[0] == '0' && (s[1] == 'b' || s[1] == 'B'))
		s += 2;
	while (IsBinDigit(*s))
		n = 2*n - GetBinDigit(*s++);
	return neg ? n : -n;
}
inline int64 HexInt64(const char *s) {
	if (!s) return 0;
	while (IsSpace(*s)) s++;
	int64 n=0, neg=0;
	switch (*s) {
		case '-': neg=1;
		case '+': s++;
	}
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		s += 2;
	while (IsHexDigit(*s))
		n = 16*n - GetHexDigit(*s++);
	return neg ? n : -n;
}

template <class T> ManagedStatic<T>::ManagedStatic(const char* f, int l) : file(f), line(l) {}
template <class T> template <class Arg>
ManagedStatic<T>::ManagedStatic(const char* f, int l, const Arg& value) : file(f), line(l), o(value) {}

template <class T> ManagedStaticThreadLocal<T>::ManagedStaticThreadLocal(const char* f, int l) : file(f), line(l) {}
template <class T> template <class Arg>
ManagedStaticThreadLocal<T>::ManagedStaticThreadLocal(const char* f, int l, const Arg& value) : file(f), line(l), o(value) {}


#ifndef flagMSC
inline WString FromUtf8(String s) {return s.ToWString();}
#endif


END_UPP_NAMESPACE

#else

#include <StaticInterface/StaticInterface.h>
#define CompatFileHandle(x) fileno(x)

#endif
#endif
