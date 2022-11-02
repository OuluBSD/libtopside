#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN



template <class Gfx>
void TextureT<Gfx>::Clear() {
	if (tex) {
		Gfx::DeleteTexture(tex);
	}
}

template <class Gfx>
void TextureT<Gfx>::Load(const ByteImage& img) {
	Clear();
	
	Gfx::GenTexture(tex);
	ASSERT(tex);
	
	Gfx::ActiveTexture(CHANNEL_NONE);
	Gfx::BindTextureRW(GVar::TEXMODE_2D, tex);
	//not here, requires framebuffer: Gfx::TexParameteri(GVar::TEXMODE_2D, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
	Gfx::TexImage2D(const_cast<ByteImage&>(img));
	Gfx::GenerateMipmap(GVar::TEXMODE_2D);
	Gfx::UnbindTexture(GVar::TEXMODE_2D);
	Gfx::DeactivateTexture();
}

template <class Gfx>
void TextureT<Gfx>::Load(const FloatImage& img) {
	Clear();
	
	Gfx::GenTexture(tex);
	ASSERT(tex);
	
	Gfx::ActiveTexture(CHANNEL_NONE);
	Gfx::BindTextureRW(GVar::TEXMODE_2D, tex);
	//not here, requires framebuffer: Gfx::TexParameteri(GVar::TEXMODE_2D, GVar::FILTER_LINEAR, GVar::WRAP_REPEAT);
	Gfx::TexImage2D(const_cast<FloatImage&>(img));
	Gfx::GenerateMipmap(GVar::TEXMODE_2D);
	Gfx::UnbindTexture(GVar::TEXMODE_2D);
	Gfx::DeactivateTexture();
}



GFX3D_EXCPLICIT_INITIALIZE_CLASS(TextureT)
GFX3D_EXCPLICIT_INITIALIZE_CLASS(StateDrawT)
//GFX3D_EXCPLICIT_INITIALIZE_CLASS(BinderIfaceT)


NAMESPACE_PARALLEL_END
