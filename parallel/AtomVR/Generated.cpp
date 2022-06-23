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
#if defined flagLOCALHMD
AtomTypeCls LocalHMDPipe::GetAtomType()
{
	return ATOM11(LOCAL_H_M_D_PIPE, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, EVENT);
}

LinkTypeCls LocalHMDPipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void LocalHMDPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<LocalHMDSinkDevice>(this);
}

AtomTypeCls LocalHMDPipe::GetType() const
{
	return GetAtomType();
}

#endif
AtomTypeCls BluetoothHoloPipe::GetAtomType()
{
	return ATOM11(BLUETOOTH_HOLO_PIPE, PIPE, CENTER, EVENT, CENTER, ORDER, CENTER, EVENT);
}

LinkTypeCls BluetoothHoloPipe::GetLinkType()
{
	return LINKTYPE(PIPE, PROCESS);
}

void BluetoothHoloPipe::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<DevBluetoothSinkDevice>(this);
}

AtomTypeCls BluetoothHoloPipe::GetType() const
{
	return GetAtomType();
}

}

}

