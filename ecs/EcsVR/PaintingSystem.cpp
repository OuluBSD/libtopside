#include "EcsVR.h"

NAMESPACE_ECS_BEGIN



void PaintingInteractionSystemHolo::Update(double dt) {
	// probably not PaintingInteractionSystemBase::Update(dt);
	TODO
	
	for (auto& enabled_entity : GetEnabledEntities()) {
		auto entity		= enabled_entity.Get<EntityRef>();
		auto paint		= enabled_entity.Get<PaintComponentRef>();
		
		MotionControllerComponentRef controller = entity->Get<MotionControllerComponent>();
		paint->beam->Get<PbrRenderable>()->SetEnabled(paint->cur_state == PaintComponent::State::Manipulating);
		// Set properties required for rendering
		paint->touchpad_indicator->Get<PbrRenderable>()->SetEnabled(paint->cur_state == PaintComponent::State::ColorSelection);
		
		for (auto& go : paint->clr_pick_objects) {
			go->Get<PbrRenderable>()->SetEnabled(paint->cur_state == PaintComponent::State::ColorSelection);
		}
		
		const bool show_controller = paint->cur_state == PaintComponent::State::Manipulating;
		entity->Get<PbrRenderable>()->SetEnabled(show_controller);
		paint->paint_brush->Get<PbrRenderable>()->SetEnabled(!show_controller);
		
		if (auto location = controller->location) {
			const vec3 position = location->GetPosition();
			const quat orientation = location->GetOrientation();
			const vec4 paint_tip_color = paint->cur_state == PaintComponent::State::ColorSelection ? SelectColor(paint->touchpad_x, paint->touchpad_y) : paint->selected_color;
			paint->paint_brush->Get<PbrRenderable>()->color = paint_tip_color;
			
			if (paint->cur_state == PaintComponent::State::Manipulating) {
				// Update the paint strokes based on the change in location
				if (paint->prev_manip_loc) {
					const vec3 previous_position = paint->prev_manip_loc->GetPosition();
					const quat previous_orientation = paint->prev_manip_loc->GetOrientation();
					const quat orientation_delta = orientation * inverse(previous_orientation);
					const mat4 manipulation_transform = translate(-previous_position) * rotate(orientation_delta) * translate(position);
					
					for (auto stroke : paint->strokes) {
						stroke->Get<Transform>()->SetFromMatrix(stroke->Get<Transform>()->GetMatrix() * manipulation_transform);
					}
				}
				
				paint->prev_manip_loc = location;
				// Move the paint strokes based on manipulation changes
				constexpr double ThumbstickMovementThresholdPercent = 0.2f; // Deadzone to prevent slight thumbstick movement
				constexpr float MovementSpeedInMetersPerSecond = 2.5f;
				
				if (const auto& pointer_pose = location->GetSourcePointerPose()) {
					const vec3 position = pointer_pose->GetPosition();
					const vec3 forward = pointer_pose->GetForwardDirection();
					
					if (abs(paint->thumbstick_y) > ThumbstickMovementThresholdPercent) {
						const vec3 forward_movement = forward * paint->thumbstick_y * MovementSpeedInMetersPerSecond * dt;
						
						// Move all paintings along beam path
						for (auto& stroke : paint->strokes) {
							stroke->Get<Transform>()->position += forward_movement;
						}
					}
					
					paint->beam->Get<Transform>()->position =
					        position +
					        forward * (paint->beam->Get<Transform>()->size[2] * 0.5f);
					paint->beam->Get<Transform>()->orientation = pointer_pose->GetOrientation();
				}
			}
			else if (paint->cur_state == PaintComponent::State::ColorSelection) {
				constexpr float colorpicker_diameter = 0.025f;
				constexpr float colorpicker_height = 0.015f;
				const mat4 paint_brush_to_world = paint->paint_brush->Get<Transform>()->GetMatrix();
				const vec3 touchpad_indicator_on_paint_brush = { paint->touchpad_x * colorpicker_diameter, colorpicker_height, paint->touchpad_y* colorpicker_diameter * -1 };
				const vec3 touchpad_indicator_in_world = transform(touchpad_indicator_on_paint_brush, paint_brush_to_world);
				paint->touchpad_indicator->Get<Transform>()->position = touchpad_indicator_in_world;
				// Color picker plane defined as slightly above the touchpad with the same orientation as the touchpad
				const int num_colors = static_cast<int>(paint->clr_pick_objects.GetCount());
				auto iter = paint->clr_pick_objects.begin();
				
				for (int i = 0; i < num_colors; ++i, ++iter) {
					const float angle = (static_cast<float>(i * -1 - 1) / static_cast<float>(num_colors)) * (2 * M_PI) - M_PI;
					const float next_angle = (static_cast<float>((i + 1) * -1 - 1) / static_cast<float>(num_colors)) * (2 * M_PI) - M_PI;
					const float angle_delta = (next_angle - angle) / 2; // Want color icon to appear in the middle of the segment, not the start.
					const float final_angle = angle - angle_delta;
					const vec3 color_indicator_on_paint_brush = { std::cos(final_angle)* colorpicker_diameter, colorpicker_height, std::sin(final_angle)* colorpicker_diameter };
					const vec3 color_indicator_in_world = transform(color_indicator_on_paint_brush, paint_brush_to_world);
					iter()->Get<Transform>()->position = color_indicator_in_world;
				}
			}
		}
	}
}

void PaintingInteractionSystemHolo::Register(const LinkedList<EntityRef>& entities) {
	PaintingInteractionSystemBase::Register(entities);
	
	TODO // add MotionControllerComponent to new entities (see PaintBrush)
	// note: duplicate PaintingInteractionSystemBase::Register
	
	ToolSys::Register(entities);
	auto es = GetEngine().Get<EntityStore>();
	
	for (auto& entity : m_entities) {
		const auto& selected_color = colors[0];
		auto paint_brush = es->GetRoot()->Create<PaintBrush>();
		paint_brush->Get<PbrRenderable>()->color = selected_color;
		paint_brush->Get<MotionControllerComponent>()->req_hand = entity->Get<MotionControllerComponent>()->req_hand;
		auto touchpad_indicator = es->GetRoot()->Create<StaticSphere>();
		touchpad_indicator->Get<Transform>()->size = { 0.005f, 0.005f, 0.005f };
		touchpad_indicator->Get<PbrRenderable>()->color = Colors::Gray;
		PaintComponentRef paint = entity->Get<PaintComponent>();
		paint->selected_color = selected_color;
		paint->paint_brush = paint_brush;
		paint->touchpad_indicator = touchpad_indicator;
		
		for (auto color : colors) {
			auto color_picker = es->GetRoot()->Create<StaticSphere>();
			color_picker->Get<Transform>()->size = { 0.01f, 0.01f, 0.01f };
			color_picker->Get<PbrRenderable>()->color = color;
			paint->clr_pick_objects.Add(color_picker);
		}
		
		paint->beam = es->GetRoot()->Create<StaticCube>();
		paint->beam->Get<Transform>()->size = { 0.005f, 0.005f, 10.0f };
		paint->beam->Get<PbrRenderable>()->color = Colors::Aquamarine;
		paint->SetEnabled(false);
	}
	
	GetEngine().Get<SpatialInteractionSystem>()->AddListener(AsRefT<SpatialInteractionListener>());
	
}


NAMESPACE_ECS_END
