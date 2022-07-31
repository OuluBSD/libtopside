#include "Edit3D.h"


#define IMAGECLASS ImagesImg
#define IMAGEFILE <Edit3D/Images.iml>
#include <Draw/iml_source.h>



GeomKeypoint& GeomTimeline::GetAddKeypoint(int i) {
	GeomKeypoint& kp = keypoints.GetAdd(i);
	kp.frame_id = i;
	kp.position = Identity<vec3>();
	kp.orientation = Identity<quat>();
	return kp;
}

Camera& GeomProjectFile::GetAddCamera(String name) {
	int i = dictionary.FindAdd(name);
	int j = cameras.Find(i);
	if (j >= 0)
		return cameras[j];
	Camera& p = cameras.Add(i);
	//p.owner = this;
	p.id = i;
	return p;
}

OctreePointModel& GeomProjectFile::GetAddOctree(String name) {
	int i = dictionary.FindAdd(name);
	int j = octrees.Find(i);
	if (j >= 0)
		return octrees[j];
	OctreePointModel& p = octrees.Add(i);
	//p.owner = this;
	p.id = i;
	return p;
}

GeomProgram& GeomProjectFile::GetAddProgram(String name) {
	int i = dictionary.FindAdd(name);
	int j = programs.Find(i);
	if (j >= 0)
		return programs[j];
	GeomProgram& p = programs.Add(i);
	p.owner = this;
	p.id = i;
	return p;
}








Edit3D::Edit3D() {
	hsplit.Horz().SetPos(2000) << metasplit << vsplit,
	metasplit.Vert() << tree << props;
	vsplit.Vert().SetPos(7500) << grid << time;
	
	
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
	
	if (is_playing)
		bar.Add(true, t_("Pause"), ImagesImg::Pause(), THISBACK(Pause));
	else
		bar.Add(true,  t_("Play"),  ImagesImg::Play(),  THISBACK(Play));
	
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
	OctreePointModel& omodel = prj.GetAddOctree("pointcloud");
	Octree& o = omodel.octree;
	
	// Add camera
	Camera& cam = prj.GetAddCamera("camera");
	
	// Add camera progam
	GeomProgram& cam_prog = prj.GetAddProgram("camera_program");
	cam.SetProgram(cam_prog.id);
	
	
	if (test_i == 0) {
		
		// Create octree
		o.Initialize(-3, 6); // 1 << 6 = 32x32x32 meters
		
		// Create points in form of sphere
		float radius = 1;
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
				pitch = fmodf(f * M_PI * 40, M_PI) - M_PI/2;
			}
			
			vec3 pos = AxesDir(yaw, pitch) * radius;
			OctreeNode* n = o.GetAddNode(pos, -3);
			Pointcloud::Point& p = n->Add<Pointcloud::Point>();
			p.SetPosition(pos);
			//LOG(pos.ToString() + ": " + HexStr(n));
		}
		
		// Move camera linearly around sphere
		int seconds = 3;
		int keypoints = prj.fps * seconds;
		float step = M_PI * 2 / keypoints;
		float angle = 0;
		float cam_radius = radius + 2;
		for(int i = 0; i < keypoints; i++) {
			GeomKeypoint& kp = cam_prog.timeline.GetAddKeypoint(i);
			kp.position = vec3(sin(angle), 0, cos(angle)) * cam_radius;
			kp.orientation = AxesQuat(angle, 0, 0);
			angle += step;
		}
		
		
	}
	else TODO
	
	
	Data();
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









GUI_APP_MAIN {
	Edit3D app;
	
	const auto& c = CommandLine();
	if (!c.IsEmpty() && DirectoryExists(c[0]))
		app.LoadWmrStereoPointcloud(c[0]);
	else
		app.LoadTestProject(0);
	
	app.Run();
	
	
}
