#ifndef _Geometry_MeshTracker_h_
#define _Geometry_MeshTracker_h_

NAMESPACE_TOPSIDE_BEGIN


struct TrackedTriangle;


struct TrackedPoint {
	static const int MAX_TRIANGLES = 5;
	uint32 descriptor[DESCRIPTOR_UINTS];
	OctreeDescriptorPoint* dp = 0;
	const Descriptor* l = 0;
	const Descriptor* r = 0;
	vec3 global_pos;
	
	TrackedTriangle* triangles[MAX_TRIANGLES] = {0,0,0,0,0};
	byte triangle_count = 0;
	
	bool has_local_tgt = false;
	bool has_prev_local_tgt = false;
	vec3 local_tgt;
	vec3 prev_local_tgt;
	
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



class MeshTracker {
	int tracked_triangle_limit = 1000; // maximum triangle count before pruning efforts
	
	
	void FindTriangles();
	void PruneTriangles();
	void UpdateTrackedTriangles();
	void UpdateOctreePositions();
	
protected:
	Array<TrackedPoint> tracked_points;
	Array<TrackedTriangle> tracked_triangles;
	mat4 view = Identity<mat4>();
	mat4 view_inv = Identity<mat4>();
	quat orientation;
	vec3 position;
	int distance_limit = 100; // limit for different bits in 32byte desriptor (compared to popcount)
	
	
	void UpdateOctreePosition(const vec3& global_tgt, TrackedPoint& tp);
	TrackedPoint* FindTrackedPoint(const Descriptor& d);
	bool IsAlreadyInSameTriangle(const TrackedPoint& a, const TrackedPoint& b);
	OctreeDescriptorPoint* GetAddNode(const vec3& global_tgt, const uint32* descriptor_value, Octree& o);
	
public:
	typedef MeshTracker CLASSNAME;
	MeshTracker();
	
	void TriangleUpdate();
	void SetDistanceLimit(int i) {distance_limit = i;}
	
	
};


class WmrMotionControllerTracker : public MeshTracker {
	
	
public:
	typedef WmrMotionControllerTracker CLASSNAME;
	WmrMotionControllerTracker();
	
	
};

NAMESPACE_TOPSIDE_END

#endif
