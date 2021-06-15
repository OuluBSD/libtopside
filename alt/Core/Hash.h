#ifndef _CoreAlt_Hash_h_
#define _CoreAlt_Hash_h_

NAMESPACE_UPP_BEGIN

class CombineHash : Moveable<CombineHash> {
	hash_t hash = 123456789;

public:
	CombineHash() {}
	CombineHash(int v0) { Put(v0); }
	CombineHash(int v0, int v1) { Put(v0); Put(v1); }

	operator hash_t() const { return hash; }
	hash_t Get() const { return hash; }

	CombineHash& Put(int value) { hash = ((hash << 5) + hash) + value; return *this; }
	CombineHash& Put64(int64 value) {Put((int)((uint64)value >> 32ULL)); Put((int)(value & 0xFFFFFFFFULL)); return *this; }
	
	CombineHash& operator << (int value) { Put(value); return *this; }
	CombineHash& operator << (hash_t value) { Put(value); return *this; }
	CombineHash& operator << (int64 value) { Put64(value); return *this; }
	template <class T> CombineHash& operator << (const T& value) { Put(value.GetHashValue()); return *this; }
	
};

template <> inline CombineHash& CombineHash::operator << (const int& value) { Put(value); return *this; }
template <> inline CombineHash& CombineHash::operator << (const int64& value) { Put64(value); return *this; }




template <class K> inline hash_t GetHashValue(const K& k) { return k.GetHashValue(); }
template <> inline hash_t GetHashValue(const bool& k) { return k; }
template <> inline hash_t GetHashValue(const char& k) { return k; }
template <> inline hash_t GetHashValue(const int& k) { return k; }
template <> inline hash_t GetHashValue(const unsigned int& k) { return k; }
template <> inline hash_t GetHashValue(const unsigned long long& k) {union {uint64 u64; dword dw[2];}; u64 = k; return dw[0] ^ dw[1];}
#ifndef flagWIN32
template <> inline hash_t GetHashValue(const uint64& k) {union {uint64 u64; dword dw[2];}; u64 = k; return dw[0] ^ dw[1];}
#endif
template <> inline hash_t GetHashValue(const long long& k) {union {uint64 u64; dword dw[2];}; u64 = k; return dw[0] ^ dw[1];}
template <> inline hash_t GetHashValue(const long& k) { return k; }
template <> inline hash_t GetHashValue(const float& k) { return static_cast<hash_t>(k); }
template <> inline hash_t GetHashValue(const double& k) {return GetHashValue(*(uint64*)&k);}
template <> inline hash_t GetHashValue(const VOID_PTR& k) {
	#ifdef CPU_64
	return GetHashValue((uint64)k);
	#else
	return GetHashValue((uint32)k);
	#endif
}

NAMESPACE_UPP_END

#endif
