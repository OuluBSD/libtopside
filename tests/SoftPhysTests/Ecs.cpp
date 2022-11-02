#include "SoftPhysTests.h"

NAMESPACE_ECS_BEGIN


INITBLOCK_(EcsShaders) {
	using namespace TS;
	SoftShaderLibrary::AddShaderClass<LocalVertexShader>(GVar::VERTEX_SHADER, "softphystest_vertex");
	SoftShaderLibrary::AddShaderClass<LocalFragmentShader>(GVar::FRAGMENT_SHADER, "softphystest_fragment");
	
}



LocalApp::LocalApp() {
	
}

void LocalApp::Initialize() {
	if (CommandLine().GetCount() != 1)
		Panic("invalid commandline argument");
	
	int test_i = StrInt(CommandLine()[0]);
	
	if      (test_i == 0)	test = new ParticleTest();
	else if (test_i == 1)	test = new ManyTest();
	else if (test_i == 2)	test = new ClothTest();
	else Panic("invalid commandline argument");
	
	test->Initialize();
	
	AddToUpdateList();
	Serial::EcsVideoBase::Latest().AddBinder(this);
}

void LocalApp::Uninitialize() {
	RemoveFromUpdateList();
	Serial::EcsVideoBase::Latest().RemoveBinder(this);
}

void LocalApp::Update(double dt) {
	test->Update(dt);
}

void LocalApp::StateStartup(GfxDataState& state) {
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
}

void LocalApp::Render(Draw& fb) {
	SdlCpuStateDraw* sd = CastPtr<SdlCpuStateDraw>(&fb);
	ASSERT(sd);
	
	SdlOglStateDraw* od = CastPtr<SdlOglStateDraw>(&fb);
	SdlCpuStateDraw* cd = CastPtr<SdlCpuStateDraw>(&fb);
	ASSERT(od || cd);
	
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
	
	Size sz = fb.GetPageSize();
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
	}
}

void LocalApp::DrawObj(SdlCpuStateDraw& fb, bool use_texture) {
	ASSERT(fb.HasTarget());
	SdlCpuDataState& state = fb.GetState();
	
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

void LocalVertexShader::Process(SdlCpuVertexShaderArgs& a) {
	int width = a.generic->iResolution[0];
	int height = a.generic->iResolution[1];
	vec4 pos = a.v.position.Splice().Embed();
	pos[2] = -pos[2] + 2; // hack
	vec4 screen = a.va->view * pos;
	screen.Project();
	a.v.position[0] = (int)((screen[0] + 1.0) * width  / 2.0);
	a.v.position[1] = (int)((screen[1] + 1.0) * height / 2.0);
	a.v.position[2] = screen[2];
	a.v.position[3] = 1.0f;
	//ASSERT(a.v.position[2] >= 0.0f);
}

void LocalFragmentShader::Process(SdlCpuFragmentShaderArgs& args) {
	#if 0
	float w = args.generic->iResolution[0];
	float h = args.generic->iResolution[1];
	float x = args.frag_coord[0] / w;
	float y = args.frag_coord[1] / h;
	args.frag_color_out = vec4(x, y, 0, 1);
	#endif
	
	ASSERT(args.fa);
	vec3& n = args.normal;
	vec3& light_dir = args.fa->light_dir;
	float m = Dot(n, light_dir);
	
	vec4& used_clr = args.frag_color_out;
	used_clr[3] = 0;
	
	float intensity = std::max(0.0f, m);
	
	intensity = intensity * 0.5 + 0.5;
	
	auto& diffuse = args.tex_img[TEXTYPE_DIFFUSE];
	if (diffuse) {
		Texture& tex = diffuse->GetGeomTex();
		float tex_x = args.tex_coord[0];
		float tex_y = args.tex_coord[1];
		ASSERT(tex_x >= 0.0f && tex_x <= 1.0f);
		ASSERT(tex_y >= 0.0f && tex_y <= 1.0f);
		int tex_xi = tex_x * tex.GetWidth();
		int tex_yi = tex_y * tex.GetHeight();
		tex_xi = std::max(0, std::min(tex.GetWidth() - 1, tex_xi));
		tex_yi = std::max(0, std::min(tex.GetHeight() - 1, tex_yi));
		const byte* b = tex.GetIter(tex_xi, tex_yi);
		ASSERT(intensity <= 1.0f);
		float mul = intensity / 255.0;
		float R = b[0] * mul;
		float G = b[1] * mul;
		float B = b[2] * mul;
		ASSERT(R >= 0.0f && R <= 1.0f);
		ASSERT(G >= 0.0f && G <= 1.0f);
		ASSERT(B >= 0.0f && B <= 1.0f);
		used_clr[0] = B;
		used_clr[1] = G;
		used_clr[2] = R;
	}
	else {
		used_clr[0] = intensity;
		used_clr[1] = intensity;
		used_clr[2] = intensity;
	}
}

NAMESPACE_ECS_END


SIMPLE_ECS_APP_(TS::ECS::LocalApp, "geom_tutorial_base.eon", "FRAGMENT=softphystest_fragment;VERTEX=softphystest_vertex;DRAWMEM=false")


