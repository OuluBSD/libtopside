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
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.ogl.holo.events")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class UsbHoloPipe : public DevUsbSinkDevice {

public:
	RTTI_DECL1(UsbHoloPipe, DevUsbSinkDevice)
	COPY_PANIC(UsbHoloPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("usb.holo.events")
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

using UsbHoloPipeRef = Ref<UsbHoloPipe, AtomParent>;

using BluetoothHoloPipeRef = Ref<BluetoothHoloPipe, AtomParent>;

}

}



#endif
