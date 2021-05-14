#include "EcsLib.h"

#ifdef flagVR

NAMESPACE_OULU_BEGIN


struct MotionControllerPrefab :
	EntityPrefab<Transform, PbrRenderable, MotionControllerComponent, ToolComponent>
{};

struct TextDisplay : EntityPrefab<Transform, TextRenderable>
{};

static const String instruction_txt = "Press the menu button to bring interaction objects toward you.\n\n_grasp (grasp button) an interaction object to use it.";



bool HitTest(vec3 positionA, vec3 positionB, float diameter) {
	auto distance = (positionA - positionB).GetLength();
	return distance < diameter;
}






void ToolboxSystem::Uninitialize() {
	entities.Clear();
}


void ToolboxSystem::AddToolSystem(ToolSystemBaseRef system) {
	system->Register(entities);
	selector_objects.GetAdd(system->GetType()) = system->CreateToolSelector();
	selectors.GetAdd(system->GetType()) = system;
	
	for (auto& context : ctrls) {
		SwitchToolType(context.ctrl, system->GetType());
	}
}

void ToolboxSystem::RemoveToolSystem(ToolSystemBaseRef system) {
	selectors.RemoveKey(system->GetType());
	selector_objects.RemoveKey(system->GetType());
	system->Unregister();
}

void ToolboxSystem::Start() {
	auto es = GetMachine().Get<EntityStore>();
	
	for (size_t i = 0; i < ctrls.GetCount(); ++i) {
		const ControllerHand hand = static_cast<ControllerHand>(i);
		ctrls[i].hand = hand;
		ctrls[i].ctrl = es->GetRoot()->Create<MotionControllerPrefab>();
		ctrls[i].ctrl->Get<MotionControllerComponent>()->req_hand = ControllerHandToHandedness(hand);
		ctrls[i].ctrl->Get<MotionControllerComponent>()->attach_ctrl_model = true;
		entities.Add(ctrls[i].ctrl);
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
	GetMachine().Get<SpatialInteractionSystem>()->AddListener(AsRef<ISpatialInteractionListener>());
}

void ToolboxSystem::Stop() {
	GetMachine().Get<SpatialInteractionSystem>()->RemoveListener(AsRef<ISpatialInteractionListener>());
}

void ToolboxSystem::Update(double dt) {
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
			
			for (auto[transform, selector] : GetMachine().Get<EntityStore>()->GetComponents<Transform, ToolSelectorKey>()) {
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


void ToolboxSystem::OnSourcePressed(const SpatialInteractionSourceEventArgs& args) {
	if (args.State().Source().Kind() != SpatialInteractionSourceKind::Controller)
		return;
		
	auto ctrl = FindController(args.State().Source());
	
	if (!ctrl)
		return;
		
	// Bring the toolbox in front of user
	if (args.PressKind() == SpatialInteractionPressKind::Menu) {
		show_toolbox = !show_toolbox;
		
		if (show_toolbox) {
			auto holo_scene = GetMachine().Get<HolographicScene>();
			
			if (SpatialPointerPose pointer_pose = SpatialPointerPose::TryGetAtTimestamp(holo_scene->WorldCoordinateSystem(), holo_scene->CurrentTimestamp())) {
				const vec3 head_position = pointer_pose.Head().Position();
				const vec3 forward = pointer_pose.Head().ForwardDirection();
				const vec3 head_up = pointer_pose.Head().UpDirection();
				const vec3 head_direction = normalize(vec3{ forward[0], 0.0f, forward[2] });
				vec3 head_right = cross(head_direction, head_up);
				head_right[1] = 0;
				head_right = normalize(head_right);
				const vec3 toolkit_center = head_direction * 0.5f;
				{
					int i = 0;
					
					for (auto& selector : this->selector_objects) {
						const float offset = (i - floorf(this->selector_objects.GetCount() / 2.f)) / this->selector_objects.GetCount();
						const vec3 target_position = toolkit_center + head_position + head_right * offset + vec3{ 0, -0.3f, 0 };
						selector->Get<Easing>()->target_position = target_position;
						++i;
					}
				}
			}
		}
	}
	else if (args.PressKind() == SpatialInteractionPressKind::Grasp && this->show_toolbox) {
		if (const SpatialInteractionSourceLocation& location = ctrl->Get<MotionControllerComponent>()->location) {
			if (!location.pos.IsNull()) {
				const vec3 position = location.pos;
				TODO
#if 0
				
				for (auto[transform, selector] : GetMachine().Get<EntityStore>()->GetComponents<Transform, ToolSelectorKey>()) {
					if (HitTest(position, transform->position, 0.15f)) {
						SwitchToolType(*ctrl, selector->type);
						this->show_toolbox = false;
						break;
					}
				}
				
#endif
			}
		}
	}
}

String ToolboxSystem::ControllerHandToString(ControllerHand hand) {
	return hand == Left ? "Left" : "Right";
}

SpatialInteractionSourceHandedness ToolboxSystem::ControllerHandToHandedness(ControllerHand hand) {
	return hand == Left ? SpatialInteractionSourceHandedness::Left : SpatialInteractionSourceHandedness::Right;
}

void ToolboxSystem::SwitchToolType(EntityRef entity, const TypeId& new_type) {
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

EntityRef ToolboxSystem::FindController(const SpatialInteractionSource& source) {
	for (auto& context : ctrls) {
		if (context.ctrl->Get<MotionControllerComponent>()->IsSource(source)) {
			return context.ctrl;
		}
	}
	
	return EntityRef();
}


NAMESPACE_OULU_END

#endif
