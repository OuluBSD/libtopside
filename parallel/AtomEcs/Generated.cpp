#include "AtomEcs.h"

namespace TS {

namespace Parallel {

#if defined flagSCREEN
AtomTypeCls EcsProgVideo::GetAtomType()
{
	return ATOM11(ECS_PROG_VIDEO, PIPE, CENTER, PROG, CENTER, ORDER, CENTER, PROG);
}

LinkTypeCls EcsProgVideo::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void EcsProgVideo::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<EcsVideoBase>(this);
}

AtomTypeCls EcsProgVideo::GetType() const
{
	return GetAtomType();
}

#endif
}

}

