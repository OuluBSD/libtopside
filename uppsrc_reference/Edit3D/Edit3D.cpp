#include "Edit3D.h"



Edit3D::Edit3D() {
	hsplit.Horz().SetPos(2000) << metasplit << vsplit,
	metasplit.Vert() << content << props;
	vsplit.Vert().SetPos(7500) << grid << time;
	
	
	Add(hsplit.SizePos());
	
	
	AddFrame(menu);
	menu.Set([this](Bar& bar) {
		bar.Sub("File", [this](Bar& bar) {
			bar.Add("Exit", THISBACK(Exit));
		});
		
	});
}

void Edit3D::Exit() {
	Close();
}

void Edit3D::Data() {
	
	
	
	
	
	
	
}

void Edit3D::LoadWmrStereoPointcloud(String directory) {
	int id = prj.dictionary.FindAdd("pointcloud");
	OctreePointModel& omodel = prj.octrees.GetAdd(id);
	Octree& o = omodel.octree;
	
	o.Initialize(-3,3); // 1 << 3 = 8x8x8 meters
	
	Size res(640,481);
	
	DescriptorImage l_dimg, r_dimg;
	
	VirtualStereoUncamera uncam;
	float eye_dist = 0.12;
	uncam.SetAnglePixel(17.4932f, 153.022f, 175.333f, -25.7489f);
	uncam.SetEyeDistance(eye_dist);
	uncam.SetEyeOutwardAngle(DEG2RAD(35.50));
	uncam.SetDistanceLimit(0);
	
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
		int lc = orb.DetectKeypoints(l_dimg, 256);
		orb.SetInput(r_img);
		int rc = orb.DetectKeypoints(r_dimg, 256);
		
		uncam.Unrender(l_dimg, r_dimg, o);
		LOG(i << ": " << lc << " + " << rc << " keypoints in " << ts.ToString());
	}
	
	
	
}









GUI_APP_MAIN {
	Edit3D app;
	
	const auto& c = CommandLine();
	if (!c.IsEmpty() && DirectoryExists(c[0]))
		app.LoadWmrStereoPointcloud(c[0]);
	
	app.Run();
	
	
}
