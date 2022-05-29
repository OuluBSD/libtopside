#pragma once


NAMESPACE_ECS_BEGIN



class PbrRenderable :
	public Component<PbrRenderable>
{
	
	
public:
	RTTI_COMP0(PbrRenderable)
	COPY_PANIC(PbrRenderable)
	COMP_DEF_VISIT
	
	void Initialize() override;
	void Uninitialize() override;
	
    void ResetModel(String name, Optional<mat4> offset = null_opt) {
        model_name = name;
        offset = offset;
    }

    String				model_name;
    One<Pbr::Model>		model;
    Optional<vec4>		color;
    Optional<mat4>		offset;
    Optional<double>	alpha_multiplier;
    
};


class PbrModelCache : public System<PbrModelCache>
{
	
public:
	SYS_RTTI(PbrModelCache)
	ECS_SYS_CTOR(PbrModelCache);
	SYS_DEF_VISIT
	
	Pbr::Model& AddModel(String name);
    /*void SetResources(Shared<Pbr::Resources> pbr_res) {this->pbr_res = pbr_res;}

    void RegisterModel(String name, Shared<Pbr::Model> model);
    bool ModelExists(String name);*/
    
    void SetModel(String name, PbrRenderable& pbr_rend_comp);
    void SetModel(String name, ComponentMap& componentMap);

	static constexpr const char* POOL_NAME = "model_cache";
	
	//PoolRef GetPool() const {return GetEngine().Get<EntityStore>()->GetRoot()->GetAddPool(POOL_NAME);}
	
	
	void Attach(PbrRenderable* p);
	void Detach(PbrRenderable* p);
	
	const Vector<PbrRenderable*>& GetComponents() const {return comps;}
	
protected:
	bool Initialize() override;
    void Update(double) override;
    void Uninitialize() override;

private:
    Pbr::Resources* pbr_res = 0;
    
    LinkedMap<String, Pbr::Model> model_map;
    
    Vector<PbrRenderable*> comps;
    
};


NAMESPACE_ECS_END


