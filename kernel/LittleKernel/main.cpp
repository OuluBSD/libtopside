#include "LittleKernel.h"


EXTERN_C_BEGIN


void WriteMonitor(const char* s, int n, void* arg) {
	struct multiboot* mboot_ptr = (struct multiboot*)arg;
	MON.WriteN(s,n);
}

int multiboot_main(struct multiboot *mboot_ptr) {
	
    ResetInterruptHandlers();
    
    // Descriptor table
    global->dt.Init();
    
    
    // All our initialisation calls will go in here.
    if (mboot_ptr) mboot_ptr->OnMonitorCreate();
    Screen& scr = global->monitor;
    scr.Clear();
	KCout().SetCallback(WriteMonitor, mboot_ptr);
	
	
	size_t initrd_location = 0;
	FindRamDisk(mboot_ptr, initrd_location);
	
	KLOG("Enabling interrupts");
	EnableInterrupts();
	
	KLOG("Enabling paging");
	InitialisePaging();
	
	KLOG("Initialising tasking");
	InitialiseTasking();
	
	KLOG("Initialising initrd");
	fs_root = InitialiseInitrd(initrd_location);
	
	KLOG("Initialising syscalls");
	InitialiseSyscalls();
	
	// Virtual device drivers
	global->input.Init();
	
	// Device drivers
	
	
	
	SwitchToUserMode();
	
	
	
	syscall_MonitorWrite("Hello, user world!\n");
	
	#if 0
	size_t a = KMemoryAllocate(4);
    size_t b = KMemoryAllocate(8);
    size_t c = KMemoryAllocate(8);
    MON.Write("a: ");
    MON.WriteHex(a);
    MON.Write(", b: ");
    MON.WriteHex(b);
    MON.Write("\nc: ");
    MON.WriteHex(c);

    KFree((void*)c);
    KFree((void*)b);
    size_t d = KMemoryAllocate(12);
    MON.Write(", d: ");
    MON.WriteHex(d).NewLine();
    
    
    a = KMemoryAllocate(1024*1024);
    MON.Write("\nhuge a: ");
    MON.WriteHex(a);
    MON.Put('\n');
    
    global->timer.Init(1);
    #endif
    
    
    bool single_user = true;
    
    if (single_user) {
        Run_Shell(0, 0, mboot_ptr);
        
    }
    
	return 0xDEADABBA;
}

EXTERN_C_END
