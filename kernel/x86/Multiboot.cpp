#include "Kernel.h"


void FindRamDisk(struct multiboot *mboot_ptr, size_t& initrd_location) {
	// Find the location of our initial ramdisk.
	initrd_location = 0;
	size_t initrd_end = 0;
	if (mboot_ptr->mods_count > 0) {
		initrd_location = *((size_t*)mboot_ptr->mods_addr);
		initrd_end = *(size_t*)(mboot_ptr->mods_addr+4);
	}
	
	InitLinkerVariables(initrd_end);
}

