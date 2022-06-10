#if 0
#include "EcsVR.h"

NAMESPACE_ECS_BEGIN


void PbrRenderable::Initialize() {
	auto sys = GetEngine().Get<PbrModelCache>();
	if (sys)
		sys->Attach(this);
}

void PbrRenderable::Uninitialize() {
	auto sys = GetEngine().Get<PbrModelCache>();
	if (sys)
		sys->Detach(this);
}





bool PbrModelCache::Initialize() {
	if (!HolographicScopeBinder::Initialize())
		return false;
	
	return true;
}

Pbr::Model& PbrModelCache::AddModel(String name) {
	ASSERT(!model_map.Find(name));
	Pbr::Model& m = model_map.Add(name);
	m.CreateRootNode();
	return m;
}

void PbrModelCache::Attach(PbrRenderable* p) {
	VectorFindAdd(comps, p);
}

void PbrModelCache::Detach(PbrRenderable* p) {
	VectorRemoveKey(comps, p);
}

#if 0

void PbrModelCache::RegisterModel(String name, Shared<Pbr::Model> model) {
	if (name.IsEmpty()) {
		throw Exc("Cannot register model with empty name");
	}
	
	model_map.GetAdd(name) = model;
}

#endif

void PbrModelCache::SetModel(String name, PbrRenderable& dst) {
	dst.model_name = name;
	auto it = model_map.Find(name);
	
	if (it) {
		Pbr::Model& src = *it;
		
		// Each instance gets its own copy of the model data (the heavyweight model data is immutable and reference counted).
		dst.model.Create();
		src.Copy(s->pbr_res, *dst.model);
		LOG("Model " << dst.model_name << " successfully attached to Entity [Deferred]");
	}
}

void PbrModelCache::SetModel(String name, ComponentMap& m) {
	PbrRenderableRef pbr_rend_comp = m.Get<PbrRenderable>();
	SetModel(name, *pbr_rend_comp);
}

#if 0

bool PbrModelCache::ModelExists(String name) {
	return model_map.Find(name);
}

#endif

void PbrModelCache::Update(double dt) {
	for (PbrRenderable* c : comps) {
		
		// Find any PbrRenderable component which is waiting for a model to be loaded.
		if (!c->model && c->model_name.GetCount() > 0) {
			SetModel(c->model_name, *c);
		}
		
		// Apply any material updates as needed.
		if (c->model) {
			for (uint32 i = 0; i < c->model->GetPrimitiveCount(); ++i) {
				auto& material = c->model->GetPrimitive(i).GetMaterial();
				vec4 cur_clr = material.parameters.Get().base_clr_factor;
				
				if (c->color && i == 0) {
					cur_clr = vec4(*c->color);
				}
				
				cur_clr[3] = (c->alpha_multiplier) ? *c->alpha_multiplier : 1.0f;
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
	TODO //model_map.Clear();
}


NAMESPACE_ECS_END

#endif
