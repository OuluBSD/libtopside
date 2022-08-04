#include "Edit3D.h"


#define IMAGECLASS ImagesImg
#define IMAGEFILE <Edit3D/Images.iml>
#include <Draw/iml_source.h>



NAMESPACE_TOPSIDE_BEGIN




Edit3D::Edit3D() {
	state.prj = &prj;
	
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
	tool.Set(THISBACK(Toolbar));
	
	tree.WhenAction << THISBACK(TreeSelect);
	
}

void Edit3D::Toolbar(Bar& bar) {
	bar.Add(true,  t_("Stop"),  ImagesImg::Stop(),  THISBACK(Stop));
	
	if (state.is_playing)
		bar.Add(true, t_("Pause"), ImagesImg::Pause(), THISBACK(Pause));
	else
		bar.Add(true,  t_("Play"),  ImagesImg::Play(),  THISBACK(Play));
	
}

GeomScene& Edit3D::GetActiveScene() {
	return prj.scenes[0];
}

void Edit3D::Exit() {
	Close();
}

void Edit3D::RefreshData() {
	PostCallback(THISBACK(Data));
}

void Edit3D::Stop() {
	
}

void Edit3D::Pause() {
	
}

void Edit3D::Play() {
	
}

void Edit3D::RefrehRenderers() {
	for(int i = 0; i < 4; i++)
		rends[i].Refresh();
}

void Edit3D::Data() {
	
	tree.SetRoot(ImagesImg::Root(), "Project");
	
	if (tree_cameras < 0)
		tree_cameras = tree.Add(0, ImagesImg::Cameras(), "Cameras");
	
	if (tree_octrees < 0)
		tree_octrees = tree.Add(0, ImagesImg::Octrees(), "Octrees");
	
	if (tree_pointclouds < 0)
		tree_pointclouds = tree.Add(0, ImagesImg::Pointclouds(), "Pointclouds");
	
	for(int i = 0; i < prj.cameras.GetCount(); i++) {
		Camera& c = prj.cameras[i];
		String name = prj.dictionary[c.id];
		int j = tree.Add(tree_cameras, ImagesImg::Camera(), c.id, name);
		
		if (i == 0 && !tree.HasFocus())
			tree.SetCursor(i);
	}
	
	for(int i = 0; i < prj.octrees.GetCount(); i++) {
		OctreePointModel& o = prj.octrees[i];
		String name = prj.dictionary[o.id];
		tree.Add(tree_octrees, ImagesImg::Octree(), o.id, name);
	}
	
	tree.Open(0);
	
	TreeSelect();
}

void Edit3D::TimelineData() {
	GeomScene& scene = GetActiveScene();
	
	time.SetCount(scene.programs.GetCount());
	time.SetKeypointRate(prj.kps);
	time.SetLength(scene.length);
	time.SetKeypointColumnWidth(13);
	
	for(int i = 0; i < scene.programs.GetCount(); i++) {
		/*int j = prj.list[i];
		int id = j / GeomProjectFile::O_COUNT;
		int type = j % GeomProjectFile::O_COUNT;*/
		int id = scene.programs.GetKey(i);
		String name = prj.dictionary[id];
		if (name.IsEmpty())
			name = IntStr(id);
		
		TimelineRowCtrl& row = time.GetRowIndex(i);
		row.SetTitle(name);
		
		GeomProgram& prog = scene.programs[i];
		row.SetKeypoints(prog.timeline.keypoints.GetKeys());
		
		row.Refresh();
	}
	
	time.Refresh();
}

void Edit3D::TreeSelect() {
	if (!tree.HasFocus())
		return;
	
	int cursor = tree.GetCursor();
	int parent = tree.GetParent(cursor);
	if (parent == tree_cameras) {
		int id = tree.Get(cursor);
		Camera& c = prj.cameras.Get(id);
	}
	else if (parent == tree_octrees) {
		
	}

}

void Edit3D::LoadTestProject(int test_i) {
	
	// Cler project
	prj.Clear();
	
	// Add pointcloud
	OctreePointModel& omodel = prj.GetAddOctree("octree");
	Octree& o = omodel.octree;
	
	// Add camera
	Camera& cam = prj.GetAddCamera("camera");
	
	// Add scene
	GeomScene& scene = prj.AddScene();
	
	// Add camera progam
	GeomProgram& cam_prog = scene.GetAddProgram("camera_program");
	cam.SetProgram(cam_prog.id);
	
	
	if (test_i == 0) {
		
		// Create octree
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
		float step = M_PI * 2 / (scene.length / kp_step);
		float angle = 0;
		float cam_radius = radius + 2;
		for(int i = 0; i < scene.length; i += kp_step) {
			GeomKeypoint& kp = cam_prog.timeline.GetAddKeypoint(i);
			kp.position = vec3(sin(angle), 0, cos(angle)) * cam_radius;
			kp.orientation = AxesQuat(angle, 0, 0);
			angle += step;
		}
		
		
	}
	else TODO
	
	
	Data();
	TimelineData();
	tree.OpenDeep(tree_cameras);
	tree.OpenDeep(tree_octrees);
}

void Edit3D::LoadWmrStereoPointcloud(String directory) {
	int id = prj.dictionary.FindAdd("pointcloud");
	OctreePointModel& omodel = prj.octrees.GetAdd(id);
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







