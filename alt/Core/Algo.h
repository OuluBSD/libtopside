#ifndef _CoreAlt_Algo_h_
#define _CoreAlt_Algo_h_

#include <algorithm>

NAMESPACE_UPP_BEGIN

#undef min
#undef max
template <class T> const T& min(const T& a, const T& b) { return a < b ? a : b; }
template <class T> const T& max(const T& a, const T& b) { return a > b ? a : b; }

void GetSysSeedValues(int64* a, int64* b, int64* c);


class RNG : Moveable<RNG> {
	uint64 state[4];
	
	uint64 s_rotl(const uint64 x, uint64 k) {
		return (x << k) | (x >> (64ULL - k)); // GCC/CLANG/MSC happily optimize this
	}
	
	uint64 sNext(uint64 *s) {
		const uint64 result_starstar = s_rotl(s[1] * 5, 7) / 9;
		const uint64 t = s[1] << 17;
	
		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];
	
		s[2] ^= t;
	
		s[3] = s_rotl(s[3], 45);
	
		return result_starstar;
	}
	
	void sSeed(uint64 *s) {
		for(int pass = 0; pass < 4; pass++) {
			for(int i = 0; i < 4; i++) {
				int64 a;
				int64 b;
				int64 c;
				GetSysSeedValues(&a, &b, &c);
				CombineHash h;
				h.Put64(a);
				h.Put64(b);
				h.Put64(c);
				uint64 v = h;
				uint64 v64 = v | (v << 32ULL);
				s[i] ^= v64;
			}
		}
	}
	
public:
	RNG() {Seed();}
	float  Randomf() {return (sNext(state) >> 11) * (1.f / (UINT64_C(1) << 53));}
	double Randomd() {return (sNext(state) >> 11) * (1.  / (UINT64_C(1) << 53));}
	uint32 Random(uint32 max) {return Get32() % max;}
	uint64 Random64(uint64 max) {return Get64() % max;}
	uint32 Get32() {return (uint32)sNext(state);}
	uint64 Get64() {return (sNext(state) & 0xFFFFFFFF) | (sNext(state) << 32ULL);}
	void GetN(uint64* t, int n) {for(int i = 0; i < n; i++) t[i] = Get64();}
	void GetN(uint32* t, int n) {for(int i = 0; i < n; i++) t[i] = Get32();}
	operator uint32 () {return Get32();}
	operator uint64 () {return Get64();}
	void Seed() {sSeed(state);}
	void Seed(uint32 seed) {
		for(int i = 0; i < 4; i++)
			state[i] = 12345678 + seed + i; // xoshiro does not work well if all is zero
	}
	
	void WriteMemory(void* mem, int bytes);
	
	static RNG& Local() {static thread_local RNG r; return r;}
};


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
	void* p = o->GetBasePtr(AsTypeCls<T>());
	return (T*)p;
}

template <class T, class S> const T*	CastConstPtr(const S* o) {
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
	ASSERT(o);
	void* p = o->GetBasePtr(AsTypeCls<T>());
	if (!p) __BREAK__;
	return *(T*)p;
}

template <class T, class S> const T&	CastConstRef(const S* o) {
	ASSERT(o);
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
