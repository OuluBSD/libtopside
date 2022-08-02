#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN



SoftPipeline::SoftPipeline() {
	
}


bool SoftPipeline::Create() {
	
	inited = true;
	return true;
}


void SoftPipeline::Clear() {
	
	inited = false;
}


void SoftPipeline::Begin() {
	for (Stage& s : stages)
		if (s.prog)
			s.prog->Begin();
}


void SoftPipeline::Use(SoftProgram& prog, uint32 bmask) {
	for (Stage& s : stages) {
		if (s.prog == &prog) {
			s.bmask |= bmask;
			return;
		}
	}
	Stage& s = stages.Add();
	s.prog = &prog;
	s.bmask = bmask;
	ASSERT(prog.pipeline == 0);
	prog.pipeline = this;
}




NAMESPACE_TOPSIDE_END
