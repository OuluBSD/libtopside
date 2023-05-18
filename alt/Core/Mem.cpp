#include "Core.h"

NAMESPACE_UPP_BEGIN


never_inline
void memcpy8__(void *p, const void *q, size_t len)
{
	ASSERT(len >= 16);
	
	byte *t = (byte *)p;
	const byte *s = (const byte *)q;

	if(len > 4*1024*1024) { // for really huge data, call memcpy to bypass the cache
		memcpy(t, s, len);
		return;
	}

	auto Copy128 = [&](size_t at) { i16x8(s + at).Store(t + at); };
	Copy128(len - 16); // copy tail
	Copy128(0); // align target data up on the next 16 bytes boundary
	if(len <= 32)
		return;
	const byte *e = t + len;
	byte *t1 = (byte *)(((uintptr_t)t | 15) + 1);
	s += t1 - t;
	t = t1;
	len = e - t;
	e -= 64;
	while(t <= e) {
		Copy128(0*16); Copy128(1*16); Copy128(2*16), Copy128(3*16);
		t += 64;
		s += 64;
	}
	if(len & 32) {
		Copy128(0*16); Copy128(1*16);
		t += 32;
		s += 32;
	}
	if(len & 16)
		Copy128(0*16);
}


NAMESPACE_UPP_END
