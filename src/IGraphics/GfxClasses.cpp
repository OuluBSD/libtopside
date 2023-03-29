#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


GfxDataState::GfxDataState() {
	
}

String GfxInputState::GetSamplerString() const {
	switch (type) {
		case GVar::CUBEMAP_INPUT:	return "samplerCube";
		case GVar::VOLUME_INPUT:	return "sampler3D";
		default:					return "sampler2D";
	}
}


NAMESPACE_PARALLEL_END
