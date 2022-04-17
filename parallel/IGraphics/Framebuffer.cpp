#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
SoftFramebufferT<Gfx>::SoftFramebufferT() {
	
}

template <class Gfx>
void SoftFramebufferT<Gfx>::Clear() {
	inited = false;
	
}

template <class Gfx>
bool SoftFramebufferT<Gfx>::Create() {
	
	
	inited = true;
	return true;
}

template <class Gfx>
void SoftFramebufferT<Gfx>::operator=(NativeTexture& tex) {
	ASSERT(!this->tex);
	this->tex = tex;
}

template <class Gfx>
void SoftFramebufferT<Gfx>::ClearData(GVar::BufferType type) {
	
}

template <class Gfx>
void SoftFramebufferT<Gfx>::ClearDataAll() {
	
}

template <class Gfx>
void SoftFramebufferT<Gfx>::SetParam(GVar::TextureType type, GVar::Filter filter, GVar::Wrap wrap) {
	ASSERT(type >= 0 && type < GVar::TEXTYPE_COUNT);
	this->filter[type] = filter;
	this->wrap[type] = wrap;
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftFramebufferT)


NAMESPACE_PARALLEL_END
