#ifndef _LittleKernel_Paging_h_
#define _LittleKernel_Paging_h_


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
Page *GetPage(uint32 address, bool make, PageDirectory *dir, bool zero=true);

/**
Handler for page faults.
**/
void PageFault(Registers regs);

/**
   Makes a copy of a page directory.
**/
PageDirectory* CloneDirectory(PageDirectory *src);



#endif
