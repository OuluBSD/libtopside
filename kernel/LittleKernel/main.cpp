#include "Kernel.h"


extern "C" {



int multiboot_main(struct multiboot *mboot_ptr) {
	
    ResetInterruptHandlers();
    
    // Descriptor table
    global->dt.Init();
    
    
    // All our initialisation calls will go in here.
    MON.Init();
	MON.Clear();
	
	
	InitLinkerVariables();
	
	
	MON.Write("Enabling interrupts\n");
	EnableInterrupts();
	
	MON.Write("Enabling paging\n");
	InitialisePaging();
	
	
	#if 1
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
