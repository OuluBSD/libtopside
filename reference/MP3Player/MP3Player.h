#ifndef _MP3Player_MP3Player_h_
#define _MP3Player_MP3Player_h_

#include <CompleteDebug/CompleteDebug.h>
#include <EcsAudioCore/EcsAudioCore.h>
#include <EcsMultimedia/EcsMultimedia.h>
using namespace TS;

NAMESPACE_TOPSIDE_BEGIN
using namespace Ecs;


class AppCustomer :
	public CustomerExt
{
	
public:
	RTTI_DECL1(AppCustomer, CustomerExt)
	
	void Visit(RuntimeVisitor& vis) override {}
	void Forward(FwdScope& fwd) override {RTLOG("AppCustomer::Forward");}
	
	COMP_MAKE_ACTION_BEGIN
		COMP_MAKE_ACTION_FALSE_TO_TRUE("center.customer.mp3player")
	COMP_MAKE_ACTION_END
	
	
	static EcsTypeCls::Type		GetEcsType() {return EcsTypeCls::EXT_TEST_CUSTOMER;}
	
};







NAMESPACE_TOPSIDE_END

#endif
