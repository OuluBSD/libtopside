#ifndef _CoreAlt_Container_h_
#define _CoreAlt_Container_h_

NAMESPACE_UPP_BEGIN


template <class T>
class Pick {
	T* var = NULL;
public:
	Pick(T& var) : var(&var) {}
	Pick(Pick&& p) : var(p.var) {p.var = NULL;}
	Pick(const Pick& p) : var(p.var) {}
	T& Get() const {return *var;}
};

template <class T> Pick<T> PickFn(T& o) {return Pick<T>(o);}

// The file is included in Oulu and this is required to prevent regular U++ errors
#ifdef flagALTCORE
template <class T> Pick<T> pick(T& o) {return Pick<T>(o);}
#endif


NAMESPACE_UPP_END

#endif
