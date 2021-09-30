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
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltStorePacket(int sink_ch,  int src_ch, Packet& p) override;
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
	bool AltInitialize(const Script::WorldState& ws) override;
	void AltUninitialize() override;
	//void AltForward(FwdScope& fwd) override {AtomBase::ForwardVoidSink(fwd);}
	void AltStorePacket(int sink_ch,  int src_ch, Packet& p) override {} // required pass
	void IntervalSinkProcess() override;
	void Visit(RuntimeVisitor& vis) override {}
	
	void IntervalSinkProcess0() {this->IntervalSinkProcess();}
	
	
};


NAMESPACE_SERIAL_END

#endif
