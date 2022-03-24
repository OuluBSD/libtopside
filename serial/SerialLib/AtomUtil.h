#ifndef _SerialLib_AtomUtil_h_
#define _SerialLib_AtomUtil_h_

NAMESPACE_SERIAL_BEGIN


class AsyncMemForwarderBase :
	virtual public LinkBase
{
	Packet		partial_packet;
	byte*		write_mem = 0;
	int			write_size = 0;
	int			write_pos = 0;
	int			partial_pos = 0;
	
	
	void	Consume(int data_begin, Packet p); // "const Packet&"" is invalid here
	
public:
	
	void	Visit(RuntimeVisitor& vis) override {}
	
	bool	IsReady(PacketIO& io) final;
	bool	ForwardAsyncMem(byte* mem, int size) override;
	bool	ProcessPackets(PacketIO& io) final;
	bool	IsConsumedPartialPacket() final {return partial_packet;}
	
	virtual bool PassConsumePacket(int sink_ch, const Packet& in) {return true;}
	
};


class FramePollerBase :
	virtual public AtomBase
{
	double		dt = 0;
	double		frame_age = 0;
	
	
public:
	
	void	Update(double dt) override;
	bool	IsReady(PacketIO& io) override;
	
	void	Visit(RuntimeVisitor& vis) override {}
	
	void	SetFPS(int fps) {dt = 1.0 / (double)fps;}
	
};


class CenterDriver :
	virtual public LinkBase
{
	
protected:
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
	
public:
	RTTI_DECL0(CenterDriver)
	
	bool Initialize(const Script::WorldState& ws) override; /*{
		customer.Create();
		LinkBaseRef r = LinkBase::AsRefT();
		ASSERT(r);
		TODO LinkSystem
		LinkBase::GetMachine().template Get<AtomSystem>()->AddDriver(r);
		return true;
	}*/
	
	void Uninitialize() override; /*{
		LinkBaseRef r = LinkBase::AsRefT();
		ASSERT(r);
		LinkBase::GetMachine().template Get<AtomSystem>()->RemoveDriver(r);
	}*/
	
	void Visit(RuntimeVisitor& vis) override {}
	
	/*cleanup TODO void UpdateConfig(double dt) final {
		ASSERT(customer);
		customer->cfg.Update(dt, true);
	}*/
	
	RealtimeSourceConfig* GetConfig() final {ASSERT(customer); return customer ? &customer->cfg : 0;}
	
};

NAMESPACE_SERIAL_END

#endif
