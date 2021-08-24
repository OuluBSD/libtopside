#ifndef _AtomDebug_Testers_h_
#define _AtomDebug_Testers_h_

NAMESPACE_SERIAL_BEGIN


class TestCustomer :
	public CustomerAtom
{
	
public:
	RTTI_DECL1(TestCustomer, CustomerAtom)
	
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override {LOG("TestCustomer::Forward");}
	
	/*ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("customer.test.single")
	ATOM_MAKE_ACTION_END*/
	
	
};


class TestRealtimeSrc :
	public AtomBase
{
	Serial::Format		internal_fmt;
	double			time = 0;
	byte			rolling_value = 0;
	
public:
	RTTI_DECL1(TestRealtimeSrc, AtomBase)
	
	static AtomTypeCls GetAtomType() {return ATOM0(TEST_CENTER_ORDER_AUDIO, CENTER, ORDER, CENTER, AUDIO);}
	
	//bool Initialize(const Script::WorldState& ws) override;
	//void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	
	
	AtomTypeCls GetType() const override {return GetAtomType();}
	void CopyTo(AtomBase* atom) const override {TODO}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	void ClearSinkSource() override {TODO}
	
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.test")
	ATOM_MAKE_ACTION_END
	
	
};


class TestRealtimeSink :
	public AtomBase
{
	RunningFlag		flag;
	byte			rolling_value = 0;
	
public:
	RTTI_DECL1(TestRealtimeSink, AtomBase)
	typedef TestRealtimeSink CLASSNAME;
	
	static AtomTypeCls GetAtomType() {return ATOM0(TEST_CENTER_AUDIO_RECEIPT, CENTER, AUDIO, CENTER, RECEIPT);}
	
	~TestRealtimeSink() {ASSERT(!flag.IsRunning());}
	//bool Initialize(const Script::WorldState& ws) override;
	//void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	void IntervalSinkProcess();
	
	AtomTypeCls GetType() const override {return GetAtomType();}
	void CopyTo(AtomBase* atom) const override {TODO}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	void ClearSinkSource() override {TODO}
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.test.realtime")
	ATOM_MAKE_ACTION_END
	
	
};


NAMESPACE_SERIAL_END

#endif
