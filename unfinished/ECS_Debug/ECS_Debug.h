#ifndef _ECS_Debug_ECS_Debug_h_
#define _ECS_Debug_ECS_Debug_h_

#include <CompleteDebug/CompleteDebug.h>
using namespace TS;

NAMESPACE_TOPSIDE_BEGIN



class DebugGenerator :
	public CustomerExt
{
	RefT_Entity<DebugSoundGeneratorComponent>	gen;
	RefT_Entity<DebugAudioSinkComponent>		audio;
	
public:
	typedef DebugGenerator CLASSNAME;
	DebugGenerator() {}
	void OnError();
	void Initialize() override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {vis & gen & audio;}
	
	COPY_PANIC(DebugGenerator);
	
};

/*PREFAB_BEGIN(DebugGeneratorPrefab)
	DebugAudioSinkComponent,
	DebugSoundGeneratorComponent,
	DebugGenerator
PREFAB_END*/



NAMESPACE_TOPSIDE_END

#endif
