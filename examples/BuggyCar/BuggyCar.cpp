#include "BuggyCar.h"

NAMESPACE_TOPSIDE_BEGIN


INITBLOCK_(Shaders) {
	using namespace TS;
	SoftShaderLibrary::AddShaderClass<BuggyCarVertexShader>(GVar::VERTEX_SHADER, "BuggyCar_vertex");
	SoftShaderLibrary::AddShaderClass<BuggyCarFragmentShader>(GVar::FRAGMENT_SHADER, "BuggyCar_fragment");
	
}


void BuggyWheel::OnAttach() {
	OdeObject::OnAttach();
	
	dQFromAxisAndAngle(orient, 1, 0, 0, M_PI*0.5);	// Set orientation from axis (1i+0j+0k) and it's (angle 90 degrees)
	dMassSetSphere(&mass, 1, radius);				// Set mass function for physics body as sphere
	dMassAdjust(&mass, wmass);						// Set mass for the mass function
	geom = dCreateSphere(0, radius);				// Set 3D geometry for the object as sphere
	
	ModelBuilder mb;
	mb	.AddCylinder(vec3(0, 0, 0), radius, 0.02)
		.SetMaterial(DefaultMaterial());
	loader = mb;
	
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

template <class T>
void BuggyCarStartup(T& state) {
	Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	RenderingSystemRef rend = eng.Get<RenderingSystem>();
	PoolRef models = ents->GetRoot()->GetAddPool("models");
	PoolRef cameras = ents->GetRoot()->GetAddPool("cameras");
	
	
	EntityRef sky = models->Create<StaticSkybox>();
	EntityRef gnd = models->Create<StaticGroundPlanePrefab>();
	
	sky->Get<ModelComponent>()->LoadModel(state);
	gnd->Get<StaticGroundPlane>()->LoadModel(state);
	
	/*EntityRef car = models->Create<BuggyCarPrefab>();
	EntityRef cam = cameras->Create<CameraPrefab>();
	
	Ref<ChaseCam> chaser = cam->Add<ChaseCam>();
	chaser->SetTarget(car->Get<Transform>());
	rend->AddViewable(cam->Get<Viewable>());*/
}





BuggyCarApp::BuggyCarApp() {
	LOG("BuggyCarApp::BuggyCarApp");
}

void BuggyCarApp::Initialize() {
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void BuggyCarApp::Render(Draw& fb) {
	SdlOglStateDraw* od = CastPtr<SdlOglStateDraw>(&fb);
	SdlCpuStateDraw* cd = CastPtr<SdlCpuStateDraw>(&fb);
	ASSERT(od || cd);
	
	if (frame == 0) {
		if (od) {
			SdlOglDataState& state = od->GetState();
			BuggyCarStartup(state);
		}
		else {
			SdlCpuDataState& state = cd->GetState();
			BuggyCarStartup(state);
			
		}
		/*
		String data_dir = ShareDirFile("models");
		String obj_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head.obj");
		String tex_path = AppendFileName(data_dir, "african_head" DIR_SEPS "african_head_diffuse.tga");
		auto& o = state.AddObject();
		if (!state.LoadModel(loader, o, obj_path))
			Panic("Couldn't load model: " + obj_path);
		loader.GetModel()->AddTextureFile(0, TEXTYPE_DIFFUSE, tex_path);
		if (!state.LoadModelTextures(loader, o))
			Panic("Couldn't load model textures: " + obj_path);*/
	}
	
	Size sz = fb.GetPageSize();
	//height = width = std::min(sz.cx, sz.cy);
	width = 1280;
	height = 720;
	
	DrawObj(od ? *(GfxStateDraw*)od : *(GfxStateDraw*)cd, true);
	
	iter++;
	frame++;
	if (ts.Seconds() >= phase_time) {
		iter = 0;
		ts.Reset();
		phase = (phase + 1) % phases;
	}
}

void BuggyCarApp::DrawObj(GfxStateDraw& fb, bool use_texture) {
	ASSERT(fb.HasTarget());
	GfxDataState& state = fb.GetGfxState();
	
	float ratio = (float)height / (float)width;
	float aspect = (float)width / (float)height;
	float f = ts.Seconds() / phase_time;
	float f2 = 1 - fabs(2 * f - 1);
	float angle = f * (2.0 * M_PI);
	float x = cos(angle);
	float y = sin(angle);
	
	float eye_angle = (use_texture ? -1 : +1) * f /** 0.25*/ * M_2PI;
	float eye_x = cos(eye_angle);
	float eye_y = sin(eye_angle);
	float x_mod = 0.2 * eye_x;
	float y_mod = 0.2 * eye_y;
	mat4 perspective {
		vec4{1,		0,	    0,		0},
		vec4{0,		1,	    0,		0},
		vec4{0,		0,	    1,		0},
		vec4{0,		0, -1./5.,		1}
	};
	
	vec3 eye {0.3f * eye_x, 0.3f * eye_y, 1};
	vec3 center {0, 0, -1};
	vec3 up {0, 1, 0};
	mat4 lookat = LookAt(eye, center, up);
	mat4 port;
	
	/*if (phase == 0)
		port = GetViewport((-1 + x_mod) * ratio, -1 + y_mod, (2 - x_mod) * ratio, 2 + y_mod, 1);
	else*/
		port = GetViewport(-1 * ratio, -1, 2 * ratio, 2, 1);
	
	state.view = port * perspective * lookat;
	state.light_dir = vec3 {sin(angle), 0.0, cos(angle)};
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

#if SOFTGL
SIMPLE_ECS_APP_(TS::ECS::BuggyCarApp, "BuggyCarSoft.eon", "FRAGMENT=BuggyCar_fragment;VERTEX=BuggyCar_vertex")
#else
SIMPLE_ECS_APP_(TS::ECS::BuggyCarApp, "BuggyCar.eon", "FRAGMENT=Fragment.glsl;VERTEX=Vertex.glsl")
#endif
