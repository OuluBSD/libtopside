#ifndef _Geometry_Frustum_h_
#define _Geometry_Frustum_h_

NAMESPACE_TOPSIDE_BEGIN


float Classify(const AABB& aabb, const Plane& plane);
float Classify(const OBB& obb, const Plane& plane);
vec3 Intersection(Plane p1, Plane p2, Plane p3);


struct Frustum {
	union {
		struct {
			Plane top;
			Plane bottom;
			Plane left;
			Plane right;
			Plane _near;
			Plane _far;
		};
		Plane planes[6];
	};

	Frustum() {}
	Frustum(const Frustum& m) {
		for(int i = 0; i < 6; i++)
			planes[i] = m.planes[i];
	}
	
	void operator=(const Frustum& m) {
		for(int i = 0; i < 6; i++)
			planes[i] = m.planes[i];
	}
	Plane& operator[](int i) {
		ASSERT(i >= 0 && i < 6);
		return planes[i];
	}
	
	const Plane& operator[](int i) const {
		ASSERT(i >= 0 && i < 6);
		return planes[i];
	}
	
	void GetCorners(vec3* outCorners) const;
	bool Intersects(const vec3& p) const;
	bool Intersects(const Sphere& s) const;
	bool Intersects(const AABB& aabb) const;
	bool Intersects(const OBB& obb) const;
	bool Contains(const AABB& aabb) const;
	
};


NAMESPACE_TOPSIDE_END

#endif
