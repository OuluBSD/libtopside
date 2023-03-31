#ifndef _EcsLib_RegistrySystem_h_
#define _EcsLib_RegistrySystem_h_

NAMESPACE_ECS_BEGIN


class RegistrySystem : public System<RegistrySystem> {
	ObjectMap reg;
	
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
	SYS_RTTI(RegistrySystem)
    ECS_SYS_CTOR(RegistrySystem)
	ECS_SYS_DEF_VISIT
	
	void Set(String key, Object value) {reg.GetAdd(key) = value;}
	Object Get(String key) {int i = reg.Find(key); return i >= 0 ? reg[i] : Object();}
	
	
	void SetAppName(String name) {Set("app.name", name);}
	
	String GetAppName() {return Get("app.name");}
	
	
};


NAMESPACE_ECS_END

#endif
