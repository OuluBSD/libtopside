#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN


SoftFramebuffer::SoftFramebuffer() {
	
}

void SoftFramebuffer::Clear() {
	inited = false;
	
}

bool SoftFramebuffer::Create() {
	
	
	inited = true;
	return true;
}

void SoftFramebuffer::ClearData(GVar::BufferType type) {
	
}

void SoftFramebuffer::SetParam(int type, GVar::Filter filter, GVar::Wrap repeat) {
	
	TODO
	
}


NAMESPACE_TOPSIDE_END
