#ifndef _AtomLocal_Debug_h_
#define _AtomLocal_Debug_h_

NAMESPACE_SERIAL_BEGIN


class RollingValueBase :
	virtual public AtomBase
{
	byte				rolling_value = 0;
	double				time = 0;
	Serial::Format		internal_fmt;
	
public:
	RTTI_DECL0(RollingValueBase)
	bool Initialize(const Script::WorldState& ws) override;
	bool ProcessPackets(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};


class VoidSinkBase :
	public AsyncMemForwarderBase
{
	byte				rolling_value = 0;
	Serial::Format		internal_fmt;
	RunningFlag			flag;
	
public:
	RTTI_DECL0(VoidSinkBase)
	typedef VoidSinkBase CLASSNAME;
	~VoidSinkBase() {ASSERT(!flag.IsRunning());}
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	//void Forward(FwdScope& fwd) override {AtomBase::ForwardVoidSink(fwd);}
	void Visit(RuntimeVisitor& vis) override {}
	
	void IntervalSinkProcess();
	
	
};


class VoidPollerSinkBase :
	virtual public AtomBase
{
	struct Thread {
		byte				rolling_value = 0;
		double				time = 0;
	};
	ArrayMap<uint64, Thread> thrds;
	Serial::Format		internal_fmt;
	double				dt = 0;
	double				ts = 0;
	bool				fail = false;
	int					dbg_total_samples = 0;
	int					dbg_total_bytes = 0;
	
public:
	RTTI_DECL0(VoidPollerSinkBase);
	bool	Initialize(const Script::WorldState& ws) override;
	void	Uninitialize() override;
	bool	ProcessPackets(PacketIO& io) override;
	void	Update(double dt) override;
	bool	IsReady(PacketIO& io) override;
	void	Visit(RuntimeVisitor& vis) override {}
	
	
};


NAMESPACE_SERIAL_END

#endif
