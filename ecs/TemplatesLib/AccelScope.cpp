#include "TemplatesLib.h"

NAMESPACE_TOPSIDE_BEGIN

const char* AccelComponentBase::names[VAR_COUNT+1] = {
	#define ACCEL_VAR(v, n) n,
	ACCEL_VAR_LIST
	#undef ACCEL_VAR
	0
};

void AccelComponentBase::ClearTex() {TODO}





template <>
bool ScopeDevLibT<AccelSpec>::DevComponent::Load(ObjectMap& st_map, int stage_i, String frag_code) {
	TODO
}


template <>
bool ScopeDevLibT<AccelSpec>::ContextComponent::Load(Object& json) {
	using DevSpec = AccelSpec;
	
	DLOG("DevContextComponent::Load begin");
	const char* fn_name = "Load";
	if (!json.IsMap()) {
		OnError(fn_name, "invalid json");
		return false;
	}
	
	Index<String> dirs;
	dirs.Add( ShareDirFile("imgs") );
	dirs.Add( ShareDirFile("sounds") );
	dirs.Add( ShareDirFile("videos") );
	
	ObjectMap& map = json.GetMap();
	
	String name = map.GetAdd("name", "unnamed").ToString();
	String description = map.GetAdd("description", "").ToString();
	DLOG("DevContextComponent::Load: name='" << name << "'");
	
	Object& stages = map.GetAdd("stages", ObjectArray());
	if (!stages.IsArray()) {
		OnError(fn_name, "no stages in");
		return false;
	}
	ObjectArray& st_arr = stages.GetArray();
	for(int i = 0; i < st_arr.GetCount(); i++) {
		Object& st_el = st_arr.Get(i);
		if (!st_el.IsMap()) {
			OnError(fn_name, "unexpected element in stages");
			return false;
		}
		
		ObjectMap& st_map = st_el.GetMap();
		
		String frag_code;
		Object& outputs = st_map.GetAdd("outputs", ObjectArray());
		if (outputs.IsArray()) {
			ObjectArray& out_arr = outputs.GetArray();
			for(int i = 0; i < out_arr.GetCount(); i++) {
				Object& out_el = out_arr.Get(i);
				if (!out_el.IsMap())
					continue;
				ObjectMap& out_map = out_el.GetMap();
				int j = out_map.Find("id");
				if (j >= 0) {
					int id = (int)out_map.GetObject(j).ToInt();
					frag_code = map.GetAdd(IntStr(id)).ToString();
				}
			}
		}
		
		String type_str = st_map.TryGet("type", "").ToString();
		
		if (type_str == "imagebuf" && st_arr.GetCount() == 1)
			type_str = "image";
		
		if (type_str == "library") {
			common_source.Add(frag_code);
		}
		else {
			TypeCls type = DevComponent::GetTypeFromString(type_str);
			if (type == AsVoidTypeCls()) {
				OnError(fn_name, "Invalid type string '" + type_str + "'");
				return false;
			}
			
			if (DevComponent::IsDevPipeComponent(type)) {
				DevComponentGroup* group = 0;
				ASSERT(groups.GetCount());
				
				// Find group
				if (0)
					;
				#define PIPECOMP(ValSpec) typename ScopeValDevLibT<VD<DevSpec,ValSpec>>::PipeComponent
				#define IFACE(x) \
					else if (type == AsTypeCls<PIPECOMP(x##Spec)>()) \
						group = &GetAddGroupContext<x##Spec>(); \
					else if (type == AsTypeCls<typename ScopeConvDevLibT<x##Spec,DevSpec,CenterSpec>::ConvertComponent>()) \
						group = &GetAddGroupContext<x##Spec>(); \
					else if (type == AsTypeCls<typename ScopeConvDevLibT<x##Spec,CenterSpec,DevSpec>::ConvertComponent>()) \
						group = &GetAddGroupContext<x##Spec>();
				IFACE_LIST
				#undef IFACE
				if (!group) {
					OnError(fn_name, "No group exists for type '" + type_str + "'");
					return false;
				}
				
				// Create new comp
				RefT_Entity<DevComponent> comp;
				if (0)
					;
				#define IFACE(x) \
					else if (type == AsTypeCls<PIPECOMP(x##Spec)>()) \
						comp = AddEntityComponent<PIPECOMP(x##Spec)>(*group);
					//else if (type == AsTypeCls<Dev##x##ConvertComponent>()) comp = AddEntityComponent<Dev##x##ConvertComponent>(*group); \
					//else if (type == AsTypeCls<x##DevConvertComponent>()) comp = AddEntityComponent<x##DevConvertComponent>(*group);
				IFACE_LIST
				#undef IFACE
				
				if (!comp)
					return false;
				
				if (!comp->Load(st_map, i, frag_code)) {
					ComponentBaseRef cb = comp->template AsRef<ComponentBase>();
					EntityRef e = cb->ComponentBase::GetEntity();
					e->Destroy();
					OnError(fn_name, "Loading stage " + IntStr(i) + " failed");
					return false;
				}
				
				//for(DevComponentConf& in : comp->in) {ASSERT(in.GetId() < 0 || in.GetType() == DevComponentConf::TYPE_BUFFER);}
			}
			else {
				// Find existing component
				bool found = false;
				for (auto& group : groups)
					if ((found = group.LoadExisting(type, st_map, i, frag_code)))
						break;
				if (!found) {
					OnError(fn_name, "did not find existing component for persistent type '" + type_str + "'");
					return false;
				}
			}
		}
	}
	
	// Find unique inputs
	DevComponentConfVector v;
	for (DevComponentGroup& g : groups)
		g.FindUniqueInputs(v);
	
	
	if (v.in.GetCount()) {
		// Create components for unique inputs
		if (!CreateComponents(v))
			return false;
		
		// Connect created components for inputs
		DumpEntityComponents();
		for (auto& group : groups)
			group.ConnectInputs(v);
		
		// Connect inputs
		if (!ConnectComponentInputs())
			return false;
		
	}
	
	// Connect outputs
	if (!ConnectComponentOutputs())
		return false;
	
	DLOG("DevContextComponent::Load end");
	return true;
}


NAMESPACE_TOPSIDE_END
