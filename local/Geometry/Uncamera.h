#ifndef _Geometry_Uncamera_h_
#define _Geometry_Uncamera_h_

NAMESPACE_TOPSIDE_BEGIN


class Uncamera {
	
protected:
	quat orientation;
	
public:
	Uncamera();
	
};


class VirtualStereoUncamera : public Uncamera, public LensPoly {
	struct TrackedTriangle;
	
	
	struct TrackedPoint {
		static const int MAX_TRIANGLES = 5;
		uint32 descriptor[DESCRIPTOR_UINTS];
		OctreeDescriptorPoint* dp;
		const Descriptor* l;
		const Descriptor* r;
		vec3 global_pos;
		
		TrackedTriangle* triangles[MAX_TRIANGLES];
		byte triangle_count = 0;
		
		bool has_stereo_target = false;
		vec3 stereo_tgt;
		vec3 prev_stereo_tgt;
		
		void ResetTemp() {l = 0; r = 0; has_stereo_target = false;}
		bool IsMaxTriangles() const {return triangle_count >= MAX_TRIANGLES;}
		void Attach(TrackedTriangle& tt);
		void Detach(TrackedTriangle& tt);
	};
	
	struct TrackedTriangle {
		TrackedPoint* a;
		TrackedPoint* b;
		
		void Track(TrackedPoint& a, TrackedPoint& b);
		void Untrack();
	};
	
	int distance_limit = 100; // limit for different bits in 32byte desriptor (compared to popcount)
	float eye_dist = 0.068f;
	float error_factor = 0.25; // error_factor is multiplier for the distance, what is searched
	int tracked_triangle_limit = 1000; // maximum triangle count before pruning efforts
	
	mat4 view = Identity<mat4>();
	mat4 view_inv = Identity<mat4>();
	mat4 prev_view = Identity<mat4>();
	mat4 prev_view_inv = Identity<mat4>();
	
	
	Array<TrackedPoint> tracked_points;
	Array<TrackedTriangle> tracked_triangles;
	
	
	// temp
	struct HorizontalMatch : Moveable<HorizontalMatch> {
		const Descriptor* l;
		const Descriptor* r;
		vec3 tgt;
		vec3 global_tgt;
	};
	Vector<Vector<const Descriptor*>> l_desc, r_desc;
	Vector<HorizontalMatch> horz_match;
	
	
	
	TrackedPoint* FindTrackedPoint(const Descriptor& d);
	bool IsAlreadyInSameTriangle(const TrackedPoint& a, const TrackedPoint& b);
	void UpdateOctreePosition(const vec3& global_tgt, TrackedPoint& tp);
	
public:
	typedef VirtualStereoUncamera CLASSNAME;
	VirtualStereoUncamera();
	
	void SetEyeDistance(float f) {eye_dist = f;}
	void SetDistanceLimit(int i) {distance_limit = i;}
	
	void Unrender(const DescriptorImage& l_img, const DescriptorImage& r_img, Octree& o);
	
};




NAMESPACE_TOPSIDE_END

#endif
