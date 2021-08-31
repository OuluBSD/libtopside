#ifndef _AtomDebug_Testers_h_
#define _AtomDebug_Testers_h_

NAMESPACE_SERIAL_BEGIN




class TestRealtimeSrc :
	public Atom<TestRealtimeSrc>
{
	Serial::Format		internal_fmt;
	double				time = 0;
	byte				rolling_value = 0;
	
public:
	using AtomT = Atom<TestRealtimeSrc>;
	RTTI_DECL1(TestRealtimeSrc, AtomT)
	COPY_PANIC(TestRealtimeSrc)
	static AtomTypeCls GetAtomType() {return ATOM0(TEST_CENTER_ORDER_AUDIO, SOURCE, CENTER, ORDER, CENTER, AUDIO);}
	
	//bool Initialize(const Script::WorldState& ws) override;
	//void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	void StorePacket(Packet& p) override;
	void Forward(FwdScope& fwd) override;
	
	
	AtomTypeCls GetType() const override {return GetAtomType();}
	void CopyTo(AtomBase* atom) const override {TODO}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	void ClearSinkSource() override {TODO}
	
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.test")
	ATOM_MAKE_ACTION_END
	
	
	static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::TEST_RT_SRC;}
	
};


class TestRealtimeSink :
	public Atom<TestRealtimeSink>
{
	RunningFlag		flag;
	byte			rolling_value = 0;
	
public:
	using AtomT = Atom<TestRealtimeSink>;
	RTTI_DECL1(TestRealtimeSink, AtomT)
	COPY_PANIC(TestRealtimeSink)
	typedef TestRealtimeSink CLASSNAME;
	
	static AtomTypeCls GetAtomType() {return ATOM0(TEST_CENTER_AUDIO_RECEIPT, SINK, CENTER, AUDIO, CENTER, RECEIPT);}
	
	~TestRealtimeSink() {ASSERT(!flag.IsRunning());}
	//bool Initialize(const Script::WorldState& ws) override;
	//void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<AtomT>(this);}
	void StorePacket(Packet& p) override;
	void IntervalSinkProcess();
	
	AtomTypeCls GetType() const override {return GetAtomType();}
	void CopyTo(AtomBase* atom) const override {TODO}
	void VisitSource(RuntimeVisitor& vis) override {TODO}
	void VisitSink(RuntimeVisitor& vis) override {TODO}
	void ClearSinkSource() override {TODO}
	void Forward(FwdScope& fwd) override;
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.test.realtime")
	ATOM_MAKE_ACTION_END
	
	static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::TEST_RT_SINK;}
	
};


NAMESPACE_SERIAL_END

#endif
