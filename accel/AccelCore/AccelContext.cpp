#include "AccelCore.h"

NAMESPACE_TOPSIDE_BEGIN

void AccelContextComponent::Initialize() {
	DLOG("AccelContextComponent::Initialize");
	Ref<AccelSystem> fusion_sys = GetEntity()->GetMachine().Get<AccelSystem>();
	if (fusion_sys)
		fusion_sys	-> Add(AsRef<AccelContextComponent>());
	
}

void AccelContextComponent::Uninitialize() {
	Ref<AccelSystem> fusion_sys = GetEntity()->GetMachine().Get<AccelSystem>();
	if (fusion_sys)
		fusion_sys	-> Remove(AsRef<AccelContextComponent>());
}

void AccelContextComponent::Update(double dt) {
	DLOG("AccelContextComponent::Update: begin");
	
	#if 0
	//lock.Enter();
	
	if (!post_load.IsVoid()) {
		DLOG("AccelContextComponent::Update: load new program");
		
		Object to_load;
		Swap(post_load, to_load);
		
		for(AccelComponentRef& comp : comps) {
			if (comp->IsTypeTemporary()) {
				comp->Close();
				comp->GetECS().Destroy();
			}
		}
		
		Clear();
		FindComponents();
		DumpEntityComponents();
		
		Load(to_load);
		Reset();
		
		//  Reload stage pointers
		if (!RefreshStageQueue())
			return;
		DumpEntityComponents();
		
		is_open = true;
		for(AccelComponentRef& comp : comps) {
			if (!comp->IsOpen() && !comp->Open()) {
				DLOG("AccelContextComponent::Update: error: a component did not open properly");
				is_open = false;
			}
		}
		
		if (!is_open) {
			DLOG("AccelContextComponent::Update: error: did not open properly");
			return;
		}
		
		RefreshPipeline();
	}
	
	//lock.Leave();
	#endif
	
	DLOG("AccelContextComponent::Update: end");
}



NAMESPACE_TOPSIDE_END
