#include "Core.h"

NAMESPACE_UPP


#define ENDIAN_SWAP { while(count--) { EndianSwap(*v++); } }

void EndianSwap(word *v, size_t count) ENDIAN_SWAP
void EndianSwap(int16 *v, size_t count) ENDIAN_SWAP
void EndianSwap(dword *v, size_t count) ENDIAN_SWAP
void EndianSwap(int *v, size_t count) ENDIAN_SWAP
void EndianSwap(int64 *v, size_t count) ENDIAN_SWAP
void EndianSwap(uint64 *v, size_t count) ENDIAN_SWAP

void MemoryIgnoreLeaksBegin() {}
void MemoryIgnoreLeaksEnd() {}


END_UPP_NAMESPACE
