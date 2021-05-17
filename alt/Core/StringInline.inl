static int CharOctInt(const T *s) {
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

static int CharBinInt(const T *s) {
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

static int64 CharBinInt64(const T *s) {
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

static int CharHexInt(const T *s) {
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

static int64 CharHexInt64(const T *s) {
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

static int CharInt(const T *s)
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

static int64 CharInt64(const T *s)
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

static uint64 CharIntU64(const T *s)
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

static double CharDbl(const T* s) {
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

static const T* IntChar(T *p, int bufsize, int x) {
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

static const T* IntChar64(T *p, int bufsize, int64 x) {
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

static const T* IntCharU64(T *p, int bufsize, uint64 x) {
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


static int Length(const T* c, int max_len=-1) {
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

static int Compare(const T* a, const T* b) {
	while (*a || *b) {
		T ac = *a++;
		T bc = *b++;
		int diff = ac - bc;
		if (diff)
			return diff;
	}
	return 0;
}

static int Compare(const T* a, const T* b, int len) {
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

static void Copy(T* dst, const T* src) {
	ASSERT(dst && src);
	if (!dst || !src) return;
	while (*src)
		* dst++ = *src++;
	*dst = 0;
}





int Find(T chr, int pos = 0) const {
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

int Find(const StringT& str, int pos = 0) const {
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

int ReverseFind(const StringT& str) const {
	return ReverseFind(str, GetCount() - 1);
}

int ReverseFind(const StringT& str, int pos) const {
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

int FindFirstOf(const T* str, int pos=0) const {
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

int FindFirstNotOf(const T* str, int pos=0) const {
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

int ReverseFindFirstNotOf(const T* str) const {
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
