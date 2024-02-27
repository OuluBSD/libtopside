#ifndef _Emu_Stubs_h_
#define _Emu_Stubs_h_


#define TODO Panic("TODO");


struct FsNode;


struct multiboot {
	
};



inline void FindRamDisk(struct multiboot *mboot_ptr, size_t& initrd_location) {}
inline void EnableInterrupts() {}
inline void InitialisePaging() {}
inline void InitialiseTasking() {}
FsNode* InitialiseInitrd(size_t initrd_location);
inline void InitialiseSyscalls() {}
inline void SwitchToUserMode() {}

#endif
