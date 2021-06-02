#include "Shadertoy.h"

NAMESPACE_TOPSIDE_BEGIN


INITBLOCK {
	ContextComponentBase::RegisterDefaultFileExt<AccelSpec>(".toy");
	ContextComponentBase::Register<AccelSpec, ShadertoyContextLoader>(".toy");
}


NAMESPACE_TOPSIDE_END
