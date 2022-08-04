#ifndef _Edit3D_Geom_h_
#define _Edit3D_Geom_h_

NAMESPACE_TOPSIDE_BEGIN



struct GeomProgram;
struct GeomProjectFile;
struct GeomScene;
struct Edit3D;


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
	GeomScene* owner = 0;
	GeomTimeline timeline;
	int id = -1;
	
	
};

struct GeomScene {
	GeomProjectFile* owner = 0;
	ArrayMap<int, GeomProgram> programs;
	int length = 0;
	
	GeomProgram& GetAddProgram(String name);
	
};

struct GeomProjectFile {
	enum {
		O_OCTREE,
		O_MODEL,
		O_CAMERA,
		O_PROGRAM,
		O_COUNT
	};
	
	Index<String> dictionary;
	ArrayMap<int, OctreePointModel> octrees;
	ArrayMap<int, Model> models;
	ArrayMap<int, Camera> cameras;
	Array<GeomScene> scenes;
	Index<int> list;
	int kps = 5;
	int fps = 60;
	
	void Clear() {
		dictionary.Clear();
		octrees.Clear();
		models.Clear();
		cameras.Clear();
		scenes.Clear();
		list.Clear();
	}
	
	Camera& GetAddCamera(String name);
	OctreePointModel& GetAddOctree(String name);
	GeomScene& AddScene();
	
};

typedef enum {
	VIEWMODE_YZ,
	VIEWMODE_XZ,
	VIEWMODE_XY,
	VIEWMODE_PERSPECTIVE,
} ViewMode;

typedef enum {
	CAMSRC_FOCUS,
	CAMSRC_PROGRAM,
} CameraSource;

struct GeomCamera {
	vec3 position = vec3(0);
	quat orientation = Identity<quat>();
	float distance = 10;
	float fov = 120;
	float scale = 1;
	
	
	void LoadCamera(ViewMode m, Camera& cam, Size sz) const;
	mat4 GetViewMatrix(ViewMode m, Size sz) const;
	Frustum GetFrustum(ViewMode m, Size sz) const;
	
};

struct GeomWorldState {
	GeomProjectFile* prj = 0;
	
	GeomCamera focus, program;
	
	CameraSource active_camera;
	dword frame_i = 0;
	bool is_playing = false;
	
	
	GeomWorldState();
	
};


NAMESPACE_TOPSIDE_END

#endif
