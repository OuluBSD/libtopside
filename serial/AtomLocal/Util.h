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
	bool ProcessPackets(PacketIO& io) override;
	void UpdateConfig(double dt) override;
	
};


class JoinerBase :
	virtual public AtomBase
{
	byte scheduler_iter = 1;
	
public:
	JoinerBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	
	
};


class SplitterBase :
	virtual public AtomBase
{
	
public:
	SplitterBase();
	bool Initialize(const Script::WorldState& ws) final;
	void Uninitialize() final;
	void Visit(RuntimeVisitor& vis) override {}
	bool IsReady(PacketIO& io) final;
	bool ProcessPackets(PacketIO& io) final;
	
	
};

class TestEventSrcBase :
	virtual public AtomBase
{
	
public:
	RTTI_DECL0(TestEventSrcBase);
	
	TestEventSrcBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};


class EventStateBase :
	virtual public AtomBase
{
	String			target;
	EnvStateRef		state;
	
public:
	RTTI_DECL0(EventStateBase);
	
	EventStateBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			ProcessPackets(PacketIO& io) override;
	void			Visit(RuntimeVisitor& vis) override {vis & state;}
	
	void			Event(const CtrlEvent& e);
	void			LeftDown(Point p, dword keyflags);
	void			LeftUp(Point p, dword keyflags);
	void			MouseMove(Point p, dword keyflags);
	bool			Key(dword key, int count);
	void			SetBool(dword key, bool b) {state->SetBool(key, b);}
	
	bool			GetBool(dword key) {return state->GetBool(key);}
	EnvState&		GetState() const;
	
};


NAMESPACE_SERIAL_END

#endif
