#ifndef _LittleCommon_Heap_h_
#define _LittleCommon_Heap_h_


#define KHEAP_START         0xC0000000
#define KHEAP_INITIAL_SIZE  0x100000

#define HEAP_INDEX_SIZE   0x20000
#define HEAP_MAGIC        0x123890AB
#define HEAP_MIN_SIZE     0x70000


/**
   Size information for a hole/block
**/
struct Header {
    size_t magic;   // Magic number, used for error checking and identification.
    uint8 is_hole;   // 1 if this is a hole. 0 if this is a block.
    size_t size;    // size of the block, including the end footer.
};

struct Footer {
    size_t magic;     // Magic number, same as in header_t.
    Header *header; // Pointer to the block header.
};

class Heap {
	OrderedArray<Header> index;
    size_t start_address; // The start of our allocated space.
    size_t end_address;   // The end of our allocated space. May be expanded up to max_address.
    size_t max_address;   // The maximum address the heap can be expanded to.
    uint8 supervisor;     // Should extra pages requested by us be mapped as supervisor-only?
    uint8 readonly;       // Should extra pages requested by us be mapped as read-only?
	
	int32 FindSmallestHole(size_t size, uint8 page_align);
	void Expand(size_t new_size);
	size_t Contract(size_t new_size);
	
public:
	// Create a new heap.
	Heap& Create(size_t start, size_t end, size_t max, uint8 supervisor, uint8 readonly);
	
	// Allocates a contiguous region of memory 'size' in size. If page_align==1, it creates that block starting
	// on a page boundary.
	void *Allocate(size_t size, uint8 page_align);
	
	void Free(void *p);
	
	
};



size_t BaseKMemoryAllocate(size_t sz, int align, size_t *phys);



size_t KMemoryAllocateAligned(size_t sz);  // page aligned.
size_t KMemoryAllocatePhysical(size_t sz, size_t *phys = 0); // returns a physical address.
size_t KMemoryAllocateAlignedPhysical(size_t sz, size_t *phys = 0); // page aligned and returns a physical address.
size_t KMemoryAllocate(size_t sz); // vanilla (normal). 	

void KFree(void* addr);






#endif
