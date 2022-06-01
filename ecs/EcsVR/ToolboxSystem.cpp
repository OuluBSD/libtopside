#include "EcsVR.h"

#if 1

NAMESPACE_ECS_BEGIN


/*struct MotionControllerPrefab :
	EntityPrefab<Transform, PbrRenderable, MotionControllerComponent, ToolComponent>
{};*/







void ToolboxSystem::Start() {
	ToolboxSystemBase::Start();
	
	for (size_t i = 0; i < ctrls.GetCount(); ++i) {
		const ControllerHand hand = static_cast<ControllerHand>(i);
		TODO // add MotionControllerComponent to ctrl
		/*ctrls[i].ctrl = es->GetRoot()->Create<MotionControllerPrefab>();
		ctrls[i].ctrl->Get<MotionControllerComponent>()->req_hand = ControllerHandToHandedness(hand);
		ctrls[i].ctrl->Get<MotionControllerComponent>()->attach_ctrl_model = true;*/
	}
	
	GetEngine().Get<SpatialInteractionSystem>()->AddListener(AsRefT<SpatialInteractionListener>());
}

void ToolboxSystem::Stop() {
	ToolboxSystemBase::Stop();
	TODO //GetEngine().Get<SpatialInteractionSystem>()->RemoveListener(AsRef<ISpatialInteractionListener>());
}

void ToolboxSystem::OnSourcePressed(const SpatialInteractionSourceEventArgs& args) {
	TODO
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
}

SpatialInteractionSourceHandedness ToolboxSystem::ControllerHandToHandedness(ControllerHand hand) {
	return hand == Left ? SpatialInteractionSourceHandedness::Left : SpatialInteractionSourceHandedness::Right;
}

EntityRef ToolboxSystemBase::FindController(const SpatialInteractionSource& source) {
	for (auto& context : ctrls) {
		TODO /*if (context.ctrl->Get<MotionControllerComponent>()->IsSource(source)) {
			return context.ctrl;
		}*/
	}
	
	return EntityRef();
}


NAMESPACE_ECS_END

#endif
