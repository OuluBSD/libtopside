#include <Core/Core.h>


NAMESPACE_UPP_BEGIN

void sSeed(uint64 *s) {
	RNG::sSeed(s);
}

RNG::RNG() {
	Seed();
}

float  RNG::Randomf() {
	uint64 s = Get64() >> 42;
	float f = (1.f / (UINT64_C(1) << 22));
	float r = s * f;
	return r;
}

double RNG::Randomd() {
	return (Get64() >> 11) * (1.  / (UINT64_C(1) << 53));
}

uint32 RNG::Random(uint32 max) {
	return Get32() % max;
}

uint64 RNG::Random64(uint64 max) {
	return Get64() % max;
}

uint32 RNG::Get32() {
	return (uint32)sNext(state);
}

uint64 RNG::Get64() {
	return (sNext(state) & 0xFFFFFFFF) | (sNext(state) << 32ULL);
}

void RNG::GetN(uint64* t, int n) {
	for (int i = 0; i < n; i++)
		t[i] = Get64();
}

void RNG::GetN(uint32* t, int n) {
	for (int i = 0; i < n; i++)
		t[i] = Get32();
}

RNG::operator uint32() {
	return Get32();
}

RNG::operator uint64() {
	return Get64();
}

void RNG::Seed() {
	sSeed(state);
}

void RNG::Seed(uint32 seed) {
	for (int i = 0; i < 4; i++)
		state[i] = 12345678 + seed + i; // xoshiro does not work well if all is zero
}

void RNG::WriteMemory(void* mem_, int bytes) {
	if (bytes <= 0)
		return;
	
	int blocks = bytes / 8;
	int mod = bytes % 8;
	
	byte* dst = (byte*)mem_;
	byte* block_end = dst + blocks * 8;
	while (dst != block_end) {
		*(uint64*)dst = Get64();
		dst += 8;
	}
	
	union {
		byte b[8];
		uint64 u64;
	};
	u64 = Get64();
	for(int i = 0; i < mod; i++)
		*dst++ = b[i];
	
	ASSERT(dst == (byte*)mem_ + bytes);
}


NAMESPACE_UPP_END
