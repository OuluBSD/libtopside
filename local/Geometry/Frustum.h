#ifndef _Geometry_Frustum_h_
#define _Geometry_Frustum_h_

NAMESPACE_TOPSIDE_BEGIN


float Classify(const AABB& aabb, const Plane& plane);
float Classify(const OBB& obb, const Plane& plane);
vec3 Intersection(Plane p1, Plane p2, Plane p3);


struct Frustum {
	Plane top;
	Plane bottom;
	Plane left;
	Plane right;
	Plane _near;
	Plane _far;

	Frustum() {}
	Frustum(const Frustum& m) {
		for(int i = 0; i < 6; i++)
			(*this)[i] = m[i];
	}
	
	Plane& operator[](int i) {
		switch (i) {
			case 0: return top;
			case 1: return bottom;
			case 2: return left;
			case 3: return right;
			case 4: return _near;
			case 5: return _far;
		}
		Panic("invalid [] pos");
		NEVER();
		TODO
	}
	
	const Plane& operator[](int i) const {
		switch (i) {
			case 0: return top;
			case 1: return bottom;
			case 2: return left;
			case 3: return right;
			case 4: return _near;
			case 5: return _far;
		}
		Panic("invalid [] pos");
		NEVER();
		TODO
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
