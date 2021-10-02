#ifndef _AtomLocal_Util_h_
#define _AtomLocal_Util_h_

NAMESPACE_SERIAL_BEGIN


class CustomerBase :
	virtual public AtomBase
{
	int			packet_count = 0;
	int			packet_thrds = 0;
	off32_gen	off_gen;
	
protected:
	friend class Loop;
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
public:
	RTTI_DECL0(CustomerBase);
	
	RTSrcConfig* GetConfig() override {ASSERT(customer); return customer ? &customer->cfg : 0;}
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	bool IsLoopComplete(FwdScope& fwd) override {return fwd.GetPos() > 0;}
	void Visit(RuntimeVisitor& vis) override {}
	void StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	bool LoadPacket(int ch_i, const Packet& p) override;
	void UpdateConfig(double dt) override;
	
};


class JoinerBase :
	virtual public AtomBase
{
	Packet	cur_side;
	
public:
	JoinerBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	void Visit(RuntimeVisitor& vis) override {}
	bool LoadPacket(int ch_i, const Packet& p) override;
	void StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	
	
};


class SplitterBase :
	virtual public AtomBase
{
	Packet	cur_side;
	
public:
	SplitterBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	void Visit(RuntimeVisitor& vis) override {}
	bool LoadPacket(int ch_i, const Packet& p) override;
	void StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	
	
};

#ifdef flagGUI

class OglShaderBase :
	public OglBufferBase
{
	Packet		last_packet;
	
public:
	RTTI_DECL1(OglShaderBase, OglBufferBase);
	
	OglShaderBase();
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	bool IsReady(ValDevCls vd) override;
	bool LoadPacket(int ch_i, const Packet& p) override;
	void StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<OglBufferBase>(this);}
	
	
};

#endif

NAMESPACE_SERIAL_END

#endif
