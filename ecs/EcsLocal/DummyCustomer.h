#ifndef _EcsLocal_DummyCustomer_h_
#define _EcsLocal_DummyCustomer_h_


NAMESPACE_ECS_BEGIN



class AudioPlayerCustomer :
	public CustomerExt
{
	
public:
	RTTI_DECL1(AudioPlayerCustomer, CustomerExt)
	
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override {RTLOG("AudioPlayerCustomer::Forward");}
	
	EXT_MAKE_ACTION_BEGIN
		EXT_MAKE_ACTION_UNDEF_TO_TRUE("center.customer.audio.player")
	EXT_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_CUSTOMER;}
	
};



NAMESPACE_ECS_END

#endif
