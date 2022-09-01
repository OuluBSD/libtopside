#include "AtomVR.h"

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if (defined flagFREEBSD && defined flagOPENHMD) || (defined flagLINUX && defined flagOPENHMD)
String OpenHMDPipe::GetAction() {
	return "x11.ogl.ohmd.events";
}

AtomTypeCls OpenHMDPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::OPEN_HMDPIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,EVENT),0);
	return t;
}

LinkTypeCls OpenHMDPipe::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void OpenHMDPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<OpenHMDSinkDevice>(this);
}

AtomTypeCls OpenHMDPipe::GetType() const {
	return GetAtomType();
}
#endif


#if defined flagLOCALHMD
String LocalHMDPipe::GetAction() {
	return "x11.ogl.holo.events";
}

AtomTypeCls LocalHMDPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::LOCAL_HMDPIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,EVENT),0);
	return t;
}

LinkTypeCls LocalHMDPipe::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void LocalHMDPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<LocalHMDSinkDevice>(this);
}

AtomTypeCls LocalHMDPipe::GetType() const {
	return GetAtomType();
}
#endif


#if (defined flagFREEBSD) || (defined flagLINUX)
String RemoteVRServerPipe::GetAction() {
	return "tcp.ogl.holo.events";
}

AtomTypeCls RemoteVRServerPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::REMOTE_VRSERVER_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,EVENT),0);
	return t;
}

LinkTypeCls RemoteVRServerPipe::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void RemoteVRServerPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<RemoteVRServerSinkDevice>(this);
}

AtomTypeCls RemoteVRServerPipe::GetType() const {
	return GetAtomType();
}
#endif


#if (defined flagFREEBSD) || (defined flagLINUX)
String BluetoothHoloPipe::GetAction() {
	return "bluetooth.holo.events";
}

AtomTypeCls BluetoothHoloPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::BLUETOOTH_HOLO_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,EVENT),0);
	return t;
}

LinkTypeCls BluetoothHoloPipe::GetLinkType() {
	return LINKTYPE(PIPE, PROCESS);
}

void BluetoothHoloPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<DevBluetoothSinkDevice>(this);
}

AtomTypeCls BluetoothHoloPipe::GetType() const {
	return GetAtomType();
}
#endif


}

}

