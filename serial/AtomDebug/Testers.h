#ifndef _AtomDebug_Testers_h_
#define _AtomDebug_Testers_h_

#if HAVE_MANUAL_DBG_CLASSES

NAMESPACE_SERIAL_BEGIN




class TestRealtimeSrc :
	public CenterSourceAsync<TestRealtimeSrc>
{
	
public:
	RTTI_DECL1(TestRealtimeSrc, BaseT)
	COPY_PANIC(TestRealtimeSrc)
	static AtomTypeCls GetAtomType() {return ATOM0(TEST_CENTER_ORDER_AUDIO, SOURCE, CENTER, ORDER, CENTER, AUDIO);}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<BaseT>(this);}
	AtomTypeCls GetType() const override {return GetAtomType();}
	void StorePacket(Packet& p) override;
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.test")
	ATOM_MAKE_ACTION_END
	
	
};


class TestRealtimeSink :
	public CenterSinkSync<TestRealtimeSink>
{
	
public:
	RTTI_DECL1(TestRealtimeSink, BaseT)
	COPY_PANIC(TestRealtimeSink)
	typedef TestRealtimeSink CLASSNAME;
	static AtomTypeCls GetAtomType() {return ATOM0(TEST_CENTER_AUDIO_RECEIPT, SINK, CENTER, AUDIO, CENTER, RECEIPT);}
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<BaseT>(this);}
	AtomTypeCls GetType() const override {return GetAtomType();}
	void IntervalSinkProcess() override;
	
	ATOM_MAKE_ACTION_BEGIN
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
		ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.test.realtime")
	ATOM_MAKE_ACTION_END
	
	
};


NAMESPACE_SERIAL_END

#endif
#endif
