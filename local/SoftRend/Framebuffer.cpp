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

void SoftFramebuffer::operator=(SDL_Texture* tex) {
	ASSERT(!this->tex);
	this->tex = tex;
}

void SoftFramebuffer::ClearData(GVar::BufferType type) {
	
}

void SoftFramebuffer::ClearDataAll() {
	
}

void SoftFramebuffer::SetParam(GVar::TextureType type, GVar::Filter filter, GVar::Wrap wrap) {
	ASSERT(type >= 0 && type < GVar::TEXTYPE_COUNT);
	this->filter[type] = filter;
	this->wrap[type] = wrap;
}


NAMESPACE_TOPSIDE_END
