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
	void StorePacket(int sink_ch,  int src_ch, Packet& p) override;
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
	void StorePacket(int sink_ch,  int src_ch, Packet& p) override {} // required pass
	void Visit(RuntimeVisitor& vis) override {}
	
	void IntervalSinkProcess();
	
	
};


NAMESPACE_SERIAL_END

#endif
