#include "Kernel.h"




uint32 EndlessKMemoryAllocateAligned(uint32 sz) {
	//MON.Write("EndlessKMemoryAllocateAligned: sz ").WriteDec(sz).Write(" placement_address ").WriteHex(global->placement_address).NewLine();
	
	if (global->placement_address & 0x00000FFF) { // If the address is not already page-aligned
		// Align it.
		global->placement_address &= 0xFFFFF000;
		global->placement_address += 0x1000;
		//MON.Write("EndlessKMemoryAllocateAligned: aligned to ").WriteHex(global->placement_address).NewLine();
	}
	uint32 tmp = global->placement_address;
	//MON.Write("EndlessKMemoryAllocateAligned: returning ").WriteHex(tmp).NewLine();
	global->placement_address += sz;
	return tmp;
}

uint32 EndlessKMemoryAllocatePhysical(uint32 sz, uint32 *phys) {
	if (phys) {
		*phys = global->placement_address;
	}
	uint32 tmp = global->placement_address;
	global->placement_address += sz;
	return tmp;
}

uint32 EndlessKMemoryAllocateAlignedPhysical(uint32 sz, uint32 *phys) {
	// If the address is not already page-aligned
	if (global->placement_address & 0x00000FFF) {
		// Align it.
		global->placement_address &= 0xFFFFF000;
		global->placement_address += 0x1000;
	}
	if (phys) {
		*phys = global->placement_address;
	}
	uint32 tmp = global->placement_address;
	global->placement_address += sz;
	return tmp;
}

uint32 EndlessKMemoryAllocate(uint32 sz) {
	//MON.Write("EndlessKMemoryAllocate: ").WriteDec(sz).NewLine();
	uint32 tmp = global->placement_address;
	global->placement_address += sz;
	return tmp;
}






// A bitset of frames - used or free.

// Macros used in the bitset algorithms.
#define INDEX_FROM_BIT(a) (a/(8*4))
#define OFFSET_FROM_BIT(a) (a%(8*4))

// Static function to set a bit in the frames bitset
static void SetFrame(uint32 frame_addr) {
	uint32 frame = frame_addr / 0x1000;
	uint32 idx = INDEX_FROM_BIT(frame);
	uint32 off = OFFSET_FROM_BIT(frame);
	global->frames[idx] |= (0x1 << off);
}

// Static function to clear a bit in the frames bitset
static void ClearFrame(uint32 frame_addr) {
	uint32 frame = frame_addr / 0x1000;
	uint32 idx = INDEX_FROM_BIT(frame);
	uint32 off = OFFSET_FROM_BIT(frame);
	global->frames[idx] &= ~(0x1 << off);
}

// Static function to test if a bit is set.
static uint32 TestFrame(uint32 frame_addr) {
	uint32 frame = frame_addr / 0x1000;
	uint32 idx = INDEX_FROM_BIT(frame);
	uint32 off = OFFSET_FROM_BIT(frame);
	return (global->frames[idx] & (0x1 << off));
}

// Static function to find the first free frame.
uint32 FirstFrame() {
	uint32 i, j, c;
	c = INDEX_FROM_BIT(global->nframes);
	//KDUMPI(nframes);
	//KDUMPI(c);
	
	for (i = 0; i < c; i++) {
		if (global->frames[i] != 0xFFFFFFFF) { // nothing free, exit early.
			// at least one bit is free here.
			for (j = 0; j < 32; j++) {
				uint32 toTest = 0x1 << j;
				if (!(global->frames[i]&toTest)) {
					return i*4*8 + j;
				}
			}
		}
	}
	if (!c) {
		PANIC("FirstFrame could not find the first free frame");
	}
	else {
		PANIC("No free memory left!");
	}
	
	return 0;
}







// Function to allocate a frame.
void AllocFrame(Page *page, int is_kernel, int is_writeable) {
	#if 0
	MON.Write("AllocFrame: page=").WriteHex(page)
		.Write(", is_kernel=").WriteDec(is_kernel)
		.Write(", is_writeable=").WriteDec(is_writeable)
		.NewLine();
	#endif
	
	if (page->frame != 0) {
		return; // Frame was already allocated, return straight away.
	}
	else {
		uint32 idx = FirstFrame(); // idx is now the index of the first free frame.
		if (idx == (uint32) - 1) {
			// PANIC is just a macro that prints a message to the screen then hits an infinite loop.
			PANIC("No free frames!");
		}
		
		SetFrame(idx*0x1000); // this frame is now ours!
		
		page->present = 1; // Mark it as present.
		page->rw = (is_writeable) ? 1 : 0; // Should the page be writeable?
		page->user = (is_kernel) ? 0 : 1; // Should the page be user-mode?
		page->frame = idx;
	}
}

// Function to deallocate a frame.
void FreeFrame(Page *page) {
	uint32 frame;
	if (!(frame = page->frame)) {
		return; // The given page didn't actually have an allocated frame!
	}
	else {
		ClearFrame(frame); // Frame is now free again.
		page->frame = 0x0; // Page now doesn't have a frame.
	}
}







void InitialisePaging() {
	
	// Add space to avoid weird kernel memset problems...
	EndlessKMemoryAllocateAligned(0x100);
	
	
	// Let's make a page directory.
	global->kernel_directory = (PageDirectory*)EndlessKMemoryAllocateAligned(sizeof(PageDirectory));
	memset(global->kernel_directory, 0, sizeof(PageDirectory));
	global->current_directory = global->kernel_directory;
	
	
	// Make page frames
	uint32 mem_end_page = MEMORY_LIMIT * 1024 * 1024;
	global->nframes = mem_end_page / 0x1000;
	int frames_sz = INDEX_FROM_BIT(global->nframes) * sizeof(uint32);
	global->frames = (uint32*)EndlessKMemoryAllocate(frames_sz);
	memset((uint8*)global->frames, 0, frames_sz);
	
	
	// Map some pages in the kernel heap area.
	// Here we call get_page but not AllocFrame. This causes page_table_t's
	// to be created where necessary. We can't allocate frames yet because they
	// they need to be identity mapped first below, and yet we can't increase
	// placement_address between identity mapping and enabling the heap!
	MON.Write("..Mapping pages").NewLine();
	int i = 0;
	for (i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
		GetPage(i, 1, global->kernel_directory, true);
		
		
		
	// We need to identity map (phys addr = virt addr) from
	// 0x0 to the end of used memory, so we can access this
	// transparently, as if paging wasn't enabled.
	// NOTE that we use a while loop here deliberately.
	// inside the loop body we actually change placement_address
	// by calling KMemoryAllocate(). A while loop causes this to be
	// computed on-the-fly rather than once at the start.
	MON.Write("..Allocating kernel program pages").NewLine();
	i = 0;
	while (i < global->placement_address) {
		// Kernel code is readable but not writeable from userspace.
		AllocFrame(GetPage(i, 1, global->kernel_directory), 0, 0);
		i += 0x1000;
	}
	
	
	// Now allocate those pages we mapped earlier.
	MON.Write("..Allocating kernel heap pages").NewLine();
	for (i = KHEAP_START; i < KHEAP_START + KHEAP_INITIAL_SIZE; i += 0x1000)
		AllocFrame(GetPage(i, 1, global->kernel_directory), 0, 0);
		
		
	
	// Before we enable paging, we must register our page fault handler.
	MON.Write("..Registering interrupt handlers").NewLine();
	RegisterInterruptHandler(14, PageFault);
	
	// Now, enable paging!
	MON.Write("..Switching page directory").NewLine();
	SwitchPageDirectory(global->kernel_directory);
	
	// Initialise the kernel heap.
	MON.Write("..Initializing kernel heap").NewLine();
	global->kheap.Create(KHEAP_START, KHEAP_START + KHEAP_INITIAL_SIZE, 0xCFFFF000, 0, 0);
	
}

void SwitchPageDirectory(PageDirectory *dir) {
	ASSERT(dir != 0);
	global->current_directory = dir;
	//MON.Write("...SwitchPageDirectory: 0 ").WriteHex(&dir->tables_physical).NewLine();
	asm volatile("mov %0, %%cr3":: "r"(&dir->tables_physical));
	uint32 cr0 = 0;
	//MON.Write("...SwitchPageDirectory: 1\n");
	asm volatile("mov %%cr0, %0": "=r"(cr0));
	cr0 |= 0x80000000; // Enable paging!
	//MON.Write("...SwitchPageDirectory: 2, ").WriteHex(cr0).NewLine();
	asm volatile("mov %0, %%cr0":: "r"(cr0));
}

Page *GetPage(uint32 address, bool make, PageDirectory *dir, bool zero) {
	// Turn the address into an index.
	address /= 0x1000;
	// Find the page table containing this address.
	uint32 table_idx = address / 1024;
	ASSERT(table_idx < 1024);
	
	//KDUMPH(dir);
	//KDUMPH(address);
	//KDUMPI(table_idx);
	
	if (dir->tables[table_idx]) {
		// If this table is already assigned
		////MON.Write("  table already assigned: ").WriteDec(address).Write(" ").WriteDec(table_idx).NewLine();
		return &dir->tables[table_idx]->pages[address%1024];
	}
	else if (make) {
		////MON.Write("  assigning table: ").WriteDec(address).NewLine();
		uint32 tmp;
		dir->tables[table_idx] = (PageTable*)EndlessKMemoryAllocateAlignedPhysical(sizeof(PageTable), &tmp);
		if (zero)
			memset(dir->tables[table_idx], 0, 0x1000);
		dir->tables_physical[table_idx] = tmp | 0x7; // PRESENT, RW, US.
		return &dir->tables[table_idx]->pages[address%1024];
	}
	else {
		return 0;
	}
}




void PageFault(Registers regs) {
	// A page fault has occurred.
	// The faulting address is stored in the CR2 register.
	uint32 faulting_address;
	
	asm volatile("mov %%cr2, %0" : "=r"(faulting_address));

	// The error code gives us details of what happened.
	int present   = !(regs.err_code & 0x1); // Page not present
	int rw = regs.err_code & 0x2;           // Write operation?
	int us = regs.err_code & 0x4;           // Processor was in user-mode?
	int reserved = regs.err_code & 0x8;     // Overwritten CPU-reserved bits of page entry?
	int id = regs.err_code & 0x10;          // Caused by an instruction fetch?
	
	// Output an error message.
	MON.Write("Page fault! ( ");
	if (present) {
		MON.Write("present ");
	}
	if (rw) {
		MON.Write("read-only ");
	}
	if (us) {
		MON.Write("user-mode ");
	}
	if (reserved) {
		MON.Write("reserved ");
	}
	MON.Write(") at 0x");
	MON.WriteHex(faulting_address);
	MON.Write("\n");
	PANIC("Page fault");
	
	while (1)
		;
}



extern "C" {
	void copy_page_physical(uint32 src, uint32 dst);
}

static PageTable *CloneTable(PageTable *src, uint32 *physAddr)
{
    // Make a new page table, which is page aligned.
    PageTable* table = (PageTable*)EndlessKMemoryAllocateAlignedPhysical(sizeof(PageTable), physAddr);
    
    // Ensure that the new table is blank.
    memset(table, 0, sizeof(PageDirectory));

    // For every entry in the table...
    int i;
    for (i = 0; i < 1024; i++)
    {
        // If the source entry has a frame associated with it...
        if (!src->pages[i].frame)
            continue;
        
        // Get a new frame.
        AllocFrame(&table->pages[i], 0, 0);
        
        // Clone the flags from source to destination.
        if (src->pages[i].present) table->pages[i].present = 1;
        if (src->pages[i].rw)      table->pages[i].rw = 1;
        if (src->pages[i].user)    table->pages[i].user = 1;
        if (src->pages[i].accessed)table->pages[i].accessed = 1;
        if (src->pages[i].dirty)   table->pages[i].dirty = 1;
        
        // Physically copy the data across. This function is in process.s.
        copy_page_physical(src->pages[i].frame*0x1000, table->pages[i].frame*0x1000);
    }
    return table;
}

