#include "AccelCore.h"

#if 0

NAMESPACE_TOPSIDE_BEGIN




AccelComponentGroup::AccelComponentGroup() {
	
}

bool AccelComponentGroup::Open() {
	int dbg_i = 0;
	for(AccelComponentRef& comp : comps) {
		if (!comp->IsOpen() && !comp->Open()) {
			DLOG("AccelComponentGroup::Open: error: a component did not open properly (comp #" + IntStr(dbg_i) + ")");
			return false;
		}
		++dbg_i;
	}
	return true;
}

void AccelComponentGroup::Close() {
	for(AccelComponentRef& comp : comps) {
		comp->Close();
		comp->AsRef<ComponentBase>()->Destroy();
	}
}

void AccelComponentGroup::CloseTemporary() {
	for(AccelComponentRef& comp : comps) {
		if (comp->IsTypeTemporary()) {
			comp->Close();
			comp->AsRef<ComponentBase>()->Destroy();
		}
	}
}

void AccelComponentGroup::Clear() {
	Close();
	#if HAVE_OPENGL
	Ogl_ClearPipeline();
	#endif
	comps.Clear();
	gl_stages.Clear();
}

void AccelComponentGroup::FindComponents() {
	comps.Clear();
	ASSERT(GetParent());
	EntityRef e = GetParent()->GetEntity();
	for (ComponentRef& comp : e->GetComponents().GetValues()) {
		if (comp) {
			ComponentBase& base = *comp;
			AccelComponent* fcomp = CastPtr<AccelComponent>(&base);
			if (fcomp) {
				TypeCls comp_ctx = base.GetValSpecType();
				if (group_classes.Find(comp_ctx)) {
					ASSERT(!fcomp->ctx);
					fcomp->ctx = AsRefT();
					comps.Add(fcomp->AsRefT());
				}
			}
		}
	}
}

void AccelComponentGroup::UpdateCompFlags() {
	bool any_has_fbo = HasContext<DisplayContext>();
	int comp_i = 0;
	int comp_count = comps.GetCount();
	for (AccelComponentRef& comp : comps) {
		bool is_last = comp_i == comp_count-1;
		
		comp->has_fbo = is_last && any_has_fbo;
		
		++comp_i;
	}
}

AccelComponentRef AccelComponentGroup::GetComponentById(int id) const {
	ASSERT(id >= 0);
	for (const auto& s : comps)
		if (s->id == id)
			return s;
	THROW(Exc("AccelComponent not found"));
}

void AccelComponentGroup::FindUniqueInputs(AcceleratorHeaderVector& v) {
	for (auto& comp : comps)
		for(AcceleratorHeader& in : comp->in)
			if (/*in.IsTypeComponentSource() &&*/ v.Find(in) < 0)
				v.Add(in);
}

bool AccelComponentGroup::LoadExisting(TypeCls type, ObjectMap& st_map, int stage_i, String frag_code) {
	static const char* fn_name = "AccelComponentGroup::LoadExisting";
	for (auto& comp : comps) {
		if (comp->GetTypeId() == type) {
			if (!comp->Load(st_map, stage_i, frag_code)) {
				GetParent()->OnError(fn_name, "Loading stage " + IntStr(stage_i) + " failed");
				return false;
			}
			return true;
		}
	}
	return false;
}

void AccelComponentGroup::ConnectInputs(AcceleratorHeaderVector& v) {
	for (auto& comp : comps) {
		for(AcceleratorHeader& in : comp->in) {
			if (in.IsTypeComponentSource()) {
				int i = v.Find(in);
				ASSERT(i >= 0);
				AcceleratorHeader& found = v.in[i];
				ASSERT(in.GetId() < 0);
				in.CopyIdStream(found);
				ASSERT(in.GetId() >= 0);
			}
		}
	}
}

void AccelComponentGroup::UpdateBuffers() {
	for(auto& comp : comps)
		comp->UpdateTexBuffers();
}

bool AccelComponentGroup::CheckInputTextures() {
#if HAVE_OPENGL
	for(auto& comp : comps)
		if (!comp->Ogl_CheckInputTextures())
			return false;
#endif
	return true;
}

void AccelComponentGroup::CreatePackets() {
	if (comps.IsEmpty())
		return;
	
	ASSERT(!expts.IsEmpty());
	ASSERT(GetParent()->is_open);
	
	for(auto& comp : comps)
		comp->PreProcess();
	
	// Accelerator cannot store buffered packets:
	// - 'cost' of storing packets is infinity
	//   --> processing of packets must happen in edge-in (when sink gets packet)
	for(AccelComponentRef& comp : comps)
		{ASSERT(comp->IsEmptyStream());}
	for(AccelComponentRef& comp : comps)
		comp->ClearStream();
	
	TODO // use default System::Update(double dt) instead
	
	
	/*int i = 0;
	for(AccelComponentRef& comp : comps) {
		adfgwdfgsdfg
		
#if HAVE_OPENGL
		Ogl_ProcessStage(*comp, gl_stages[i]);
#endif
		++i;
	}*/
	
	for(AccelComponentRef& comp : comps)
		comp->PostProcess();
	
	TODO //create packets
}

bool AccelComponentGroup::IsLast(const AccelComponent* comp) const {
	return comps.GetCount() && comps.Top() == comp;
}





NAMESPACE_TOPSIDE_END
