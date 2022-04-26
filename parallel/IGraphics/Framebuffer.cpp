#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
SoftFramebufferT<Gfx>::SoftFramebufferT() {
	sz = Size(0,0);
	for(int i = 0; i < TEXTYPE_COUNT; i++)
		color[i] = 0;
}

template <class Gfx>
void SoftFramebufferT<Gfx>::Clear() {
	sz = Size(0,0);
	
}

/*template <class Gfx>
void SoftFramebufferT<Gfx>::operator=(NativeTexture& tex) {
	ASSERT(!this->tex);
	this->tex = tex;
}*/

template <class Gfx>
void SoftFramebufferT<Gfx>::ClearData(GVar::BufferType type) {
	
}

template <class Gfx>
void SoftFramebufferT<Gfx>::ClearDataAll() {
	
}

template <class Gfx>
typename Gfx::NativeColorBufferRef SoftFramebufferT<Gfx>::GetFirst(GVar::RenderTarget tgt) {
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		if ((dword)tgt & (1 << i) && color[i])
			return color[i];
	}
	return NULL;
}

template <class Gfx>
void SoftFramebufferT<Gfx>::SetColor(TexType tgt, NativeColorBufferRef b) {
	ASSERT(b);
	ASSERT(tgt >= TEXTYPE_NONE && tgt < TEXTYPE_COUNT);
	color[tgt] = b;
}

template <class Gfx>
void SoftFramebufferT<Gfx>::SetSize(GVar::RenderTarget tgt, Size sz) {
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		if ((dword)tgt & (1 << i) && color[i])
			color[i]->Set(sz, 3);
	}
}

template <class Gfx>
void SoftFramebufferT<Gfx>::Zero(GVar::RenderTarget tgt) {
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		if ((dword)tgt & (1 << i) && color[i])
			color[i]->Zero();
	}
}

/*template <class Gfx>
void SoftFramebufferT<Gfx>::SetLocalData(Size sz, byte channels) {
	owned.Create();
	owned->Create(sz, channels);
	gtex = &*owned;
}*/

template <class Gfx>
void SoftFramebufferT<Gfx>::SetParam(GVar::TextureType type, GVar::Filter filter, GVar::Wrap wrap) {
	ASSERT(type >= 0 && type < GVar::TEXTYPE_COUNT);
	this->filter[type] = filter;
	this->wrap[type] = wrap;
}


SOFTREND_EXCPLICIT_INITIALIZE_CLASS(SoftFramebufferT)


NAMESPACE_PARALLEL_END