#ifndef _CoreAlt_Algo_h_
#define _CoreAlt_Algo_h_

#include <algorithm>

NAMESPACE_UPP_BEGIN

#undef min
#undef max
template <class T> const T& min(const T& a, const T& b) { return a < b ? a : b; }
template <class T> const T& max(const T& a, const T& b) { return a > b ? a : b; }



inline dword Random() {return (dword)RNG::Local().Random(UINT32_MAX);}
inline void Random64(uint64* t, int n) {return RNG::Local().GetN(t, n);}
inline dword Random(dword n) {return (dword)RNG::Local().Random(n);}
inline uint64 Random64() {return RNG::Local().Get64();}
inline uint64 Random64(uint64 n) {return RNG::Local().Random64(n);}
inline double Randomf() {return RNG::Local().Randomf();}
inline void SeedRandom() {return RNG::Local().Seed();}
inline void SeedRandom(dword seed) {return RNG::Local().Seed(seed);}


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








class SpinLock {
    std::atomic_flag locked = ATOMIC_FLAG_INIT;
public:
    void Enter() {
        while (locked.test_and_set(std::memory_order_acquire)) { ; }
    }
    void Leave() {
        locked.clear(std::memory_order_release);
    }
    bool TryEnter() {
        return !locked.test_and_set(std::memory_order_acquire);
    }
};


using AtomicBool = std::atomic<bool>;
using AtomicInt = std::atomic<int>;
using Atomic = AtomicInt;


inline int AtomicInc(AtomicInt& a) {return ++a;}
inline int AtomicDec(AtomicInt& a) {return --a;}


struct FakeAtomicInt : Moveable<FakeAtomicInt> {
	SpinLock lock;
	int value;
	FakeAtomicInt() : value(0) {}
	FakeAtomicInt(int i) : value(i) {}
	FakeAtomicInt(const AtomicInt& ai) : value(ai) {}
	operator int() {return value;}
	int operator = (int i) {
		lock.Enter();
		value = i;
		lock.Leave();
		return i;
	}
	int operator++(int) {
		lock.Enter();
		int i = value++;
		lock.Leave();
		return i;
	}
	int operator--(int) {
		lock.Enter();
		int i = value--;
		lock.Leave();
		return i;
	}
	int Get() const {return value;}
};


NAMESPACE_UPP_END

#endif
