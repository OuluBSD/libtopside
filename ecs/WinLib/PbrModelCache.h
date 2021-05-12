#pragma once


namespace Pbr {
struct Model;
struct Resources;
}


NAMESPACE_OULU_BEGIN


struct PbrRenderable;

////////////////////////////////////////////////////////////////////////////////
// PbrModelCache
// Stores all of the PbrModels in the system to avoid duplication. As well as
// it allows for lazy-assignment of Model files to PbrRenderable components
// This allows you to set the ModelName on a PbrRenderable component, and the 
// PbrModelCache will automatically assign the Model field of the PbrRenderable once the model has been loaded
class PbrModelCache : public System<PbrModelCache>
{
public:
    PbrModelCache(Engine& core, Shared<Pbr::Resources> pbr_res);

    void RegisterModel(std::string_view name, Shared<Pbr::Model> model);
    bool ModelExists(std::string_view name);
    PbrRenderable* SetModel(std::string_view name, PbrRenderable* pbrRenderableComponent);
    PbrRenderable* SetModel(std::string_view name, ComponentMap& componentMap);

protected:
    void Update(double) override;
    void Uninitialize() override;

private:
    Shared<Pbr::Resources> pbr_res{ nullptr };
    std::map<std::string, Shared<Pbr::Model>> m_modelMap;
};


NAMESPACE_OULU_END
