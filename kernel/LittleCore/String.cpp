#include "LittleCore.h"
#include <LittleCommon/LittleCommon.h>


KString::KString(KString&& s) {
	str = s.str;
	sz = s.sz;
	owned = s.owned;
	s.str = 0;
	s.sz = 0;
	s.owned = 0;
}

void KString::Clear() {
	if (!owned) {
		str = 0;
		sz = 0;
	}
	else {
		ASSERT(str);
		if (str) {
			int* ref = GetRefPtr();
			if (--(*ref) <= 0) {
				KFree(ref);
			}
			str = 0;
		}
		sz = 0;
		owned = false;
	}
}

void KString::Link(const char* s, int len) {
	Clear();
	if (len < 0)
		len = (int)strnlen(s, 0x100000); // 1meg max
	str = s;
	sz = len;
	owned = false;
}

void KString::Set(const char* s, int len) {
	Clear();
	if (len < 0)
		len = (int)strnlen(s, 0x100000); // 1meg max
	if (len < 128)
		len = GetReserveSize(len);
	Reserve(len);
	const char* dst = str;
	memcpy((void*)dst, (void*)s, len);
}

void KString::Ref(const KString& s) {
	Clear();
	str = s.str;
	sz = s.sz;
	owned = s.owned;
	IncRef();
}
void KString::IncRef() {
	if (owned && str) {
		int* ref = GetRefPtr();
		(*ref)++;
	}
}

void KString::DecRef() {
	if (owned && str) {
		int* ref = GetRefPtr();
		(*ref)--;
		ASSERT(*ref > 0);
	}
}

KString& KString::Cat(const KString& s) {
	if (s.str && s.sz > 0) {
		if (!owned)
			Own(s.sz);
		else
			Reserve(sz + s.sz);
		char* p = (char*)str + sz;
		sz += s.sz;
		memcpy(p, s.str, s.sz);
	}
	return *this;
}

KString& KString::Cat(char c) {
	if (!owned)
		Own(1);
	else
		Reserve(sz + 1);
	char* p = (char*)str + sz;
	sz++;
	*p = c;
	return *this;
}

void KString::Own(int extra_size) {
	bool ownable = !owned && str && sz;
	if (!ownable) {
		Clear();
		return;
	}
	
	// Calculate new memory size
	extra_size = extra_size < 0 ? 0 : extra_size;
	int new_sz = sizeof(int) * 2 + GetReserveSize(sz + extra_size);
	int* new_mem = (int*)KMemoryAllocate(new_sz);
	ASSERT(new_mem);
	
	// Write header
	int& refs = new_mem[0];
	int& reserved = new_mem[1];
	refs = 1;
	reserved = new_sz;
	
	// Copy data
	const char* old_str = str;
	str = (const char*)&new_mem[2];
	memcpy((void*)str, (void*)old_str, sz);
}

void KString::Reserve(unsigned int new_sz) {
	if (!owned) {
		Own(new_sz - sz);
		return;
	}
	if (new_sz <= *GetReservedPtr())
		return;
	ASSERT(new_sz > 0);
	if (new_sz < 128)
		new_sz = GetReserveSize(new_sz);
	
	// Have old values in stack
	const char* old_str = str;
	int* old_mem = ((int*)old_str) - 2;
	int& old_refs = old_mem[0];
	int& old_reserved = old_mem[1];
	
	// Allocate new memory
	int* new_mem = (int*)KMemoryAllocate(new_sz);
	ASSERT(new_mem);
	
	// Write header
	int& refs = new_mem[0];
	int& reserved = new_mem[1];
	refs = 1;
	reserved = new_sz;
	
	// Copy data
	if (sz > 0) {
		str = (const char*)&new_mem[2];
		memcpy((void*)str, (void*)old_str, sz);
	}
	
	// Check & free old string
	if (--old_refs <= 0) {
		KFree(old_mem);
	}
}

KString KString::Mid(int begin) const {
	KString s;
	begin = max(0, begin);
	int len = max(0, sz - begin);
	if (len > 0) {
		if (!owned) {
			s.str = str + begin;
			s.owned = false;
			s.sz = len;
		}
		else {
			s.Set(str + begin, len);
		}
	}
	return s;
}

KString KString::Mid(int begin, int len) const {
	KString s;
	begin = max(0, begin);
	int max_len = max(0, sz - begin);
	len = min(len, max_len);
	if (len > 0) {
		if (!owned) {
			s.str = str + begin;
			s.owned = false;
			s.sz = len;
		}
		else {
			s.Set(str + begin, len);
		}
	}
	return s;
}

int KString::GetReserveSize(int len) {
	int new_alloc = 1;
	while (new_alloc <= len)
		new_alloc <<= 1;
	return new_alloc;
}



KString HexString(void* data_, int len) {
	const char* data = (const char*)data_;
	KString s = "0x";
	for(int i = 0; i < len; i++) {
		char c = data[len-1-i];
		byte low = (byte)c & 0xF;
		byte high = ((byte)c >> 4) & 0xF;
		s.Cat(HexDigit(high));
		s.Cat(HexDigit(low));
	}
	return s;
}


KString KString::IntHex(int i) {
	return HexString((void*)&i, sizeof(int));
}

KString KString::IntHex64(int64 i) {
	return HexString((void*)&i, sizeof(int64));
}

KString KString::IntStr(int i) {
	char buf[10];
	const char* value = IntChar(buf, 10, i);
	return KString(value);
}

KString KString::IntStr64(int64 i) {
	char buf[30];
	const char* value = IntChar64(buf, 30, i);
	return KString(value);
}
