#ifndef _Edit3D_Edit3D_h_
#define _Edit3D_Edit3D_h_

#include <CtrlLib/CtrlLib.h>
#include <LocalCtrl/LocalCtrl.h>
#include <Geometry/Geometry.h>
#include <ComputerVision/ComputerVision.h>
#include <Pointcloud/Pointcloud.h>
using namespace Upp;
using namespace TS;


#define IMAGECLASS ImagesImg
#define IMAGEFILE <Edit3D/Images.iml>
#include <Draw/iml_header.h>


struct GeomProgram;
struct GeomProjectFile;


struct GeomKeypoint {
	int frame_id = -1;
	vec3 position;
	quat orientation;
	
};

struct GeomTimeline {
	ArrayMap<int, GeomKeypoint> keypoints;
	GeomProgram* owner = 0;
	
	
	GeomKeypoint& GetAddKeypoint(int i);
	
};

struct GeomProgram {
	GeomProjectFile* owner = 0;
	GeomTimeline timeline;
	int id = -1;
	
	
};

struct GeomProjectFile {
	Index<String> dictionary;
	ArrayMap<int, OctreePointModel> octrees;
	ArrayMap<int, Model> models;
	ArrayMap<int, Camera> cameras;
	ArrayMap<int, GeomProgram> programs;
	int fps = 25;
	
	void Clear() {
		dictionary.Clear();
		octrees.Clear();
		models.Clear();
		cameras.Clear();
		programs.Clear();
	}
	
	Camera& GetAddCamera(String name);
	OctreePointModel& GetAddOctree(String name);
	GeomProgram& GetAddProgram(String name);
	
};

class Edit3D : public TopWindow {
	Splitter metasplit, hsplit, vsplit;
	TreeCtrl tree;
	ArrayCtrl props;
	GridCtrl grid;
	TimelineCtrl time;
	MenuBar menu;
	ToolBar tool;
	
	GeomProjectFile prj;
	int tree_cameras = -1;
	int tree_octrees = -1;
	int tree_pointclouds = -1;
	
	bool is_playing = false;
	
public:
	typedef Edit3D CLASSNAME;
	Edit3D();
	
	void Data();
	void TreeSelect();
	void Exit();
	void RefreshData();
	void Stop();
	void Pause();
	void Play();
	void Toolbar(Bar& bar);
	
	void LoadTestProject(int test_i);
	void LoadWmrStereoPointcloud(String directory);
	
};


#endif
