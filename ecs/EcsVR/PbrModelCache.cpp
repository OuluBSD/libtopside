#include "EcsVR.h"
#if 1

NAMESPACE_ECS_BEGIN



void PbrModelCache::RegisterModel(String name, Shared<Pbr::Model> model) {
	if (name.IsEmpty()) {
		throw Exc("Cannot register model with empty name");
	}
	
	model_map.GetAdd(name) =  model;
}

PbrRenderableRef PbrModelCache::SetModel(String name, PbrRenderableRef pbr_rend_comp) {
	pbr_rend_comp->model_name = name;
	auto it = model_map.Find(name);
	
	if (it) {
		// Each instance gets its own copy of the model data (the heavyweight model data is immutable and reference counted).
		pbr_rend_comp->model.Create();
		it()->Clone(*pbr_res, *pbr_rend_comp->model);
		LOG("Model " << pbr_rend_comp->model_name << " successfully attached to Entity [Deferred]");
	}
	
	return pbr_rend_comp;
}

PbrRenderableRef PbrModelCache::SetModel(String name, ComponentMap& componentMap) {
	PbrRenderableRef pbr_rend_comp = componentMap.Get<PbrRenderable>();
	return SetModel(name, pbr_rend_comp);
}

bool PbrModelCache::ModelExists(String name) {
	return model_map.Find(name);
}

void PbrModelCache::Update(double dt) {
	for (auto& comp_set : GetPool()->GetComponents<PbrRenderable>()) {
		auto pbr_renderable = comp_set.Get<PbrRenderableRef>();
		
		// Find any PbrRenderable component which is waiting for a model to be loaded.
		if (!pbr_renderable->model && pbr_renderable->model_name.GetCount() > 0) {
			(void)SetModel(pbr_renderable->model_name, pbr_renderable);
		}
		
		// Apply any material updates as needed.
		if (pbr_renderable->model) {
			for (uint32_t i = 0; i < pbr_renderable->model->GetPrimitiveCount(); ++i) {
				auto& material = pbr_renderable->model->GetPrimitive(i).GetMaterial();
				vec4 cur_clr = material.parameters.Get().base_clr_factor;
				
				if (pbr_renderable->color && i == 0) {
					cur_clr = vec4(*pbr_renderable->color);
				}
				
				cur_clr[3] = (pbr_renderable->alpha_multiplier) ? *pbr_renderable->alpha_multiplier : 1.0f;
				const vec4& mat_base_clr = material.parameters.Get().base_clr_factor;
				
				if (	cur_clr[0] != mat_base_clr[0] ||
						cur_clr[1] != mat_base_clr[1] ||
						cur_clr[2] != mat_base_clr[2] ||
						cur_clr[3] != mat_base_clr[3])
				{
					material.parameters.Set([&](Pbr::Material::ConstantBufferData & data) {
						data.base_clr_factor = cur_clr;
					});
				}
			}
		}
	}
}

void PbrModelCache::Uninitialize() {
	model_map.Clear();
}


NAMESPACE_ECS_END

#endif
