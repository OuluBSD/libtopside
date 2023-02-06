#ifndef _Statistics_Random_h_
#define _Statistics_Random_h_

NAMESPACE_TOPSIDE_BEGIN


class RandomNumberGenerator : Moveable<RandomNumberGenerator> {
	uint64 state[4];
	
	uint64 s_rotl(const uint64 x, int k) {
		return (x << k) | (x >> (64 - k)); // GCC/CLANG/MSC happily optimize this
	}
	
	uint64 sNext(uint64 *s) {
		const uint64 result_starstar = s_rotl(s[1] * 5, 7) * 9;
		const uint64 t = s[1] << 17;
	
		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];
	
		s[2] ^= t;
	
		s[3] = s_rotl(s[3], 45);
	
		return result_starstar;
	}
	
public:
	
	static void sSeed(uint64 *s) {
		for(int pass = 0; pass < 4; pass++) {
			for(int i = 0; i < 4; i++) {
				int64 a;
				int64 b;
				int64 c;
				GetSysSeedValues(&a, &b, &c);
				CombineHash h;
				h.Put((uint32)(a >> 32ULL));
				h.Put((uint32)a);
				h.Put((uint32)(b >> 32ULL));
				h.Put((uint32)b);
				h.Put((uint32)(c >> 32ULL));
				h.Put((uint32)c);
				s[i] ^= h;
			}
		}
	}
	
	RandomNumberGenerator() {Seed();}
	float  Randomf() {return (sNext(state) >> 11) * (1.f / (UINT64_C(1) << 53));}
	double Randomd() {return (sNext(state) >> 11) * (1.  / (UINT64_C(1) << 53));}
	uint64 Random(uint64 max) {return Get() % max;}
	uint64 Get() {return sNext(state);}
	void GetN(uint64* t, int n) {for(int i = 0; i < n; i++) t[i] = sNext(state);}
	operator uint64 () {return Get();}
	void Seed() {sSeed(state);}
	void Seed(uint32 seed) {
		for(int i = 0; i < 4; i++)
			state[i] = 12345678 + seed + i; // xoshiro does not work well if all is zero
	}
	
	
	Vector<int> Permutation(int num);
	
	//static RandomNumberGenerator& Local() {static thread_local RandomNumberGenerator r; return r;}
};




NAMESPACE_TOPSIDE_END

#endif
