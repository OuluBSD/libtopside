#ifndef _LittleCommon_Paging_h_
#define _LittleCommon_Paging_h_


size_t EndlessKMemoryAllocateAligned(size_t sz);
size_t EndlessKMemoryAllocatePhysical(size_t sz, size_t *phys);
size_t EndlessKMemoryAllocateAlignedPhysical(size_t sz, size_t *phys);
size_t EndlessKMemoryAllocate(size_t sz);


#endif
