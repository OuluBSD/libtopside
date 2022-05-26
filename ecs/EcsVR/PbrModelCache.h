#pragma once


NAMESPACE_ECS_BEGIN



class PbrRenderable :
	public Component<PbrRenderable>
{
	
	
public:
	RTTI_COMP0(PbrRenderable)
	COPY_PANIC(PbrRenderable)
	COMP_DEF_VISIT
	
    void ResetModel(String name, Optional<mat4> offset = null_opt) {
        model_name = name;
        offset = offset;
    }

    String				model_name;
    //One<Pbr::Model>		model;
    Optional<vec4>		color;
    Optional<mat4>		offset;
    Optional<double>	alpha_multiplier;
    
};


#if 0

class PbrModelCache : public System<PbrModelCache>
{
	
public:
	SYS_RTTI(PbrModelCache)
	ECS_SYS_CTOR(PbrModelCache);
	SYS_DEF_VISIT
	
    void SetResources(Shared<Pbr::Resources> pbr_res) {this->pbr_res = pbr_res;}

    void RegisterModel(String name, Shared<Pbr::Model> model);
    bool ModelExists(String name);
    PbrRenderableRef SetModel(String name, PbrRenderableRef pbr_rend_comp);
    PbrRenderableRef SetModel(String name, ComponentMap& componentMap);

	static constexpr const char* POOL_NAME = "model_cache";
	
	PoolRef GetPool() const {return GetEngine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
	
protected:
    void Update(double) override;
    void Uninitialize() override;

private:
    Shared<Pbr::Resources> pbr_res;
    LinkedMap<String, Shared<Pbr::Model>> model_map;
    
    
};

#endif

NAMESPACE_ECS_END


