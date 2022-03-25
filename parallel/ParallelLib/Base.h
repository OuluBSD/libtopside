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
	RTTI_DECL0(CustomerBase);
	
	void Visit(RuntimeVisitor& vis) override {}
	void Uninitialize() override;
	
	/*RTSrcConfig* GetConfig() override {ASSERT(customer); return customer ? &customer->cfg : 0;}
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Forward(FwdScope& fwd) override;
	bool IsLoopComplete(FwdScope& fwd) override {return fwd.GetPos() > 0;}
	bool ProcessPackets(PacketIO& io) override;
	void UpdateConfig(double dt) override;*/
	
};


NAMESPACE_PARALLEL_END

#endif
