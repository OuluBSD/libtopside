#ifndef _SerialLib_EntitySystem_h_
#define _SerialLib_EntitySystem_h_

namespace  TS {
namespace  Ecs {
class Engine;
}}


NAMESPACE_SERIAL_BEGIN

TS::Ecs::Engine* CreateEcsEngine();

class EntitySystem : public System<EntitySystem> {
	TS::Ecs::Engine* engine = 0;
	ObjectMap reg;
	
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
    void ClearEngine();
    
public:
	SYS_RTTI(EntitySystem)
    SYS_CTOR(EntitySystem)
	SYS_DEF_VISIT
	~EntitySystem() {ClearEngine();}
	
	static ParallelTypeCls::Type GetSerialType() {return ParallelTypeCls::ENTITY_SYSTEM;}
	
};

NAMESPACE_SERIAL_END

#endif
