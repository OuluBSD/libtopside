#include "BuggyCar.h"

NAMESPACE_TOPSIDE_BEGIN


void BuggyWheel::OnAttach() {
	OdeObject::OnAttach();
	
	dQFromAxisAndAngle(orient, 1, 0, 0, M_PI*0.5);	// Set orientation from axis (1i+0j+0k) and it's (angle 90 degrees)
	dMassSetSphere(&mass, 1, radius);				// Set mass function for physics body as sphere
	dMassAdjust(&mass, wmass);						// Set mass for the mass function
	geom = dCreateSphere(0, radius);				// Set 3D geometry for the object as sphere
	
	ModelBuilder mb;
	mb	.AddCylinder(vec3(0, 0, 0), radius, 0.02)
		.SetMaterial(DefaultMaterial());
	model = mb;
	
	model_geom = rotate(identity<mat4>(), M_PI_2, vec3(0,0,1));
	
	AttachContent();
}


NAMESPACE_TOPSIDE_END



NAMESPACE_ECS_BEGIN


void BuggyCarInitializer() {
	Engine& eng = GetActiveEngine();
	eng.GetAdd<EntityStore>();
	eng.GetAdd<ComponentStore>();
	eng.GetAdd<PhysicsSystem>();
}

void BuggyCarStartup() {
	Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	PoolRef pool = ents->GetRoot()->GetAddPool("models");
	pool->Create<StaticGroundPlanePrefab>();
	pool->Create<BuggyCarPrefab>();
}


NAMESPACE_ECS_END


NAMESPACE_TOPSIDE_BEGIN

using ObjMap = VectorMap<String,Object>;
MAKE_STATIC(ObjMap, args)

void Runner(String app_name) {
	TODO
	String eon_file;
	DUMP(eon_file);
	DUMPC(args);
	Serial::DebugMain("", eon_file, args, 0);
}


NAMESPACE_TOPSIDE_END


ECS_INITIALIZE_STARTUP_(TS::Ecs::BuggyCarInitializer, TS::Ecs::BuggyCarStartup) \
ECS_APP_MAIN {
	using namespace UPP;
	String eon_file = GetDataFile("BuggyCar.eon");
	if (FileExists(eon_file)) {
		TS::DefaultRunner("Gui App", eon_file);
	}
	else {
		LOG("BuggyCar.eon file not found");
	}
}


NAMESPACE_UPP
INITBLOCK {
	using namespace TS;
	AppFlags& f = GetAppFlags();
	if (1)
		f.gfx = AppFlags::GFX_OPENGL;
	else
		f.gfx = AppFlags::GFX_SW;
	
	f.have_ode_physics = true;
}
END_UPP_NAMESPACE
