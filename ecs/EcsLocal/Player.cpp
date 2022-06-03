#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN

void PlayerHandComponent::Initialize() {
	
}

void PlayerHandComponent::Uninitialize() {
	
}

bool PlayerHandComponent::IsSource(const HandLocationSource& rhs) const {
	TODO
}

bool PlayerHandComponent::Arg(String key, Object value) {
	if (key == "hand") {
		if ((String)value == "left")
			req_hand = PlayerHandedness::Left;
		else if ((String)value == "right")
			req_hand = PlayerHandedness::Right;
		else
			return false;
	}
	else if (key == "body") {
		EntityStoreRef es = GetEngine().TryGet<EntityStore>();
		if (!es)
			return false;
		EntityRef e = es->FindEntity(value);
		if (e) {
			PlayerBodyComponentRef bc = e->Find<PlayerBodyComponent>();
			if (bc && bc->SetHand(req_hand, AsRefT())) {
				body = bc;
			}
		}
		else {
			LOG("PlayerHandComponent::Arg: could not find entity: " + (String)value);
			return false;
		}
	}
	return true;
}








void PlayerHeadComponent::Initialize() {
	
}

void PlayerHeadComponent::Uninitialize() {
	
}

bool PlayerHeadComponent::Arg(String key, Object value) {
	if (key == "body") {
		EntityStoreRef es = GetEngine().TryGet<EntityStore>();
		if (!es)
			return false;
		EntityRef e = es->FindEntity(value);
		if (e) {
			PlayerBodyComponentRef bc = e->Find<PlayerBodyComponent>();
			if (bc && bc->SetHead(AsRefT())) {
				body = bc;
			}
		}
		else {
			LOG("PlayerHeadComponent::Arg: could not find entity: " + (String)value);
			return false;
		}
	}
	return true;
}







void PlayerBodyComponent::Initialize() {
	Ref<PlayerBodySystem> sys = GetEngine().TryGet<PlayerBodySystem>();
	ASSERT(sys);
	if (sys) sys->Attach(AsRefT());
}

void PlayerBodyComponent::Uninitialize() {
	Ref<PlayerBodySystem> sys = GetEngine().TryGet<PlayerBodySystem>();
	ASSERT(sys);
	if (sys) sys->Detach(AsRefT());
}

bool PlayerBodyComponent::Arg(String key, Object value) {
	if (key == "height")
		height = StrDbl(value);
	
	return true;
}

bool PlayerBodyComponent::SetHand(PlayerHandedness hand, PlayerHandComponentRef comp) {
	if (hand == PlayerHandedness::Left) {
		if (hands[0])
			return false;
		hands[0] = comp;
	}
	else if (hand == PlayerHandedness::Right) {
		if (hands[1])
			return false;
		hands[1] = comp;
	}
	else return false;
	
	return true;
}

bool PlayerBodyComponent::SetHead(PlayerHeadComponentRef head) {
	if (this->head)
		return false;
	this->head = head;
	
	return true;
}






bool PlayerBodySystem::Initialize() {
	
	return true;
}

void PlayerBodySystem::Start() {
	
}

void PlayerBodySystem::Update(double dt) {
	for (PlayerBodyComponentRef& b : bodies) {
		EntityRef e = b->GetEntity();
		TransformRef trans = e->Find<Transform>();
		if (!trans)
			continue;
		
		float eyes_from_height = 0.15; // guesstimate, that height of eyes is 15cm from your total height
		float hand_from_height = 0.4; // guesstimate
		
		vec3 body_feet_pos = trans->position;
		vec3 head_direction(0,0,1);
		vec3 head_pos(0,0,0);
		vec3 head_up(0,1,0);
		
		if (b->head) {
			vec3 head_rel_pos(0, b->height - eyes_from_height, 0);
			head_pos = body_feet_pos + head_rel_pos;
			ASSERT(head_pos[1] > 0.0f);
			
			TransformRef head_trans = b->head->GetEntity()->Find<Transform>();
			if (head_trans) {
				head_trans->position = head_pos;
				
				head_trans->use_lookat = true;
				head_trans->up = b->head->up;
				head_trans->direction = b->head->direction;
				
				head_up = head_trans->up;
				head_direction = head_trans->direction;
			}
		}
		
		for(int i = 0; i < 2; i++) {
			if (b->hands[i]) {
				TransformRef hand_trans = b->hands[i]->GetEntity()->Find<Transform>();
				if (hand_trans) {
					float horz_deg = (i == 1 ? -1 : +1) * 30;
					camera_object(
						head_pos, head_direction, head_up,
						DEG2RAD(-horz_deg), DEG2RAD(-30), 0.3f,
						hand_trans->position, hand_trans->orientation);
				}
			}
		}
		
	}
}

void PlayerBodySystem::Stop() {
	
}

void PlayerBodySystem::Uninitialize() {
	
}

void PlayerBodySystem::RefreshComponentsForSource(const HandLocationSource& source) {
	
	TODO
	
}

void PlayerBodySystem::Attach(PlayerBodyComponentRef h) {
	ArrayFindAdd(bodies, h);
}

void PlayerBodySystem::Detach(PlayerBodyComponentRef h) {
	ArrayRemoveKey(bodies, h);
}


NAMESPACE_ECS_END
