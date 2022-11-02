#include "Internal.h"


NAMESPACE_SOFTPHYS_BEGIN


PhysicsSystem::PhysicsSystem() {
	lin_proj_perc = 0.45f;
	penet_slack = 0.01f;
	impulse_iter = 5;

	do_lin_proj = true;
	rend_rand_clr = false;

	colliders1.Reserve(100);
	colliders2.Reserve(100);
	results.Reserve(100);
}

void PhysicsSystem::Collide(Space& space, void* data, NearCallback cb) {
	ASSERT(VectorFind(spaces, &space) >= 0);
	colliders1.Clear();
	colliders2.Clear();
	results.Clear();

	{
		// Find objects whom are colliding
		// First, build a list of colliding objects
		CollisionManifold result;
		for (Geometry* b0 : space.geoms) {
			for (Geometry* b1 : space.geoms) {
				if (b0 == b1)
					break;
				cb(data, b0, b1);
			}
		}
	}
}

#if 0
void PhysicsSystem::asdf() {
	ResetCollisionManifold(&result);
	if (bodies[i]->HasVolume() && bodies[j]->HasVolume()) {
		RigidbodyVolume* m1 = (RigidbodyVolume*)bodies[i];
		RigidbodyVolume* m2 = (RigidbodyVolume*)bodies[j];
		result = FindCollisionFeatures(*m1, *m2);
	}
	if (result.colliding) {
#if 0 
		bool isDuplicate = false;
		for (int k = 0, kSize = colliders1.GetCount(); k < kSize; ++k) {
			if (colliders1[k] == bodies[i] || colliders1[k] == bodies[j]) {
				if (colliders2[k] == bodies[i] || colliders2[k] == bodies[j]) {
					isDuplicate = true;
					break;
				}
			}
		}

		if (!isDuplicate) {
			for (int k = 0, kSize = colliders2.GetCount(); k < kSize; ++k) {
				if (colliders2[k] == bodies[i] || colliders2[k] == bodies[j]) {
					if (colliders1[k] == bodies[i] || colliders1[k] == bodies[j]) {
						isDuplicate = true;
						break;
					}
				}
			}
		}
		if (!isDuplicate)
#endif

		{
			colliders1.Add(bodies[i]);
			colliders2.Add(bodies[j]);
			results.Add(result);
		}
	}
}
#endif

void PhysicsSystem::Update(float dt) {

	// Calculate foces acting on the object
	for (Space* s : spaces)
		for(Geometry* g : s->geoms)
			g->ApplyForces();

	// Same as above, calculate forces acting on cloths
	for (Cloth* c : cloths)
		c->ApplyForces();
	

	// Apply impulses to resolve collisions
	for (int k = 0; k < impulse_iter; ++k) { // Apply impulses
		for (int i = 0, size = results.GetCount(); i < size; ++i) {
			for (int j = 0, jSize = results[i].contacts.GetCount(); j < jSize; ++j) {
				if (colliders1[i]->HasVolume() && colliders2[i]->HasVolume()) {
					RigidbodyVolume* m1 = (RigidbodyVolume*)colliders1[i];
					RigidbodyVolume* m2 = (RigidbodyVolume*)colliders2[i];
					ApplyImpulse(*m1, *m2, results[i], j);
				}
			}
		}
	}

	// Integrate velocity and impulse of objects
	for (Space* s : spaces)
		for(Geometry* g : s->geoms)
			g->Update(dt);
	
	// Same as above, integrate velocity and impulse of cloths
	for (Cloth* c : cloths)
		c->Update(dt);
	
	// Correct position to avoid sinking!
	if (do_lin_proj) {
		for (int i = 0, size = results.GetCount(); i < size; ++i) {
			if (!colliders1[i]->HasVolume() && !colliders2[i]->HasVolume()) {
				continue;
			}

			RigidbodyVolume* m1 = (RigidbodyVolume*)colliders1[i];
			RigidbodyVolume* m2 = (RigidbodyVolume*)colliders2[i];
			float totalMass = m1->InvMass() + m2->InvMass();

			if (totalMass == 0.0f) {
				continue;
			}

			float depth = fmaxf(results[i].depth - penet_slack, 0.0f);
			float scalar = (totalMass == 0.0f) ? 0.0f : depth / totalMass;
			vec3 correction = results[i].normal * scalar * lin_proj_perc;

			m1->position = m1->position - correction * m1->InvMass();
			m2->position = m2->position + correction * m2->InvMass();

			m1->SynchCollisionVolumes();
			m2->SynchCollisionVolumes();
		}
	}

	// Apply spring forces
	for (Spring& s : springs)
		s.ApplyForce(dt);

	// Same as above, apply spring forces for cloths
	for (Cloth* c : cloths)
		c->ApplySpringForces(dt);
	
	// Solve constraints
	for (Space* s : spaces)
		for(Geometry* g : s->geoms)
			g->SolveConstraints(constraints);
	
	// Same as above, solve cloth constraints
	for (Cloth* c : cloths)
		c->SolveConstraints(constraints);
	
}

void PhysicsSystem::AddSpace(Space& space) {
	spaces.Add(&space);
}

/*void PhysicsSystem::AddRigidbody(Geometry* body) {
	bodies.Add(body);
}*/

void PhysicsSystem::AddConstraint(const OBB_& obb) {
	constraints.Add(obb);
}

/*void PhysicsSystem::ClearRigidbodys() {
	geoms.Clear();
}*/

void PhysicsSystem::ClearConstraints() {
	constraints.Clear();
}

void PhysicsSystem::AddSpring(const Spring& spring) {
	springs.Add(spring);
}

void PhysicsSystem::ClearSprings() {
	springs.Clear();
}

void PhysicsSystem::AddCloth(Cloth* cloth) {
	cloths.Add(cloth);
}

void PhysicsSystem::ClearCloths() {
	cloths.Clear();
}



NAMESPACE_SOFTPHYS_END
