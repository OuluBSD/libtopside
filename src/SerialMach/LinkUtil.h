#ifndef _SerialLib_LinkUtil_h_
#define _SerialLib_LinkUtil_h_

NAMESPACE_SERIAL_BEGIN


class AsyncMemForwarderBase :
	public Link
{
	Packet			partial_packet;
	byte*			write_mem = 0;
	int				write_size = 0;
	int				write_pos = 0;
	int				partial_pos = 0;
	PacketBuffer	buffer;
	
	off32_gen	dbg_off_gen;
	off32		dbg_offset;
	int			dbg_data_offset = 0;
	
	
	void	Consume(int data_begin, Packet p); // "const Packet&"" is invalid here
	
public:
	RTTI_DECL1(AsyncMemForwarderBase, Link)
	AsyncMemForwarderBase();
	void	Visit(RuntimeVisitor& vis) override {vis.VisitThis<Link>(this);}
	
	bool	IsReady(PacketIO& io) final;
	bool	ForwardAsyncMem(byte* mem, int size) override;
	bool	ProcessPackets(PacketIO& io) final;
	bool	IsConsumedPartialPacket() final {return partial_packet;}
	
	virtual bool PassConsumePacket(int sink_ch, const Packet& in) {return true;}
	
};


class FramePollerBase :
	public Link
{
	double		dt = 0;
	double		frame_age = 0;
	
	
public:
	RTTI_DECL1(FramePollerBase, Link)
	
	void	Update(double dt) override;
	bool	IsReady(PacketIO& io) override;
	
	void	Visit(RuntimeVisitor& vis) override {vis.VisitThis<Link>(this);}
	
	void	SetFPS(int fps) {dt = 1.0 / (double)fps;}
	
};


class CenterDriver :
	public Link
{
	
protected:
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
	
public:
	RTTI_DECL1(CenterDriver, Link)
	
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void	Visit(RuntimeVisitor& vis) override {vis.VisitThis<Link>(this);}
	
	RealtimeSourceConfig* GetConfig() final {ASSERT(customer); return customer ? &customer->cfg : 0;}
	
};

NAMESPACE_SERIAL_END

#endif
