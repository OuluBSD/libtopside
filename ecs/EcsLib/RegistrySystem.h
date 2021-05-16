#ifndef _EcsLib_RegistrySystem_h_
#define _EcsLib_RegistrySystem_h_

NAMESPACE_TOPSIDE_BEGIN


class RegistrySystem : public System<RegistrySystem> {
	ObjectMap reg;
	
	void Visit(RuntimeVisitor& vis) override {}
	
protected:
    bool Initialize() override;
    void Start() override;
    void Update(double dt) override;
    void Stop() override;
    void Uninitialize() override;
    
public:
    SYS_CTOR(RegistrySystem)
	
	
	void Set(String key, Object value) {reg.GetAdd(key) = value;}
	Object Get(String key) {int i = reg.Find(key); return i >= 0 ? reg[i] : Object();}
	
	
	void SetAppName(String name) {Set("app.name", name);}
	
	String GetAppName() {return Get("app.name");}
	
};


NAMESPACE_TOPSIDE_END

#endif
