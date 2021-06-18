#ifndef _TemplatesLocalTests_TemplatesLocalTests_h_
#define _TemplatesLocalTests_TemplatesLocalTests_h_

#include <TemplatesLocal/TemplatesLocal.h>

NAMESPACE_TOPSIDE_BEGIN


class TestCustomer :
	public CustomerExt
{
	
public:
	
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override {LOG("TestCustomer::Forward");}
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("customer.id.ABCD")
	COMP_MAKE_ACTION_END
	
};


class TestRealtimeSink :
	public AudioOutputExt
{
	
public:
	
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override {LOG("TestRealtimeSink::Forward");}
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.audio.sink.realtime")
	COMP_MAKE_ACTION_END
	
};

NAMESPACE_TOPSIDE_END

#endif
