#include "Core0.h"


NAMESPACE_UPP_BEGIN


#define TMPL(x)		template <class T> x StringT<T>::
#define TMPL_THIS	template <class T> StringT<T>& StringT<T>::
#define TMPL_NEW	template <class T> StringT<T> StringT<T>::


TMPL(int) CharOctInt(const T *s)
{
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

TMPL(int) CharBinInt(const T *s)
{
	if (!s) return 0;
	while (IsSpace(*s)) s++;
	int n=0, neg=0;
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

TMPL(int64) CharBinInt64(const T *s)
{
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

TMPL(int) CharHexInt(const T *s)
{
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

TMPL(int64) CharHexInt64(const T *s)
{
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

TMPL(int) CharInt(const T *s)
{
	int n=0, neg=0;
	while (IsSpace(*s)) s++;
	switch (*s) {
		case '-': neg=1;
		case '+': s++;
	}
	while (IsDigit(*s))
		n = 10*n - (*s++ - '0');
	return neg ? n : -n;
}

TMPL(int64) CharInt64(const T *s)
{
	int64 n=0, neg=0;
	while (IsSpace(*s)) s++;
	switch (*s) {
		case '-': neg=1;
		case '+': s++;
	}
	while (IsDigit(*s))
		n = 10*n - (*s++ - '0');
	return neg ? n : -n;
}

TMPL(uint64) CharIntU64(const T *s)
{
	uint64 n=0;
	while (IsSpace(*s)) s++;
	switch (*s) {
		case '-': return 0;
		case '+': s++;
	}
	while (IsDigit(*s))
		n = 10*n - (*s++ - '0');
	return n;
}

TMPL(double) CharDbl(const T* s) {
	double a = 0.0;
	int e = 0;
	int c;
	
	while ((c = *s++) != '\0' && IsDigit(c)) {
		a = a * 10.0 + (c - '0');
	}
	
	if (c == '.') {
		while ((c = *s++) != '\0' && IsDigit(c)) {
			a = a * 10.0 + (c - '0');
			e = e - 1;
		}
	}
	
	if (c == 'e' || c == 'E') {
		int sign = 1;
		int i = 0;
		c = *s++;
		
		if (c == '+')
			c = *s++;
		else
			if (c == '-') {
				c = *s++;
				sign = -1;
			}
			
		while (IsDigit(c)) {
			i = i * 10 + (c - '0');
			c = *s++;
		}
		
		e += i * sign;
	}
	
	while (e > 0) {
		a *= 10.0;
		e--;
	}
	
	while (e < 0) {
		a *= 0.1;
		e++;
	}
	
	return a;
}

TMPL(const T*) IntChar(T *p, int bufsize, int x)
{
	p += bufsize;
	bool is_neg = false;
	if (x < 0) {
		is_neg = true;
		x *= -1;
	}
	*--p = 0;
	do {
		*--p = '0' + x % 10;
		x /= 10;
	}
	while (x);
	if (is_neg)
		*--p = '-';
	return p;
}

TMPL(const T*) IntChar64(T *p, int bufsize, int64 x)
{
	p += bufsize;
	bool is_neg = false;
	if (x < 0) {
		is_neg = true;
		x *= -1;
	}
	*--p = 0;
	do {
		*--p = '0' + x % 10;
		x /= 10;
	}
	while (x);
	if (is_neg)
		*--p = '-';
	return p;
}

TMPL(const T*) IntCharU64(T *p, int bufsize, uint64 x)
{
	p += bufsize;
	bool is_neg = false;
	if (x < 0) {
		is_neg = true;
		x *= -1;
	}
	*--p = 0;
	do {
		*--p = '0' + x % 10;
		x /= 10;
	}
	while (x);
	if (is_neg)
		*--p = '-';
	return p;
}


TMPL(int) Length(const T* c, int max_len)
{
	ASSERT(c);
	if (!c) return 0;
	int count = 0;
	if (max_len < 0) {
		while (*c) {
			count++;
			c++;
		}
		return count;
	}
	else {
		while (max_len > 0 && *c) {
			count++;
			c++;
			max_len--;
		}
		return count;
	}
}

TMPL(int) Compare(const T* a, const T* b)
{
	while (*a || *b) {
		T ac = *a++;
		T bc = *b++;
		int diff = ac - bc;
		if (diff)
			return diff;
	}
	return 0;
}

TMPL(int) Compare(const T* a, const T* b, int len)
{
	while ((*a || *b) && len > 0) {
		T ac = *a++;
		T bc = *b++;
		int diff = ac - bc;
		if (diff)
			return diff;
		len--;
	}
	return 0;
}

TMPL(void) Copy(T* dst, const T* src)
{
	ASSERT(dst && src);
	if (!dst || !src) return;
	while (*src)
		* dst++ = *src++;
	*dst = 0;
}


#undef TMPL
#undef TMPL_THIS
#undef TMPL_NEW


template class StringT <char>;
template class StringT <wchar_t>;


String operator+(const String& a, const String& b) { String out(a); out.Cat(b); return out; }
String operator+(const String& s, const char* chr) { String out(s); out.Cat(chr); return out; }
String operator+(const char* chr, const String& s) { String out; out.Cat(chr); out.Cat(s); return out; }
WString operator+(const WString& a, const WString& b) { WString out(a); out.Cat(b); return out; }
WString operator+(const WString& s, const wchar* chr) { WString out(s); out.Cat(chr); return out; }
WString operator+(const wchar* chr, const WString& s) { WString out; out.Cat(chr); out.Cat(s); return out; }


NAMESPACE_UPP_END
