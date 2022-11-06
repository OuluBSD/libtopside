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
	bool Recv(int sink_ch, const Packet& in) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
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
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	
};


class VoidSinkBase :
	public Atom
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
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	bool Consume(const void* data, int len) override;
	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override;
	
	
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
	int					dbg_limit = 0;
	
public:
	RTTI_DECL1(VoidPollerSinkBase, Atom)
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Update(double dt) override;
	bool IsReady(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool Recv(int sink_ch, const Packet& in) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	
	
};

class VoidBase :
	public Atom
{
	
public:
	RTTI_DECL1(VoidBase, Atom)
	bool Initialize(const Script::WorldState& ws) override {return true;}
	void Uninitialize() override {}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override {return true;}
	
};

#ifdef flagSCREEN
class EventStateBase :
	public Atom
{
	static Vector<BinderIfaceEvents*>	binders;
	String			target;
	EnvStateRef		state;
	bool			dbg_print = false;
	int				dbg_iter = 0;
	int				dbg_limit = 0;
	
	static EventStateBase* latest;
	
public:
	RTTI_DECL1(EventStateBase, Atom)
	
	EventStateBase();
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	void Update(double dt) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this); vis & state;}
	bool IsReady(PacketIO& io) override;
	bool Recv(int sink_ch, const Packet& in) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	
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
	
	static EventStateBase* Latest() {return latest;}
	
	static void AddBinder(BinderIfaceEvents* iface);
	static void RemoveBinder(BinderIfaceEvents* iface);
	
};
#endif

class TestEventSrcBase :
	public Atom
{
	int sent_count = 0;
	TransformMatrix trans;
	ControllerMatrix ctrl;
	
public:
	RTTI_DECL1(TestEventSrcBase, Atom)
	
	TestEventSrcBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this);}
	bool IsReady(PacketIO& io) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	
	
};




NAMESPACE_PARALLEL_END

#endif
