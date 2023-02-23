#ifndef _Core_Heap_h_
#define _Core_Heap_h_

NAMESPACE_UPP_BEGIN


inline void* MemoryAlloc(size_t size) {return malloc(size);}
inline void MemoryFree(void* ptr) {free(ptr);}


NAMESPACE_UPP_END

#endif
