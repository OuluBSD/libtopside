#ifndef _LittleCommon_InputDevice_h_
#define _LittleCommon_InputDevice_h_


struct InputDevice {
	
	// Runtime params
	bool (*input_fn)(dword, int, void*) = 0;
	void* input_arg = 0;
	
	void Init();
	void InterruptCallback(struct Registers regs);
};


#endif
