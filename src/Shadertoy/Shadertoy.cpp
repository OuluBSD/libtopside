#include "Shadertoy.h"

NAMESPACE_TOPSIDE_BEGIN


INITBLOCK_(ShaderToy) {
	SerialLoaderFactory::Register<SerialShadertoyLoader>(".toy");
}


NAMESPACE_TOPSIDE_END
