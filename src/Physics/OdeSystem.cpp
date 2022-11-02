#include "Physics.h"

#ifdef flagODE

NAMESPACE_TOPSIDE_BEGIN






Ecs::OdeSystem* OdeNode::GetWorld() {
	OdeNode* n = this;
	while (n->owner)
		n = n->owner;
	return CastPtr<Ecs::OdeSystem>(n);
}

OdeSpace* OdeNode::GetSpace() {
	OdeNode* n = this;
	while (n) {
		OdeSpace* s = CastPtr<OdeSpace>(n);
		if (s)
			return s;
		n = n->owner;
	}
	return NULL;
}

dWorldID OdeNode::GetWorldId() {
	return GetWorld()->GetWorldId();
}

dSpaceID OdeNode::GetWorldSpaceId() {
	return GetWorld()->GetSpaceId();
}







OdeObject::OdeObject() {
	
}

OdeObject::~OdeObject() {
	if (geom) dGeomDestroy(geom);
	if (body) dBodyDestroy(body);
}

void OdeObject::LoadModel(GfxDataState& s) {
	TODO
	
}

void OdeObject::AttachContent() {
	ASSERT(geom != 0);
	ASSERT(body != 0);
	dBodySetMass(body, &mass);						// Set mass of the physics body
	dGeomSetBody(geom, body);						// Set physics body of a geometry
	dBodySetQuaternion(body, orient);				// Set orientation of a physics body
	
	dSpaceID space = GetSpace()->GetSpaceId();
	dSpaceAdd(space, geom);
}

void OdeObject::DetachContent() {
	ASSERT(geom != 0);
	ASSERT(body != 0);
	dSpaceRemove(GetSpace()->GetSpaceId(), geom);
}

void OdeObject::Refresh() {
	
	ASSERT(fb_obj);
	if (!fb_obj)
		return;
	
	if (is_override_phys_geom) {
		mat4 v = override_geom * model_geom;
		fb_obj->Set(v, identity<mat4>());
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
		
		mat4 v = trans * rot * model_geom;
		fb_obj->Set(v, identity<mat4>());
	}
}

void OdeObject::LoadModel(CpuDataState& state) {
	auto& o = cpu_obj ? *cpu_obj : state.AddObject();
	cpu_obj = cpu_obj ? cpu_obj : &o;
	fb_obj = cpu_obj;
	if (!state.LoadModel(loader, o))
		Panic("Couldn't load model: ModelComponent");
	if (!state.LoadModelTextures(loader, o))
		Panic("Couldn't load model textures: ModelComponent");
}

void OdeObject::LoadModel(OglDataState& state) {
	auto& o = ogl_obj ? *ogl_obj : state.AddObject();
	ogl_obj = ogl_obj ? ogl_obj : &o;
	fb_obj = ogl_obj;
	if (!state.LoadModel(loader, o))
		Panic("Couldn't load model: ModelComponent");
	if (!state.LoadModelTextures(loader, o))
		Panic("Couldn't load model textures: ModelComponent");
}





NAMESPACE_TOPSIDE_END






NAMESPACE_ECS_BEGIN


vec3 OdeSystem::EarthGravity = {0, -9.81, 0};

void OdeSystem::NearCallback(void *, dGeomID o1, dGeomID o2) {
	
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

void AddEngineOdeSystem() {
	GetActiveEngine().Add<OdeSystem>();
}



NAMESPACE_ECS_END









#ifdef flagAUTOSTART_SYSTEMS
NAMESPACE_UPP

INITBLOCK_(OdeSystem) {
	TS::Engine::WhenInitialize << callback(TS::AddEngineOdeSystem);
}

END_UPP_NAMESPACE
#endif
#endif
