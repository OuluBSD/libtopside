#ifndef _Emu_Stubs_h_
#define _Emu_Stubs_h_


#define TODO Panic("TODO");

struct multiboot {
	
};

struct DescriptorTable {
	
	void Init() {}
	void SetGate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran) {}
	void InterruptSetGate(uint8 num, uint32 base, uint16 sel, uint8 flags) {}
	void Flush() {}
	void InterruptFlush() {}
	void SetKernelStack(uint32 stack) {}
	
	void InitDescriptors() {}
	void InitInterruptGates() {}
	
	
};


inline void FindRamDisk(struct multiboot *mboot_ptr, size_t& initrd_location) {}
inline void EnableInterrupts() {}
inline void InitialisePaging() {}
inline void InitialiseTasking() {}
FsNode* InitialiseInitrd(size_t initrd_location);
inline void InitialiseSyscalls() {}
inline void SwitchToUserMode() {}

#endif
