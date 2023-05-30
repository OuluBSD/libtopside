#include "Core.h"

NAMESPACE_UPP_BEGIN

template<> StringT<char>	StringT<char>::ToString() const {return *this;}
template<> StringT<wchar_t>	StringT<char>::ToWString() const {return FromUtf8(Begin(), GetCount());}
template<> StringT<char>	StringT<wchar_t>::ToString() const {return ToUtf8(Begin(), GetCount());}
template<> StringT<wchar_t>	StringT<wchar_t>::ToWString() const {return *this;}


#if 0
template <> StringT<char>::StringT(const char* c) {
	Zero(); *this = c;
}

template <> StringT<wchar_t>::StringT(const char* c) {
	*this = String(c).ToWString();
}

template <> StringT<wchar_t>::StringT(const wchar_t* c) {
	Zero(); *this = c;
}

template <> StringT<char>::StringT(const wchar_t* c) {
	*this = WString(c).ToString();
}
#endif

void DebugStringLog(void* addr, const char* msg, int refs, int event) {
	LOG("String0: " << HexStr(addr) << ": debug(" << event << "): " << (String)msg << ": " << refs);
}

double ScanDouble(const char* c) {
	double a;
	sscanf(c, "%lf",&a);
	return a;
}

bool FitsInInt64(double x) {
	return x >= -9223372036854775808.0 && x < 9223372036854775808.0;
}


void NextCStringLine(StringStream& t, const char *linepfx, int& pl)
{
	t << "\"\r\n" << (linepfx ? linepfx : "") << "\"";
	pl = t.GetLength();
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

String HexString(void* data_, int len) {
	const char* data = (const char*)data_;
	String s = "0x";
	for(int i = 0; i < len; i++) {
		char c = data[len-1-i];
		byte low = (byte)c & 0xF;
		byte high = ((byte)c >> 4) & 0xF;
		s.Cat(HexDigit(high));
		s.Cat(HexDigit(low));
	}
	return s;
}

int CompareNoCase(String a, String b) {
	TODO
}



NAMESPACE_UPP_END
