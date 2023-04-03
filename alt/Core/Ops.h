#ifndef _CoreAlt_Ops_h_
#define _CoreAlt_Ops_h_

NAMESPACE_UPP_BEGIN

inline int SignificantBits(dword x) {
	// basically log2(x) + 1 except that for 0 this is 0, number of significant bits of x
#ifdef COMPILER_MSC
	DWORD index;
	return _BitScanReverse(&index, x) ? index + 1 : 0;
#else
	return x ? 32 - __builtin_clz(x) : 0;
#endif
}

inline int SignificantBits64(uint64 x) {
	// basically log2(x) + 1 except that for 0 this is 0, number of significant bits of x
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




#if defined(CPU_X86) && defined(COMPILER_MSC)
#ifdef COMPILER_GCC
#ifdef CPU_64
inline word   SwapEndian16(word v)    { __asm__("xchgb %b0,%h0" : "=Q" (v) :  "0" (v)); return v; }
inline int16  SwapEndian16(int16 v)   { __asm__("xchgb %b0,%h0" : "=Q" (v) :  "0" (v)); return v; }
#else
inline word   SwapEndian16(word v)    { __asm__("xchgb %b0,%h0" : "=q" (v) :  "0" (v)); return v; }
inline int16  SwapEndian16(int16 v)   { __asm__("xchgb %b0,%h0" : "=q" (v) :  "0" (v)); return v; }
#endif
inline dword  SwapEndian32(dword v)   { __asm__("bswap %0" : "=r" (v) : "0" (v)); return v; }
inline int    SwapEndian32(int v)     { __asm__("bswap %0" : "=r" (v) : "0" (v)); return v; }
#endif

#ifdef COMPILER_MSC
#pragma intrinsic (_byteswap_ushort, _byteswap_ulong, _byteswap_uint64, strlen)

inline word   SwapEndian16(word v)    { return _byteswap_ushort(v); }
inline int16  SwapEndian16(int16 v)   { return _byteswap_ushort(v); }
inline dword  SwapEndian32(dword v)   { return _byteswap_ulong(v); }
inline int    SwapEndian32(int v)     { return _byteswap_ulong(v); }
#endif

inline void   EndianSwap(word& v)     { v = SwapEndian16(v); }
inline void   EndianSwap(int16& v)    { v = SwapEndian16(v); }
inline void   EndianSwap(dword& v)    { v = SwapEndian32(v); }
inline void   EndianSwap(int& v)      { v = SwapEndian32(v); }

#else

#ifdef COMPILER_GCC

inline dword  SwapEndian32(dword v)   { return __builtin_bswap32(v); }
inline int    SwapEndian32(int v)     { return __builtin_bswap32(v); }

inline word   SwapEndian16(word v)    { return SwapEndian32(v) >> 16; } // GCC bug workaround
inline int16  SwapEndian16(int16 v)   { return SwapEndian32(v) >> 16; }

inline void   EndianSwap(word& v)     { v = SwapEndian16(v); }
inline void   EndianSwap(int16& v)    { v = SwapEndian16(v); }
inline void   EndianSwap(dword& v)    { v = SwapEndian32(v); }
inline void   EndianSwap(int& v)      { v = SwapEndian32(v); }

#else

inline void   EndianSwap(word& v)     { byte *x = (byte *)(&v); Swap(x[0], x[1]); }
inline void   EndianSwap(int16& v)    { EndianSwap(*(word *)&v); }
inline void   EndianSwap(dword& v)    { byte *x = (byte *)&v; Swap(x[0], x[3]); Swap(x[1], x[2]); }
inline void   EndianSwap(int& v)      { EndianSwap(*(dword *)&v); }
inline word   SwapEndian16(word v)    { EndianSwap(v); return v; }
inline int16  SwapEndian16(int16 v)   { EndianSwap(v); return v; }
inline dword  SwapEndian32(dword v)   { EndianSwap(v); return v; }
inline int    SwapEndian32(int v)     { EndianSwap(v); return v; }

#endif

#endif

#if defined(CPU_AMD64) && (defined(COMPILER_GCC) || defined(COMPILER_MSC))
#ifdef COMPILER_GCC
inline uint64  SwapEndian64(uint64 v) { __asm__("bswap %0" : "=r" (v) : "0" (v)); return v; }
inline int64   SwapEndian64(int64 v)  { __asm__("bswap %0" : "=r" (v) : "0" (v)); return v; }
#endif
#ifdef COMPILER_MSC
inline uint64  SwapEndian64(uint64 v) { return _byteswap_uint64(v); }
inline int64   SwapEndian64(int64 v)  { return _byteswap_uint64(v); }
#endif

inline void   EndianSwap(int64& v)    { v = SwapEndian64(v); }
inline void   EndianSwap(uint64& v)   { v = SwapEndian64(v); }

#else

#ifdef COMPILER_GCC

inline uint64  SwapEndian64(uint64 v) { return __builtin_bswap64(v); }
inline int64   SwapEndian64(int64 v)  { return __builtin_bswap64(v); }

inline void    EndianSwap(int64& v)   { v = SwapEndian64(v); }
inline void    EndianSwap(uint64& v)  { v = SwapEndian64(v); }

#else
inline void   EndianSwap(int64& v)    { byte *x = (byte *)&v; Swap(x[0], x[7]); Swap(x[1], x[6]); Swap(x[2], x[5]); Swap(x[3], x[4]); }
inline void   EndianSwap(uint64& v)   { EndianSwap(*(int64 *)&v); }
inline int64  SwapEndian64(int64 v)   { EndianSwap(v); return v; }
inline uint64 SwapEndian64(uint64 v)  { EndianSwap(v); return v; }
#endif
#endif

inline word   SwapEndian16(int w)     { return SwapEndian16((word)w); }
inline word   SwapEndian16(dword w)   { return SwapEndian16((word)w); }

void EndianSwap(word *v, size_t count);
void EndianSwap(int16 *v, size_t count);
void EndianSwap(dword *v, size_t count);
void EndianSwap(int *v, size_t count);
void EndianSwap(int64 *v, size_t count);
void EndianSwap(uint64 *v, size_t count);


template <class T>
void Swap(T& a, T& b) {
	uint8 tmp[sizeof(T)];
	MemoryCopy((void*)tmp, (void*)&a, sizeof(T));
	MemoryCopy((void*)&a, (void*)&b, sizeof(T));
	MemoryCopy((void*)&b, (void*)tmp, sizeof(T));
}



#ifdef CPU_64

#define HASH64

#define HASH_CONST1 I64(0xf7c21089bee7c0a5)
#define HASH_CONST2 I64(0xc85abc8da7534a4d)
#define HASH_CONST3 I64(0x8642b0fe3e86671b)

typedef qword hash_t;

inline dword FoldHash(qword h)
{
	return (dword)SwapEndian64(HASH_CONST3 * h);
}

#else

#define HASH_CONST1 0xbee7c0a5
#define HASH_CONST2 0xa7534a4d
#define HASH_CONST3 0x8e86671b

typedef dword hash_t;

inline dword FoldHash(dword h)
{
	return SwapEndian32(HASH_CONST3 * h);
}

#endif


NAMESPACE_UPP_END

#endif
