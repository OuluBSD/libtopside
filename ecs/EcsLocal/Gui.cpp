#include "EcsLocal.h"

NAMESPACE_ECS_BEGIN


#ifdef flagGUI

DefaultGuiAppComponent::DefaultGuiAppComponent() {
	
}

void DefaultGuiAppComponent::Initialize() {
	//if (CommandLine().GetCount() != 1)
	//	Panic("invalid commandline argument");
	
	//wins = GetEngine().Get<WindowSystem>();
	//ASSERT(wins);
	
	
	AddToUpdateList();
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void DefaultGuiAppComponent::Uninitialize() {
	RemoveFromUpdateList();
	Serial::EcsVideoBase::Latest().RemoveBinder(this);
}

void DefaultGuiAppComponent::Update(double dt) {
	
}

void DefaultGuiAppComponent::StateStartup(GfxDataState& state) {
	Engine& eng = GetActiveEngine();
	EntityStoreRef ents = eng.Get<EntityStore>();
	RenderingSystemRef rend = eng.Get<RenderingSystem>();
	PoolRef models = ents->GetRoot()->GetAddPool("models");
	
	//test->Refresh(state);
	
	/*EntityRef sky = models->Create<StaticSkybox>();
	EntityRef gnd = models->Create<DefStaticGroundPlanePrefab>();
	EntityRef car = models->Create<BuggyCarPrefab>();
	
	this->sky = sky->Get<ModelComponent>();
	this->gnd = gnd->Get<DefStaticGroundPlane>();
	this->car = car->Get<BuggyCar>();
	
	//this->sky->LoadModel(state);
	//this->gnd->LoadModel(state);
	this->car->LoadModel(state);
	
	PoolRef cameras = ents->GetRoot()->GetAddPool("cameras");
	EntityRef cam = cameras->Create<CameraPrefab>();
	chaser = cam->Add<ChaseCam>();
	chaser->SetTarget(car->Get<Transform>());
	rend->AddViewable(cam->Get<Viewable>());*/
	TODO
}

bool DefaultGuiAppComponent::Render(Draw& d) {
	
	ProgDraw* pd = CastPtr<ProgDraw>(&d);
	ASSERT(pd);
	if (!pd) {
		return false;
	}
	// loop windowsystem windows and render them
	//ProgDraw& pd = Serial::EcsVideoBase::Latest().GetProgDraw();
	
	/*int win_count = wins->GetCount();
	for(int i = 0; i < win_count; i++) {
		wins->Redraw(i, true);
	}*/
	
	
	
	/*SdlCpuStateDraw* sd = CastPtr<SdlCpuStateDraw>(&fb);
	ASSERT(sd);
	
	SdlOglStateDraw* od = CastPtr<SdlOglStateDraw>(&fb);
	SdlCpuStateDraw* cd = CastPtr<SdlCpuStateDraw>(&fb);
	ASSERT(od || cd);*/
	
	/*if (frame == 0) {
		if (od) {
			SdlOglDataState& state = od->GetState();
			StateStartup(state);
		}
		else {
			SdlCpuDataState& state = cd->GetState();
			StateStartup(state);
		}
	}*/
	
	/*Size sz = fb.GetPageSize();
	//height = width = std::min(sz.cx, sz.cy);
	width = 1280;
	height = 720;
	
	test->Resize(width, height);
	
	GfxDataState& s = od ? (GfxDataState&)od->GetState() : (GfxDataState&)cd->GetState();
	s.dbg_render = true;
	test->Refresh(s);
	
	//fb.DrawRect(sz, Black());
	
	DrawObj(*sd, true);
	
	iter++;
	frame++;
	if (ts.Seconds() >= phase_time) {
		iter = 0;
		ts.Reset();
		phase = (phase + 1) % phases;
	}*/
	
	return true;
}

void DefaultGuiAppComponent::DrawObj(GfxStateDraw& fb, bool use_texture) {
	/*ASSERT(fb.HasTarget());
	SdlCpuDataState& state = fb.GetState();
	
	float ratio = (float)height / (float)width;
	float aspect = (float)width / (float)height;
	float f = ts.Seconds() / phase_time;
	float f2 = 1 - fabs(2 * f - 1);
	float angle = f * (2.0 * M_PI);
	float x = cos(angle);
	float y = sin(angle);
	
	//float eye_angle = (use_texture ? -1 : +1) * f * 0.25 * M_2PI;
	float eye_angle = (use_texture ? -1 : +1) * f * M_2PI;
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
	
	//if (phase == 0)
	//	port = GetViewport((-1 + x_mod) * ratio, -1 + y_mod, (2 - x_mod) * ratio, 2 + y_mod, 1);
	//else
		port = GetViewport(-1 * ratio, -1, 2 * ratio, 2, 1);
	
	state.view = port * perspective * lookat;
	state.light_dir = vec3 {sin(angle), 0.0, cos(angle)};
	*/
	TODO
}

#endif


NAMESPACE_ECS_END
