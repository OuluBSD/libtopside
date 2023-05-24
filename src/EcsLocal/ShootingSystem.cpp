#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


bool ShootingInteractionSystemBase::Initialize() {
	if (!InteractionListener::Initialize(GetEngine(), AsRefT<InteractionListener>()))
		return false;
	
	return true;
}

void ShootingInteractionSystemBase::Uninitialize() {
	InteractionListener::Uninitialize(GetEngine(), AsRefT<InteractionListener>());
}

void ShootingInteractionSystemBase::Attach(ShootingComponentRef c) {
	ArrayFindAdd(comps, c);
	
	// The "barrel_to_ctrl" is to transform from the tip of the barrel to the location of the controller
	const mat4 barrel_to_ctrl = Translate(vec3(0.0f, 0.0675f, 0.0f)) * XRotation(ConvertToRadians(-10));
	
	Ref<Entity> entity = c->GetEntity();
	entity->Get<ShootingComponent>()->barrel_to_ctrl = barrel_to_ctrl;
}

void ShootingInteractionSystemBase::Detach(ShootingComponentRef c) {
	ArrayRemoveKey(comps, c);
}

String ShootingInteractionSystemBase::GetInstructions() const {
	return "Pull the trigger to fire the gun.\n\n"
	       "You can feel controller vibrate for each bullet.\n\n";
}

String ShootingInteractionSystemBase::GetDisplayName() const {
	return "Shooting";
}

EntityRef ShootingInteractionSystemBase::CreateToolSelector() const {
	auto selector = GetPool()->Create<ToolSelectorPrefab>();
	selector->Get<ModelComponent>()->SetPrefabModel("Gun");
	selector->Get<ToolSelectorKey>()->type = GetType();
	return selector;
}

void ShootingInteractionSystemBase::Register() {
	
}

void ShootingInteractionSystemBase::Unregister() {
	
}

void ShootingInteractionSystemBase::Activate(EntityRef entity) {
	entity->Get<ModelComponent>()->SetEnabled(false);
}

void ShootingInteractionSystemBase::Deactivate(EntityRef entity) {
	entity->Get<ModelComponent>()->SetEnabled(true);
}

void ShootingInteractionSystemBase::OnControllerReleased(const CtrlEvent& e) {
	// pass
}

void ShootingInteractionSystemBase::OnControllerPressed(const CtrlEvent& e) {
	
	if (e.type == EVENT_HOLO_PRESSED && e.value == ControllerMatrix::TRIGGER) {
		for (ShootingComponentRef& shooting : comps) {
			if (!shooting->IsEnabled())
				continue;
			EntityRef entity = shooting->GetEntity();
			TransformRef trans = entity->Find<Transform>();
			if (!trans)
				continue;
			
			const mat4 trans_mat = trans->GetMatrix();
			const mat4 barrel_to_world =
				trans_mat * shooting->barrel_to_ctrl
				;
				
			vec3 position = Position(barrel_to_world);
			quat orientation = MatQuat(barrel_to_world);
			vec3 forward = Forward(barrel_to_world);
			forward.Normalize();
			vec3 bullet_velocity = forward * shooting->bullet_speed;
			
			#if 0
			LOG("ShootingInteractionSystemBase::OnControllerPressed: "
				"position: " << position.ToString() << ", "
				"orientation: " << orientation.ToString() << ", "
				"forward: " << forward.ToString() << ", "
				"bullet_velocity: " << bullet_velocity.ToString());
			#endif
			
			// Create bullet and send it on it's merry way
			EntityRef bullet = GetPool()->Create<Bullet>();
			TransformRef bullet_trans = bullet->Get<Transform>();
			RigidBodyRef bullet_rbody = bullet->Get<RigidBody>();
			PhysicsBodyRef bullet_pbody = bullet->Get<PhysicsBody>();
			bullet_trans->data.position = position;
			bullet_trans->data.orientation = orientation;
			bullet_rbody->velocity = bullet_velocity;
			bullet_pbody->BindDefault();
				
			//SendContinuousBuzzForDuration(args.State().Source(), 125_ms);
		}
	}
}

void ShootingInteractionSystemBase::OnControllerUpdated(const CtrlEvent& e) {
	for (ShootingComponentRef& shooting : comps) {
		if (!shooting->IsEnabled()) continue;
		
		EntityRef entity = shooting->GetEntity();
		ModelComponentRef model = entity->Find<ModelComponent>();
		
		// Show the controllers while we're holding grasp, to help show how the model relates to the real world object
		ASSERT(e.ctrl);
		bool should_render_controller = e.ctrl->ctrl[1].IsGrasped();
		model->color[3] = should_render_controller ? 0.25f : 1.0f;
	}
}















void ShootingComponent::Etherize(Ether& e) {
	CustomToolComponent::Etherize(e);
	
	e % bullet_speed
	  % barrel_to_ctrl;
	
}

void ShootingComponent::Initialize() {
	ToolComponentRef tool = GetEntity()->Find<ToolComponent>();
	if (tool)
		tool->AddTool(AsRefT<ComponentBase>());
	
	Ref<ShootingInteractionSystemBase> sys = GetEngine().TryGet<ShootingInteractionSystemBase>();
	if (sys)
		sys-> Attach(AsRefT());
}

void ShootingComponent::Uninitialize() {
	ToolComponentRef tool = GetEntity()->Find<ToolComponent>();
	if (tool)
		tool->RemoveTool(AsRefT<ComponentBase>());
	
	Ref<ShootingInteractionSystemBase> sys = GetEngine().TryGet<ShootingInteractionSystemBase>();
	if (sys)
		sys->Detach(AsRefT());
}

bool ShootingComponent::LoadModel(ModelComponent& mdl) {
	ModelCacheRef sys = GetEngine().GetMachine().Get<ModelCache>();
	if (!sys)
		return false;
	
	String path = KnownModelNames::GetPath(KnownModelNames::Gun);
	ModelRef m = sys->GetAddModelFile(path);
	mdl.SetModelMatrix(YRotation(M_PIf));
	mdl.SetModel(m);
	
	if (0) {
		Ref<ModelComponent> m = GetEntity()->Find<ModelComponent>();
		ASSERT(m);
		if (m) {
			m->SetRotation(ConvertToRadians(180), ConvertToRadians(70), 0.0f);
			m->SetTranslation(vec3(0, 0.05f, 0.0f));
		}
	}
	
	return true;
}


NAMESPACE_ECS_END
