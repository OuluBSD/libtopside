#ifndef _CoreAlt_Algo_h_
#define _CoreAlt_Algo_h_

#include <algorithm>

NAMESPACE_UPP_BEGIN

template <class T>
inline int sgn(T a) { return a > 0 ? 1 : a < 0 ? -1 : 0; }

template <class I, class T>
I FindIf(I begin, I end, std::function<T> fn) {
	while (begin != end) {
		if (fn(*begin))
			return begin;
		begin++;
	}
	return end;
}


#ifndef flagSTDRTTI
template <class T, class S> T*			CastPtr(S* o) {
	if (!o) return 0;
	void* p = o ->GetBasePtr(AsTypeCls<T>());
	return (T*)p;
}

template <class T, class S> const T*	CastConstPtr(const S* o) {
	if (!o) return 0;
	void* p = o->GetBasePtr(AsTypeCls<T>());
	return (const T*)p;
}

template <class T, class S> T&			CastRef(S& o) {
	void* p = o.GetBasePtr(AsTypeCls<T>());
	if (!p) __BREAK__;
	return *(T*)p;
}

template <class T, class S> const T&	CastConstRef(const S& o) {
	void* p = o.GetBasePtr(AsTypeCls<T>());
	if (!p) __BREAK__;
	return *(const T*)p;
}

template <class T, class S> T&			CastRef(S* o) {
	if (!o) return 0;
	void* p = o->GetBasePtr(AsTypeCls<T>());
	if (!p) __BREAK__;
	return *(T*)p;
}

template <class T, class S> const T&	CastConstRef(const S* o) {
	if (!o) return 0;
	void* p = o->GetBasePtr(AsTypeCls<T>());
	if (!p) __BREAK__;
	return *(const T*)p;
}
#endif




NAMESPACE_UPP_END

#endif
