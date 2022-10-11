#include "SoftRend.h"

NAMESPACE_TOPSIDE_BEGIN



SoftFramebuffer::SoftFramebuffer() {
	sz = Size(0,0);
	for(int i = 0; i < TEXTYPE_COUNT; i++)
		color[i] = 0;
}


void SoftFramebuffer::Clear() {
	sz = Size(0,0);
	
}



void SoftFramebuffer::ClearData(GVar::BufferType type) {
	if (type == GVar::COLOR_BUFFER) {
		for(int i = 0; i < TEXTYPE_COUNT; i++) {
			if (color[i])
				color[i]->Zero();
		}
	}
	else if (type == GVar::DEPTH_BUFFER) {
		// TODO don't pass, but pass for now
		//if (depth)
		//	depth->Zero();
	}
	else if (type == GVar::STENCIL_BUFFER) {
		// TODO don't pass, but pass for now
	}
	else {
		TODO
	}
}


void SoftFramebuffer::ClearDataAll() {
	
}


ByteImage* SoftFramebuffer::GetFirst(GVar::RenderTarget tgt) {
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		if ((dword)tgt & (1 << i) && color[i])
			return color[i];
	}
	return NULL;
}


void SoftFramebuffer::SetColor(TexType tgt, ByteImage* b) {
	ASSERT(b);
	ASSERT(tgt >= TEXTYPE_NONE && tgt < TEXTYPE_COUNT);
	color[tgt] = b;
}


void SoftFramebuffer::SetSize(GVar::RenderTarget tgt, Size sz) {
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		if ((dword)tgt & (1 << i) && color[i]) {
			if (color[i]->GetChannels() > 0)
				color[i]->Resize(sz);
			else
				color[i]->Set(sz, 3);
		}
	}
}


void SoftFramebuffer::Zero(GVar::RenderTarget tgt, RGBA clr) {
	for(int i = 0; i < TEXTYPE_COUNT; i++) {
		if ((dword)tgt & (1 << i) && color[i])
			color[i]->Zero(clr);
	}
}

void SoftFramebuffer::SetParam(GVar::TextureMode type, GVar::Filter filter, GVar::Wrap wrap) {
	ASSERT(type >= 0 && type < GVar::TEXMODE_COUNT);
	this->filter[type] = filter;
	this->wrap[type] = wrap;
}
 



NAMESPACE_TOPSIDE_END
