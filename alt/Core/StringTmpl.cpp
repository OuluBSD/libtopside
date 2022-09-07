#include "Core0.h"


NAMESPACE_UPP_BEGIN


#define TMPL(x)		template <class T> x StringT<T>::
#define TMPL_THIS	template <class T> StringT<T>& StringT<T>::
#define TMPL_NEW	template <class T> StringT<T> StringT<T>::


TMPL(void) Clear() {
	if (is_big) { BIG->Dec(); BIG = NULL; is_big = false;} else {buf[0] = 0;}
	count = 0;
	special = 0;
}

TMPL_THIS operator=(const T* c) {
	Clear();
	if (!c) return *this;
	count = Length(c);
	if (count < buf_size) {
		Copy(buf, c);
	}
	else {
		T* buf = (T*)malloc(sizeof(T) * (count + 1));
		MemoryCopy(buf, c, sizeof(T) * count);
		buf[count] = 0;
		BIG = new String0T(buf, count + 1);
		is_big = true;
	}
	return *this;
}

TMPL_THIS Set(const T* c, int len) {
	Clear();
	if (!c) return *this;
	count = min(Length(c, len), len);
	if (count < buf_size) {
		MemoryCopy(buf, c, sizeof(T) * count);
		buf[count] = 0;
	}
	else {
		T* buf = (T*)malloc(sizeof(T) * (count + 1));
		MemoryCopy(buf, c, sizeof(T) * count);
		buf[count] = 0;
		BIG = new String0T(buf, count + 1);
		is_big = true;
	}
	return *this;
}

TMPL_THIS SetData(void* c, int len) {
	Clear();
	if (!c) return *this;
	if (len == 0) return *this;
	ASSERT(len > 0);
	count = len;
	if (count < buf_size) {
		MemoryCopy(buf, c, sizeof(T) * count);
	}
	else {
		T* buf = (T*)malloc(sizeof(T) * count);
		MemoryCopy(buf, c, sizeof(T) * count);
		BIG = new String0T(buf, count);
		is_big = true;
	}
	special = 0xFF;
	//ASSERT(c[len-1] == 0);
	return *this;
}

TMPL(void*) GetWritableData(byte special, int len) {
	Clear();
	ASSERT(len > 0);
	count = len;
	this->special = special;
	if (count < buf_size) {
		buf[len] = 0;
		return buf;
	}
	else {
		T* buf = (T*)malloc(sizeof(T) * count);
		buf[len] = 0;
		BIG = new String0T(buf, count);
		is_big = true;
		return buf;
	}
}

TMPL_THIS operator=(const StringT& str) {
	if (this == &str)
		return *this;
	if (!str.is_big) {
		Clear();
		MemoryCopy(buf, str.buf, sizeof(buf));
		is_big = false;
	}
	else {
		if (BIG == str.BIG_FIELD)
			return *this;
		Clear();
		is_big = true;
		BIG = str.BIG_FIELD;
		BIG->Inc();
	}
	count = str.count;
	special = str.special;
	return *this;
}

TMPL_THIS Cat(T c, int count) {
	// TODO this is inefficient; optimize
	for(int i = 0; i < count; i++) Cat(c);
	return *this;
}

TMPL_THIS Cat(T i) {
	if (!is_big) {
		is_big = count + 1 >= buf_size;
		if (!is_big) {
			buf[count] = i;
			count++;
			buf[count] = 0;
		}
		else {
			T* buf = (T*)malloc(sizeof(T) * (count + 1 + 1));
			MemoryCopy(buf, this->buf, sizeof(T) * count);
			buf[count] = i;
			count++;
			buf[count] = 0;
			BIG = new String0T(buf, count + 1);
			is_big = true;
		}
	}
	else {
		if (BIG->GetRefs() == 1) {
			int new_count = count + 1 + 1;
			if (new_count > BIG->GetAlloc())
				BIG->IncreaseReserved();
			T* c = BIG->Begin();
			c[count] = i;
			count++;
			c[count] = 0;
		}
		else {
			T* buf = (T*)malloc(sizeof(T) * (count + 1 + 1));
			MemoryCopy(buf, BIG->Get(), sizeof(T) * count);
			buf[count] = i;
			count++;
			buf[count] = 0;
			BIG->Dec();
			BIG = new String0T(buf, count + 1);
		}
	}
	return *this;
}

TMPL_THIS Cat(const T* str, int str_count) {
	if (!is_big) {
		is_big = count + str_count >= buf_size;
		if (!is_big) {
			MemoryCopy(&buf[count], str, sizeof(T) * str_count);
			count += str_count;
			buf[count] = 0;
		}
		else {
			int alloc = count + str_count + 1;
			T* buf = (T*)malloc(sizeof(T) * (alloc));
			MemoryCopy(buf, this->buf, sizeof(T) * count);
			MemoryCopy(&buf[count], str, sizeof(T) * str_count);
			count += str_count;
			buf[count] = 0;
			BIG = new String0T(buf, alloc);
			is_big = true;
		}
	}
	else {
		if (BIG->GetRefs() == 1) {
			int new_count = count + str_count + 1;
			if (new_count > BIG->GetAlloc())
				BIG->IncreaseReserved(new_count);
			T* c = BIG->Begin();
			MemoryCopy(c + count, str, sizeof(T) * str_count);
			count += str_count;
			c[count] = 0;
		}
		else {
			int alloc = count + str_count + 1;
			T* buf = (T*)malloc(sizeof(T) * (alloc));
			MemoryCopy(buf, BIG->Get(), sizeof(T) * count);
			MemoryCopy(&buf[count], str, sizeof(T) * str_count);
			count += str_count;
			buf[count] = 0;
			BIG->Dec();
			BIG = new String0T(buf, alloc);
		}
	}
	return *this;
}

TMPL(void) Replace(const StringT& s, const StringT& value) {
	if (s == value) return;
	int i = Find(s);
	while (i >= 0) {
		Replace(i, s.GetCount(), value);
		i = Find(s, i + value.GetCount());
	}
}

TMPL(void) Replace(int i, int len, const StringT& value) {
	int new_len = this->count - len + value.GetCount();
	const T* begin = Begin();
	int alloc = new_len + 1;
	T* buf = (T*)malloc(sizeof(T) * (alloc));
	int cursor = 0;
	if (i > 0) {
		MemoryCopy(buf, begin, sizeof(T) * i);
		cursor += i;
	}
	if (value.GetCount() > 0) {
		MemoryCopy(buf + cursor, value.Begin(), sizeof(T) * value.GetCount());
		cursor += value.GetCount();
	}
	int c = i + len;
	int end_len = this->count - c;
	if (end_len > 0) {
		MemoryCopy(buf + cursor, begin + c, sizeof(T) * end_len);
		cursor += end_len;
	}
	buf[cursor++] = 0;

	Clear();
	this->is_big = true;
	this->count = new_len;
	BIG = new String0T(buf, alloc);
	ASSERT(cursor == new_len+1);
}

TMPL_NEW Mid(int i) const {
	if (i >= GetCount())
		return StringT();
	if (i < 0)
		i = 0;
	return Mid(i, GetCount() - i);
}

TMPL_NEW Mid(int i, int size) const {
	size = min(size, count - i);
	if (size <= 0)
		return StringT();
	ASSERT(i >= 0 && i + size <= count);
	return StringT(Begin() + i, size);
}

TMPL(void) Remove(int begin, int count) {
	ASSERT(begin >= 0 && count >= 0);
	begin = max(0, begin);
	count = max(0, count);
	int end = begin + count;
	int c = GetCount();
	ASSERT(begin <= c && end <= c);
	end = min(c, end);
	begin = min(c, begin);
	int l = begin;
	int r = c - end;
	if (l && r)
		*this = Left(l) + Right(r);
	else if (l)
		*this = Left(l);
	else if (r)
		*this = Right(r);
	else
		Clear();
}

TMPL(bool) Insert(int begin, const T* str, int n) {
	if (begin < 0 || begin > GetCount() || !str || n <= 0)
		return false;
	ASSERT(begin >= 0 && begin <= GetCount());
	begin = max(0, min(begin, GetCount()));
	StringT part(str, n);
	int l = begin;
	int r = GetCount() - begin;
	if (l && r)
		*this = Left(l) + part + Right(r);
	else if (l)
		*this = Left(l) + part;
	else if (r)
		*this = part + Right(r);
	else
		*this = part;
	return true;
}

TMPL(bool) operator<(const StringT& s) const {
	if (s.count == 0) return false;
	if (count == 0) return true;
	return Compare(s.Begin(), Begin(), min(count+1, s.count+1)) > 0;
}

TMPL(bool) operator>(const StringT& s) const {
	if (s.count == 0) return true;
	if (count == 0) return false;
	return Compare(s.Begin(), Begin(), min(count+1, s.count+1)) < 0;
}

TMPL(bool) operator==(const StringT& s) const {
	if (s.GetCount() != GetCount())
		return false;
	return Compare(s.Begin(), Begin(), min(count+1, s.count+1)) == 0;
}

TMPL(bool) operator!=(const StringT& s) const {
	return !(*this == s);
}

template <>
bool StringT<char>::operator==(const char* s) const {
	int len = (int)strnlen(s, 1 << 20);
	if (len != GetCount())
		return false;
	return Compare(s, Begin(), len) == 0;
}

template <>
bool StringT<char>::operator!=(const char* s) const {
	int len = (int)strnlen(s, 1 << 20);
	if (len != GetCount())
		return true;
	return Compare(s, Begin(), len) != 0;
}

template <>
int StringT<char>::Compare(const char* s) const {
	return Compare(s, Begin(), std::max(GetCount(), (int)strnlen(s, 1 << 20)));
}

template <>
int StringT<char>::Compare(const StringT& s) const {
	return Compare(s.Begin(), Begin(), std::max(GetCount(), s.GetCount()));
}

TMPL_NEW IntStr(int i) {
	T buf[10];
	const T* value = IntChar(buf, 10, i);
	return StringT(value);
}

TMPL_NEW IntStr64(int64 i) {
	T buf[30];
	const T* value = IntChar64(buf, 30, i);
	return StringT(value);
}

template <>
StringT<char> StringT<char>::DblStr(double d) {
	char output[50];
	snprintf(output, 50, "%g", d);
	return StringT(output);
}

template <>
StringT<wchar_t> StringT<wchar_t>::DblStr(double d) {
	return String::DblStr(d).ToWString();
}

String DblStr(double d) { return String::DblStr(d); }

TMPL_THIS operator << (double d) { Cat(DblStr(d)); return *this; }

TMPL(hash_t) GetHashValue() const {
	CombineHash ch;
	const T* buf = Begin();
	for (int i = 0; i < count; i++)
		ch.Put(*buf++);
	return ch;
}


TMPL(int) Find(T chr, int pos) const {
	if (GetCount() == 0) return -1;
	if (pos == count)
		return -1;
	ASSERT(pos >= 0 && pos < GetCount());
	const T* cur = Begin();
	for (int i = pos; i < count; i++) {
		if (*(cur + i) == chr)
			return i;
	}
	return -1;
}

TMPL(int) Find(const StringT& str, int pos) const {
	if (GetCount() == 0) return -1;
	if (pos == count)
		return -1;
	ASSERT(pos >= 0 && pos < GetCount());
	const T* cur = Begin();
	const T* cmp = str.Begin();
	int len = str.GetCount();
	for (int i = pos; i < count; i++) {
		if (Compare(cur + i, cmp, len) == 0)
			return i;
	}
	return -1;
}

TMPL(int) ReverseFind(const StringT& str) const {
	return ReverseFind(str, GetCount() - 1);
}

TMPL(int) ReverseFind(const StringT& str, int pos) const {
	if (GetCount() == 0) return -1;
	ASSERT(pos >= 0 && pos < GetCount());
	const T* cur = Begin();
	const T* cmp = str.Begin();
	int len = str.GetCount();
	for (int i = pos; i >= 0; i--) {
		if (Compare(cur + i, cmp, len) == 0)
			return i;
	}
	return -1;
}

TMPL(int) FindFirstOf(const T* str, int pos) const {
	ASSERT(pos >= 0 && pos <= GetCount());
	if (GetCount() <= 0 || !str) return -1;
	const T* it  = Begin();
	const T* end = End();
	int i = 0;
	while (it != end) {
		T chr = *it++;
		const T* cmp_it = str;
		bool match = false;
		while (1) {
			T cmp_chr = *cmp_it++;
			if (!cmp_chr)
				break;
			if (chr == cmp_chr) {
				match = true;
				break;
			}
		}
		if (match)
			return i;
		i++;
	}
	return -1;
}

TMPL(int) FindFirstNotOf(const T* str, int pos) const {
	ASSERT(pos >= 0 && pos <= GetCount());
	if (GetCount() <= 0 || !str) return -1;
	const T* it  = Begin();
	const T* end = End();
	int i = 0;
	it += pos;
	while (it != end) {
		T chr = *it++;
		const T* cmp_it = str;
		bool match = false;
		while (1) {
			T cmp_chr = *cmp_it++;
			if (!cmp_chr)
				break;
			if (chr == cmp_chr) {
				match = true;
				break;
			}
		}
		if (!match)
			return i;
		i++;
	}
	return -1;
}

TMPL(int) ReverseFindFirstNotOf(const T* str) const {
	if (GetCount() <= 0 || !str) return -1;
	const T* begin = Begin();
	const T* it = End();
	int i = GetCount();
	while (it != begin) {
		T chr = *--it;
		const T* cmp_it = str;
		bool match = false;
		while (1) {
			T cmp_chr = *cmp_it++;
			if (!cmp_chr)
				break;
			if (chr == cmp_chr) {
				match = true;
				break;
			}
		}
		i--;
		if (!match)
			return i;
	}
	return -1;
}


#undef TMPL
#undef TMPL_THIS
#undef TMPL_NEW


template class StringT <char>;
template class StringT <wchar_t>;

	


NAMESPACE_UPP_END
