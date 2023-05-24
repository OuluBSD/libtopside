#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


struct ToolComponentPrefab : EntityPrefab<Transform, ModelComponent, PlayerHandComponent, ToolComponent> {};
struct TextDisplay : EntityPrefab<Transform, TextRenderable> {};


static const String instruction_txt = "Press the menu button to bring interaction objects toward you.\n\n_grasp (grasp button) an interaction object to use it.";


bool HitTest(vec3 positionA, vec3 positionB, float diameter) {
	auto distance = (positionA - positionB).GetLength();
	return distance < diameter;
}





void ToolComponent::Etherize(Ether& e) {
	e % title
	  % description;
	
	TODO // tools: make refs & tool_type TypeCId
}

void ToolComponent::Initialize() {
	ToolboxSystemBaseRef sys = GetEngine().TryGet<ToolboxSystemBase>();
	if (sys)
		sys->Attach(AsRefT());
}

void ToolComponent::Uninitialize() {
	ToolboxSystemBaseRef sys = GetEngine().TryGet<ToolboxSystemBase>();
	if (sys)
		sys->Detach(AsRefT());
}

bool ToolComponent::Arg(String key, Object value) {
	if (key == "hand") {
		String path = value;
		EntityStoreRef es = GetEngine().Get<EntityStore>();
		EntityRef hand_ent = es->FindEntity(path);
		if (!hand_ent) {
			LOG("ToolComponent::Arg: error: could not find entity with path: " << path);
			return false;
		}
		this->active_hand = hand_ent->Find<PlayerHandComponent>();
		if (!this->active_hand) {
			LOG("ToolComponent::Arg: error: entity does not have PlayerHandComponent: " << path);
			return false;
		}
	}
	return true;
}

void ToolComponent::SwitchOff() {
	if (active_tool) {
		active_tool->SetEnabled(false);
		active_tool.Clear();
		RefreshModel();
	}
}

void ToolComponent::SwitchNext() {
	if (tools.IsEmpty())
		return;
	
	if (tools.GetCount() == 1 && tools[0] == active_tool)
		return;
	
	int idx = -1;
	if (active_tool.IsEmpty())
		idx = 0;
	else {
		int i = 0;
		for (CustomToolComponentRef& cb : tools) {
			if (cb == active_tool) {
				idx = i;
				break;
			}
			i++;
		}
		SwitchOff();
	}
	
	idx = (idx + 1) % tools.GetCount();
	
	active_tool = tools[idx];
	active_tool->SetEnabled(true);
	RefreshModel();
}

void ToolComponent::AddTool(CustomToolComponentRef cb) {
	ArrayFindAdd(tools, cb);
	
	if (!active_tool) {
		active_tool = cb;
		active_tool->SetEnabled(true);
		RefreshModel();
	}
	else
		cb->SetEnabled(false);
}

void ToolComponent::RemoveTool(CustomToolComponentRef cb) {
	if (active_tool == cb) {
		if (tools.GetCount() > 1)
			SwitchNext();
		else
			SwitchOff();
	}
	
	ArrayRemoveKey(tools, cb);
	
}

void ToolComponent::RefreshModel() {
	ModelComponentRef mdl = GetEntity()->Find<ModelComponent>();
	if (mdl) {
		if (active_tool) {
			active_tool->LoadModel(*mdl);
		}
		else {
			mdl->Clear();
		}
	}
}








bool ToolboxSystemBase::Initialize() {
	if (!InteractionListener::Initialize(GetEngine(), AsRefT<InteractionListener>()))
		return false;
	
	return true;
}

void ToolboxSystemBase::Uninitialize() {
	InteractionListener::Uninitialize(GetEngine(), AsRefT<InteractionListener>());
	
}

bool ToolboxSystemBase::Arg(String key, Object value) {
	if (key == "test.tool.changer")
		test_tool_changer = value.ToString() == "true";
	return true;
}

void ToolboxSystemBase::Attach(ToolComponentRef tool) {
	ArrayFindAdd(tools, tool);
}

void ToolboxSystemBase::Detach(ToolComponentRef tool) {
	ArrayRemoveKey(tools, tool);
}

void ToolboxSystemBase::AddToolSystem(ToolSystemBaseRef system) {
	#if 0
	selector_objects.GetAdd(system->GetType()) = system->CreateToolSelector();
	#endif
	selectors.GetAdd(system->GetType()) = system;
	
}

void ToolboxSystemBase::RemoveToolSystem(ToolSystemBaseRef system) {
	selectors.RemoveKey(system->GetType());
	#if 0
	selector_objects.RemoveKey(system->GetType());
	#endif
}

void ToolboxSystemBase::Start() {
	auto es = GetEngine().Get<EntityStore>();
	
	#if 0
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
	ctrls[Left].dbg_txt->Get<Transform>()->orientation = AxisAngleQuat({ 0, 1, 0 }, M_PI * 0.15f);
	ctrls[Left].dbg_txt->Get<Transform>()->size = vec3{ 2.0f };
	ctrls[Left].dbg_txt->Get<TextRenderable>()->font_size = 52.0f;
	
	ctrls[Right].dbg_txt = es->GetRoot()->Create<TextDisplay>();
	ctrls[Right].dbg_txt->Get<Transform>()->position = { 2.5, 1.25f, -4.f };
	ctrls[Right].dbg_txt->Get<Transform>()->orientation = AxisAngleQuat({ 0, 1, 0 }, -M_PI * 0.15f);
	ctrls[Right].dbg_txt->Get<Transform>()->size = vec3{ 2.0f };
	ctrls[Right].dbg_txt->Get<TextRenderable>()->font_size = 52.0f;
	#endif
}

void ToolboxSystemBase::Stop() {
	
}

void ToolboxSystemBase::OnControllerPressed(const CtrlEvent& e) {
	
#if 0
	if (args.State().Source().Kind() != SpatialInteractionSourceKind::Controller)
		return;
		
	auto ctrl = FindController(args.State().Source());
	
	if (!ctrl)
		return;
		
	// Bring the toolbox in front of user
	if (args.PressKind() == SpatialInteractionPressKind::Menu) {
		show_toolbox = !show_toolbox;
		
		if (show_toolbox) {
			auto holo_scene = GetEngine().Get<HolographicScene>();
			
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
				
				for (auto[transform, selector] : GetEngine().Get<EntityStore>()->GetComponents<Transform, ToolSelectorKey>()) {
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
#endif


	if (e.type == EVENT_HOLO_PRESSED && e.value == ControllerMatrix::SQUEEZE) {
		if (test_tool_changer) {
			for (ToolComponentRef& tool : tools)
				tool->SwitchNext();
		}
	}
}

void ToolboxSystemBase::Update(double dt) {
	
	for (ToolComponentRef& tool : tools) {
		if (tool->active_hand) {
			TransformRef trans = tool->GetEntity()->Find<Transform>();
			TransformRef hand_trans = tool->active_hand->GetEntity()->Find<Transform>();
			if (trans && hand_trans) {
				// Very simple offset
				*trans = *hand_trans;
				
				// add offset between hand and tool
				#if 0
				mat4 orig_pos = Translate(trans->data.position);
				mat4 rel_pos = Translate(VEC_FWD * 0.1);
				mat4 orient = QuatMat(trans->data.orientation);
				mat4 new_pos = orig_pos * (orient * rel_pos);
				vec3 pos = new_pos.GetTranslation();
				trans->data.position = pos;
				#endif
				
				//trans->position += hand_trans->direction * 0.2;
			}
		}
	}
	
	if (!show_toolbox) {
		{
			int i = 0;
			
			for (auto& selector : selector_objects) {
				const float offset = (i - floorf(selector_objects.GetCount() / 2.f)) / selector_objects.GetCount();
				selector->Get<Easing>()->target_position = vec3{ offset, 1.25f, -5.f };
				++i;
			}
		}
		
	}
	else {
#if 0
		for (size_t i = 0; i < ctrls.GetCount(); ++i) {
			String displayed_text = String(ControllerHandToString(ctrls[i].hand)) + " switch to: ";
			const vec3 ctrl_position = ctrls[i].ctrl->Get<Transform>()->position;
			TODO
			
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
			
			ctrls[i].dbg_txt->Get<TextRenderable>()->text = displayed_text;
		}
#endif
	}
}

void ToolboxSystemBase::SwitchToolType(EntityRef entity, const TypeId& new_type) {
	ToolComponentRef tool = entity->Get<ToolComponent>();
	
	TODO
	#if 0
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
	#endif
}


NAMESPACE_ECS_END
