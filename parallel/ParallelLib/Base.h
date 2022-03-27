#ifndef _ParallelLib_Base_h_
#define _ParallelLib_Base_h_

NAMESPACE_PARALLEL_BEGIN


class CustomerBase :
	public Atom
{
	int			packet_count = 0;
	int			packet_thrds = 0;
	off32_gen	off_gen;
	
protected:
	friend class Space;
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
	
public:
	RTTI_DECL1(CustomerBase, Atom)
	
	void Visit(RuntimeVisitor& vis) override {}
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool ProcessPacket(PacketValue& v) override;
	
	RTSrcConfig* GetConfig() override {ASSERT(customer); return customer ? &customer->cfg : 0;}
	/*bool PostInitialize() override;
	void Forward(FwdScope& fwd) override;
	bool IsLoopComplete(FwdScope& fwd) override {return fwd.GetPos() > 0;}*/
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
	void Visit(RuntimeVisitor& vis) override {}
	void Uninitialize() override {}
	bool ProcessPacket(PacketValue& v) override;
	const Format& GetInternalFormat() const override {return internal_fmt;}
	
};


class VoidSinkBase :
	public Atom
			//AsyncMemForwarderBase
{
	byte				rolling_value = 0;
	Format				internal_fmt;
	
public:
	RTTI_DECL1(VoidSinkBase, Atom)
	typedef VoidSinkBase CLASSNAME;
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	//very old: void Forward(FwdScope& fwd) override {AtomBase::ForwardVoidSink(fwd);}
	void Visit(RuntimeVisitor& vis) override {}
	bool ProcessPacket(PacketValue& v) override;
	bool Consume(const void* data, int len) override;
	const Format& GetInternalFormat() const override {return internal_fmt;}
	
	
	
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
	bool	Initialize(const Script::WorldState& ws) override;
	void	Uninitialize() override;
	/*bool	ProcessPackets(PacketIO& io) override;
	void	Update(double dt) override;
	bool	IsReady(PacketIO& io) override;*/
	void	Visit(RuntimeVisitor& vis) override {}
	bool ProcessPacket(PacketValue& v) override;
	const Format& GetInternalFormat() const override {return internal_fmt;}
	
	
};


NAMESPACE_PARALLEL_END

#endif
