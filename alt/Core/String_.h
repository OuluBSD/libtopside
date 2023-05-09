#ifndef _CoreAlt_String_h_
#define _CoreAlt_String_h_

#include "Defs.h"
#include <memory>

NAMESPACE_UPP_BEGIN

class Stream;
class Object;
class Value;

inline bool IsOctDigit(int c) { return c >= '0' && c <= '7'; }
inline bool IsHexDigit(int c) { return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }
inline bool IsBinDigit(int c) { return c == '0' || c == '1'; }
inline bool IsDigit(int c) { return c >= '0' && c <= '9'; }
inline bool IsSpace(int c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }
inline bool IsAlpha(int c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
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

inline void MemoryCopySlow(void* dst, const void* src, int len) {
	uint32* dst4 = (uint32*)dst;
	uint32* src4 = (uint32*)src;
	while (len >= 4) {
		uint32 value = *src4++;

		*dst4++ = value;

		len -= 4;
	}
	uint8* dst1 = (uint8*)dst4;
	uint8* src1 = (uint8*)src4;
	while (len > 0) {
		*dst1++ = *src1++;
		len -= 1;
	}
}

inline void MemorySet(void* dst, int value, int len) {
	byte bvalue = value & 0xFF;
	byte* b = (byte*)dst;
	for (int i = 0; i < len; i++) {
		*b++ = bvalue;
	}
}

void MemoryMoveSlow(void* dst, const void* src, int len);

void DebugStringLog(void* addr, const char* msg, int refs, int event);

template <class T>
class String0 {
	T* data = NULL;
	AtomicInt refs;
	int alloc = 0;
	
	#ifdef flagDEBUG
	bool do_debug_track = false;
	int dbg_event = 0;
	#endif
	
public:
	String0(T* str, int alloc) : data(str), refs(1), alloc(alloc) {}
	String0(String0&& s) = delete;
	~String0() {Clear();}

	#ifdef flagDEBUG
	void DebugFollow() {
		do_debug_track = true;
		
		#ifdef flagDEBUG
		if (do_debug_track)
			DebugStringLog(this, "begin follow", refs, dbg_event++);
		#endif
	}
	#else
	void DebugFollow() {}
	#endif
	
	void Clear() {if (data) {free(data); data = 0; refs = 0; alloc = 0;}}
	
	void IncreaseReserved() {
		uint64 new_alloc = 1;
		while (new_alloc <= alloc)
			new_alloc <<= 1;
		if (new_alloc >= INT_MAX)
			new_alloc = INT_MAX;
		Reserve((int)new_alloc);
	}
	void IncreaseReserved(int min_alloc) {
		uint64 new_alloc = 1;
		while (new_alloc <= min_alloc)
			new_alloc <<= 1;
		if (new_alloc >= INT_MAX)
			new_alloc = INT_MAX;
		Reserve((int)new_alloc);
	}
	void Reserve(int new_alloc) {
		if (new_alloc <= alloc)
			return;
		T* new_data = (T*)malloc(new_alloc * sizeof(T));
		if (data) {
			if (alloc > 0)
				MemoryCopy(new_data, data, sizeof(T) * alloc);
			free(data);
		}
		data = new_data;
		alloc = new_alloc;
	}

	const T* Get() const { return data; }
	T* Begin() { return data; }
	operator const T* () const { return data; }

	int GetAlloc() const { return alloc; }
	int GetRefs() const { return refs; }
	void Inc() {
		refs++;
		
		#ifdef flagDEBUG
		if (do_debug_track)
			DebugStringLog(this, "Inc", refs, dbg_event++);
		#endif
	}
	void Dec() {
		refs--;
		
		#ifdef flagDEBUG
		if (do_debug_track)
			DebugStringLog(this, "Dec", refs, dbg_event++);
		#endif
		
		if (refs <= 0)
			delete this;
	}

};


template <class T>
struct StringStd;

template <>
struct StringStd<char> {
	using Std = std::string;
};

template <>
struct StringStd<wchar_t> {
	using Std = std::string;
};


template <class T>
class StringT : Moveable<StringT<T>> {
	using Std = typename StringStd<T>::Std;
	
	typedef String0<T> String0T;
	static const int buf_size = 8;
	static const int buf_bytes = buf_size * sizeof(T);
	static_assert(buf_bytes % sizeof(void*) == 0, "buffer size modulus ptr size must be zero");
	static const int ptr_count = buf_bytes / sizeof(void*);
	
	union {
		T buf[buf_size];
		String0T* s[ptr_count];
	};
	
	#define BIG_FIELD s[0]
	void Zero() {memset(this, 0, sizeof(StringT));}
	
	#define BIG (this->BIG_FIELD)
	
	byte special = 0;
	bool is_big = false;
	int count = 0;
	
	
public:
	StringT() {Zero();}
	StringT(const T* c) {Zero(); *this = c;}
	StringT(const T* c, int len) {Zero(); Set(c, len);}
	StringT(const T* b, const T* e) {Zero(); int len = (int)(e-b); if (len > 0) Set(b, len);}
	StringT(T c, int len) {Zero(); Cat(c, len);}
	StringT(const StringT& s) {Zero(); *this = s;}
	StringT(StringT&& s) {Zero(); Swap(*this, s);}
	StringT(Nuller n) {Zero();}
	~StringT() {Clear();}
	
	void DebugFollow() {if (is_big) BIG->DebugFollow();}
	
	void Clear();
	bool IsNullInstance() const;
	
	const String0T* GetString0() const {return BIG;}
	
	void Serialize(Stream& s);
	
	StringT& operator=(const Value& c);
	StringT& operator=(const Object& c);
	
	StringT& operator=(const T* c);
	
	StringT& Set(const T* c, int len);
	StringT& SetData(void* c, int len);
	void* GetWritableData(byte special, int len);
	StringT& operator=(const StringT& str);
	StringT& operator+=(int i) {return Cat(i);}
	StringT& Cat(T c, int count);
	StringT& Cat() {return *this;}
	StringT& Cat(T i);
	StringT& Cat(const T* str, int str_count);
	StringT& Cat(const StringT& str) {return Cat(str.Begin(), str.GetCount());}
	
	void Replace(const StringT& s, const StringT& value);
	void Replace(int i, int len, const StringT& value);
	
	int GetCount() const { return count; }
	int GetLength() const { return count; }
	
	bool IsEmpty() const { return count == 0; }
	bool IsString() const {return !IsSpecial();}
	bool IsSpecial() const {return special != 0;}
	bool IsSpecial(byte st) const {return special == st;}
	void SetSpecial(byte st) {special = st;}
	byte GetSpecial() const {return special;}
	
	StringT Mid(int i) const;
	StringT Mid(int i, int size) const;
	StringT Left(int i) const { return Mid(0, min(i, GetCount())); }
	StringT Right(int i) const { return Mid(max(0, GetCount() - i), i); }
	
	void Remove(int begin, int count=1);
	bool Insert(int begin, T chr) {return Insert(begin, &chr, 1);}
	bool Insert(int begin, const T* str, int n);
	const T* Begin() const { return is_big ? BIG->Get() : buf; }
	const T* begin() const { return is_big ? BIG->Get() : buf; }
	const T* End() const { return Begin() + GetCount(); }
	const T* end() const { return Begin() + GetCount(); }
	operator const T*() const {return Begin();}
	const T* operator~() const {return Begin();}
	
	bool operator<(const StringT& s) const;
	bool operator>(const StringT& s) const;
	bool operator==(const StringT& s) const;
	bool operator!=(const StringT& s) const;
	bool operator==(const char* s) const;
	bool operator!=(const char* s) const;
	int Compare(const char* s) const;
	int Compare(const StringT& s) const;
	
	T operator[] (int i) const {return Get(i);}
	T Get(int i) const { ASSERT(i >= 0 && i < count); return *(Begin() + i); }

	StringT& operator += (const StringT& s) { Cat(s); return *this; }
	StringT& operator << (const StringT& s) { Cat(s); return *this; }
	StringT& operator << (int i) { Cat(IntStr(i)); return *this; }
	StringT& operator << (double d);

	static int OctInt(const StringT& s) { return CharOctInt(s.Begin()); }
	static int BinInt(const StringT& s) { return CharBinInt(s.Begin()); }
	static int64 BinInt64(const StringT& s) { return CharBinInt64(s.Begin()); }
	static int HexInt(const StringT& s) { return CharHexInt(s.Begin()); }
	static int64 HexInt64(const StringT& s) { return CharHexInt64(s.Begin()); }
	static int StrInt(const StringT& s) { return CharInt(s.Begin()); }
	static int64 StrInt64(const StringT& s) { return CharInt64(s.Begin()); }
	static double StrDbl(const StringT& s) { return CharDbl(s.Begin()); }

	static StringT IntStr(int i);
	static StringT IntStr64(int64 i);
	static StringT DblStr(double d);
	
	StringT<char> ToString() const;
	StringT<wchar_t> ToWString() const;

	hash_t GetHashValue() const;
	
	void Reserve(int i) {}
	
	int Find(T chr, int pos = 0) const ;
	int Find(const StringT& str, int pos = 0) const;
	int ReverseFind(const StringT& str) const;
	int ReverseFind(const StringT& str, int pos) const;
	int FindFirstOf(const T* str, int pos=0) const;
	int FindFirstNotOf(const T* str, int pos=0) const;
	int ReverseFindFirstNotOf(const T* str) const;
	
	static int CharOctInt(const T *s);
	static int CharBinInt(const T *s);
	static int64 CharBinInt64(const T *s);
	static int CharHexInt(const T *s);
	static int64 CharHexInt64(const T *s);
	static int CharInt(const T *s);
	static int64 CharInt64(const T *s);
	static uint64 CharIntU64(const T *s);
	static double CharDbl(const T* s);
	static const T* IntChar(T *p, int bufsize, int x);
	static const T* IntChar64(T *p, int bufsize, int64 x);
	static const T* IntCharU64(T *p, int bufsize, uint64 x);
	static int Length(const T* c, int max_len=-1);
	static int Compare(const T* a, const T* b);
	static int Compare(const T* a, const T* b, int len);
	static void Copy(T* dst, const T* src);
	
	Std ToStd();
	
	
};


#if 0
typedef StringT<char> String;
typedef StringT<wchar_t> WString;
#else
using String = StringT<char>;
using WString = StringT<wchar_t>;
#endif


String operator+(const String& a, const String& b);
String operator+(const String& s, const char*);
String operator+(const char* chr, const String& s);

WString operator+(const WString& a, const WString& b);
WString operator+(const WString& s, const wchar_t*);
WString operator+(const wchar_t* chr, const WString& s);



class Exc : public String {
public:
	Exc() {}
	Exc(const String& s) : String(s) {}
};
typedef Exc MemoryLimitExc;
typedef Exc NeverExc;
typedef Exc TodoExc;
typedef Exc SystemExc;


NAMESPACE_UPP_END

#endif
