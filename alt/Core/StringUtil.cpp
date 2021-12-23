#include "Core.h"

NAMESPACE_UPP_BEGIN


String operator+ (const char* c, const String& l) { String s(c); s.Cat(l); return s; }
String operator+ (const String& c, const String& l) { String s(c); s.Cat(l); return s; }
WString operator+ (const wchar_t* c, const WString& l) { WString s(c); s.Cat(l); return s; }
WString operator+ (const WString& c, const WString& l) { WString s(c); s.Cat(l); return s; }


NAMESPACE_UPP_END
