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
	eng.GetAdd<RenderingSystem>();
	eng.GetAdd<EntityStore>();
	eng.GetAdd<ComponentStore>();
	eng.GetAdd<OdeSystem>();
	eng.GetAdd<EventSystem>();
	
	Serial::Machine& mach = Serial::GetActiveMachine();
	//eng.GetAdd<PhysicsSystem>();
}

void BuggyCarStartup() {
	Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	RenderingSystemRef rend = eng.Get<RenderingSystem>();
	PoolRef models = ents->GetRoot()->GetAddPool("models");
	PoolRef cameras = ents->GetRoot()->GetAddPool("cameras");
	EntityRef gnd = models->Create<StaticGroundPlanePrefab>();
	EntityRef car = models->Create<BuggyCarPrefab>();
	EntityRef cam = cameras->Create<CameraPrefab>();
	
	Ref<ChaseCam> chaser = cam->Add<ChaseCam>();
	chaser->SetTarget(car->Get<Transform>());
	rend->AddViewable(cam->Get<Viewable>());
}


NAMESPACE_ECS_END


/*NAMESPACE_TOPSIDE_BEGIN

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



APP_INITIALIZE_DEFAULT_INTERNAL_EON
ECS_INITIALIZE_STARTUP_(TS::Ecs::BuggyCarInitializer, TS::Ecs::BuggyCarStartup)
APP_STARTUP_(TS::BindEcsToSerial)
ECS_APP_MAIN {
	using namespace UPP;
	String eon_file  = GetDataFile("BuggyCar.eon");
	String frag_file = GetDataFile("Fragment.glsl");
	String vtx_file  = GetDataFile("Vertex.glsl");
	if (FileExists(eon_file) && FileExists(frag_file) && FileExists(vtx_file)) {
		args.GetAdd("FRAGMENT_SHADER_PATH", frag_file);
		args.GetAdd("VERTEX_SHADER_PATH", vtx_file);
		TS::DefaultRunner("Gui App", eon_file, &args);
	}
	else {
		LOG("All files were not found");
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
END_UPP_NAMESPACE*/

//APP_INITIALIZE_DEFAULT_INTERNAL_EON
SIMPLE_ECS_APP_(TS::ECS::BuggyCar, "BuggyCar.eon", "FRAGMENT=Fragment.glsl;VERTEX=Vertex.glsl")
