#include "LittleLibrary.h"


ProgramBase::ProgramBase() {
	
	
}

bool ProgramBase::Init(int argc, const char** argv) {
	
	if (!args.Parse(argc,argv))
		return false;
	
	return true;
}

void ProgramBase::Run() {
	
	
}
