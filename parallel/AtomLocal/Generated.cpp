#include "AtomLocal.h"

namespace TS {

namespace Parallel {

#if defined flagVR
AtomTypeCls SpatialInteractionSA::GetAtomType()
{
	return ATOM11(SPATIAL_INTERACTION_S_A, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, RECEIPT);
}

LinkTypeCls SpatialInteractionSA::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void SpatialInteractionSA::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<SpatialInteractionAtom>(this);
}

AtomTypeCls SpatialInteractionSA::GetType() const
{
	return GetAtomType();
}

#endif
}

}

