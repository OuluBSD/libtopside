#ifndef _AtomVR_Generated_h_
#define _AtomVR_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if (defined flagFREEBSD && defined flagOPENHMD) || (defined flagLINUX && defined flagOPENHMD)
class OpenHMDPipe : public OpenHMDSinkDevice {

public:
	RTTI_DECL1(OpenHMDPipe, OpenHMDSinkDevice)
	COPY_PANIC(OpenHMDPipe)
	static String GetAction();
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
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagFREEBSD) || (defined flagLINUX)
class RemoteVRServerPipe : public RemoteVRServerSinkDevice {

public:
	RTTI_DECL1(RemoteVRServerPipe, RemoteVRServerSinkDevice)
	COPY_PANIC(RemoteVRServerPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

#if (defined flagFREEBSD && defined flagHACK) || (defined flagLINUX && defined flagHACK)
class BluetoothHoloPipe : public DevBluetoothSinkDevice {

public:
	RTTI_DECL1(BluetoothHoloPipe, DevBluetoothSinkDevice)
	COPY_PANIC(BluetoothHoloPipe)
	static String GetAction();
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	
};
#endif

}

}
#endif
