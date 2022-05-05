#include "IGraphics.h"

NAMESPACE_PARALLEL_BEGIN


String GfxInputState::GetSamplerString() const {
	switch (type) {
		case GVar::VOLUME_INPUT:	return "sampler3D";
		default:					return "sampler2D";
	}
}


NAMESPACE_PARALLEL_END
