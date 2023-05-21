#include "Edit3D.h"


#define IMAGECLASS ImagesImg
#define IMAGEFILE <Edit3D/Images.iml>
#include <Draw/iml_source.h>



NAMESPACE_TOPSIDE_BEGIN




Edit3D::Edit3D() :
	v0(this),
	v1(this),
	v_rdbg(this)
{
	state.prj = &prj;
	anim.state = &state;
	video.anim = &anim;
	
	anim.WhenSceneEnd << THISBACK(OnSceneEnd);
	
	Sizeable().MaximizeBox();
	Title("Edit3D");
	
	SetView(VIEW_GEOMPROJECT);
	Add(v0.hsplit.SizePos());
	
	AddFrame(menu);
	menu.Set([this](Bar& bar) {
		bar.Sub(t_("File"), [this](Bar& bar) {
			bar.Add(t_("Exit"), THISBACK(Exit));
		});
		bar.Sub(t_("View"), [this](Bar& bar) {
			bar.Add(t_("Geometry"), THISBACK1(SetView, VIEW_GEOMPROJECT)).Key(K_ALT|K_1);
			bar.Add(t_("Video import"), THISBACK1(SetView, VIEW_VIDEOIMPORT)).Key(K_ALT|K_2);
			bar.Add(t_("Remote debug"), THISBACK1(SetView, VIEW_REMOTE_DEBUG)).Key(K_ALT|K_3);
		});
		
	});
	
	AddFrame(tool);
	RefrehToolbar();
	
	
	tc.Set(-1000/60, THISBACK(Update));
	
}

void Edit3D::SetView(ViewType view) {
	
	if (this->view == VIEW_GEOMPROJECT)
		RemoveChild(&v0.hsplit);
	else if (this->view == VIEW_VIDEOIMPORT)
		RemoveChild(&v1);
	else if (this->view == VIEW_REMOTE_DEBUG)
		RemoveChild(&v_rdbg);
	
	this->view = view;
	
	if (this->view == VIEW_GEOMPROJECT)
		Add(v0.hsplit.SizePos());
	else if (this->view == VIEW_VIDEOIMPORT)
		Add(v1.SizePos());
	else if (this->view == VIEW_REMOTE_DEBUG)
		Add(v_rdbg.SizePos());
	
}

void Edit3D::RefrehToolbar() {
	tool.Set(THISBACK(Toolbar));
}

void Edit3D::Toolbar(Bar& bar) {
	bar.Add(true,  t_("Stop"),  ImagesImg::Stop(),  THISBACK(Stop)).Key(K_F6);
	
	if (anim.is_playing)
		bar.Add(true, t_("Pause"), ImagesImg::Pause(), THISBACK(Pause)).Key(K_F5);
	else
		bar.Add(true,  t_("Play"),  ImagesImg::Play(),  THISBACK(Play)).Key(K_F5);
	
}

GeomScene& Edit3D::GetActiveScene() {
	return state.GetActiveScene();
}

void Edit3D::Exit() {
	Close();
}

void Edit3D::RefreshData() {
	PostCallback(THISBACK(Data));
}

void Edit3D::Stop() {
	anim.Reset();
	RefrehToolbar();
}

void Edit3D::Pause() {
	anim.Pause();
	RefrehToolbar();
}

void Edit3D::Play() {
	anim.Play();
	RefrehToolbar();
}

void Edit3D::OnSceneEnd() {
	RefrehToolbar();
}

void Edit3D::RefrehRenderers() {
	if (view == VIEW_GEOMPROJECT) {
		for(int i = 0; i < 4; i++)
			v0.rends[i].Refresh();
	}
	else if (view == VIEW_VIDEOIMPORT) {
		v1.RefreshRenderers();
	}
}

void Edit3D::Update() {
	double dt = ts.Seconds();
	ts.Reset();
	
	if (view == VIEW_GEOMPROJECT)
		v0.Update(dt);
	else if (view == VIEW_VIDEOIMPORT)
		v1.Update(dt);
}

void Edit3D::Data() {
	if (view == VIEW_GEOMPROJECT)
		v0.Data();
}

void Edit3D::CreateDefaultInit() {
	
	// Cler project
	prj.Clear();
	
	// Add scene
	GeomScene& scene = prj.AddScene();
	
	
}

void Edit3D::CreateDefaultPostInit() {
	GeomScene& scene = prj.GetScene(0);
	GeomObject* cam = scene.FindCamera("camera");
	
	if (cam) {
		GeomKeypoint& kp = cam->timeline.keypoints.Get(0);
		state.program.position = kp.position;
		state.program.orientation = kp.orientation;
	}
	else {
		state.program.position = vec3(0,0,0);
		state.program.orientation = Identity<quat>();
	}
	
	state.active_scene = 0;
	
	Data();
	v0.TimelineData();
	v0.tree.OpenDeep(v0.tree_scenes);
}

void Edit3D::LoadEmptyProject() {
	CreateDefaultInit();
	CreateDefaultPostInit();
	
}

void Edit3D::LoadTestCirclingCube() {
	GeomScene& scene = prj.GetScene(0);
	GeomObject& cam = scene.GetAddCamera("camera");
	GeomObject& mdl = scene.GetAddModel("some model");
	
	ModelBuilder mb;
	mb.AddBox(0, 1, 1);
	
	mdl.mdl = mb.Detach();
	
	scene.length = prj.kps * 4 + 1;
	float step = M_PI * 2 / 4;
	float angle = 0;
	float cam_radius = 2;
	for(int i = 0; i < 5; i++) {
		GeomKeypoint& kp = cam.timeline.GetAddKeypoint(i * prj.kps);
		kp.position = vec3(sin(angle), 0, cos(angle)) * cam_radius;
		kp.orientation = AxesQuat(angle, 0, 0);
		angle += step;
	}
}

void Edit3D::LoadTestOctree() {
	GeomScene& scene = prj.GetScene(0);
	GeomObject& cam = scene.GetAddCamera("camera");
	
	// Create octree
	GeomObject& omodel = scene.GetAddOctree("octree");
	Octree& o = omodel.octree.octree;
	o.Initialize(-3, 8); // 1 << 6 = 32x32x32 meters
	
	// Create points in form of sphere
	float radius = 100;
	bool random_points = 1;
	int points = 256;
	for(int i = 0; i < points; i++) {
		float yaw, pitch;
		if (random_points) {
			yaw = Randomf() * M_PI * 2;
			float f = (Randomf() * 2 - 1);
			pitch = f * (M_PI / 2);
		}
		else {
			float f = ((float)i / (float)points);
			yaw = f * M_PI * 2;
			pitch = 0;//fmodf(f * M_PI * 40, M_PI) - M_PI/2;
		}
		
		vec3 pos = AxesDir(yaw, pitch) * radius;
		OctreeNode* n = o.GetAddNode(pos, -3);
		Pointcloud::Point& p = n->Add<Pointcloud::Point>();
		p.SetPosition(pos);
		//LOG(pos.ToString() + ": " + HexStr(n));
	}
	
	// Move camera linearly around sphere
	int seconds = 3;
	scene.length = prj.kps * seconds;
	int kp_step = 3;
	float step = M_PI * 2 / (scene.length / kp_step - 1);
	float angle = 0;
	float cam_radius = radius + 2;
	for(int i = 0; i < scene.length; i += kp_step) {
		GeomKeypoint& kp = cam.timeline.GetAddKeypoint(i);
		kp.position = vec3(sin(angle), 0, cos(angle)) * cam_radius;
		kp.orientation = AxesQuat(angle, 0, 0);
		angle += step;
	}

}

void Edit3D::LoadTestProject(int test_i) {
	CreateDefaultInit();
	
	switch (test_i) {
		case 0: LoadTestCirclingCube(); break;
		case 1: LoadTestOctree(); break;
		default: break;
	}
	
	CreateDefaultPostInit();
}

void Edit3D::LoadWmrStereoPointcloud(String directory) {
	video.SetWmrCamera();
	video.LoadDirectory(directory, 30);
	Data();
	v0.TimelineData();
	v0.tree.OpenDeep(v0.tree_scenes);
	
	SetView(VIEW_VIDEOIMPORT);
}

void Edit3D::LoadRemote(EditClientService* svc, bool debug) {
	this->svc = svc;
	this->debug_remote = debug;
	
	if (svc) {
		svc->sync.SetTarget(prj, state, anim, video);
	}
	
	if (debug_remote) {
		svc->SetDebuggingMode();
		
		LoadEmptyProject();
		SetView(VIEW_REMOTE_DEBUG);
	}
	else
		LoadTestProject(0);
	
	svc->edit = this;
	svc->sync.SetRequireAllSync();
	svc->SetReady();
}

void Edit3D::OnDebugMetadata() {
	
	TODO
	
}



EditConfiguration::EditConfiguration() {
	background_clr = Color(43, 44, 46);
	
	
}



NAMESPACE_TOPSIDE_END







