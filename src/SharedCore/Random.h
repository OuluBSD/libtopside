#ifndef _SharedCore_Random_h_
#define _SharedCore_Random_h_


NAMESPACE_UPP

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
				h << a;
				h << b;
				h << c;
				uint64 v = h;
				uint64 v64 = v | (v << 32ULL);
				s[i] ^= v64;
			}
		}
	}
	
public:
	RNG();
	float  Randomf();
	double Randomd();
	uint32 Random(uint32 max);
	uint64 Random64(uint64 max);
	uint32 Get32();
	uint64 Get64();
	void GetN(uint64* t, int n);
	void GetN(uint32* t, int n);
	operator uint32 ();
	operator uint64 ();
	void Seed();
	void Seed(uint32 seed);
	
	void WriteMemory(void* mem, int bytes);
	
	static RNG& Local() {static thread_local RNG r; return r;}
};

END_UPP_NAMESPACE


#endif
