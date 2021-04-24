#ifndef _CoreAlt_Fn_h_
#define _CoreAlt_Fn_h_

NAMESPACE_UPP_BEGIN



class Stream;  Stream& VppLog(); void Panic(); void LogCString(const char* c);
inline void* MemoryAlloc(size_t size) {return malloc(size);}
inline void MemoryFree(void* ptr) {free(ptr);}


//$-constexpr int findarg(const T& x, const T1& p0, ...);

template <class T, class K>
constexpr int findarg(const T& x, const K& k)
{
	return x == k ? 0 : -1;
}

template <class T, class K, typename... L>
constexpr int findarg(const T& sel, const K& k, const L& ...args)
{
	if(sel == k)
		return 0;
	int q = findarg(sel, args...);
	return q >= 0 ? q + 1 : -1;
}




const int    INT_NULL           =    INT_MIN;
const int64  INT64_NULL         =    INT64_MIN;
const double DOUBLE_NULL        =    -1.0E+308;
const double DOUBLE_NULL_LIM    =    -1.0E+307;

class Nuller {
public:

	Nuller() {}
	operator int() const      { return INT_NULL; }
	operator int64() const    { return INT64_NULL; }
	operator double() const   { return DOUBLE_NULL; }
	operator bool() const     { return false; }
};

extern const Nuller Null;

template <class T> void SetNull(T& x) { x = Null; }
template <class T> inline bool IsNull(const T& o) {return o.IsNullInstance();}
template<> inline bool  IsNull(const int& i)     { return i == INT_NULL; }
template<> inline bool  IsNull(const int64& i)   { return i == INT64_NULL; }
template<> inline bool  IsNull(const double& r)  { double d=r<0.0?-r:+r; return !(d < -DOUBLE_NULL); }
template<> inline bool  IsNull(const bool& r  )  { return false; }


NAMESPACE_UPP_END

#endif
