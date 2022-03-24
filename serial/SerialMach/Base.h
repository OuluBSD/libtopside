#ifndef _SerialMach_Base_h_
#define _SerialMach_Base_h_


NAMESPACE_SERIAL_BEGIN


class CustomerBase :
	virtual public LinkBase
{
	int			packet_count = 0;
	int			packet_thrds = 0;
	off32_gen	off_gen;
	
protected:
	friend class Space;
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
	//void UpdateConfig(double dt) override;
	
};





NAMESPACE_SERIAL_END

#endif
