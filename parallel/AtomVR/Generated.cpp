#include "AtomVR.h"

namespace TS {

namespace Parallel {

#if defined flagOPENHMD
AtomTypeCls OpenHMDPipe::GetAtomType()
{
	return ATOM11(OPEN_H_M_D_PIPE, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, EVENT);
}

LinkTypeCls OpenHMDPipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void OpenHMDPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<OpenHMDSinkDevice>(this);
}

AtomTypeCls OpenHMDPipe::GetType() const
{
	return GetAtomType();
}

#endif
}

}

