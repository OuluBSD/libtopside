#ifndef _EcsCore_StateSystem_h_
#define _EcsCore_StateSystem_h_


NAMESPACE_OULU_BEGIN


class StateSystem : public System<StateSystem> {

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
