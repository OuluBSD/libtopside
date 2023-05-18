#ifndef _Core_Mem_h_
#define _Core_Mem_h_

NAMESPACE_UPP_BEGIN


void memcpy8__(void *p, const void *q, size_t count);

inline
void memcpy8(void *p, const void *q, size_t count)
{
	byte *t = (byte *)p;
	byte *s = (byte *)q;
	if(count <= 4) {
		if(count < 2) {
			if(count)
				t[0] = s[0];
			return;
		}
		*(word *)t = *(word *)s;
		*(word *)(t + count - 2) = *(word *)(s + count - 2);
		return;
	}
	if(count <= 16) {
		if(count <= 8) {
			*(dword *)(t) = *(dword *)(s);
			*(dword *)(t + count - 4) = *(dword *)(s + count - 4);
			return;
		}
		*(uint64 *)t = *(uint64 *)s;
		*(uint64 *)(t + count - 8) = *(uint64 *)(s + count - 8);
		return;
	}
	#if 0
	if(count <= 32) { // improves String::LSet
		auto Copy128 = [&](size_t at) { i16x8(s + at).Store(t + at); };
		Copy128(count - 16);
		Copy128(0);
		return;
	}
	#endif

	memcpy8__(t, s, count);
}


NAMESPACE_UPP_END

#endif
