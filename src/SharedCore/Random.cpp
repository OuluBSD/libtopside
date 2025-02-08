#include <Core/Core.h>
#if !defined IS_UPP_CORE && !defined IS_TS_CORE
	#include <Local/Local.h>
#endif


NAMESPACE_UPP_BEGIN

#if IS_TS_CORE
void sSeed(uint64 *s) {
	RNG::sSeed(s);
}
#else
// NOTE: duplicate code from U++, BUT this must be duplicate
//       reason: CoCreateGuid seems to require never_inline static qualifiers
//               and without them it overwrites stack variables
never_inline
static void sSeed(uint64 *s)
{
#ifdef PLATFORM_POSIX
	int fd = open("/dev/urandom", O_RDONLY);
	if(fd != -1) {
		IGNORE_RESULT(
			read(fd, s, 4 * sizeof(uint64))
		);
		close(fd);
	}
#else
	for(int pass = 0; pass < 4; pass++) {
		for(int i = 0; i < 4; i++) {
			CombineHash h[2];
			for(int j = 0; j < 2; j++) {
				h[j] << GetSysTime().Get() << usecs() << msecs() << j << pass << i;
				for(int p = 0; p < 2; p++) {
					Uuid uuid;
					CoCreateGuid((GUID *)&uuid); // GUID is basically a random number...
					h[j] << uuid.v[0] << uuid.v[1];
				}
			}
			s[i] ^= MAKEQWORD(h[0], h[1]);
		}
	}
#endif
}
#endif

void GetSysSeedValues(int64* a, int64* b, int64* c) {
	if(a) sSeed((uint64*)a);
	if(b) sSeed((uint64*)b);
	if(c) sSeed((uint64*)c);
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


RNG& RNG::Local() {
	static thread_local RNG r;
	return r;
}


NAMESPACE_UPP_END
