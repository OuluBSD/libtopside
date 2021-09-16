#include "Core.h"


NAMESPACE_UPP_BEGIN


void RNG::WriteMemory(void* mem_, int bytes) {
	if (bytes <= 0)
		return;
	
	int blocks = bytes / 8;
	int mod = bytes % 8;
	
	byte* dst = (byte*)mem_;
	byte* block_end = dst + blocks * 8;
	while (dst != block_end) {
		*(uint64*)dst = Get();
		dst += 8;
	}
	
	union {
		byte b[8];
		uint64 u64;
	};
	u64 = Get();
	for(int i = 0; i < mod; i++)
		*dst++ = b[i];
	
	ASSERT(dst == (byte*)mem_ + bytes);
}


NAMESPACE_UPP_END
