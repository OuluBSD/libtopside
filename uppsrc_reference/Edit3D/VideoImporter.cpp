#include "Edit3D.h"

NAMESPACE_TOPSIDE_BEGIN


GeomVideo::GeomVideo() {
	
}

void GeomVideo::Update(double dt) {
	ASSERT(is_importing);
	GeomAnim& anim = *this->anim;
	
	anim.Update(dt);
	
	//if (anim.position >= position)
	Next();
	
	if (position == 1)
		is_importing = false;
	
}

void GeomVideo::LoadDirectory(String directory, int fps, String name) {
	GeomAnim& anim = *this->anim;
	GeomWorldState& state = *anim.state;
	GeomProject& prj = *state.prj;
	
	this->directory = directory;
	if (name.IsEmpty())
		name = "octree";
	
	// Cler project
	prj.Clear();
	prj.kps = fps;
	
	// Add scene
	GeomScene& scene = prj.AddScene();
	state.active_scene = 0;
	
	// Add camera
	cam = &scene.GetAddCamera("camera");
	
	// Octree
	GeomObject& go = scene.GetAddOctree("octree");
	OctreePointModel& omodel = go.octree;
	Octree& o = omodel.octree;
	this->octree = &o;
	this->go = &go;
	
	// Resolution: 1 / (1 << __3__) = 0.125 meters
	// Size: 1 << __8__ = 256x256x256 meters
	o.Initialize(-3,8);
	
	video_length = 0;
	for(int i = 0; i < 100000; i++) {
		ts.Reset();
		
		String filepath = AppendFileName(directory, IntStr(i) + ".jpg");
		if (!FileExists(filepath))
			break;
		
		video_length = i+1;
	}
	scene.length = video_length;
	is_importing = video_length > 0;
	
	//anim.is_playing = true;
	
	position = 0;
	
}

void GeomVideo::SetWmrCamera() {
	eye_dist = 0.12;
	uncam.SetAnglePixel(17.4932f, 153.022f, 175.333f, -25.7489f);
	uncam.SetEyeDistance(eye_dist);
	uncam.SetYLevelHeight(10);
	uncam.SetEyeOutwardAngle(DEG2RAD(35.50));
	uncam.SetDistanceLimit(128); // max 256, lower is stricter
}

void GeomVideo::Next() {
	GeomAnim& anim = *this->anim;
	GeomWorldState& state = *anim.state;
	GeomProject& prj = *state.prj;
	GeomScene& scene = state.GetActiveScene();
	
	
	if (position >= video_length) {
		is_importing = false;
		return;
	}
	
	
	ts.Reset();
	
	String filepath = AppendFileName(directory, IntStr(position) + ".jpg");
	Image img = StreamRaster::LoadFileAny(filepath);
	if (img.IsEmpty())
		return;
	
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
	
	TODO
	/*
	uncam.Unrender(l_dimg, r_dimg, *octree);
	
	LOG(position << ": " << lc << " + " << rc << " keypoints in " << ts.ToString());
	
	
	{
		GeomObject& o = *cam;
		GeomTimeline& time = o.timeline;
		ASSERT(time.keypoints.Find(position) < 0);
		GeomKeypoint& kp = time.keypoints.Add(position);
		kp.position = uncam.GetPosition();
		kp.orientation = uncam.GetOrientation();
	}
	*/
	anim.position = position;
	
	position++;
	is_importing = position < video_length;
	
}


NAMESPACE_TOPSIDE_END
