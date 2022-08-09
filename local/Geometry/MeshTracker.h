#ifndef _Geometry_MeshTracker_h_
#define _Geometry_MeshTracker_h_

NAMESPACE_TOPSIDE_BEGIN


struct TrackedTriangle;


struct TrackedPoint {
	static const int MAX_TRIANGLES = 5;
	uint32 descriptor[DESCRIPTOR_UINTS];
	OctreeDescriptorPoint* dp = 0;
	
	TrackedTriangle* triangles[MAX_TRIANGLES] = {0,0,0,0,0};
	byte triangle_count = 0;
	
	bool has_local_tgt = false;
	vec3 local_tgt, global_tgt;
	
	mutable const Descriptor* l = 0;
	mutable const Descriptor* r = 0;
	mutable bool has_next_local_tgt = false;
	mutable vec3 next_local_tgt, next_global_tgt;
	
	void ResetTemp() {l = 0; r = 0;}
	bool IsMaxTriangles() const {return triangle_count >= MAX_TRIANGLES;}
	void Attach(TrackedTriangle& tt);
	void Detach(TrackedTriangle& tt);
};

struct TrackedTriangle {
	TrackedPoint* a = 0;
	TrackedPoint* b = 0;
	TrackedPoint* c = 0;
	
	void Track(TrackedPoint& a, TrackedPoint& b, TrackedPoint& c);
	void Untrack();
};



struct MeshTrackerFrame {
	vec3 position;
	quat orientation;
	Array<TrackedPoint> tracked_points;
	Array<TrackedTriangle> tracked_triangles;
	mat4 view = Identity<mat4>();
	mat4 view_change = Identity<mat4>();
	mat4 view_inv = Identity<mat4>();
	
};



class MeshTracker {
	int tracked_triangle_limit = 1000; // maximum triangle count before pruning efforts
	
	
	
protected:
	int distance_limit = 100; // limit for different bits in 32byte desriptor (compared to popcount)
	
	
	void UpdateOctreePosition(MeshTrackerFrame& to, TrackedPoint& tp, bool local_value, bool next_value);
	const TrackedPoint* FindTrackedPoint(const MeshTrackerFrame& from, const Descriptor& d);
	bool IsAlreadyInSameTriangle(const TrackedPoint& a, const TrackedPoint& b);
	OctreeDescriptorPoint* GetAddNode(const vec3& global_tgt, const uint32* descriptor_value, Octree& o);
	
public:
	typedef MeshTracker CLASSNAME;
	MeshTracker();
	
	void SolveTransform(const MeshTrackerFrame& from, MeshTrackerFrame& to);
	void ProcessTriangles(MeshTrackerFrame& to);
	void FindTriangles(MeshTrackerFrame& to);
	void PruneTriangles(MeshTrackerFrame& to);
	void UpdateTrackedTriangles(const MeshTrackerFrame& from, MeshTrackerFrame& to);
	void UpdateOctreePositions(const MeshTrackerFrame& from, MeshTrackerFrame& to);
	
	void SetDistanceLimit(int i) {distance_limit = i;}
	
	//const vec3& GetPosition() const {return position;}
	//const quat& GetOrientation() const {return orientation;}
	
};


class WmrMotionControllerTracker : public MeshTracker {
	
	
public:
	typedef WmrMotionControllerTracker CLASSNAME;
	WmrMotionControllerTracker();
	
	
};

NAMESPACE_TOPSIDE_END

#endif
