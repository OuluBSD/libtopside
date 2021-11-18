#ifndef _SerialLib_EntitySystem_h_
#define _SerialLib_EntitySystem_h_


namespace  TS {
namespace  Ecs {
class Engine;
}}


NAMESPACE_SERIAL_BEGIN

Ecs::Engine* CreateEcsEngine();

class EntitySystem : public System<EntitySystem> {
	One<Ecs::Engine> engine;
	ObjectMap reg;
	
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
	SYS_RTTI(EntitySystem)
    SYS_CTOR(EntitySystem)
	SYS_DEF_VISIT
	
	static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::ENTITY_SYSTEM;}
	
};

NAMESPACE_SERIAL_END

#endif
