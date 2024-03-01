#include "Emu.h"

	
void DescriptorTable::Init() {}
void DescriptorTable::SetGate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran) {}
void DescriptorTable::InterruptSetGate(uint8 num, uint32 base, uint16 sel, uint8 flags) {}
void DescriptorTable::Flush() {}
void DescriptorTable::InterruptFlush() {}
void DescriptorTable::SetKernelStack(uint32 stack) {}
void DescriptorTable::InitDescriptors() {}
void DescriptorTable::InitInterruptGates() {}

	

void InitialisePaging() {
	TRACE(InitialisePaging)
	
	// Add space to avoid weird kernel memset problems...
	//EndlessKMemoryAllocateAligned(0x100);
	
	size_t sz = 1024 * 1024 * 64;
	size_t start = EndlessKMemoryAllocateAligned(sz);
	
	// Initialise the kernel heap.
	MON.Write("..Initializing kernel heap").NewLine();
	global->kheap.Create(start, start + sz, -1, 0, 0);
	
}
