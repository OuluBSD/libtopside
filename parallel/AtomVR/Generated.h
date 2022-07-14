#ifndef _AtomVR_Generated_h_
#define _AtomVR_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if defined flagOPENHMD
class OpenHMDPipe : public OpenHMDSinkDevice {

public:
	RTTI_DECL1(OpenHMDPipe, OpenHMDSinkDevice)
	COPY_PANIC(OpenHMDPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.ogl.ohmd.events")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagLOCALHMD
class LocalHMDPipe : public LocalHMDSinkDevice {

public:
	RTTI_DECL1(LocalHMDPipe, LocalHMDSinkDevice)
	COPY_PANIC(LocalHMDPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.ogl.holo.events")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class RemoteVRServerPipe : public RemoteVRServerSinkDevice {

public:
	RTTI_DECL1(RemoteVRServerPipe, RemoteVRServerSinkDevice)
	COPY_PANIC(RemoteVRServerPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("tcp.ogl.holo.events")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class BluetoothHoloPipe : public DevBluetoothSinkDevice {

public:
	RTTI_DECL1(BluetoothHoloPipe, DevBluetoothSinkDevice)
	COPY_PANIC(BluetoothHoloPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("bluetooth.holo.events")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagOPENHMD
using OpenHMDPipeRef = Ref<OpenHMDPipe, AtomParent>;
#endif

#if defined flagLOCALHMD
using LocalHMDPipeRef = Ref<LocalHMDPipe, AtomParent>;
#endif

using RemoteVRServerPipeRef = Ref<RemoteVRServerPipe, AtomParent>;

using BluetoothHoloPipeRef = Ref<BluetoothHoloPipe, AtomParent>;

}

}



#endif
