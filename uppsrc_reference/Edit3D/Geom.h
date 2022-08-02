#ifndef _Edit3D_Geom_h_
#define _Edit3D_Geom_h_

NAMESPACE_TOPSIDE_BEGIN



struct GeomProgram;
struct GeomProjectFile;
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

typedef enum {
	CAMERA_YZ,
	CAMERA_XZ,
	CAMERA_XY,
	CAMERA_PERSPECTIVE,
	CAMERA_CAMERA,
} ViewMode;

struct GeomWorldState {
	GeomProjectFile* prj = 0;
	vec3 focus_position = vec3(0);
	quat focus_orientation = Identity<quat>();
	float focus_distance = 10;
	float focus_fov = 90;
	float focus_scale = 100;
	vec3 camera_position = vec3(0);
	quat camera_orientation = Identity<quat>();
	float camera_fov = 90;
	int active_camera = -1;
	dword frame_i = 0;
	bool is_playing = false;
	
	
	void LoadCamera(ViewMode m, Camera& cam, Size sz) const;
	mat4 GetViewMatrix(ViewMode m, Size sz) const;
	Frustum GetFrustum(ViewMode m, Size sz) const;
	
};


NAMESPACE_TOPSIDE_END

#endif
