#ifndef _CoreAlt_Topt_h_
#define _CoreAlt_Topt_h_

NAMESPACE_UPP_BEGIN

struct EmptyClass {};



#ifdef NO_MOVEABLE_CHECK

template <class T>
inline void AssertMoveable(T *) {}

#define MoveableTemplate(T)

template <class T, class B = EmptyClass>
class Moveable : public B
{
};

template <class T>
struct Moveable_ {
};

#define NTL_MOVEABLE(T)

#else

template <class T>
inline void AssertMoveablePtr(T, T) {}

template <class T>
inline void AssertMoveable0(T *t) { AssertMoveablePtr(&**t, *t); }
// COMPILATION ERROR HERE MEANS TYPE T WAS NOT MARKED AS Moveable

template <class T>
inline void AssertMoveable0(T **t) {}

template <class T, class B = EmptyClass>
struct Moveable : public B {
	friend void AssertMoveable0(T *) {}
};

template <class T>
struct Moveable_ {
	friend void AssertMoveable0(T *) {}
};

template <class T>
inline void AssertMoveable(T *t = 0) { if(t) AssertMoveable0(t); }


#define NTL_MOVEABLE(T) template<> inline void AssertMoveable<T>(T *) {}

#endif

NTL_MOVEABLE(bool)
NTL_MOVEABLE(char)
NTL_MOVEABLE(signed char)
NTL_MOVEABLE(unsigned char)
NTL_MOVEABLE(short)
NTL_MOVEABLE(unsigned short)
NTL_MOVEABLE(int)
NTL_MOVEABLE(unsigned int)
NTL_MOVEABLE(long)
NTL_MOVEABLE(unsigned long)
NTL_MOVEABLE(long long)
NTL_MOVEABLE(unsigned long long)
NTL_MOVEABLE(float)
NTL_MOVEABLE(double)
NTL_MOVEABLE(void *)
NTL_MOVEABLE(const void *)
NTL_MOVEABLE(wchar_t)

#ifdef flagSTDRTTI
NTL_MOVEABLE(TypeCls)
#endif

#ifdef flagGLM
NTL_MOVEABLE(glm::vec2)
NTL_MOVEABLE(glm::vec3)
NTL_MOVEABLE(glm::vec4)
NTL_MOVEABLE(glm::mat2)
NTL_MOVEABLE(glm::mat3)
NTL_MOVEABLE(glm::mat4)
#endif

// TODO check if needed actually
#if 0 //defined flagWIN32
NTL_MOVEABLE(int64)
NTL_MOVEABLE(uint64)
#endif


template <class K> inline hash_t GetHashValue(const K* k) { return (hash_t)(size_t)k; }
template <class K> inline hash_t GetHashValue(const K& k) { return k.GetHashValue(); }
template <> inline hash_t GetHashValue(const bool& k) { return k; }
template <> inline hash_t GetHashValue(const char& k) { return k; }
template <> inline hash_t GetHashValue(const short& k) { return k; }
template <> inline hash_t GetHashValue(const int& k) { return k; }
template <> inline hash_t GetHashValue(const unsigned char& k) { return k; }
template <> inline hash_t GetHashValue(const unsigned short& k) { return k; }
template <> inline hash_t GetHashValue(const unsigned int& k) { return k; }
template <> inline hash_t GetHashValue(const unsigned long& k) { return k; }
#if CPU_64
template <> inline hash_t GetHashValue(const unsigned long long& k) {return *(hash_t*)&k;}
template <> inline hash_t GetHashValue(const long long& k) {return *(hash_t*)&k;}
#endif
#if CPU_32
template <> inline hash_t GetHashValue(const unsigned long long& k) {union {uint64 u64; dword dw[2];}; u64 = k; return dw[0] ^ dw[1];}
template <> inline hash_t GetHashValue(const long long& k) {union {uint64 u64; dword dw[2];}; u64 = k; return dw[0] ^ dw[1];}
#endif
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


struct CombineHash {
	hash_t hash;

	template <class T> CombineHash& Do(const T& x)                  { Put(GetHashValue(x)); return *this; }

public:
	CombineHash& Put(hash_t h)                                      { hash = HASH_CONST2 * hash + h; return *this; }

	operator hash_t() const                                         { return hash; }

	CombineHash()                                                   { hash = HASH_CONST1; }
	template <class T>
	CombineHash(const T& h1)                                        { hash = HASH_CONST1; Do(h1); }
	template <class T, class U>
	CombineHash(const T& h1, const U& h2)                           { hash = HASH_CONST1; Do(h1); Do(h2); }
	template <class T, class U, class V>
	CombineHash(const T& h1, const U& h2, const V& h3)              { hash = HASH_CONST1; Do(h1); Do(h2); Do(h3); }
	template <class T, class U, class V, class W>
	CombineHash(const T& h1, const U& h2, const V& h3, const W& h4)	{ hash = HASH_CONST1; Do(h1); Do(h2); Do(h3); Do(h4); }

	template <class T> CombineHash& operator<<(const T& x)          { Do(x); return *this; }
};


template <> inline CombineHash& CombineHash::operator << (const size_t& value) { Put(value); return *this; }


template <class T>
int NumberCompare__(const T& a, const T& b)
{
	if(a < b) return -1;
	if(a > b) return 1;
	return 0;
}

inline int SgnCompare(const int& a, const int& b)                         { return NumberCompare__(a, b); }
inline int SgnCompare(const int64& a, const int64& b)                     { return NumberCompare__(a, b); }
inline int SgnCompare(const double& a, const double& b)                   { return NumberCompare__(a, b); }


NAMESPACE_UPP_END

#endif
