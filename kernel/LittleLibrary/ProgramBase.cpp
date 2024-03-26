#include "LittleLibrary.h"


bool ProgramBase_InputDevice(dword chr, int count, void* arg) {
	if (!arg)
		return false;
	ProgramBase* rb = (ProgramBase*)arg;
	rb->Key(chr, count);
	return true;
}

ProgramBase::ProgramBase() {
	
	
}

ProgramBase::~ProgramBase() {
	
	if (global->input.input_arg == this)
		global->input.input_arg = 0;
	
}

bool ProgramBase::Init(int argc, const char** argv) {
	
	// Override input receiver
	global->input.input_fn = &ProgramBase_InputDevice;
	global->input.input_arg = this;
		
	if (!args.Parse(argc,argv))
		return false;
	
	return true;
}

void ProgramBase::Run() {
	
	
}
