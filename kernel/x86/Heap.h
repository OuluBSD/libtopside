#ifndef _LittleKernel_Heap_h_
#define _LittleKernel_Heap_h_




uint32 KMemoryAllocateAligned(uint32 sz);  // page aligned.
uint32 KMemoryAllocatePhysical(uint32 sz, uint32 *phys = 0); // returns a physical address.
uint32 KMemoryAllocateAlignedPhysical(uint32 sz, uint32 *phys = 0); // page aligned and returns a physical address.
uint32 KMemoryAllocate(uint32 sz); // vanilla (normal). 	

void KFree(void* addr);

	
	

#define KHEAP_START         0xC0000000
#define KHEAP_INITIAL_SIZE  0x100000

#define HEAP_INDEX_SIZE   0x20000
#define HEAP_MAGIC        0x123890AB
#define HEAP_MIN_SIZE     0x70000


/**
   Size information for a hole/block
**/
struct Header {
    uint32 magic;   // Magic number, used for error checking and identification.
    uint8 is_hole;   // 1 if this is a hole. 0 if this is a block.
    uint32 size;    // size of the block, including the end footer.
};

struct Footer {
    uint32 magic;     // Magic number, same as in header_t.
    Header *header; // Pointer to the block header.
};

class Heap {
	OrderedArray<Header> index;
    uint32 start_address; // The start of our allocated space.
    uint32 end_address;   // The end of our allocated space. May be expanded up to max_address.
    uint32 max_address;   // The maximum address the heap can be expanded to.
    uint8 supervisor;     // Should extra pages requested by us be mapped as supervisor-only?
    uint8 readonly;       // Should extra pages requested by us be mapped as read-only?
	
	int32 FindSmallestHole(uint32 size, uint8 page_align);
	void Expand(uint32 new_size);
	uint32 Contract(uint32 new_size);
	
public:
	// Create a new heap.
	Heap& Create(uint32 start, uint32 end, uint32 max, uint8 supervisor, uint8 readonly);
	
	// Allocates a contiguous region of memory 'size' in size. If page_align==1, it creates that block starting
	// on a page boundary.
	void *Allocate(uint32 size, uint8 page_align);
	
	void Free(void *p);
	
	
};



uint32 BaseKMemoryAllocate(uint32 sz, int align, uint32 *phys);






#endif
