#ifndef _TemplatesLocalTests_TemplatesLocalTests_h_
#define _TemplatesLocalTests_TemplatesLocalTests_h_

#include <TemplatesLocal/TemplatesLocal.h>

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
		COMP_MAKE_ACTION_FALSE_TO_TRUE("customer.id.ABCD")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_TEST_CUSTOMER;}
	
};


class TestRealtimeSrc :
	public AudioInputExt
{
	
public:
	
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void StorePacket(Packet& p) override;
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_TEST_AUDIO_IN;}
	
};

class TestRealtimeSink :
	public AudioOutputExt
{
	RunningFlag				flag;
	
public:
	RTTI_DECL1(TestRealtimeSink, AudioOutputExt)
	typedef TestRealtimeSink CLASSNAME;
	
	~TestRealtimeSink() {ASSERT(!flag.IsRunning());}
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override;
	void IntervalSinkProcess();
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.sink.realtime")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::COMP_TEST_AUDIO_OUT;}
	
};

NAMESPACE_TOPSIDE_END

#endif
