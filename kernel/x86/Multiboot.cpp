#include "Kernel.h"


void FindRamDisk(struct multiboot *mboot_ptr) {
	// Find the location of our initial ramdisk.
	uint32 initrd_location = 0;
	uint32 initrd_end = 0;
	if (mboot_ptr->mods_count > 0) {
		initrd_location = *((uint32*)mboot_ptr->mods_addr);
		initrd_end = *(uint32*)(mboot_ptr->mods_addr+4);
	}
	
	InitLinkerVariables(initrd_end);
}
