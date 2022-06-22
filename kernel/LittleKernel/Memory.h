#ifndef _LittleKernel_Memory_h_
#define _LittleKernel_Memory_h_

#include "Common.h"
#include "Heap.h"

//void  operator delete(void*);
void* operator new(unsigned int);

extern "C" {

	
}


struct Page	{
	uint32 present    : 1;   // Page present in memory
	uint32 rw         : 1;   // Read-only if clear, readwrite if set
	uint32 user       : 1;   // Supervisor level only if clear
	uint32 accessed   : 1;   // Has the page been accessed since last refresh?
	uint32 dirty      : 1;   // Has the page been written to since last refresh?
	uint32 unused     : 7;   // Amalgamation of unused and reserved bits
	uint32 frame      : 20;  // Frame address (shifted right 12 bits)
};

struct PageTable {
	Page pages[1024];
};

struct PageDirectory {
	/**
	Array of pointers to pagetables.
	**/
	PageTable *tables[1024];
	/**
	Array of pointers to the pagetables above, but gives their *physical*
	location, for loading into the CR3 register.
	**/
	size_t tables_physical[1024];
	/**
	The physical address of tables_physical. This comes into play
	when we get our kernel heap allocated and the directory
	may be in a different location in virtual memory.
	**/
	size_t physical_addr;
};

/**
Sets up the environment, page directories etc and
enables paging.
**/
void InitialisePaging();

/**
Causes the specified page directory to be loaded into the
CR3 register.
**/
void SwitchPageDirectory(PageDirectory*);

/**
Retrieves a pointer to the page required.
If make == 1, if the page-table in which this page should
reside isn't created, create it!
**/
Page *GetPage(uint32 address, bool make, PageDirectory *dir, bool zero);

/**
Handler for page faults.
**/
void PageFault(Registers regs);





static void SetFrame(uint32 frame_addr);
static void ClearFrame(uint32 frame_addr);
static uint32 TestFrame(uint32 frame_addr);
static uint32 FirstFrame();


void FreeFrame(Page *page);
void AllocFrame(Page *page, int is_kernel, int is_writeable);


void PageFault(Registers regs);




struct SVar {
	DescriptorTable dt;
	Monitor monitor;
	Timer timer;
	Heap kheap;
	
	uint32 *frames;
	uint32 nframes;
	PageDirectory* kernel_directory = 0;
	PageDirectory* current_directory = 0;
	uint32 placement_address;
	
	FixedArray<Callback1<int>, 1> cbtestarr;
	FixedArray<Callback1<Registers>, 256 > interrupt_handlers;
	
};
extern SVar* global;


void InitLinkerVariables();

#endif
