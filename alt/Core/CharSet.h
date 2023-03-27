#ifndef _Core_CharSet_h_
#define _Core_CharSet_h_

NAMESPACE_UPP_BEGIN


String ToUtf8(const wchar_t* s, int len);
WString FromUtf8(const char* s, int len);

inline String ToUtf8(wchar code) { return ToUtf8(&code, 1); }

extern Tuple<dword, const char *> KeyNames__[];

template<> inline String AsString(const WString& o) {return ToUtf8(o.Begin(), o.GetCount());}
		   inline String ToString(const WString& o) {return ToUtf8(o.Begin(), o.GetCount());}
template<> inline WString ToWString(const CString& o) {return FromUtf8(o, -1);}
template<> inline WString ToWString(const String& o) {return FromUtf8(o.Begin(), o.GetCount());}
inline WString ToWString(const wchar_t* o) {return WString(o);}
inline WString ToWString(const char* o) {return ToWString(String(o));}


NAMESPACE_UPP_END

#endif
