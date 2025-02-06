#ifndef _LittleCommon_Multiboot_h_
#define _LittleCommon_Multiboot_h_


EXTERN_C_BEGIN
	
void FindRamDisk(struct multiboot *mboot_ptr, size_t& initrd_location);
void EnableInterrupts();
void InitialisePaging();
void InitialiseTasking();
void InitialiseSyscalls();
void SwitchToUserMode();

EXTERN_C_END


#endif
