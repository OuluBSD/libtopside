#ifndef _Edit3D_Geom_h_
#define _Edit3D_Geom_h_

NAMESPACE_TOPSIDE_BEGIN



struct GeomProgram;
struct GeomProjectFile;
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
	String name;
	int type = 0;
	
	One<Model> mdl;
	Camera cam;
	OctreePointModel octree;
	
	GeomTimeline timeline;
	
	bool IsModel() const {return type == O_MODEL;}
	bool IsOctree() const {return type == O_OCTREE;}
	
};

struct GeomDirectory {
	ArrayMap<String, GeomDirectory> subdir;
	Array<GeomObject> objs;
	
	
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
	GeomProjectFile* owner = 0;
	String name;
	int length = 0;
	
};

struct GeomProjectFile {
	Array<GeomScene> scenes;
	int kps = 5;
	int fps = 60;
	
	void Clear() {
		scenes.Clear();
	}
	
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
	
	
	void LoadCamera(ViewMode m, Camera& cam, Size sz, float far=1000) const;
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
