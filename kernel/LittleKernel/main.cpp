#include "Kernel.h"


extern "C" {



int multiboot_main(struct multiboot *mboot_ptr) {
	
    ResetInterruptHandlers();
    
    // Descriptor table
    global->dt.Init();
    
    
    // All our initialisation calls will go in here.
    MON.Init();
	MON.Clear();
	
	
	// Find the location of our initial ramdisk.
	uint32 initrd_location = 0;
	uint32 initrd_end = 0;
	if (mboot_ptr->mods_count > 0) {
		initrd_location = *((uint32*)mboot_ptr->mods_addr);
		initrd_end = *(uint32*)(mboot_ptr->mods_addr+4);
	}
	
	
	InitLinkerVariables(initrd_end);
	
	
	MON.Write("Enabling interrupts\n");
	EnableInterrupts();
	
	MON.Write("Enabling paging\n");
	InitialisePaging();
	
	MON.Write("Initialising tasking\n");
	InitialiseTasking();
	
	MON.Write("Initialising initrd\n");
	fs_root = InitialiseInitrd(initrd_location);
	
	MON.Write("Initialising syscalls\n");
	InitialiseSyscalls();

	SwitchToUserMode();
	
	syscall_MonitorWrite("Hello, user world!\n");
	
	#if 0
	uint32 a = KMemoryAllocate(4);
    uint32 b = KMemoryAllocate(8);
    uint32 c = KMemoryAllocate(8);
    MON.Write("a: ");
    MON.WriteHex(a);
    MON.Write(", b: ");
    MON.WriteHex(b);
    MON.Write("\nc: ");
    MON.WriteHex(c);

    KFree((void*)c);
    KFree((void*)b);
    uint32 d = KMemoryAllocate(12);
    MON.Write(", d: ");
    MON.WriteHex(d).NewLine();
    
    
    a = KMemoryAllocate(1024*1024);
    MON.Write("\nhuge a: ");
    MON.WriteHex(a);
    MON.Put('\n');
    
    global->timer.Init(1);
    #endif
    
	return 0xDEADABBA;
}

}
