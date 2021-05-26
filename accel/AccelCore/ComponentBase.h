#ifndef _AccelCore_ComponentBase_h_
#define _AccelCore_ComponentBase_h_

#if 0

NAMESPACE_TOPSIDE_BEGIN



class AccelComponent : public RefScopeEnabler<AccelComponent,Entity> {
	RTTI_DECL_R0(AccelComponent)
	
	
public:
	COPY_PANIC(AccelComponent);
	
	AccelComponent();
	
	void Update0(double dt);
	
};

using AccelComponentRef				= Ref<AccelComponent,				RefParent1<Entity>>;



NAMESPACE_TOPSIDE_END

#endif
#endif
