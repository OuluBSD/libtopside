#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN



float Classify(const AABB& aabb, const Plane& plane) {
	// maximum extent in direction of plane normal
	float r = fabsf(aabb.size[0] * plane.normal[0])
		+ fabsf(aabb.size[1] * plane.normal[1])
		+ fabsf(aabb.size[2] * plane.normal[2]);

	// signed distance between box center and plane
	//float d = plane.Test(mCenter);
	float d = Dot(plane.normal, aabb.position) + plane.distance;

	// return signed distance
	if (fabsf(d) < r) {
		return 0.0f;
	}
	else if (d < 0.0f) {
		return d + r;
	}
	return d - r;
}

float Classify(const OBB& obb, const Plane& plane) {
	vec3 normal = MultiplyVector(plane.normal, obb.orientation);

	// maximum extent in direction of plane normal
	float r = fabsf(obb.size[0] * normal[0])
		+ fabsf(obb.size[1] * normal[1])
		+ fabsf(obb.size[2] * normal[2]);

	// signed distance between box center and plane
	//float d = plane.Test(mCenter);
	float d = Dot(plane.normal, obb.position) + plane.distance;

	// return signed distance
	if (fabsf(d) < r) {
		return 0.0f;
	}
	else if (d < 0.0f) {
		return d + r;
	}
	return d - r;
}


vec3 Intersection(Plane p1, Plane p2, Plane p3) {
	/*return ((Cross(p2.normal, p3.normal) * -p1.distance) +
		(Cross(p3.normal, p1.normal) * -p2.distance) +
		(Cross(p1.normal, p2.normal) * -p3.distance)) /
		(Dot(p1.normal, Cross(p2.normal, p3.normal)));*/
		
#if 1
	mat3 D {
		p1.normal[0], p2.normal[0], p3.normal[0],
		p1.normal[1], p2.normal[1], p3.normal[1],
		p1.normal[2], p2.normal[2], p3.normal[2]
	};
	vec3 A(-p1.distance, -p2.distance, -p3.distance);

	mat3 Dx = D, Dy = D, Dz = D;
	Dx[0][0] = A[0]; Dx[0][1] = A[1]; Dx[0][2] = A[2];
	Dy[1][0] = A[0]; Dy[1][1] = A[1]; Dy[1][2] = A[2];
	Dz[2][0] = A[0]; Dz[2][1] = A[1]; Dz[2][2] = A[2];

	float detD = Determinant(D);

	if (CMP(detD, 0)) {
		return vec3(0,0,0);
	}

	float detDx = Determinant(Dx);
	float detDy = Determinant(Dy);
	float detDz = Determinant(Dz);

	return vec3(detDx / detD, detDy / detD, detDz / detD);
#else 
	vec3 m1(p1.normal[0], p2.normal[0], p3.normal[0]);
	vec3 m2(p1.normal[1], p2.normal[1], p3.normal[1]);
	vec3 m3(p1.normal[2], p2.normal[2], p3.normal[2]);
	vec3 d(-p1.distance, -p2.distance, -p3.distance);
	
	vec3 u = Cross(m2, m3);
	vec3 v = Cross(m1, d);
	float denom = Dot(m1, u);

	if (CMP(denom, 0.0f)) {
		return vec3(0,0,0);
	}

	vec3 result;
	result[0] = Dot(d, u) / denom;
	result[1] = Dot(m3, v) / denom;
	result[2] = -Dot(m2, v) / denom;
	return result;
#endif
}

void Frustum::GetCorners(vec3* outCorners) const {
	const Plane& top = planes[TOP];
	const Plane& bottom = planes[BOTTOM];
	const Plane& left = planes[LEFT];
	const Plane& right = planes[RIGHT];
	const Plane& _near = planes[NEAR];
	const Plane& _far = planes[FAR];
	outCorners[0] = Intersection(_near, top,    left);
	outCorners[1] = Intersection(_near, top,    right);
	outCorners[2] = Intersection(_near, bottom, left);
	outCorners[3] = Intersection(_near, bottom, right);
	outCorners[4] = Intersection(_far,  top,    left);
	outCorners[5] = Intersection(_far,  top,    right);
	outCorners[6] = Intersection(_far,  bottom, left);
	outCorners[7] = Intersection(_far,  bottom, right);
}

bool Frustum::Intersects(const vec3& p) const {
	for (int i = 0; i < 6; ++i) {
		vec3 normal = (*this)[i].normal;
		float dist = (*this)[i].distance;
		float side = Dot(p, normal) + dist;
		if (side < 0.0f) {
			return false;
		}
	}
	
	return true;
}

bool Frustum::Intersects(const Sphere& s) const {
	for (int i = 0; i < 6; ++i) {
		vec3 normal = (*this)[i].normal;
		float dist = (*this)[i].distance;
		float side = Dot(s.position, normal) + dist;
		if (side < -s.radius) {
			return false;
		}
	}

	return true;
}

bool Frustum::Intersects(const OBB& obb) const {
	for (int i = 0; i < 6; ++i) {
		float side = Classify(obb, (*this)[i]);
		if (side < 0) {
			return false;
		}
	}
	return true;
}

bool Frustum::Intersects(const AABB& aabb) const {
	for (int i = 0; i < 6; ++i) {
		float side = Classify(aabb, (*this)[i]);
		if (side < 0) {
			return false;
		}
	}
	return true;
}

bool Frustum::Contains(const AABB& aabb) const {
	return Intersects(aabb); // misleading name
}



NAMESPACE_TOPSIDE_END
