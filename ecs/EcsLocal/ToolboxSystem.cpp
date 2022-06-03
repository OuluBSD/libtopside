#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


struct ToolComponentPrefab : EntityPrefab<Transform, ModelComponent, PlayerHandComponent, ToolComponent> {};
struct TextDisplay : EntityPrefab<Transform, TextRenderable> {};


static const String instruction_txt = "Press the menu button to bring interaction objects toward you.\n\n_grasp (grasp button) an interaction object to use it.";


bool HitTest(vec3 positionA, vec3 positionB, float diameter) {
	auto distance = (positionA - positionB).GetLength();
	return distance < diameter;
}


bool ToolboxSystemBase::Initialize() {
	return true;
}

void ToolboxSystemBase::Uninitialize() {
	entities.Clear();
}

void ToolboxSystemBase::AddToolSystem(ToolSystemBaseRef system) {
	system->Register(entities);
	selector_objects.GetAdd(system->GetType()) = system->CreateToolSelector();
	selectors.GetAdd(system->GetType()) = system;
	
	for (auto& context : ctrls) {
		SwitchToolType(context.ctrl, system->GetType());
	}
}

void ToolboxSystemBase::RemoveToolSystem(ToolSystemBaseRef system) {
	selectors.RemoveKey(system->GetType());
	selector_objects.RemoveKey(system->GetType());
	system->Unregister();
}

void ToolboxSystemBase::Start() {
	auto es = GetEngine().Get<EntityStore>();
	
	for (size_t i = 0; i < ctrls.GetCount(); ++i) {
		const ControllerHand hand = static_cast<ControllerHand>(i);
		ctrls[i].hand = hand;
		EntityRef& e = ctrls[i].ctrl;
		e = es->GetRoot()->Create<ToolComponentPrefab>();
		ASSERT(e);
		entities.Add(e);
	}
	
	instruction_text = es->GetRoot()->Create<TextDisplay>();
	instruction_text->Get<TextRenderable>()->text = instruction_txt;
	instruction_text->Get<Transform>()->position = { 0, 1.5f, -5.f };
	instruction_text->Get<Transform>()->size = vec3{ 2.0f };
	
	ctrls[Left].dbg_txt = es->GetRoot()->Create<TextDisplay>();
	ctrls[Left].dbg_txt->Get<Transform>()->position = { -2.5, 1.25f, -4.f };
	ctrls[Left].dbg_txt->Get<Transform>()->orientation = make_quat_from_axis_angle({ 0, 1, 0 }, M_PI * 0.15f);
	ctrls[Left].dbg_txt->Get<Transform>()->size = vec3{ 2.0f };
	ctrls[Left].dbg_txt->Get<TextRenderable>()->font_size = 52.0f;
	
	ctrls[Right].dbg_txt = es->GetRoot()->Create<TextDisplay>();
	ctrls[Right].dbg_txt->Get<Transform>()->position = { 2.5, 1.25f, -4.f };
	ctrls[Right].dbg_txt->Get<Transform>()->orientation = make_quat_from_axis_angle({ 0, 1, 0 }, -M_PI * 0.15f);
	ctrls[Right].dbg_txt->Get<Transform>()->size = vec3{ 2.0f };
	ctrls[Right].dbg_txt->Get<TextRenderable>()->font_size = 52.0f;
	
}

void ToolboxSystemBase::Stop() {
	
}

void ToolboxSystemBase::Update(double dt) {
	static const int fps_sz = 32;
	static float fps[fps_sz] = {};
	static uint32 curr_fps = 0;
	fps[curr_fps++] = dt;
	curr_fps %= fps_sz;
	const float avg_dt = std::accumulate(std::begin(fps), std::end(fps), 0.0f) / fps_sz;
	instruction_text->Get<TextRenderable>()->text =
	        IntStr(static_cast<int>(std::round(1.0f / avg_dt))) + " FPS\n\n" + instruction_txt;
	        
	if (!show_toolbox) {
		{
			int i = 0;
			
			for (auto& selector : selector_objects) {
				const float offset = (i - floorf(selector_objects.GetCount() / 2.f)) / selector_objects.GetCount();
				selector->Get<Easing>()->target_position = vec3{ offset, 1.25f, -5.f };
				++i;
			}
		}
		
		// Update the debug text for each Controller based on the currently selected tool
		for (size_t i = 0; i < ctrls.GetCount(); ++i) {
			String displayed_text = String(ControllerHandToString(ctrls[i].hand)) + ": ";
			
			if (auto tool = ctrls[i].ctrl->Get<ToolComponent>()) {
				displayed_text += tool->title + "\n\n" + tool->description;
			}
			
			ctrls[i].dbg_txt->Get<TextRenderable>()->text = displayed_text;
		}
	}
	else {
		for (size_t i = 0; i < ctrls.GetCount(); ++i) {
			String displayed_text = String(ControllerHandToString(ctrls[i].hand)) + " switch to: ";
			const vec3 ctrl_position = ctrls[i].ctrl->Get<Transform>()->position;
			TODO
#if 0
			
			for (auto[transform, selector] : GetEngine().Get<EntityStore>()->GetComponents<Transform, ToolSelectorKey>()) {
				if (HitTest(ctrl_position, transform->position, 0.15f)) {
					auto it = selectors.find(selector->type);
					
					if (it != selectors.end()) {
						displayed_text += it->second->GetDisplayName();
						displayed_text += "\n\n";
						displayed_text += it->second->GetInstructions();
					}
				}
			}
			
#endif
			ctrls[i].dbg_txt->Get<TextRenderable>()->text = displayed_text;
		}
	}
}

String ToolboxSystemBase::ControllerHandToString(ControllerHand hand) {
	return hand == Left ? "Left" : "Right";
}

void ToolboxSystemBase::SwitchToolType(EntityRef entity, const TypeId& new_type) {
	ToolComponentRef tool = entity->Get<ToolComponent>();
	{
		// Disable old tool
		auto it = selectors.Find(tool->tool_type);
		
		if (it) {
			it()->Deactivate(entity);
		}
	}
	{
		// Enable new tool
		auto it = selectors.Find(new_type);
		
		if (it) {
			ToolSystemBase& c = *it();
			c.Activate(entity);
			tool->tool_type = c.GetType();
			tool->description = c.GetInstructions();
			tool->title = c.GetDisplayName();
		}
	}
}


NAMESPACE_ECS_END