#ifndef _EcsCore_ExchangeSystem_h_
#define _EcsCore_ExchangeSystem_h_


NAMESPACE_OULU_BEGIN


class ExchangeSystem : public System<ExchangeSystem> {

public:
	using System::System;
	
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
	
};


NAMESPACE_OULU_END


#endif
