#ifndef _CoreAlt_Ops_h_
#define _CoreAlt_Ops_h_

NAMESPACE_UPP_BEGIN

inline
	int SignificantBits(dword x)
{ // basically log2(x) + 1 except that for 0 this is 0, number of significant bits of x
#ifdef COMPILER_MSC
	DWORD index;
	return _BitScanReverse(&index, x) ? index + 1 : 0;
#else
	return x ? 32 - __builtin_clz(x) : 0;
#endif
}

inline
	int SignificantBits64(uint64 x)
{ // basically log2(x) + 1 except that for 0 this is 0, number of significant bits of x
#ifdef COMPILER_MSC
#ifdef CPU_64
	DWORD index;
	return _BitScanReverse64(&index, x) ? index + 1 : 0;
#else
	if (x & 0xffffffff00000000)
		return SignificantBits(HIDWORD(x)) + 32;
	else
		return SignificantBits((DWORD)x);
#endif
#else
	return x ? 64 - __builtin_clzl(x) : 0;
#endif
}

NAMESPACE_UPP_END

#endif
