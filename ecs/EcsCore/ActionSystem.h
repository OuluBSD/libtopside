#ifndef _EcsCore_ActionSystem_h_
#define _EcsCore_ActionSystem_h_


NAMESPACE_OULU_BEGIN


class ActionSystem : public System<ActionSystem> {

public:
	using System::System;
	
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(float dt) override;
    void Stop() override;
    void Uninitialize() override;
	
};


NAMESPACE_OULU_END


#endif
