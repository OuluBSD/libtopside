#include "Physics.h"



NAMESPACE_OULU_BEGIN


void OdeObject::Paint(Shader& s) {
	
	
	if (is_override_phys_geom) {
		s.SetMat4("model", override_geom * model_geom);
	}
	else {
		dVector3 pos;
		dGeomCopyPosition (geom, pos);
		vec3 v3 = MakeVec3(pos);
		mat4 trans = translate(identity<mat4>(), v3);
		
		dQuaternion result;
		dGeomGetQuaternion (geom, result);
		quat q;
		q[3] = result[0];
		q[0] = result[1];
		q[1] = result[2];
		q[2] = result[3];
		mat4 rot = ToMat4(q);
		
		s.SetMat4("model", trans * rot * model_geom);
	}
	
	
	s.Paint(*model.GetModel());
}





PhysicsSystem* OdeNode::GetWorld() {
	OdeNode* n = this;
	while (n->portal)
		n = n->portal;
	return dynamic_cast<PhysicsSystem*>(n);
}

OdeSpace* OdeNode::GetSpace() {
	OdeNode* n = this;
	while (n) {
		OdeSpace* s = dynamic_cast<OdeSpace*>(n);
		if (s)
			return s;
		n = n->portal;
	}
	return NULL;
}

dWorldID OdeNode::GetWorldId() {
	return GetWorld()->GetWorldId();
}

dSpaceID OdeNode::GetWorldSpaceId() {
	return GetWorld()->GetSpaceId();
}








void OdeObject::AttachContent() {
	ASSERT(geom != 0);
	ASSERT(body != 0);
	dBodySetMass(body, &mass);						// Set mass of the physics body
	dGeomSetBody(geom, body);						// Set physics body of a geometry
	dBodySetQuaternion(body, orient);				// Set orientation of a physics body
	
	
	//LOG(ToString());
	
	
	dSpaceID space = GetSpace()->GetSpaceId();
	dSpaceAdd(space, geom);
}

void OdeObject::DetachContent() {
	ASSERT(geom != 0);
	ASSERT(body != 0);
	dSpaceRemove(GetSpace()->GetSpaceId(), geom);
}











vec3 PhysicsSystem::EarthGravity = {0, -9.81, 0};

void PhysicsSystem::NearCallback(void *, dGeomID o1, dGeomID o2) {
	
	// only collide things with the ground
	/*int g1 = (o1 == ground.geom || o1 == ground_box.geom);
	int g2 = (o2 == ground.geom || o2 == ground_box.geom);
	if (!(g1 ^ g2)) return;*/

	const int N = 10;
	dContact contact[N];
	int n = dCollide(o1, o2, N, &contact[0].geom, sizeof(dContact));
	if (n > 0) {
		for (int i = 0; i < n; i++) {
			contact[i].surface.mode = dContactSlip1 | dContactSlip2 | dContactSoftERP | dContactSoftCFM | dContactApprox1;
			contact[i].surface.mu = dInfinity;
			contact[i].surface.slip1 = 0.1;
			contact[i].surface.slip2 = 0.1;
			contact[i].surface.soft_erp = 0.5;
			contact[i].surface.soft_cfm = 0.3;
			dJointID c = dJointCreateContact(world,contactgroup,&contact[i]);
			dJointAttach(c,
						 dGeomGetBody(contact[i].geom.g1),
						 dGeomGetBody(contact[i].geom.g2));
		}
	}
}

void AddMachinePhysicsSystem() {
	GetMachine().Add<PhysicsSystem>();
}




NAMESPACE_OULU_END


#ifdef flagAUTOSTART_SYSTEMS
NAMESPACE_UPP

INITBLOCK(PhysicsSystem) {
	Oulu::Machine::WhenStarting << callback(Oulu::AddMachinePhysicsSystem);
}

END_UPP_NAMESPACE
#endif
