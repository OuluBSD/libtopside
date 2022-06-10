#ifndef _EcsVR_AtomBinder_h_
#define _EcsVR_AtomBinder_h_

NAMESPACE_ECS_BEGIN


struct HolographicScopeBinder : RTTIBase {
	RTTI_DECL0(HolographicScopeBinder)
	
    HolographicScope* s = 0;
	
	
	bool Initialize();
	void Uninitialize();
	
	
	
	HolographicScope& GetScope() const {return *s;}
	
};


NAMESPACE_ECS_END

#endif
