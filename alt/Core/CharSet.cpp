#include "Core.h"

NAMESPACE_UPP_BEGIN


#if !defined flagMSC
typedef std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> UnicodeConverter;
UnicodeConverter& GetUnicodeConverter() {static UnicodeConverter conv; return conv;}
#endif



String ToUtf8(const wchar_t* s, int len) {
	if (len <= 0)
		return String();
	#ifdef flagSTDEXC
	try {
	#endif
		#if defined flagMSC
		MAKE_STATIC_LOCAL(Vector<char>, tmp);
		int sz = len * 4;
		tmp.SetCount(sz, 0);
		char* buf = tmp.Begin();
		WideCharToMultiByte(CP_UTF8, 0, s, len, buf, sz, 0, 0);
		String ret(buf, sz);
		#else
		std::wstring ws(s, len);
		std::string str = GetUnicodeConverter().to_bytes(ws);
		String ret(str.c_str(), str.size());
		#endif
		return ret;
	#ifdef flagSTDEXC
	}
	catch (std::range_error e) {
		LOG("ToUtf8: std::range_error: " + String(e.what()));
	}
	#endif
	return String();
}

WString FromUtf8(const char* s, int len) {
	if (len <= 0)
		return WString();
	#ifdef flagSTDEXC
	try {
	#endif
		#if defined flagMSC
		MAKE_STATIC_LOCAL(Vector<wchar_t>, tmp);
		int sz = len;
		tmp.SetCount(sz, 0);
		wchar_t* buf = tmp.Begin();
		MultiByteToWideChar(CP_UTF8, 0, s, len, buf, sz);
		WString ret(buf, sz);
		#else
		std::string str(s, len);
		std::wstring ws = GetUnicodeConverter().from_bytes(str);
		WString ret(ws.c_str(), ws.size());
		#endif
		return ret;
	#ifdef flagSTDEXC
	}
	catch (std::range_error e) {
		LOG("FromUtf8: std::range_error: " + String(e.what()));
	}
	#endif
	return WString();
}




dword FetchUtf8(const char *&_s, const char *_lim, bool& ok)
{
	const byte *s = (const byte *)_s;
	const byte *lim = (const byte *)_lim;
	dword code = *s;
	if(code < 0x80) {
		_s++;
		return *s;
	}
	else
	if(code >= 0xC2) {
		dword c;
		if(code < 0xE0 && s + 1 < lim &&
		   s[1] >= 0x80 && s[1] < 0xc0 &&
		   (c = ((code - 0xC0) << 6) + s[1] - 0x80) >= 0x80 && c < 0x800) {
			_s += 2;
			return c;
		}
		else
		if(code < 0xF0 && s + 2 < lim &&
		   s[1] >= 0x80 && s[1] < 0xc0 && s[2] >= 0x80 && s[2] < 0xc0 &&
		   (c = ((code - 0xE0) << 12) + ((s[1] - 0x80) << 6) + s[2] - 0x80) >= 0x800 &&
		   !(c >= 0xEE00 && c <= 0xEEFF)) {
			_s += 3;
			return c;
		}
		else
		if(code < 0xF8 && s + 3 < lim &&
		   s[1] >= 0x80 && s[1] < 0xc0 && s[2] >= 0x80 && s[2] < 0xc0 && s[3] >= 0x80 && s[3] < 0xc0 &&
		   (c = ((code - 0xF0) << 18) + ((s[1] - 0x80) << 12) + ((s[2] - 0x80) << 6) + s[3] - 0x80) >= 0x10000 &&
		   c < 0x110000) {
			_s += 4;
			return c;
		}
	}
	_s++;
	ok = false;
	return 0xEE00 + code; // ERROR ESCAPE
}


NAMESPACE_UPP_END
