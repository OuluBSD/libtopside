#ifndef _SerialLib_EntitySystem_h_
#define _SerialLib_EntitySystem_h_


namespace  TS {
namespace  Ecs {
class Engine;
}}


NAMESPACE_SERIAL_BEGIN

Ecs::Engine* CreateEcsEngine();

class EntitySystem : public System<EntitySystem> {
	Ecs::Engine* engine = 0;
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
	
	static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::ENTITY_SYSTEM;}
	
};

NAMESPACE_SERIAL_END

#endif
