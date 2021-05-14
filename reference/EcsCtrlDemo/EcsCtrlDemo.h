#ifndef _EcsCtrlDemo_EcsCtrlDemo_h
#define _EcsCtrlDemo_EcsCtrlDemo_h

#include <Complete/Complete.h>
using namespace Upp;



NAMESPACE_OULU_BEGIN



class EcsCtrlDemo :
	public TopWindow
{
	TabMgrCtrl tabs;
	
	TimeCallback tc, data_tc;
	TimeStop ts;
	
	void MachineUpdater();
	
	
public:
	typedef EcsCtrlDemo CLASSNAME;
	EcsCtrlDemo(Machine& mach);
	
	bool InitializeDefault();
	
	void Updated() override;
	void OnError();
	
	
	Machine& mach;
	static constexpr const char* POOL_NAME = "shaders";
	
	PoolRef GetPool() {return mach.Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
};



void Startup();


NAMESPACE_OULU_END


#endif
