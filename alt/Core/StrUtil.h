#ifndef _Core_StringUtil_h_
#define _Core_StringUtil_h_

NAMESPACE_UPP_BEGIN


String operator+ (const char* c, const String& l);
String operator+ (const String& c, const String& l);
WString operator+ (const wchar_t* c, const WString& l);
WString operator+ (const WString& c, const WString& l);

template<> inline const char* AsTypeName<Exc>() {return "Exc";}
template<> inline const char* AsTypeName<String>() {return "String";}
template<> inline const char* AsTypeName<WString>() {return "WString";}

#define NEVER() THROW(NeverExc())

inline int ToUpper(int chr) {
	if (chr >= 'a' && chr <= 'z')
		return 'A' + (chr - 'a');
	return chr;
}

inline int ToLower(int chr) {
	if (chr >= 'A' && chr <= 'Z')
		return 'a' + (chr - 'A');
	return chr;
}

String ToUpper(const String& s);
String ToLower(const String& s);

WString ToUpper(const WString& s);
WString ToLower(const WString& s);

inline String ToUpperFirst(const String& s) {
	return ToUpper(s.Left(1)) + s.Mid(1);
}

inline double StrDbl(String s) { return String::StrDbl(s); }
inline int ScanInt(String s) { return String::StrInt(s); }
inline int64 ScanInt64(String s) { return String::StrInt64(s); }
inline int StrInt(String s) { return String::StrInt(s); }
inline int OctInt(String s) { return String::OctInt(s); }
inline int HexInt(String s) { return String::HexInt(s); }
inline int64 HexInt64(String s) { return String::HexInt64(s); }
inline int BinInt(String s) { return String::BinInt(s); }
inline int64 BinInt64(String s) { return String::BinInt64(s); }
inline int64 StrInt64(String s) { return String::StrInt64(s); }
inline String IntStr(int i) { return String::IntStr(i); }
inline String IntStr64(int64 i) { return String::IntStr64(i); }
String DblStr(double d);
double ScanDouble(const char* c);
bool FitsInInt64(double x);

String TrimLeft(String s);
String TrimRight(String s);
String TrimBoth(String s);


template <class T> inline String AsString(const T& o) {return o.ToString();}
template<> inline String AsString(const bool& o) {return o ? "true" : "false";}
template<> inline String AsString(const int& o) {return IntStr(o);}
template<> inline String AsString(const uint32& o) {return IntStr64(o);}
template<> inline String AsString(const int64& o) {return IntStr64(o);}
template<> inline String AsString(const byte& o) {return IntStr(o);}
template<> inline String AsString(const char& o) {String s; s.Cat(o); return s;}
template<> inline String AsString(const float& o) {return DblStr(o);}
template<> inline String AsString(const double& o) {return DblStr(o);}
template<> inline String AsString(const String& o) {return o;}
template <class T> inline WString ToWString(const T& o) {return o.ToWString();}

template <class T> inline int64 ToInt(const T& o) {return o.ToInt();}
template<> inline int64 ToInt(const bool& o) {return (int64)o;}
template<> inline int64 ToInt(const int& o) {return (int64)o;}
template<> inline int64 ToInt(const int64& o) {return (int64)o;}
template<> inline int64 ToInt(const byte& o) {return (int64)o;}
template<> inline int64 ToInt(const char& o) {return (int64)o;}
template<> inline int64 ToInt(const float& o) {return (int64)o;}
template<> inline int64 ToInt(const double& o) {return (int64)o;}
template<> inline int64 ToInt(const String& o) {return StrInt(o);}
template<> inline int64 ToInt(const WString& o) {return WString::StrInt(o);}

template <class T> inline double ToDouble(const T& o) {return o.ToDouble();}
template<> inline double ToDouble(const bool& o) {return (double)o;}
template<> inline double ToDouble(const int& o) {return (double)o;}
template<> inline double ToDouble(const int64& o) {return (double)o;}
template<> inline double ToDouble(const byte& o) {return (double)o;}
template<> inline double ToDouble(const char& o) {return (double)o;}
template<> inline double ToDouble(const float& o) {return (double)o;}
template<> inline double ToDouble(const double& o) {return (double)o;}
template<> inline double ToDouble(const String& o) {return StrDbl(o);}
template<> inline double ToDouble(const WString& o) {return WString::StrDbl(o);}

inline int HexDigit(int c) {return "0123456789ABCDEF"[c & 15];}
inline int HexDigitLower(int c) {return "0123456789abcdef"[c & 15];}
inline String HexStr(int64 p, bool prefix=true, bool high_chr=true) {
	String o;
	if (p < 0) {
		o.Cat('-');
		p = -p;
	}
	if (prefix)
		o.Cat("0x");
	bool zero = true;
	uint64 i = 64;
	int (*chr_fn)(int) = high_chr ? HexDigit : HexDigitLower;
	do {
		i -= 8;
		byte b = (p >> i) & 0xFFULL;
		if (b || !zero) {
			byte hi = b >> 4;
			byte lo = b & 0xF;
			if (hi || !zero)
				o.Cat(chr_fn(hi));
			o.Cat(chr_fn(lo));
			zero = false;
		}
	}
	while (i);
	if (zero) o.Cat('0');
	return o;
}
inline String HexStr(void* p, bool prefix=true, bool high_chr=true) {return HexStr((uint64)p, prefix, high_chr);}
String HexString(const char* data, int len);
inline String FormatIntHex(const void *ptr) { return HexStr((void*)ptr); }
inline String FormatHex(const void *ptr) { return HexStr((void*)ptr); }


String AsCString(const char *s, const char *lim);
String AsCString(const char *s);
String AsCString(const String& s);
WString FromUtf8(const String& x);


template <class T> String AsTypeString() {return AsTypeName<T>();}

int CompareNoCase(String a, String b);


struct RtErr {
	bool is_err = false;
	String err_msg;
public:
	
	void SetRtErr(String msg) {is_err = true; err_msg = msg;}
	void Clear() {is_err = false; err_msg.Clear();}
	bool IsRtErr() const {return is_err;}
	String GetRtErr() const {return err_msg;}
};

#define PRE_ERR(x) SetRtErr(x + ": " + GetRtErr())
#define CHK_RT_ERR if (IsRtErr()) return;
#define CHK_RT_ERR_(x) if (IsRtErr()) {PRE_ERR(x); return;}


NAMESPACE_UPP_END

#endif
