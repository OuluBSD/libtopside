#ifndef _Edit3D_Geom_h_
#define _Edit3D_Geom_h_

NAMESPACE_TOPSIDE_BEGIN



struct GeomProgram;
struct GeomProject;
struct GeomScene;
struct GeomDirectory;
struct Edit3D;


struct GeomKeypoint {
	int frame_id = -1;
	vec3 position;
	quat orientation;
	
};

struct GeomTimeline {
	ArrayMap<int, GeomKeypoint> keypoints;
	
	GeomKeypoint& GetAddKeypoint(int i);
	int FindPre(int kp_i) const;
	int FindPost(int kp_i) const;
	
};

struct GeomObject {
	enum {
		O_NULL,
		O_MODEL,
		O_CAMERA,
		O_OCTREE,
		
		O_COUNT
	};
	
	GeomDirectory* owner = 0;
	
	hash_t key;
	String name;
	int type = 0;
	
	GeomObject() {}
	One<Model> mdl;
	Camera cam;
	OctreePointModel octree;
	Octree* octree_ptr = 0;
	
	GeomTimeline timeline;
	
	bool IsModel() const {return type == O_MODEL;}
	bool IsOctree() const {return type == O_OCTREE;}
	bool IsCamera() const {return type == O_CAMERA;}
	String GetPath() const;
	
};

struct GeomDirectory {
	virtual ~GeomDirectory() {}
	
	ArrayMap<String, GeomDirectory> subdir;
	Array<GeomObject> objs;
	String name;
	GeomDirectory* owner = 0;
	
	GeomProject& GetProject() const;
	GeomDirectory& GetAddDirectory(String name);
	GeomObject& GetAddModel(String name);
	GeomObject& GetAddCamera(String name);
	GeomObject& GetAddOctree(String name);
	GeomObject* FindObject(String name);
	
};

struct GeomObjectIterator {
	static const int MAX_LEVELS = 128;
	int pos[MAX_LEVELS] = {0};
	GeomDirectory* addr[MAX_LEVELS];
	GeomObject* obj;
	int level = 0;
	
	
	bool Next();
	operator bool() const;
	GeomObject& operator*();
	GeomObject* operator->();
	bool operator==(const GeomObjectIterator& it) const {
		if (it.level != level || it.obj != obj)
			return false;
		for(int i = 0; i <= level; i++)
			if (pos[i] != it.pos[i])
				return false;
		return true;
	}
	void operator++() {Next();}
	void operator++(int) {Next();}
	
};

struct GeomObjectCollection {
	using Iterator = GeomObjectIterator;
	
	Iterator iter;
	
	
	GeomObjectCollection(GeomDirectory& d);
	Iterator begin() const {return iter;}
	Iterator end() const {return Iterator();}
	Iterator begin() {return iter;}
	Iterator end() {return Iterator();}
	
};

struct GeomScene : GeomDirectory {
	GeomProject* owner = 0;
	int length = 0;
	
};

struct GeomProject {
	Array<GeomScene> scenes;
	int kps = 5;
	int fps = 60;
	
	hash_t key_counter;
	
	void Clear() {
		scenes.Clear();
		kps = 5;
		fps = 60;
		key_counter = 1;
	}
	
	GeomScene& AddScene();
	hash_t NewKey() {return key_counter++;}
	
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
	CAMSRC_VIDEOIMPORT_FOCUS,
	CAMSRC_VIDEOIMPORT_PROGRAM,
} CameraSource;

struct GeomCamera {
	vec3 position = vec3(0);
	quat orientation = Identity<quat>();
	float distance = 10;
	float fov = 120;
	float scale = 1;
	
	
	void LoadCamera(ViewMode m, Camera& cam, Size sz, float far=1000) const;
	mat4 GetViewMatrix(ViewMode m, Size sz) const;
	Frustum GetFrustum(ViewMode m, Size sz) const;
	
};

struct GeomObjectState {
	GeomObject* obj;
	vec3 position;
	quat orientation;
};

struct GeomWorldState {
	GeomProject* prj = 0;
	GeomCamera focus, program;
	int active_scene = -1;
	int active_camera_obj_i = -1;
	
	Array<GeomObjectState> objs;
	
	
	GeomWorldState();
	
	void UpdateObjects();
	GeomScene& GetActiveScene();
	bool HasActiveScene() const {return active_scene >= 0;}
	
};

struct GeomAnim {
	GeomWorldState* state = 0;
	double time = 0;
	int position = 0;
	bool is_playing = false;
	
	void Reset();
	void Play();
	void Pause();
	void Update(double dt);
	
	
	Callback WhenSceneEnd;
	
};


NAMESPACE_TOPSIDE_END

#endif
