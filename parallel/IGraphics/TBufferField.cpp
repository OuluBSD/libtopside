#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
bool GfxBufferFieldT<Gfx>::Initialize(AtomBase& a, const Script::WorldState& ws) {
	if (!buf.Initialize(a, ws))
		return false;
	
	if (buf.mode == Buffer::MULTI_STEREO)
		data.is_stereo = true;
	
	buf.SetDataStateOverride(&data, true);
	return true;
}

template <class Gfx>
bool GfxBufferFieldT<Gfx>::ImageInitialize(bool is_win_fbo, Size screen_sz) {
	return buf.ImageInitialize(is_win_fbo, screen_sz);
}

template <class Gfx>
bool GfxBufferFieldT<Gfx>::PostInitialize() {
	return buf.PostInitialize();
}



GFX3D_EXCPLICIT_INITIALIZE_CLASS(GfxBufferFieldT)


NAMESPACE_PARALLEL_END
