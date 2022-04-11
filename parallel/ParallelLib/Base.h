#ifndef _ParallelLib_Base_h_
#define _ParallelLib_Base_h_

NAMESPACE_PARALLEL_BEGIN


class CustomerBase :
	public Atom
{
	int			packet_count = 0;
	int			packet_thrds = 0;
	
protected:
	friend class Space;
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
	
public:
	RTTI_DECL1(CustomerBase, Atom)
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool ProcessPacket(PacketValue& in, PacketValue& out) override;
	bool IsForwardReady() override;
	void ForwardPacket(PacketValue& in, PacketValue& out) override;
	
	
	RTSrcConfig* GetConfig() override {ASSERT(customer); return customer ? &customer->cfg : 0;}
	bool PostInitialize() override;
	void UpdateConfig(double dt) override;
	
};


class RollingValueBase :
	public Atom
{
	byte				rolling_value = 0;
	double				time = 0;
	Format				internal_fmt;
	
public:
	RTTI_DECL1(RollingValueBase, Atom)
	bool Initialize(const Script::WorldState& ws) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	void Uninitialize() override {}
	bool ProcessPacket(PacketValue& in, PacketValue& out) override;
	//const Format& GetInternalFormat() const override {return internal_fmt;}
	
};


class VoidSinkBase :
	public Atom
			//AsyncMemForwarderBase
{
	byte				rolling_value = 0;
	Format				internal_fmt;
	int					dbg_total_samples = 0;
	int					dbg_total_bytes = 0;
	int					dbg_iter = 0;
	int					dbg_limit = 0;
	Format				fmt;
	
public:
	RTTI_DECL1(VoidSinkBase, Atom)
	typedef VoidSinkBase CLASSNAME;
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	//very old: void Forward(FwdScope& fwd) override {AtomBase::ForwardVoidSink(fwd);}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool ProcessPacket(PacketValue& in, PacketValue& out) override;
	bool Consume(const void* data, int len) override;
	//const Format& GetInternalFormat() const override {return internal_fmt;}
	
	
	
};

class VoidPollerSinkBase :
	public Atom
{
	struct Thread {
		byte				rolling_value = 0;
		double				time = 0;
	};
	ArrayMap<uint64, Thread> thrds;
	Format				internal_fmt;
	double				dt = 0;
	double				ts = 0;
	bool				fail = false;
	int					dbg_total_samples = 0;
	int					dbg_total_bytes = 0;
	
public:
	RTTI_DECL1(VoidPollerSinkBase, Atom)
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Update(double dt) override;
	bool IsReady(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool ProcessPacket(PacketValue& in, PacketValue& out) override;
	//const Format& GetInternalFormat() const override {return internal_fmt;}
	
	
};

class VoidBase :
	public Atom
{
	
public:
	RTTI_DECL1(VoidBase, Atom)
	bool Initialize(const Script::WorldState& ws) override {return true;}
	void Uninitialize() override {}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool ProcessPacket(PacketValue& in, PacketValue& out) override {return true;}
	
};

#ifdef flagSCREEN
class EventStateBase :
	public Atom
{
	String			target;
	EnvStateRef		state;
	
public:
	RTTI_DECL1(EventStateBase, Atom)
	
	EventStateBase();
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool IsReady(PacketIO& io) override;
	bool ProcessPacket(PacketValue& in, PacketValue& out) override;
	
	void Event(const CtrlEvent& e);
	void LeftDown(Point pt, dword keyflags);
	void LeftUp(Point pt, dword keyflags);
	void MouseMove(Point pt, dword keyflags);
	bool Key(dword key, int count);
	void MouseWheel(Point p, int zdelta, dword keyflags);
	
	void			SetBool(dword key, bool b) {state->SetBool(key, b);}
	void			SetInt(dword key, int i) {state->SetInt(key, i);}
	
	bool			GetBool(dword key) {return state->GetBool(key);}
	int				GetInt(dword key) {return state->GetInt(key);}
	EnvState&		GetState() const;
	
};
#endif

class TestEventSrcBase :
	public Atom
{
	int sent_count = 0;
	
public:
	RTTI_DECL1(TestEventSrcBase, Atom)
	
	TestEventSrcBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool IsReady(PacketIO& io) override;
	bool ProcessPacket(PacketValue& in, PacketValue& out) override;
	
	
};




NAMESPACE_PARALLEL_END

#endif
