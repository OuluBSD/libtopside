#ifndef _Core_Heap_h_
#define _Core_Heap_h_

NAMESPACE_UPP_BEGIN


inline void  *MemoryAlloc(size_t size)     { return new byte[size]; }
inline void  *MemoryAllocSz(size_t &size)  { return new byte[size]; }
inline void   MemoryFree(void *p)          { delete[] (byte *) p; }
inline void  *MemoryAlloc32()              { return new byte[32]; }
inline void  *MemoryAlloc48()              { return new byte[48]; }
inline void   MemoryFree32(void *ptr)      { delete[] (byte *)ptr; }
inline void   MemoryFree48(void *ptr)      { delete[] (byte *)ptr; }

void MemoryIgnoreLeaksBegin();
void MemoryIgnoreLeaksEnd();

NAMESPACE_UPP_END

#endif
