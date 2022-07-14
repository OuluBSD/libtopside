#include "Internal.h"


NAMESPACE_SOFTPHYS_BEGIN


Particle::Particle() {
	type = RIGIDBODY_TYPE_PARTICLE;
	friction = 0.95f;
	bounce = 0.7f;
	gravity = vec3(0.0f, -9.82f, 0.0f);

#ifdef EULER_INTEGRATION
	mass = 1.0f;
#endif
}

void Particle::Update(float dt) {
#ifdef EULER_INTEGRATION
	old_position = position;
	vec3 acceleration = forces *InvMass();
	#ifdef ACCURATE_EULER_INTEGRATION
		vec3 oldVelocity = velocity;
		velocity = velocity * friction + acceleration * dt;
		position = position + (oldVelocity + velocity) * 0.5f * dt;
	#else
		velocity = velocity * friction + acceleration * dt;
		position = position + velocity * dt;
	#endif
#else
	vec3 velocity = position - old_position;
	old_position = position;
	float deltaSquare = dt * dt;
	position = position + (velocity * friction + forces * deltaSquare);
#endif
}

void Particle::ApplyForces() {
#ifdef EULER_INTEGRATION
	forces = gravity *mass;
#else
	forces = gravity *mass;
#endif
}

void Particle::SolveConstraints(const Vector<OBB_>& constraints) {
	int size = constraints.GetCount();
	for (int i = 0; i < size; ++i) {
		line3 traveled(old_position, position);
		if (Linetest(constraints[i], traveled)) {
			//if (PointInOBB(position, constraints[i])) {
#ifndef EULER_INTEGRATION
			vec3 velocity = position - old_position;
#endif
			vec3 direction = Normalize(velocity);
			Ray ray(old_position, direction);
			RaycastResult result;

			if (Raycast(constraints[i], ray, &result)) {
				// Place object just a little above collision result
				position = result.point + result.normal * 0.003f;

				vec3 vn = result.normal * Dot(result.normal, velocity);
				vec3 vt = velocity - vn;

#ifdef EULER_INTEGRATION
				old_position = position;
				velocity = vt - vn * bounce;
#else
				old_position = position - (vt - vn * bounce);
#endif
				break;
			}
		}
	}
}

void Particle::SetPosition(const vec3& pos) {
	position = pos;
	old_position = pos;
}

vec3 Particle::GetPosition() {
	return position;
}

void Particle::SetBounce(float b) {
	bounce = b;
}

float Particle::GetBounce() {
	return bounce;
}

void Particle::AddImpulse(const vec3& impulse) {
#ifdef EULER_INTEGRATION
	velocity = velocity + impulse;
#else
	vec3 velocity = position - old_position;
	velocity = velocity + impulse;
	old_position = position - velocity;
#endif
}

float Particle::InvMass() {
	if (mass == 0.0f) { return 0.0f; }
	return 1.0f / mass;
}

void Particle::SetMass(float m) {
	mass = m;
}

vec3 Particle::GetVelocity() {
#ifdef EULER_INTEGRATION
	return velocity;
#else
	return position - old_position;
#endif
}

void Particle::SetFriction(float f) {
	friction = f;
}


NAMESPACE_SOFTPHYS_END
