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


#if (defined flagFREEBSD && defined flagHACK) || (defined flagLINUX && defined flagHACK)
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


#if (defined flagUWP && defined flagDX12)
String HoloContextAtom::GetAction() {
	return "holo.context";
}

AtomTypeCls HoloContextAtom::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::HOLO_CONTEXT_ATOM;
	t.role = AtomRole::DRIVER;
	t.AddIn(VD(CENTER,RECEIPT),0);
	t.AddOut(VD(CENTER,RECEIPT),0);
	return t;
}

LinkTypeCls HoloContextAtom::GetLinkType() {
	return LINKTYPE(DRIVER, DRIVER);
}

void HoloContextAtom::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<HoloContextBase>(this);
}

AtomTypeCls HoloContextAtom::GetType() const {
	return GetAtomType();
}
#endif


#if (defined flagUWP && defined flagDX12)
String HoloEventAtomPipe::GetAction() {
	return "holo.event.pipe";
}

AtomTypeCls HoloEventAtomPipe::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::HOLO_EVENT_ATOM_PIPE;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(CENTER,ORDER),0);
	t.AddOut(VD(CENTER,EVENT),0);
	return t;
}

LinkTypeCls HoloEventAtomPipe::GetLinkType() {
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void HoloEventAtomPipe::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<HoloEventsBase>(this);
}

AtomTypeCls HoloEventAtomPipe::GetType() const {
	return GetAtomType();
}
#endif


#if (defined flagUWP && defined flagDX12 && defined flagDX12)
String HoloD12FboAtomSA::GetAction() {
	return "holo.fbo.standalone";
}

AtomTypeCls HoloD12FboAtomSA::GetAtomType() {
	AtomTypeCls t;
	t.sub = SubAtomCls::HOLO_D12_FBO_ATOM_SA;
	t.role = AtomRole::PIPE;
	t.AddIn(VD(DX,ORDER),0);
	t.AddOut(VD(DX,RECEIPT),0);
	return t;
}

LinkTypeCls HoloD12FboAtomSA::GetLinkType() {
	return LINKTYPE(POLLER_PIPE, PROCESS);
}

void HoloD12FboAtomSA::Visit(RuntimeVisitor& vis) {
	vis.VisitThis<HoloD12VideoSinkDevice>(this);
}

AtomTypeCls HoloD12FboAtomSA::GetType() const {
	return GetAtomType();
}
#endif


}

}

