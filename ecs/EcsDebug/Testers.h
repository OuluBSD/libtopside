#ifndef _EcsDebug_Testers_h_
#define _EcsDebug_Testers_h_
#endif


NAMESPACE_ECS_BEGIN



class TestCustomer :
	public CustomerExt
{
	
public:
	RTTI_DECL1(TestCustomer, CustomerExt)
	
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override {LOG("TestCustomer::Forward");}
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("customer.test.single")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_CUSTOMER;}
	
};


class TestInputCustomer :
	public CustomerExt
{
	
public:
	RTTI_DECL1(TestInputCustomer, CustomerExt)
	
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override {LOG("TestInputCustomer::Forward");}
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("customer.test.input")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_CUSTOMER_INPUT;}
	
};


class TestOutputCustomer :
	public CustomerExt
{
	
public:
	RTTI_DECL1(TestOutputCustomer, CustomerExt)
	
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override {LOG("TestOutputCustomer::Forward");}
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("customer.test.output")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_CUSTOMER_OUTPUT;}
	
};


class TestRealtimeSrc :
	public AudioInputExt
{
	Ecs::Format		internal_fmt;
	double			time = 0;
	byte			rolling_value = 0;
	
public:
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.src.test")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_AUDIO_IN;}
	
};

class TestRealtimeSink :
	public AudioOutputExt
{
	RunningFlag		flag;
	byte			rolling_value = 0;
	
public:
	RTTI_DECL1(TestRealtimeSink, AudioOutputExt)
	typedef TestRealtimeSink CLASSNAME;
	
	~TestRealtimeSink() {ASSERT(!flag.IsRunning());}
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	void IntervalSinkProcess();
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.sink.test.realtime")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_AUDIO_OUT;}
	
};



NAMESPACE_ECS_END
