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

void SoftPipeline::Use(SoftProgram& prog, uint32 bmask) {
	
}



NAMESPACE_TOPSIDE_END
