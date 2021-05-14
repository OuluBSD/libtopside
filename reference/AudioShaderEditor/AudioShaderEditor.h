#ifndef _AudioShaderEditor_AudioShaderEditor_h
#define _AudioShaderEditor_AudioShaderEditor_h

#include <Complete/Complete.h>
using namespace Upp;



NAMESPACE_OULU_BEGIN



class AudioShaderEditor :
	public TopWindow
{
	TabMgrCtrl tabs;
	
	TimeCallback tc, data_tc;
	TimeStop ts;
	
	void MachineUpdater();
	
	
public:
	typedef AudioShaderEditor CLASSNAME;
	AudioShaderEditor(Machine& mach);
	
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
