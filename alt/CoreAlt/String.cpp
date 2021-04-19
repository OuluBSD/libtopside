#include "Core.h"

NAMESPACE_UPP_BEGIN


double ScanDouble(const char* c) {
	double a;
	sscanf(c, "%lf",&a);
	return a;
}

String FormatScientific(double d) {
	char buffer [100];
	int len = snprintf ( buffer, 100, "%.8g", d);
	return String(buffer, len);
}

bool FitsInInt64(double x) {
	return x >= -9223372036854775808.0 && x < 9223372036854775808.0;
}


String ToUtf8(const wchar_t* s, int len) {
	if (len <= 0)
		return String();
	try {
		std::wstring ws(s, len);
		std::string str = GetUnicodeConverter().to_bytes(ws);
		String ret(str.c_str(), str.size());
		return ret;
	}
	catch (std::range_error e) {
		LOG("ToUtf8: std::range_error: " + String(e.what()));
	}
	return String();
}

WString FromUtf8(const char* s, int len) {
	if (len <= 0)
		return WString();
	try {
		std::string str(s, len);
		std::wstring ws = GetUnicodeConverter().from_bytes(str);
		WString ret(ws.c_str(), ws.size());
		return ret;
	}
	catch (std::range_error e) {
		LOG("FromUtf8: std::range_error: " + String(e.what()));
	}
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

void NextCStringLine(StringStream& t, const char *linepfx, int& pl)
{
	t << "\"\r\n" << (linepfx ? linepfx : "") << "\"";
	pl = t.GetLength();
}

String FromCString(const char *s, const char *lim) {
	StringStream t;
	
	if (*s == '\"') {
		s++;
		lim--;
	}
	int i, j;
	int l = lim - s;
	char esc_char[] = { '\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\'};
	char essc_str[] = {  'a', 'b', 'f', 'n', 'r', 't', 'v', '\\'};
	for (i = 0;i < l;i++) {
		if (s[i] == '\\') {
			i++;
			for (j = 0; j < 8 ;j++) {
				if (s[i] == essc_str[j]) {
					t.Cat(esc_char[j]);
					break;
				}
			}
			if (j == 8)
				t.Cat(s[i]);
		}
		else {
			t.Cat(s[i]);
		}
	}
	
	return t.GetResult();
}

String AsCString(const char *s, const char *lim) {
	StringStream t;
	t.Cat('\"');
	
	int i, j;
	int l = lim - s;
	char esc_char[] = { '\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\'};
	char essc_str[] = {  'a', 'b', 'f', 'n', 'r', 't', 'v', '\\'};
	for (i = 0;i < l;i++) {
		for (j = 0; j < 8 ;j++) {
			if (s[i] == esc_char[j]) {
				t.Cat('\\');
				t.Cat(essc_str[j]);
				break;
			}
		}
		if (j == 8)
			t.Cat(s[i]);
	}
	
	t.Cat('\"');
	return t.GetResult();
}


String AsCString(const char *s) {
	return AsCString(s, s + strlen(s));
}

String AsCString(const String& s) {
	return AsCString(s, s.End());
}


WString FromUtf8(const String& x) {
	return ToWString(x);
}

String HexString(const char* data, int len) {
	String s = "0x";
	for(int i = 0; i < len; i++) {
		char c = data[i];
		byte low = (byte)c & 0xF;
		byte high = ((byte)c >> 4) & 0xF;
		s.Cat(HexDigit(low));
		s.Cat(HexDigit(high));
	}
	return s;
}

NAMESPACE_UPP_END
