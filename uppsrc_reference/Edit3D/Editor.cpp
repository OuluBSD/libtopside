#include "Edit3D.h"


#define IMAGECLASS ImagesImg
#define IMAGEFILE <Edit3D/Images.iml>
#include <Draw/iml_source.h>



NAMESPACE_TOPSIDE_BEGIN




Edit3D::Edit3D() {
	state.prj = &prj;
	anim.state = &state;
	
	anim.WhenSceneEnd << THISBACK(OnSceneEnd);
	
	Sizeable().MaximizeBox();
	Title("Edit3D");
	
	hsplit.Horz().SetPos(2000) << metasplit << vsplit,
	metasplit.Vert() << tree << props;
	vsplit.Vert().SetPos(7500) << grid << time;
	
	grid.SetGridSize(2,2);
	for(int i = 0; i < 4; i++) {
		rends[i].owner = this;
		grid.Add(rends[i]);
	}
	rends[0].SetViewMode(VIEWMODE_YZ);
	rends[1].SetViewMode(VIEWMODE_XZ);
	rends[2].SetViewMode(VIEWMODE_XY);
	rends[3].SetViewMode(VIEWMODE_PERSPECTIVE);
	rends[0].SetCameraSource(CAMSRC_FOCUS);
	rends[1].SetCameraSource(CAMSRC_FOCUS);
	rends[2].SetCameraSource(CAMSRC_FOCUS);
	rends[3].SetCameraSource(CAMSRC_PROGRAM);
	
	Add(hsplit.SizePos());
	
	AddFrame(menu);
	menu.Set([this](Bar& bar) {
		bar.Sub(t_("File"), [this](Bar& bar) {
			bar.Add(t_("Exit"), THISBACK(Exit));
		});
		
	});
	
	AddFrame(tool);
	RefrehToolbar();
	
	tree.WhenAction << THISBACK(TreeSelect);
	
	tc.Set(-1000/60, THISBACK(Update));
	
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
	for(int i = 0; i < 4; i++)
		rends[i].Refresh();
}

void Edit3D::Update() {
	double dt = ts.Seconds();
	ts.Reset();
	
	bool was_playing = anim.is_playing;
	anim.Update(dt);
	
	time.SetSelectedColumn(anim.position);
	time.Refresh();
	
	if (anim.is_playing || was_playing) {
		for(int i = 0; i < 4; i++) {
			rends[i].Refresh();
		}
	}
}

void Edit3D::Data() {
	
	tree.SetRoot(ImagesImg::Root(), "Project");
	
	if (tree_scenes < 0)
		tree_scenes = tree.Add(0, ImagesImg::Scenes(), "Scenes");
	
	for(int i = 0; i < prj.scenes.GetCount(); i++) {
		GeomScene& scene = prj.scenes[i];
		String name = scene.name.IsEmpty() ? "Scene #" + IntStr(i) : scene.name;
		int j = tree.Add(tree_scenes, ImagesImg::Scene(), i, name);
		
		TreeDirectory(j, scene);
		
		if (i == 0 && !tree.HasFocus())
			tree.SetCursor(j);
	}
	
	/*for(int i = 0; i < prj.octrees.GetCount(); i++) {
		OctreePointModel& o = prj.octrees[i];
		String name = prj.dictionary[o.id];
		tree.Add(tree_octrees, ImagesImg::Octree(), o.id, name);
	}*/
	
	tree.Open(0);
	
	TreeSelect();
}

void Edit3D::TreeDirectory(int id, GeomDirectory& dir) {
	for(int i = 0; i < dir.subdir.GetCount(); i++) {
		GeomDirectory& subdir = dir.subdir[i];
		String name = dir.subdir.GetKey(i);
		int j = tree.Add(id, ImagesImg::Directory(), i, name);
		TreeDirectory(j, subdir);
	}
	for(int i = 0; i < dir.objs.GetCount(); i++) {
		GeomObject& o = dir.objs[i];
		Image img;
		switch (o.type) {
			case GeomObject::O_CAMERA: img = ImagesImg::Camera(); break;
			case GeomObject::O_MODEL:  img = ImagesImg::Model(); break;
			case GeomObject::O_OCTREE: img = ImagesImg::Octree(); break;
			default: img = ImagesImg::Object();
		}
		int j = tree.Add(id, img, i, o.name);
	}
}

void Edit3D::TimelineData() {
	GeomScene& scene = GetActiveScene();
	
	time.SetCount(scene.objs.GetCount());
	time.SetKeypointRate(prj.kps);
	time.SetLength(scene.length);
	time.SetKeypointColumnWidth(13);
	
	for(int i = 0; i < scene.objs.GetCount(); i++) {
		GeomObject& o = scene.objs[i];
		/*int j = prj.list[i];
		int id = j / GeomProject::O_COUNT;
		int type = j % GeomProject::O_COUNT;*/
		
		String name = o.name.IsEmpty() ? IntStr(i) : o.name;
		
		TimelineRowCtrl& row = time.GetRowIndex(i);
		row.SetTitle(name);
		
		row.SetKeypoints(o.timeline.keypoints.GetKeys());
		
		row.Refresh();
	}
	
	time.Refresh();
}

void Edit3D::TreeSelect() {
	if (!tree.HasFocus())
		return;
	
	int cursor = tree.GetCursor();
	int parent = tree.GetParent(cursor);
	if (parent == tree_scenes) {
		int i = tree.Get(cursor);
		GeomScene& s = prj.scenes[i];
	}

}

void Edit3D::LoadTestProject(int test_i) {
	
	// Cler project
	prj.Clear();
	
	// Add scene
	GeomScene& scene = prj.AddScene();
	
	// Add camera
	GeomObject& cam = scene.GetAddCamera("camera");
	
	
	if (test_i == 0) {
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
	else if (test_i == 1) {
		
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
	else TODO
	
	
	GeomKeypoint& kp = cam.timeline.keypoints.Get(0);
	state.program.position = kp.position;
	state.program.orientation = kp.orientation;
	state.active_scene = 0;
	
	Data();
	TimelineData();
	tree.OpenDeep(tree_scenes);
}

void Edit3D::LoadWmrStereoPointcloud(String directory) {
	GeomScene& scene = GetActiveScene();
	GeomObject& go = scene.GetAddOctree("octree");
	OctreePointModel& omodel = go.octree;
	Octree& o = omodel.octree;
	
	o.Initialize(-3,8); // 1 << 8 = 256x256x256 meters
	
	Size res(640,481);
	
	DescriptorImage l_dimg, r_dimg;
	
	VirtualStereoUncamera uncam;
	int point_limit = 2048;
	float eye_dist = 0.12;
	uncam.SetAnglePixel(17.4932f, 153.022f, 175.333f, -25.7489f);
	uncam.SetEyeDistance(eye_dist);
	uncam.SetYLevelHeight(10);
	uncam.SetEyeOutwardAngle(DEG2RAD(35.50));
	uncam.SetDistanceLimit(128); // max 256, lower is stricter
	
	OrbSystem orb;
	
	TimeStop ts;
	for(int i = 0; i < 100000; i++) {
		ts.Reset();
		
		String filepath = AppendFileName(directory, IntStr(i) + ".jpg");
		if (!FileExists(filepath))
			break;
		
		Image img = StreamRaster::LoadFileAny(filepath);
		if (img.IsEmpty())
			break;
		
		Size sz = img.GetSize();
		Size single_sz(sz.cx / 2, sz.cy);
		Image l_img, r_img;
		l_img = Crop(img, RectC(           0, 0, single_sz.cx, single_sz.cy));
		r_img = Crop(img, RectC(single_sz.cx, 0, single_sz.cx, single_sz.cy));
		
		l_dimg.SetResolution(single_sz);
		r_dimg.SetResolution(single_sz);
		
		orb.SetInput(l_img);
		int lc = orb.DetectKeypoints(l_dimg, point_limit);
		orb.SetInput(r_img);
		int rc = orb.DetectKeypoints(r_dimg, point_limit);
		
		uncam.Unrender(l_dimg, r_dimg, o);
		LOG(i << ": " << lc << " + " << rc << " keypoints in " << ts.ToString());
	}
	
}




EditConfiguration::EditConfiguration() {
	background_clr = Color(43, 44, 46);
	
	
}



NAMESPACE_TOPSIDE_END







