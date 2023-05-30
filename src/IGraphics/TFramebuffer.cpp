#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


#ifdef flagSDL2
template <>
void FramebufferT<SdlCpuGfx>::DrawFill(const byte* mem, int sz, int mem_pitch) {
	SDL_Texture* tex = color_buf[0];
	ASSERT(tex);
	
	uint32 fmt = 0;
	int access, w = 0, h = 0;
	if (SDL_QueryTexture(tex, &fmt, &access, &w, &h) < 0 || w == 0 || h == 0)
		return;
	
	SDL_Surface* surf = 0;
	SDL_Rect r {0, 0, w, h};
	
	#ifdef flagMSC
	ASSERT_(0, "SDL_LockTextureToSurface not working");
	return;
	#else
	if (SDL_LockTextureToSurface(tex, &r, &surf) < 0 || !surf)
		return;
	#endif
	
	int stride = surf->format->BytesPerPixel;
	int surf_pitch = surf->pitch;
	byte* pixels = (byte*)surf->pixels;
	
	
	if (sz == h * surf_pitch) {
		memcpy(pixels, mem, sz);
	}
	else {
		byte* dst = pixels;
		int copy = min(mem_pitch, surf_pitch);
		for (int y = 0; y < h; y++) {
			memcpy(dst, mem, copy);
			mem += mem_pitch;
			dst += surf_pitch;
		}
	}
	
	SDL_UnlockTexture(tex);
}


#endif

#if defined flagPOSIXDESKTOP && defined flagOGL
template <>
void FramebufferT<X11OglGfx>::DrawFill(const byte* mem, int sz, int pitch) {
	Panic("Not implemented");
}
#endif

template <class Gfx>
void FramebufferT<Gfx>::DrawFill(const byte* mem, int sz, int pitch) {
	Panic("Not implemented");
}

template <class Gfx>
typename Gfx::NativeFrameBufferConstRef FramebufferT<Gfx>::GetReadFramebuffer() const {return frame_buf[this->buf_i];}

template <class Gfx>
typename Gfx::NativeColorBufferRef FramebufferT<Gfx>::GetActiveColorBuffer() {return color_buf[this->buf_i];}

template <class Gfx>
void FramebufferT<Gfx>::Init(NativeColorBufferRef clr, int w, int h, int stride) {
	//Gfx::GenTexture(color_buf[0]);
	ASSERT(!color_buf[0]);
	ASSERT(!frame_buf[0]);
	ASSERT(clr);
	Gfx::ClearFramebufferRef(frame_buf[0]);
	color_buf[0] = clr;
	this->size.cx = w;
	this->size.cy = h;
	this->channels = stride;
}

template <class Gfx>
void FramebufferT<Gfx>::Init(NativeFrameBufferRef fbo, NativeColorBufferRef clr, int w, int h, int stride) {
	//Gfx::GenTexture(color_buf[0]);
	ASSERT(!color_buf[0]);
	ASSERT(!frame_buf[0]);
	ASSERT(fbo);
	ASSERT(clr);
	frame_buf[0] = fbo;
	color_buf[0] = clr;
	this->size.cx = w;
	this->size.cy = h;
	this->channels = stride;
}

template <class Gfx>
void FramebufferT<Gfx>::SetWindowFbo(bool b) {
	this->is_win_fbo = b;
	if (b) {
		ASSERT(frame_buf[0]);
		Gfx::SetContextDefaultFramebuffer(frame_buf[0]);
	}
}


GFX3D_EXCPLICIT_INITIALIZE_CLASS(InputStateT)
GFX_EXCPLICIT_INITIALIZE_CLASS(FramebufferT)
GFXVIDEO_EXCPLICIT_INITIALIZE_CLASS(FramebufferT)


NAMESPACE_PARALLEL_END
