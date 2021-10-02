#ifndef _SerialLib_AtomUtil_h_
#define _SerialLib_AtomUtil_h_

NAMESPACE_SERIAL_BEGIN


class AsyncMemForwarderBase :
	virtual public AtomBase
{
	Packet		partial_packet;
	byte*		write_mem = 0;
	int			write_size = 0;
	int			write_pos = 0;
	int			partial_pos = 0;
	
	
	void	Consume(int data_begin, Packet p);
	
public:
	
	void	Visit(RuntimeVisitor& vis) override {}
	bool	IsReady(ValDevCls vd) override;
	bool	ForwardAsyncMem(byte* mem, int size) override;
	bool	LoadPacket(int ch_i, const Packet& p) override;
	void	StorePacket(int sink_ch,  int src_ch, Packet& p) override;
	bool	IsConsumedPartialPacket() override {return partial_packet;}
	virtual bool PassLoadPacket(int ch_i, const Packet& p) {return ch_i == GetSink()->GetSinkCount()-1;}
	
};


class FramePollerBase :
	virtual public AtomBase
{
	double		dt = 0;
	double		frame_age = 0;
	
	
public:
	
	void	Update(double dt) override;
	bool	IsReady(ValDevCls vd) override;
	void	Visit(RuntimeVisitor& vis) override {}
	
	void	SetFPS(int fps) {dt = 1.0 / (double)fps;}
	
};


class CenterDriver :
	virtual public AtomBase
{
	
protected:
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
	
public:
	RTTI_DECL0(CenterDriver)
	
	bool Initialize(const Script::WorldState& ws) override {
		customer.Create();
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().template Get<AtomSystem>()->AddDriver(r);
		return true;
	}
	
	void Uninitialize() override {
		AtomBaseRef r = AtomBase::AsRefT();
		ASSERT(r);
		AtomBase::GetMachine().template Get<AtomSystem>()->RemoveDriver(r);
	}
	
	void Visit(RuntimeVisitor& vis) override {}
	
	void UpdateConfig(double dt) override {
		ASSERT(customer);
		customer->cfg.Update(dt, true);
	}
	
	RealtimeSourceConfig* GetConfig() override {ASSERT(customer); return customer ? &customer->cfg : 0;}
	
};

NAMESPACE_SERIAL_END

#endif
