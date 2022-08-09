#ifndef _Edit3D_StagedVideoImporter_h_
#define _Edit3D_StagedVideoImporter_h_

NAMESPACE_TOPSIDE_BEGIN


struct GeomStagedVideo : GeomVideo {
	/*GeomAnim* anim = 0;
	int video_length = 0;
	DescriptorImage l_dimg, r_dimg;
	VirtualStereoUncamera uncam;
	OrbSystem orb;
	bool is_importing = false;
	int point_limit = 2048;
	float eye_dist = 0.06;
	TimeStop ts;
	int position = 0;
	String directory;
	Octree* octree = 0;
	GeomObject* go = 0;
	GeomObject* cam = 0;
	*/
	StagedVirtualStereoUncamera uncam;
	TimeStop ts;
	RunningFlag flag;
	
	enum {
		STAGE_NULL,
		STAGE_IMAGES_DIRECTORY,
		STAGE_DESCRIPTORS,
		STAGE_STEREO_KEYPOINTS,
		STAGE_PROCESS_MESH,
		STAGE_SOLVE_TRANSFORM,
		STAGE_PROCESS_TRANSFORM,
		
		STAGE_END,
	};
	bool is_staged = true;
	int stage = 0;
	
	
	void Start();
	void Process();
public:
	typedef GeomStagedVideo CLASSNAME;
	GeomStagedVideo();
	
	void LoadDirectory(String dir, int fps, String name="");
	void SetWmrCamera();
	 
	void Update(double dt);
	void Stop();
	
};


NAMESPACE_TOPSIDE_END

#endif
