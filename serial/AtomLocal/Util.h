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
	void StorePacket(int sink_ch, int src_ch, const Packet& in, Packet& out) override;
	bool LoadPacket(int sink_ch, const Packet& in, Vector<int>& fwd_src_chs) override;
	void UpdateConfig(double dt) override;
	
};


class JoinerBase :
	virtual public AtomBase
{
	
public:
	JoinerBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	bool IsReady(dword active_iface_mask) override;
	bool LoadPacket(int sink_ch, const Packet& in, Vector<int>& fwd_src_chs) override;
	void StorePacket(int sink_ch, int src_ch, const Packet& in, Packet& out) override;
	
	
};


class SplitterBase :
	virtual public AtomBase
{
	
public:
	SplitterBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	bool LoadPacket(int sink_ch, const Packet& in, Vector<int>& fwd_src_chs) override;
	void StorePacket(int sink_ch, int src_ch, const Packet& in, Packet& out) override;
	
	
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
	bool IsReady(dword active_iface_mask) override;
	bool LoadPacket(int sink_ch, const Packet& in, Vector<int>& fwd_src_chs) override;
	void StorePacket(int sink_ch, int src_ch, const Packet& in, Packet& out) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<OglBufferBase>(this);}
	
	
};

#endif


class TestEventSrcBase :
	virtual public AtomBase
{
	
public:
	RTTI_DECL0(TestEventSrcBase);
	
	TestEventSrcBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool IsReady(dword active_iface_mask) override;
	bool LoadPacket(int sink_ch, const Packet& in, Vector<int>& fwd_src_chs) override;
	void StorePacket(int sink_ch, int src_ch, const Packet& in, Packet& out) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};


class EventStateBase :
	virtual public AtomBase
{
	
public:
	RTTI_DECL0(EventStateBase);
	
	EventStateBase();
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(dword active_iface_mask) override;
	bool LoadPacket(int sink_ch, const Packet& in, Vector<int>& fwd_src_chs) override;
	void StorePacket(int sink_ch, int src_ch, const Packet& in, Packet& out) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};


NAMESPACE_SERIAL_END

#endif
