#ifndef _AtomLocal_Util_h_
#define _AtomLocal_Util_h_

NAMESPACE_SERIAL_BEGIN


class CustomerBase :
	virtual public AtomBase
{
	int			packet_count = 0;
	int			packet_thrds = 0;
	off32_gen	off_gen;
	
public:
	RTTI_DECL0(CustomerBase);
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltForward(FwdScope& fwd) override;
	void Visit(RuntimeVisitor& vis) override {}
	void AltStorePacket(int sink_ch,  int src_ch, Packet& p) override;
	void LoadPacket(int ch_i, const Packet& p) override;
};


class JoinerBase :
	virtual public AtomBase
{
	
	
public:
	JoinerBase();
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};


class SplitterBase :
	virtual public AtomBase
{
	
	
public:
	SplitterBase();
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};

#ifdef flagGUI

class OglShaderBase :
	public OglBufferBase
{
	Packet		last_packet;
	
public:
	RTTI_DECL1(OglShaderBase, OglBufferBase);
	
	OglShaderBase();
	bool AltInitialize(const Script::WorldState& ws) override;
	bool AltPostInitialize() override;
	void AltUninitialize() override;
	void AltForward(FwdScope& fwd) override;
	bool AltIsReady(ValDevCls vd) override;
	void LoadPacket(int ch_i, const Packet& p) override;
	void AltStorePacket(int sink_ch,  int src_ch, Packet& p) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<OglBufferBase>(this);}
	
	
};

#endif

NAMESPACE_SERIAL_END

#endif