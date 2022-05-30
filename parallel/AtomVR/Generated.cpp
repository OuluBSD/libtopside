#include "AtomVR.h"

namespace TS {

namespace Parallel {

#if defined flagVR && defined flagOGL
AtomTypeCls X11OglHoloFboProg::GetAtomType()
{
	return ATOM11(X11_OGL_HOLO_FBO_PROG, PIPE, OGL, FBO, OGL, ORDER, OGL, FBO);
}

LinkTypeCls X11OglHoloFboProg::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void X11OglHoloFboProg::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<X11OglHoloFboBase>(this);
}

AtomTypeCls X11OglHoloFboProg::GetType() const
{
	return GetAtomType();
}

#endif
}

}

