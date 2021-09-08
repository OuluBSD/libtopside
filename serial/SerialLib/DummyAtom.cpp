#include "SerialLib.h"

NAMESPACE_SERIAL_BEGIN


bool DummyAlt::AltInitialize(const Script::WorldState& ws) {
	
	return true;
}

void DummyAlt::AltUninitialize() {
	
}

void DummyAlt::AltForward(FwdScope& fwd) {
	
}

void DummyAlt::AltStorePacket(Packet& p) {
	InterfaceSourceRef iface_src = GetSource();
	Format fmt = iface_src->GetSourceValue().GetFormat();
	ASSERT(fmt.IsValid());
	
	off32 off = gen.Create();
	
	
	RTLOG("DummyAlt::AltStorePacket: sending packet in format: " << fmt.ToString());
	p->SetFormat(fmt);
	p->SetOffset(off);
	
	int a = fmt.GetArea();
	int b = fmt.GetSampleSize();
	int c = a*b;
	ASSERT(c > 0);
}

bool DummyAlt::AltIsReady(ValDevCls vd) {
	return true;
}


NAMESPACE_SERIAL_END
