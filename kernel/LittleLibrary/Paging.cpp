#include "LittleLibrary.h"


size_t EndlessKMemoryAllocateAligned(size_t sz) {
	//MON.Write("EndlessKMemoryAllocateAligned: sz ").WriteDec(sz).Write(" placement_address ").WriteHex(global->placement_address).NewLine();
	
	if (global->placement_address & 0x00000FFF) { // If the address is not already page-aligned
		// Align it.
		global->placement_address &= ~0x00000FFF;
		global->placement_address += 0x1000;
		//MON.Write("EndlessKMemoryAllocateAligned: aligned to ").WriteHex(global->placement_address).NewLine();
	}
	size_t tmp = global->placement_address;
	//MON.Write("EndlessKMemoryAllocateAligned: returning ").WriteHex(tmp).NewLine();
	global->placement_address += sz;
	return tmp;
}

size_t EndlessKMemoryAllocatePhysical(size_t sz, size_t *phys) {
	if (phys) {
		*phys = global->placement_address;
	}
	size_t tmp = global->placement_address;
	global->placement_address += sz;
	return tmp;
}

size_t EndlessKMemoryAllocateAlignedPhysical(size_t sz, size_t *phys) {
	// If the address is not already page-aligned
	if (global->placement_address & 0x00000FFF) {
		// Align it.
		global->placement_address &= ~0x00000FFF;
		global->placement_address += 0x1000;
	}
	if (phys) {
		*phys = global->placement_address;
	}
	size_t tmp = global->placement_address;
	global->placement_address += sz;
	return tmp;
}

size_t EndlessKMemoryAllocate(size_t sz) {
	//MON.Write("EndlessKMemoryAllocate: ").WriteDec(sz).NewLine();
	size_t tmp = global->placement_address;
	global->placement_address += sz;
	return tmp;
}



