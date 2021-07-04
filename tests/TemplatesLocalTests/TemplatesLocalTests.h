#ifndef _TemplatesLocalTests_TemplatesLocalTests_h_
#define _TemplatesLocalTests_TemplatesLocalTests_h_

#include <TemplatesLocal/TemplatesLocal.h>
#include <EcsDebug/EcsDebug.h>

NAMESPACE_TOPSIDE_BEGIN
using namespace TS::ECS;

class TestCustomer :
	public CustomerExt
{
	
public:
	RTTI_DECL1(TestCustomer, CustomerExt)
	
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override {LOG("TestCustomer::Forward");}
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("customer.single")
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
		COMP_MAKE_ACTION_FALSE_TO_TRUE("customer.input")
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
		COMP_MAKE_ACTION_FALSE_TO_TRUE("customer.output")
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
		COMP_MAKE_ACTION_FALSE_TO_TRUE("class.test_rt_src")
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
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.sink.realtime")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_AUDIO_OUT;}
	
};

class TestAudioSideInputExt :
	public SideInputExt
{
	
public:
	RTTI_DECL1(TestAudioSideInputExt, SideInputExt)
	typedef TestAudioSideInputExt CLASSNAME;
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	
	COMP_MAKE_ACTION_BEGIN
		ASSERT(cls.sub == SubCompCls::SIDE_INPUT);
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.side.in.center")
	COMP_MAKE_ACTION_END
	
	static bool MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to);
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_SIDE_OUT;}
	
};

class TestAudioSideOutputExt :
	public SideOutputExt
{
	
public:
	RTTI_DECL1(TestAudioSideOutputExt, SideOutputExt)
	typedef TestAudioSideOutputExt CLASSNAME;
	
	bool Initialize(const Eon::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	
	COMP_MAKE_ACTION_BEGIN
		ASSERT(cls.sub == SubCompCls::SIDE_OUTPUT);
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.side.out.center")
	COMP_MAKE_ACTION_END
	
	static bool MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to);
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_SIDE_OUT;}
	
};

NAMESPACE_TOPSIDE_END

#endif
