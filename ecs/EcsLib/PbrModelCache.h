#pragma once



namespace Pbr {
struct Model;
struct Resources;
}

NAMESPACE_OULU_BEGIN


struct PbrRenderable;

class PbrModelCache : public System<PbrModelCache>
{
	
public:
	void Visit(RuntimeVisitor& vis) override {TODO}
	SYS_CTOR(PbrModelCache);
	
    void SetResources(Shared<Pbr::Resources> pbr_res) {this->pbr_res = pbr_res;}

    void RegisterModel(String name, Shared<Pbr::Model> model);
    bool ModelExists(String name);
    PbrRenderableRef SetModel(String name, PbrRenderableRef pbr_rend_comp);
    PbrRenderableRef SetModel(String name, ComponentMap& componentMap);

	static constexpr const char* POOL_NAME = "model_cache";
	
	PoolRef GetPool() const {return GetMachine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
	
protected:
    void Update(double) override;
    void Uninitialize() override;

private:
    Shared<Pbr::Resources> pbr_res;
    LinkedMap<String, Shared<Pbr::Model>> model_map;
    
    
};


NAMESPACE_OULU_END


