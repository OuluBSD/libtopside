#ifndef _LittleCommon_Stubs_h_
#define _LittleCommon_Stubs_h_



struct DescriptorTable {
	
	void Init();
	void SetGate(int32 num, uint32 base, uint32 limit, uint8 access, uint8 gran);
	void InterruptSetGate(uint8 num, uint32 base, uint16 sel, uint8 flags);
	void Flush();
	void InterruptFlush();
	void SetKernelStack(uint32 stack);
	
	void InitDescriptors();
	void InitInterruptGates();
	
	
	
};




#endif
