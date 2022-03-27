#ifndef _SerialMach_LoopSystem_h_
#define _SerialMach_LoopSystem_h_


NAMESPACE_SERIAL_BEGIN
using namespace Parallel;


class LoopSystem :
	public System<LoopSystem>
{
	
public:
	SYS_RTTI(LoopSystem)
	SYS_CTOR(LoopSystem);
	SYS_DEF_VISIT
	
protected:
	
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
};

NAMESPACE_SERIAL_END


#endif
