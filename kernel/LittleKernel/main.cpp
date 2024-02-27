#include "LittleKernel.h"


EXTERN_C_BEGIN



int multiboot_main(struct multiboot *mboot_ptr) {
	
    ResetInterruptHandlers();
    
    // Descriptor table
    global->dt.Init();
    
    
    // All our initialisation calls will go in here.
    if (mboot_ptr) mboot_ptr->OnMonitorCreate();
    MON.Init();
	MON.Clear();
	
	
	size_t initrd_location = 0;
	FindRamDisk(mboot_ptr, initrd_location);
	
	
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

EXTERN_C_END
