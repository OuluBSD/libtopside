#include "Geometry.h"

NAMESPACE_TOPSIDE_BEGIN


float Length(const line3& line) {
	return Magnitude(line.start - line.end);
}

float LengthSq(const line3& line) {
	return MagnitudeSq(line.start - line.end);
}

Ray Fromvec3s(const vec3& from, const vec3& to) {
	return Ray(
		from,
		(to - from).GetNormalized()
	);
}

vec3 GetMin(const AABB& aabb) {
	vec3 p1 = aabb.position + aabb.size;
	vec3 p2 = aabb.position - aabb.size;

	return vec3(fminf(p1[0], p2[0]), fminf(p1[1], p2[1]), fminf(p1[2], p2[2]));
}
vec3 GetMax(const AABB& aabb) {
	vec3 p1 = aabb.position + aabb.size;
	vec3 p2 = aabb.position - aabb.size;

	return vec3(fmaxf(p1[0], p2[0]), fmaxf(p1[1], p2[1]), fmaxf(p1[2], p2[2]));
}

AABB FromMinMax(const vec3& min, const vec3& max) {
	return AABB((min + max) * 0.5f, (max - min) * 0.5f);
}

float PlaneEquation(const vec3& point, const Plane& plane) {
	return Dot(point, plane.normal) - plane.distance;
}

float PlaneEquation(const Plane& plane, const vec3& point) {
	return Dot(point, plane.normal) - plane.distance;
}

Stream& operator<<(Stream& os, const line3& shape) {
	os << "start: (" << shape.start[0] << ", " << shape.start[1] << ", " << shape.start[2] << "), end: (";
	os << shape.end[0] << ", " << shape.end[1] << ", " << shape.end[2] << ")";
	return os;
}

Stream& operator<<(Stream& os, const Ray& shape) {
	os << "origin: (" << shape.origin[0] << ", " << shape.origin[1] << ", " << shape.origin[2] << "), ";
	os << "direction: (" << shape.direction[0] << ", " << shape.direction[1] << ", " << shape.direction[2] << ")";
	return os;
}

Stream& operator<<(Stream& os, const Sphere& shape) {
	os << "position:" << shape.position[0] << ", " << shape.position[1] << ", " << shape.position[2] << "), ";
	os << "radius: " << shape.radius;
	return os;
}

Stream& operator<<(Stream& os, const AABB& shape) {
	vec3 min = GetMin(shape);
	vec3 max = GetMax(shape);
	os << "min: (" << min[0] << ", " << min[1] << ", " << min[2] << "), ";
	os << "max: (" << max[0] << ", " << max[1] << ", " << max[2] << ")";
	return os;
}

Stream& operator<<(Stream& os, const Plane& shape) {
	os << "normal: (" << shape.normal[0] << ", " << shape.normal[1] << ", " << shape.normal[2] << "), ";
	os << "distance: " << shape.distance;
	return os;
}

Stream& operator<<(Stream& os, const tri3& shape) {
	os << "a: (" << shape.a[0] << ", " << shape.a[1] << ", " << shape.a[2] << "), ";
	os << "b: (" << shape.b[0] << ", " << shape.b[1] << ", " << shape.b[2] << "), ";
	os << "c: (" << shape.c[0] << ", " << shape.c[1] << ", " << shape.c[2] << ")";
	return os;
}

Stream& operator<<(Stream& os, const OBB& shape) {
	os << "position:" << shape.position[0] << ", " << shape.position[1] << ", " << shape.position[2] << "), ";
	os << "size:" << shape.size[0] << ", " << shape.size[1] << ", " << shape.size[2] << "), ";
	os << "x basis:" << shape.orientation[0][0] << ", " << shape.orientation[1][0] << ", " << shape.orientation[2][1] << "), ";
	os << "y basis:" << shape.orientation[0][1] << ", " << shape.orientation[1][1] << ", " << shape.orientation[2][1] << "), ";
	os << "z basis:" << shape.orientation[0][2] << ", " << shape.orientation[1][2] << ", " << shape.orientation[2][2] << ")";
	return os;
}

bool PointInSphere(const vec3& point, const Sphere& sphere) {
	return MagnitudeSq(point - sphere.position) < sphere.radius * sphere.radius;
}

bool PointOnPlane(const vec3& point, const Plane& plane) {
	// This should probably use an epsilon!
	//return Dot(point, plane.normal) - plane.distance == 0.0f;

	return CMP(Dot(point, plane.normal) - plane.distance, 0.0f);
}

bool PointInAABB(const vec3& point, const AABB& aabb) {
	vec3 min = GetMin(aabb);
	vec3 max = GetMax(aabb);

	if (point[0] < min[0] || point[1] < min[1] || point[2] < min[2]) {
		return false;
	}
	if (point[0] > max[0] || point[1] > max[1] || point[2] > max[2]) {
		return false;
	}

	return true;
}

bool PointInOBB(const vec3& point, const OBB& obb) {
	vec3 dir = point - obb.position;

	for (int i = 0; i < 3; ++i) {
		const vec3& orientation = obb.orientation[i];
		vec3 axis(orientation[0], orientation[1], orientation[2]);

		float distance = Dot(dir, axis);

		if (distance > obb.size[i]) {
			return false;
		}
		if (distance < -obb.size[i]) {
			return false;
		}
	}

	return true;
}

vec3 ClosestPoint(const Sphere& sphere, const vec3& point) {
	vec3 sphereTovec3 = point - sphere.position;
	Normalize(sphereTovec3);
	sphereTovec3 = sphereTovec3 * sphere.radius;
	return sphereTovec3 + sphere.position;
}

vec3 ClosestPoint(const AABB& aabb, const vec3& point) {
	vec3 result = point;
	vec3 min = GetMin(aabb);
	vec3 max = GetMax(aabb);

	result[0] = (result[0] < min[0]) ? min[0] : result[0];
	result[1] = (result[1] < min[1]) ? min[1] : result[1];
	result[2] = (result[2] < min[2]) ? min[2] : result[2];

	result[0] = (result[0] > max[0]) ? max[0] : result[0];
	result[1] = (result[1] > max[1]) ? max[1] : result[1];
	result[2] = (result[2] > max[2]) ? max[2] : result[2];

	return result;
}

vec3 ClosestPoint(const OBB& obb, const vec3& point) {
	vec3 result = obb.position;
	vec3 dir = point - obb.position;

	for (int i = 0; i < 3; ++i) {
		const vec3& orientation = obb.orientation[i];
		vec3 axis(orientation[0], orientation[1], orientation[2]);

		float distance = Dot(dir, axis);

		if (distance > obb.size[i]) {
			distance = obb.size[i];
		}
		if (distance < -obb.size[i]) {
			distance = -obb.size[i];
		}

		result = result + (axis * distance);
	}

	return result;
}

vec3 ClosestPoint(const Plane& plane, const vec3& point) {
	// This works assuming plane.Normal is normalized, which it should be
	float distance = Dot(plane.normal, point) - plane.distance;
	// If the plane normal wasn't normalized, we'd need this:
	// distance = distance / DOT(plane.Normal, plane.Normal);

	return point - plane.normal * distance;
}

bool PointOnLine(const vec3& point, const line3& line) {
	vec3 closest = ClosestPoint(line, point);
	float distanceSq = MagnitudeSq(closest - point);
	return CMP(distanceSq, 0.0f);
}

vec3 ClosestPoint(const line3& line, const vec3& point) {
	vec3 lVec = line.end - line.start; // Line Vector
	// Project "point" onto the "Line Vector", computing:
	// closest(t) = start + t * (end - start)
	// T is how far along the line the projected point is
	float t = Dot(point - line.start, lVec) / Dot(lVec, lVec);
	// Clamp t to the 0 to 1 range
	t = fmaxf(t, 0.0f);
	t = fminf(t, 1.0f);
	// Return projected position of t
	return line.start + lVec * t;
}

bool PointOnRay(const vec3& point, const Ray& ray) {
	if (point == ray.origin) {
		return true;
	}

	vec3 norm = point - ray.origin;
	Normalize(norm);
	float diff = Dot(norm, ray.direction); // Direction is normalized
	// If BOTH vectors point in the same direction, diff should be 1
	return CMP(diff, 1.0f);
}

vec3 ClosestPoint(const Ray& ray, const vec3& point) {
	// Project point onto ray, 
	float t = Dot(point - ray.origin, ray.direction);
	// Not needed if direction is normalized!
	// t /= Dot(ray.direction, ray.direction);

	// We only want to clamp t in the positive direction.
	// The ray extends infinatley in this direction!
	t = fmaxf(t, 0.0f);

	// Compute the projected position from the clamped t
	// Notice we multiply r.Normal by t, not AB.
	// This is becuase we want the ray in the direction 
	// of the normal, which technically the line segment is
	// but this is much more explicit and easy to read.
	return vec3(ray.origin + ray.direction * t);
}

bool PointInPlane(const vec3& point, const Plane& plane) {
	return PointOnPlane(point, plane);
}
bool PointInLine(const vec3& point, const line3& line) {
	return PointOnLine(point, line);
}
bool PointInRay(const vec3& point, const Ray& ray) {
	return PointOnRay(point, ray);
}
bool ContainsPoint(const Sphere& sphere, const vec3& point) {
	return PointInSphere(point, sphere);
}
bool ContainsPoint(const vec3& point, const Sphere& sphere) {
	return PointInSphere(point, sphere);
}
bool ContainsPoint(const AABB& aabb, const vec3& point) {
	return PointInAABB(point, aabb);
}
bool ContainsPoint(const vec3& point, const AABB& aabb) {
	return PointInAABB(point, aabb);
}
bool ContainsPoint(const vec3& point, const OBB& obb) {
	return PointInOBB(point, obb);
}
bool ContainsPoint(const OBB& obb, const vec3& point) {
	return PointInOBB(point, obb);
}
bool ContainsPoint(const vec3& point, const Plane& plane) {
	return PointOnPlane(point, plane);
}
bool ContainsPoint(const Plane& plane, const vec3& point) {
	return PointOnPlane(point, plane);
}
bool ContainsPoint(const vec3& point, const line3& line) {
	return PointOnLine(point, line);
}
bool ContainsPoint(const line3& line, const vec3& point) {
	return PointOnLine(point, line);
}
bool ContainsPoint(const vec3& point, const Ray& ray) {
	return PointOnRay(point, ray);
}
bool ContainsPoint(const Ray& ray, const vec3& point) {
	return PointOnRay(point, ray);
}
vec3 ClosestPoint(const vec3& point, const Sphere& sphere) {
	return ClosestPoint(sphere, point);
}
vec3 ClosestPoint(const vec3& point, const AABB& aabb) {
	return ClosestPoint(aabb, point);
}
vec3 ClosestPoint(const vec3& point, const OBB& obb) {
	return ClosestPoint(obb, point);
}
vec3 ClosestPoint(const vec3& point, const Plane& plane) {
	return ClosestPoint(plane, point);
}
vec3 ClosestPoint(const vec3& point, const line3& line) {
	return ClosestPoint(line, point);
}
vec3 ClosestPoint(const vec3& point, const Ray& ray) {
	return ClosestPoint(ray, point);
}
vec3 ClosestPoint(const vec3& p, const tri3& t) {
	return ClosestPoint(t, p);
}

bool SphereSphere(const Sphere& s1, const Sphere& s2) {
	float radiiSum = s1.radius + s2.radius;
	float sqDistance = MagnitudeSq(s1.position - s2.position);
	return sqDistance < radiiSum * radiiSum;
}

bool SphereAABB(const Sphere& sphere, const AABB& aabb) {
	vec3 closest_pt = ClosestPoint(aabb, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closest_pt);
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

bool SphereOBB(const Sphere& sphere, const OBB& obb) {
	vec3 closest_pt = ClosestPoint(obb, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closest_pt);
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

bool SpherePlane(const Sphere& sphere, const Plane& plane) {
	vec3 closest_pt = ClosestPoint(plane, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closest_pt);
	float radiusSq = sphere.radius * sphere.radius;
	return distSq < radiusSq;
}

bool AABBAABB(const AABB& aabb1, const AABB& aabb2) {
	vec3 aMin = GetMin(aabb1);
	vec3 aMax = GetMax(aabb1);
	vec3 bMin = GetMin(aabb2);
	vec3 bMax = GetMax(aabb2);

	return	(aMin[0] <= bMax[0] && aMax[0] >= bMin[0]) &&
			(aMin[1] <= bMax[1] && aMax[1] >= bMin[1]) &&
			(aMin[2] <= bMax[2] && aMax[2] >= bMin[2]);
}

bool AABBOBB(const AABB& aabb, const OBB& obb) {
	const auto& o = obb.orientation;

	vec3 test[15] = {
		vec3(1, 0, 0), // AABB axis 1
		vec3(0, 1, 0), // AABB axis 2
		vec3(0, 0, 1), // AABB axis 3
		vec3(o[0][0], o[0][1], o[0][2]),
		vec3(o[1][0], o[1][1], o[1][2]),
		vec3(o[2][0], o[2][1], o[2][2])
	};

	for (int i = 0; i < 3; ++i) { // Fill out rest of axis
		test[6 + i * 3 + 0] = Cross(test[i], test[0]);
		test[6 + i * 3 + 1] = Cross(test[i], test[1]);
		test[6 + i * 3 + 2] = Cross(test[i], test[2]);
	}

	for (int i = 0; i < 15; ++i) {
		if (!OverlapOnAxis(aabb, obb, test[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool OverlapOnAxis(const AABB& aabb, const OBB& obb, const vec3& axis) {
	Interval a = GetInterval(aabb, axis);
	Interval b = GetInterval(obb, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(const OBB& obb1, const OBB& obb2, const vec3& axis) {
	Interval a = GetInterval(obb1, axis);
	Interval b = GetInterval(obb1, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(const AABB& aabb, const tri3& triangle, const vec3& axis) {
	Interval a = GetInterval(aabb, axis);
	Interval b = GetInterval(triangle, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(const OBB& obb, const tri3& triangle, const vec3& axis) {
	Interval a = GetInterval(obb, axis);
	Interval b = GetInterval(triangle, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

bool OverlapOnAxis(const tri3& t1, const tri3& t2, const vec3& axis) {
	Interval a = GetInterval(t1, axis);
	Interval b = GetInterval(t2, axis);
	return ((b.min <= a.max) && (a.min <= b.max));
}

Interval GetInterval(const tri3& triangle, const vec3& axis) {
	Interval result;

	result.min = Dot(axis, triangle.points[0]);
	result.max = result.min;
	for (int i = 1; i < 3; ++i) {
		float value = Dot(axis, triangle.points[i]);
		result.min = fminf(result.min, value);
		result.max = fmaxf(result.max, value);
	}

	return result;
}

Interval GetInterval(const OBB& obb, const vec3& axis) {
	vec3 vertex[8];

	vec3 C = obb.position;	// OBB Center
	vec3 E = obb.size;		// OBB Extents
	const auto& o = obb.orientation;
	vec3 A[3] = {			// OBB Axis
		o[0],
		o[1],
		o[2]
	};

	vertex[0] = C + A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	vertex[1] = C - A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	vertex[2] = C + A[0] * E[0] - A[1] * E[1] + A[2] * E[2];
	vertex[3] = C + A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	vertex[4] = C - A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	vertex[5] = C + A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	vertex[6] = C - A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	vertex[7] = C - A[0] * E[0] - A[1] * E[1] + A[2] * E[2];

	Interval result;
	result.min = result.max = Dot(axis, vertex[0]);

	for (int i = 1; i < 8; ++i) {
		float projection = Dot(axis, vertex[i]);
		result.min = (projection < result.min) ? projection : result.min;
		result.max = (projection > result.max) ? projection : result.max;
	}

	return result;
}

Interval GetInterval(const AABB& aabb, const vec3& axis) {
	vec3 i = GetMin(aabb);
	vec3 a = GetMax(aabb);

	vec3 vertex[8] = {
		vec3(i[0], a[1], a[2]),
		vec3(i[0], a[1], i[2]),
		vec3(i[0], i[1], a[2]),
		vec3(i[0], i[1], i[2]),
		vec3(a[0], a[1], a[2]),
		vec3(a[0], a[1], i[2]),
		vec3(a[0], i[1], a[2]),
		vec3(a[0], i[1], i[2])
	};

	Interval result;
	result.min = result.max = Dot(axis, vertex[0]);

	for (int i = 1; i < 8; ++i) {
		float projection = Dot(axis, vertex[i]);
		result.min = (projection < result.min) ? projection : result.min;
		result.max = (projection > result.max) ? projection : result.max;
	}

	return result;
}

bool AABBPlane(const AABB& aabb, const Plane& plane) {
	// Project the half extents of the AABB onto the plane normal
	float pLen =aabb.size[0] * fabsf(plane.normal[0]) +
				aabb.size[1] * fabsf(plane.normal[1]) +
				aabb.size[2] * fabsf(plane.normal[2]);
	// Find the distance from the center of the AABB to the plane
	float dist = Dot(plane.normal, aabb.position) - plane.distance;
	// Intersection occurs if the distance falls within the projected side
	return fabsf(dist) <= pLen;
}

bool OBBOBB(const OBB& obb1, const OBB& obb2) {
	const auto& o1 = obb1.orientation;
	const auto& o2 = obb2.orientation;

	vec3 test[15] = {
		o1[0],
		o1[1],
		o1[2],
		o2[0],
		o2[1],
		o2[2]
	};

	for (int i = 0; i < 3; ++i) { // Fill out rest of axis
		test[6 + i * 3 + 0] = Cross(test[i], test[0]);
		test[6 + i * 3 + 1] = Cross(test[i], test[1]);
		test[6 + i * 3 + 2] = Cross(test[i], test[2]);
	}

	for (int i = 0; i < 15; ++i) {
		if (!OverlapOnAxis(obb1, obb2, test[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool OBBPlane(const OBB& obb, const Plane& plane) {
	// Local variables for readability only
	const auto& o = obb.orientation;
	vec3 rot[] = { // rotation / orientation
		o[0],
		o[1],
		o[2]
	};
	vec3 normal = plane.normal;

	// Project the half extents of the AABB onto the plane normal
	float pLen =obb.size[0] * fabsf(Dot(normal, rot[0])) +
				obb.size[1] * fabsf(Dot(normal, rot[1])) +
				obb.size[2] * fabsf(Dot(normal, rot[2]));
	// Find the distance from the center of the OBB to the plane
	float dist = Dot(plane.normal, obb.position) - plane.distance;
	// Intersection occurs if the distance falls within the projected side
	return fabsf(dist) <= pLen;
}

bool PlanePlane(const Plane& plane1, const Plane& plane2) {
	// Compute direction of intersection line
	vec3 d = Cross(plane1.normal, plane2.normal);

	// Check the length of the direction line
	// if the length is 0, no intersection happened
	return !(CMP(Dot(d, d), 0));

	// We could have used the dot product here, instead of the cross product
}

bool Raycast(const Sphere& sphere, const Ray& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);

	vec3 e = sphere.position - ray.origin;
	float rSq = sphere.radius * sphere.radius;

	float eSq = MagnitudeSq(e);
	float a = Dot(e, ray.direction); // ray.direction is assumed to be normalized
	float bSq = /*sqrtf(*/eSq - (a * a)/*)*/;
	float f = sqrt(fabsf((rSq)- /*(b * b)*/bSq));

	// Assume normal intersection!
	float t = a - f;

	// No collision has happened
	if (rSq - (eSq - a * a) < 0.0f) {
		return false;
	}
	// Ray starts inside the sphere
	else if (eSq < rSq) {
		// Just reverse direction
		t = a + f;
	}
	if (outResult != 0) {
		outResult->t = t;
		outResult->hit = true;
		outResult->point = ray.origin + ray.direction * t;
		outResult->normal = (outResult->point - sphere.position).GetNormalized();
	}
	return true;
}

bool Raycast(const OBB& obb, const Ray& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);

	const auto& o = obb.orientation;
	const auto& size = obb.size;

	vec3 p = obb.position - ray.origin;

	const vec3& X = o[0];
	const vec3& Y = o[1];
	const vec3& Z = o[2];

	vec3 f(
		Dot(X, ray.direction),
		Dot(Y, ray.direction),
		Dot(Z, ray.direction)
	);

	vec3 e(
		Dot(X, p),
		Dot(Y, p),
		Dot(Z, p)
	);

#if 1
	float t[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 3; ++i) {
		if (CMP(f[i], 0)) {
			if (-e[i] - size[i] > 0 || -e[i] + size[i] < 0) {
				return false;
			}
			f[i] = 0.00001f; // Avoid div by 0!
		}

		t[i * 2 + 0] = (e[i] + size[i]) / f[i]; // tmin[x, y, z]
		t[i * 2 + 1] = (e[i] - size[i]) / f[i]; // tmax[x, y, z]
	}

	float tmin = fmaxf(fmaxf(fminf(t[0], t[1]), fminf(t[2], t[3])), fminf(t[4], t[5]));
	float tmax = fminf(fminf(fmaxf(t[0], t[1]), fmaxf(t[2], t[3])), fmaxf(t[4], t[5]));
#else 
	// The above loop simplifies the below if statements
	// this is done to make sure the sample fits into the book
	if (CMP(f[0], 0)) {
		if (-e[0] - obb.size[0] > 0 || -e[0] + obb.size[0] < 0) {
			return -1;
		}
		f[0] = 0.00001f; // Avoid div by 0!
	}
	else if (CMP(f[1], 0)) {
		if (-e[1] - obb.size[1] > 0 || -e[1] + obb.size[1] < 0) {
			return -1;
		}
		f[1] = 0.00001f; // Avoid div by 0!
	}
	else if (CMP(f[2], 0)) {
		if (-e[2] - obb.size[2] > 0 || -e[2] + obb.size[2] < 0) {
			return -1;
		}
		f[2] = 0.00001f; // Avoid div by 0!
	}

	float t1 = (e[0] + obb.size[0]) / f[0];
	float t2 = (e[0] - obb.size[0]) / f[0];
	float t3 = (e[1] + obb.size[1]) / f[1];
	float t4 = (e[1] - obb.size[1]) / f[1];
	float t5 = (e[2] + obb.size[2]) / f[2];
	float t6 = (e[2] - obb.size[2]) / f[2];

	float tmin = fmaxf(fmaxf(fminf(t1, t2), fminf(t3, t4)), fminf(t5, t6));
	float tmax = fminf(fminf(fmaxf(t1, t2), fmaxf(t3, t4)), fmaxf(t5, t6));
#endif

	// if tmax < 0, ray is intersecting AABB
	// but entire AABB is behing it's origin
	if (tmax < 0) {
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return false;
	}

	// If tmin is < 0, tmax is closer
	float t_result = tmin;

	if (tmin < 0.0f) {
		t_result = tmax;
	}

	if (outResult != 0) {
		outResult->hit = true;
		outResult->t = t_result;
		outResult->point = ray.origin + ray.direction * t_result;

		vec3 normals[] = {
			X,			// +x
			X * -1.0f,	// -x
			Y,			// +y
			Y * -1.0f,	// -y
			Z,			// +z
			Z * -1.0f	// -z
		};

		for (int i = 0; i < 6; ++i) {
			if (CMP(t_result, t[i])) {
				//outResult->normal = normals[i].GetUnsafeNormalized();
				vec3 v = normals[i];
				v.Normalize(true);
				outResult->normal = v;
			}
		}
	}
	return true;
}

void ResetRaycastResult(RaycastResult* outResult) {
	if (outResult != 0) {
		outResult->t = -1;
		outResult->hit = false;
		outResult->normal = vec3(0, 0, 1);
		outResult->point = vec3(0, 0, 0);
	}
}

bool Raycast(const AABB& aabb, const Ray& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);

	vec3 min = GetMin(aabb);
	vec3 max = GetMax(aabb);

	// Any component of direction could be 0!
	// Address this by using a small number, close to
	// 0 in case any of directions components are 0
	float t1 = (min[0] - ray.origin[0]) / (CMP(ray.direction[0], 0.0f) ? 0.00001f : ray.direction[0]);
	float t2 = (max[0] - ray.origin[0]) / (CMP(ray.direction[0], 0.0f) ? 0.00001f : ray.direction[0]);
	float t3 = (min[1] - ray.origin[1]) / (CMP(ray.direction[1], 0.0f) ? 0.00001f : ray.direction[1]);
	float t4 = (max[1] - ray.origin[1]) / (CMP(ray.direction[1], 0.0f) ? 0.00001f : ray.direction[1]);
	float t5 = (min[2] - ray.origin[2]) / (CMP(ray.direction[2], 0.0f) ? 0.00001f : ray.direction[2]);
	float t6 = (max[2] - ray.origin[2]) / (CMP(ray.direction[2], 0.0f) ? 0.00001f : ray.direction[2]);

	float tmin = fmaxf(fmaxf(fminf(t1, t2), fminf(t3, t4)), fminf(t5, t6));
	float tmax = fminf(fminf(fmaxf(t1, t2), fmaxf(t3, t4)), fmaxf(t5, t6));

	// if tmax < 0, ray is intersecting AABB
	// but entire AABB is behing it's origin
	if (tmax < 0) {
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax) {
		return false;
	}

	float t_result = tmin;

	// If tmin is < 0, tmax is closer
	if (tmin < 0.0f) {
		t_result = tmax;
	}

	if (outResult != 0) {
		outResult->t = t_result;
		outResult->hit = true;
		outResult->point = ray.origin + ray.direction * t_result;

		vec3 normals[] = {
			vec3(-1, 0, 0),
			vec3(1, 0, 0),
			vec3(0, -1, 0),
			vec3(0, 1, 0),
			vec3(0, 0, -1),
			vec3(0, 0, 1)
		};
		float t[] = { t1, t2, t3, t4, t5, t6 };

		for (int i = 0; i < 6; ++i) {
			if (CMP(t_result, t[i])) {
				outResult->normal = normals[i];
			}
		}
	}

	return true;
}

bool Raycast(const Plane& plane, const Ray& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);

	float nd = Dot(ray.direction, plane.normal);
	float pn = Dot(ray.origin, plane.normal);

	// nd must be negative, and not 0
	// if nd is positive, the ray and plane normals
	// point in the same direction. No intersection.
	if (nd >= 0.0f) {
		return false;
	}

	float t = (plane.distance - pn) / nd;

	// t must be positive
	if (t >= 0.0f) {
		if (outResult != 0) {
			outResult->t = t;
			outResult->hit = true;
			outResult->point = ray.origin + ray.direction * t;
			outResult->normal = plane.normal.GetNormalized();
		}
		return true;
	}

	return false;
}

bool Linetest(const Sphere& sphere, const line3& line) {
	vec3 closest = ClosestPoint(line, sphere.position);
	float distSq = MagnitudeSq(sphere.position - closest);
	return distSq <= (sphere.radius * sphere.radius);
}

bool Linetest(const Plane& plane, const line3& line) {
	vec3 ab = line.end - line.start;

	float nA = Dot(plane.normal, line.start);
	float nAB = Dot(plane.normal, ab);

	if (CMP(nAB, 0)) {
		return false;
	}

	float t = (plane.distance - nA) / nAB;
	return t >= 0.0f && t <= 1.0f;
}

bool Linetest(const AABB& aabb, const line3& line) {
	Ray ray;
	ray.origin = line.start;
	ray.direction = (line.end - line.start).GetNormalized();
	RaycastResult raycast;
	if (!Raycast(aabb, ray, &raycast)) {
		return false;
	}
	float t = raycast.t;

	return t >= 0 && t * t <= LengthSq(line);
}

bool Linetest(const OBB& obb, const line3& line) {
	if (MagnitudeSq(line.end - line.start) < 0.0000001f) {
		return PointInOBB(line.start, obb);
	}
	Ray ray;
	ray.origin = line.start;
	ray.direction = (line.end - line.start).GetNormalized();
	RaycastResult result;
	if (!Raycast(obb, ray, &result)) {
		return false;
	}
	float t = result.t;

	return t >= 0 && t * t <= LengthSq(line);
}

bool Raycast(const Ray& ray, const Sphere& sphere, RaycastResult* outResult) {
	return Raycast(sphere, ray, outResult);
}

bool Raycast(const Ray& ray, const AABB& aabb, RaycastResult* outResult) {
	return Raycast(aabb, ray, outResult);
}

bool Raycast(const Ray& ray, const OBB& obb, RaycastResult* outResult) {
	return Raycast(obb, ray, outResult);
}

bool Raycast(const Ray& ray, const Plane& plane, RaycastResult* outResult) {
	return Raycast(plane, ray, outResult);
}

bool Linetest(const line3& line, const Sphere& sphere) {
	return Linetest(sphere, line);
}

bool Linetest(const line3& line, const AABB& aabb) {
	return Linetest(aabb, line);
}

bool Linetest(const line3& line, const OBB& obb) {
	return Linetest(obb, line);
}

bool Linetest(const line3& line, const Plane& plane) {
	return Linetest(plane, line);
}

vec3 Centroid(const tri3& t) {
	vec3 result;
	result[0] = t.a[0] + t.b[0] + t.c[0];
	result[1] = t.a[1] + t.b[1] + t.c[1];
	result[2] = t.a[2] + t.b[2] + t.c[2];
	result = result * (1.0f / 3.0f);
	return result;
}

bool PointInTriangle(const vec3& p, const tri3& t) {
	// Move the triangle so that the point is  
	// now at the origin of the triangle
	vec3 a = t.a - p;
	vec3 b = t.b - p;
	vec3 c = t.c - p;

	// The point should be moved too, so they are both
	// relative, but because we don't use p in the
	// equation anymore, we don't need it!
	// p -= p; // This would just equal the zero vector!

	vec3 normPBC = Cross(b, c); // Normal of PBC (u)
	vec3 normPCA = Cross(c, a); // Normal of PCA (v)
	vec3 normPAB = Cross(a, b); // Normal of PAB (w)

	// Test to see if the normals are facing
	// the same direction, return false if not
	if (Dot(normPBC, normPCA) < 0.0f) {
		return false;
	}
	else if (Dot(normPBC, normPAB) < 0.0f) {
		return false;
	}

	// All normals facing the same way, return true
	return true;
}

vec3 BarycentricOptimized(const vec3& p, const tri3& t) {
	vec3 v0 = t.b - t.a;
	vec3 v1 = t.c - t.a;
	vec3 v2 = p - t.a;

	float d00 = Dot(v0, v0);
	float d01 = Dot(v0, v1);
	float d11 = Dot(v1, v1);
	float d20 = Dot(v2, v0);
	float d21 = Dot(v2, v1);
	float denom = d00 * d11 - d01 * d01;

	if (CMP(denom, 0.0f)) {
		return vec3();
	}

	vec3 result;
	result[1] = (d11 * d20 - d01 * d21) / denom;
	result[2] = (d00 * d21 - d01 * d20) / denom;
	result[0] = 1.0f - result[1] - result[2];

	return result;
}

vec3 Barycentric(const vec3& p, const tri3& t) {
	vec3 ap = p - t.a;
	vec3 bp = p - t.b;
	vec3 cp = p - t.c;

	vec3 ab = t.b - t.a;
	vec3 ac = t.c - t.a;
	vec3 bc = t.c - t.b;
	vec3 cb = t.b - t.c;
	vec3 ca = t.a - t.c;

	vec3 v = ab - Project(ab, cb);
	float a = 1.0f - (Dot(v, ap) / Dot(v, ab));

	v = bc - Project(bc, ac);
	float b = 1.0f - (Dot(v, bp) / Dot(v, bc));

	v = ca - Project(ca, ab);
	float c = 1.0f - (Dot(v, cp) / Dot(v, ca));

	return vec3(a, b, c);
}

Plane FromTriangle(const tri3& t) {
	Plane result;
	result.normal = (Cross(t.b - t.a, t.c - t.a)).GetNormalized();
	result.distance = Dot(result.normal, t.a);
	return result;
}

vec3 ClosestPoint(const tri3& t, const vec3& p) {
	Plane plane = FromTriangle(t);
	vec3 closest = ClosestPoint(plane, p);

	// Closest point was inside triangle
	if (PointInTriangle(closest, t)) {
		return closest;
	}

	vec3 c1 = ClosestPoint(line3(t.a, t.b), closest); // Line AB
	vec3 c2 = ClosestPoint(line3(t.b, t.c), closest); // Line BC
	vec3 c3 = ClosestPoint(line3(t.c, t.a), closest); // Line CA

	float magSq1 = MagnitudeSq(closest - c1);
	float magSq2 = MagnitudeSq(closest - c2);
	float magSq3 = MagnitudeSq(closest - c3);

	if (magSq1 < magSq2 && magSq1 < magSq3) {
		return c1;
	}
	else if (magSq2 < magSq1 && magSq2 < magSq3) {
		return c2;
	}

	return c3;
}

bool TriangleSphere(const tri3& t, const Sphere& s) {
	vec3 closest = ClosestPoint(t, s.position);
	float magSq = MagnitudeSq(closest - s.position);
	return magSq <= s.radius * s.radius;
}

bool TriangleAABB(const tri3& t, const AABB& a) {
	// Compute the edge vectors of the triangle  (ABC)
	vec3 f0 = t.b - t.a; 
	vec3 f1 = t.c - t.b; 
	vec3 f2 = t.a - t.c; 

	// Compute the face normals of the AABB
	vec3 u0(1.0f, 0.0f, 0.0f);
	vec3 u1(0.0f, 1.0f, 0.0f);
	vec3 u2(0.0f, 0.0f, 1.0f);

	vec3 test[13] = {
		// 3 Normals of AABB
		u0, // AABB Axis 1
		u1, // AABB Axis 2
		u2, // AABB Axis 3
		// 1 Normal of the Triangle
		Cross(f0, f1),
		// 9 Axis, cross products of all edges
		Cross(u0, f0),
		Cross(u0, f1),
		Cross(u0, f2),
		Cross(u1, f0),
		Cross(u1, f1),
		Cross(u1, f2),
		Cross(u2, f0),
		Cross(u2, f1),
		Cross(u2, f2)
	};

	for (int i = 0; i < 13; ++i) {
		if (!OverlapOnAxis(a, t, test[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool TriangleOBB(const tri3& t, const OBB& o) {
	// Compute the edge vectors of the triangle  (ABC)
	vec3 f0 = t.b - t.a;
	vec3 f1 = t.c - t.b;
	vec3 f2 = t.a - t.c;

	// Compute the face normals of the AABB
	const auto& orientation = o.orientation;
	vec3 u0 = orientation[0];
	vec3 u1 = orientation[1];
	vec3 u2 = orientation[2];

	vec3 test[13] = {
		// 3 Normals of AABB
		u0, // AABB Axis 1
		u1, // AABB Axis 2
		u2, // AABB Axis 3
		// 1 Normal of the Triangle
		Cross(f0, f1),
		// 9 Axis, cross products of all edges
		Cross(u0, f0),
		Cross(u0, f1),
		Cross(u0, f2),
		Cross(u1, f0),
		Cross(u1, f1),
		Cross(u1, f2),
		Cross(u2, f0),
		Cross(u2, f1),
		Cross(u2, f2)
	};

	for (int i = 0; i < 13; ++i) {
		if (!OverlapOnAxis(o, t, test[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool TriangleTriangle(const tri3& t1, const tri3& t2) {
#if 0
	vec3 axisToTest[] = {
		// Triangle 1, Normal
		SatCrossEdge(t1.a, t1.b, t1.b, t1.c),
		// Triangle 2, Normal
		SatCrossEdge(t2.a, t2.b, t2.b, t2.c),

		// Cross Product of edges
		SatCrossEdge(t2.a, t2.b, t1.a, t1.b),
		SatCrossEdge(t2.a, t2.b, t1.b, t1.c),
		SatCrossEdge(t2.a, t2.b, t1.c, t1.a),

		SatCrossEdge(t2.b, t2.c, t1.a, t1.b),
		SatCrossEdge(t2.b, t2.c, t1.b, t1.c),
		SatCrossEdge(t2.b, t2.c, t1.c, t1.a),

		SatCrossEdge(t2.c, t2.a, t1.a, t1.b),
		SatCrossEdge(t2.c, t2.a, t1.b, t1.c),
		SatCrossEdge(t2.c, t2.a, t1.c, t1.a),
	};
#else 
	vec3 t1_f0 = t1.b - t1.a; // Edge 0
	vec3 t1_f1 = t1.c - t1.b; // Edge 1
	vec3 t1_f2 = t1.a - t1.c; // Edge 2

	vec3 t2_f0 = t2.b - t2.a; // Edge 0
	vec3 t2_f1 = t2.c - t2.b; // Edge 1
	vec3 t2_f2 = t2.a - t2.c; // Edge 2

	vec3 axisToTest[] = {
		// Triangle 1, Normal
		Cross(t1_f0, t1_f1),
		// Triangle 2, Normal
		Cross(t2_f0, t2_f1),

		// Cross Product of edges
		Cross(t2_f0, t1_f0),
		Cross(t2_f0, t1_f1),
		Cross(t2_f0, t1_f2),

		Cross(t2_f1, t1_f0),
		Cross(t2_f1, t1_f1),
		Cross(t2_f1, t1_f2),

		Cross(t2_f2, t1_f0),
		Cross(t2_f2, t1_f1),
		Cross(t2_f2, t1_f2),
	};
#endif

	for (int i = 0; i < 11; ++i) {
		if (!OverlapOnAxis(t1, t2, axisToTest[i])) {
			return false; // Seperating axis found
		}
	}

	return true; // Seperating axis not found
}

bool TriangleTriangleRobust(const tri3& t1, const tri3& t2) {
	vec3 axisToTest[] = {
		// Triangle 1, Normal
		SatCrossEdge(t1.a, t1.b, t1.b, t1.c),
		// Triangle 2, Normal
		SatCrossEdge(t2.a, t2.b, t2.b, t2.c),

		// Cross Product of edges
		SatCrossEdge(t2.a, t2.b, t1.a, t1.b),
		SatCrossEdge(t2.a, t2.b, t1.b, t1.c),
		SatCrossEdge(t2.a, t2.b, t1.c, t1.a),

		SatCrossEdge(t2.b, t2.c, t1.a, t1.b),
		SatCrossEdge(t2.b, t2.c, t1.b, t1.c),
		SatCrossEdge(t2.b, t2.c, t1.c, t1.a),

		SatCrossEdge(t2.c, t2.a, t1.a, t1.b),
		SatCrossEdge(t2.c, t2.a, t1.b, t1.c),
		SatCrossEdge(t2.c, t2.a, t1.c, t1.a),
	};

	for (int i = 0; i < 11; ++i) {
		if (!OverlapOnAxis(t1, t2, axisToTest[i])) {
			if (!CMP(MagnitudeSq(axisToTest[i]), 0)) {
				return false; // Seperating axis found
			}
		}
	}

	return true; // Seperating axis not found
}

vec3 SatCrossEdge(const vec3& a, const vec3& b, const vec3& c, const vec3& d) {
	vec3 ab = b - a;
	vec3 cd = d - c;

	vec3 result = Cross(ab, cd);
	if (!CMP(MagnitudeSq(result), 0)) { // Is ab and cd parallel?
		return result; // Not parallel!
	}
	else { // ab and cd are parallel
		// Get an axis perpendicular to AB
		vec3 axis = Cross(ab, c - a);
		result = Cross(ab, axis);
		if (!CMP(MagnitudeSq(result), 0)) { // Still parallel?
			return result; // Not parallel
		}
	}
	// New axis being tested is parallel too.
	// This means that a, b, c and d are on a line
	// Nothing we can do!
	return vec3();
}

vec3 debugRaycastResult;

bool Raycast(const tri3& triangle, const Ray& ray, RaycastResult* outResult) {
	ResetRaycastResult(outResult);
	Plane plane = FromTriangle(triangle);

	RaycastResult planeResult;
	if (!Raycast(plane, ray, &planeResult)) {
		return false;
	}
	float t = planeResult.t;

	vec3 result = ray.origin + ray.direction * t;
	
	vec3 barycentric = Barycentric(result, triangle);
	if (barycentric[0] >= 0.0f && barycentric[0] <= 1.0f &&
		barycentric[1] >= 0.0f && barycentric[1] <= 1.0f &&
		barycentric[2] >= 0.0f && barycentric[2] <= 1.0f) {

		if (outResult != 0) {
			outResult->t = t;
			outResult->hit = true;
			outResult->point = ray.origin + ray.direction * t;
			outResult->normal = plane.normal;
		}

		return true;
	}

	return false;
}

bool Linetest(const tri3& triangle, const line3& line) {
	Ray ray;
	ray.origin = line.start;
	ray.direction = Normalized(line.end - line.start);
	RaycastResult raycast;
	if (!Raycast(triangle, ray, &raycast)) {
		return false;
	}
	float t = raycast.t;

	return t >= 0 && t * t <= LengthSq(line);
}

bool TrianglePlane(const tri3& t, const Plane& p) {
	float side1 = PlaneEquation(t.a, p);
	float side2 = PlaneEquation(t.b, p);
	float side3 = PlaneEquation(t.c, p);

	// On Plane
	if (CMP(side1, 0) && CMP(side2, 0) && CMP(side3, 0)) {
		return true;
	}

	// Triangle in front of plane
	if (side1 > 0 && side2 > 0 && side3 > 0) {
		return false;
	}

	// Triangle behind plane
	if (side1 < 0 && side2 < 0 && side3 < 0) {
		return false;
	}

	return true; // Intersection
}

vec3 Unproject(const vec3& viewport_pt, const vec2& viewportOrigin, const vec2& viewportSize, const mat4& view, const mat4& projection) {
	// Step 1, Normalize the input vector to the view port
	vec4 normalized {
		(viewport_pt[0] - viewportOrigin[0]) / viewportSize[0],
		(viewport_pt[1] - viewportOrigin[1]) / viewportSize[1],
		viewport_pt[2],
		1.0f
	};

	// Step 2, Translate into NDC space
	vec4 ndcSpace {
		normalized[0], normalized[1],
		normalized[2], normalized[3]
	};
	// X Range: -1 to 1
	ndcSpace[0] = ndcSpace[0] * 2.0f - 1.0f;
	// Y Range: -1 to 1, our Y axis is flipped!
	ndcSpace[1] = 1.0f - ndcSpace[1] * 2.0f;
	// Z Range: 0 to 1
	if (ndcSpace[2] < 0.0f) {
		ndcSpace[2] = 0.0f;
	}
	if (ndcSpace[2] > 1.0f) {
		ndcSpace[2] = 1.0f;
	}

	// Step 3, NDC to Eye Space
	mat4 invProjection = Inverse(projection);
	vec4 eyeSpace { 0.0f, 0.0f, 0.0f, 0.0f };
	// eyeSpace = Multiplyvec3(ndcSpace, invProjection);
	Multiply(eyeSpace, ndcSpace, invProjection);

	// Step 4, Eye Space to World Space
	mat4 invView = Inverse(view);
	vec4 worldSpace { 0.0f, 0.0f, 0.0f, 0.0f };
	// worldSpace = Multiplyvec3(eyeSpace, invView);
	Multiply(worldSpace, eyeSpace, invView);

	// Step 5, Undo perspective divide!
	if (!CMP(worldSpace[3], 0.0f)) {
		worldSpace[0] /= worldSpace[3];
		worldSpace[1] /= worldSpace[3];
		worldSpace[2] /= worldSpace[3];
	}

	// Return the resulting world space point
	return vec3(worldSpace[0], worldSpace[1], worldSpace[2]);
}

Ray GetPickRay(const vec2& viewport_pt, const vec2& viewportOrigin, const vec2& viewportSize, const mat4& view, const mat4& projection) {
	vec3 nearvec3(viewport_pt[0], viewport_pt[1], 0.0f);
	vec3 farvec3(viewport_pt[0], viewport_pt[1], 1.0f);

	vec3 pNear = Unproject(nearvec3, viewportOrigin, viewportSize, view, projection);
	vec3 pFar = Unproject(farvec3, viewportOrigin, viewportSize, view, projection);

	vec3 normal = Normalized(pFar - pNear);
	vec3 origin = pNear;

	return Ray(origin, normal);
}

// Chapter 15

void ResetCollisionManifold(CollisionManifold* result) {
	if (result != 0) {
		result->colliding = false;
		result->normal = vec3(0, 0, 1);
		result->depth = FLT_MAX;
		if (result->contacts.GetCount() > 0) {
			result->contacts.Clear();
		}
	}
}

Vector<vec3> GetVertices(const OBB& obb) {
	Vector<vec3> v;
	v.SetCount(8);

	vec3 C = obb.position;	// OBB Center
	vec3 E = obb.size;		// OBB Extents
	const auto& o = obb.orientation;
	vec3 A[] = {			// OBB Axis
		o[0],
		o[1],
		o[2]
	};

	v[0] = C + A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	v[1] = C - A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	v[2] = C + A[0] * E[0] - A[1] * E[1] + A[2] * E[2];
	v[3] = C + A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	v[4] = C - A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	v[5] = C + A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	v[6] = C - A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	v[7] = C - A[0] * E[0] - A[1] * E[1] + A[2] * E[2];

	return v;
}

void GetEdges(const OBB& obb, Vector<line3>& result) {
	result.Reserve(12);
	Vector<vec3> v = GetVertices(obb);

	int index[][2] = { // Indices of edges
		{ 6, 1 },{ 6, 3 },{ 6, 4 },{ 2, 7 },{ 2, 5 },{ 2, 0 },
		{ 0, 1 },{ 0, 3 },{ 7, 1 },{ 7, 4 },{ 4, 5 },{ 5, 3 }
	};

	for (int j = 0; j < 12; ++j) {
		result.Add(Line(
			v[index[j][0]], v[index[j][1]]
		));
	}
}

Vector<Plane> GetPlanes(const OBB& obb) {
	vec3 c = obb.position;	// OBB Center
	vec3 e = obb.size;		// OBB Extents
	const auto& o = obb.orientation;
	vec3 a[] = {			// OBB Axis
		o[0],
		o[1],
		o[2]
	};

	Vector<Plane> result;
	result.SetCount(6);

	result[0] = Plane(a[0]        ,  Dot(a[0], (c + a[0] * e[0])));
	result[1] = Plane(a[0] * -1.0f, -Dot(a[0], (c - a[0] * e[0])));
	result[2] = Plane(a[1]        ,  Dot(a[1], (c + a[1] * e[1])));
	result[3] = Plane(a[1] * -1.0f, -Dot(a[1], (c - a[1] * e[1])));
	result[4] = Plane(a[2]        ,  Dot(a[2], (c + a[2] * e[2])));
	result[5] = Plane(a[2] * -1.0f, -Dot(a[2], (c - a[2] * e[2])));

	return result;
}


bool ClipToPlane(const Plane& plane, const line3& line, vec3* outvec3) {
	vec3 ab = line.end - line.start;

	float nA = Dot(plane.normal, line.start);
	float nAB = Dot(plane.normal, ab);

	if (CMP(nAB, 0)) {
		return false;
	}

	float t = (plane.distance - nA) / nAB;
	if (t >= 0.0f && t <= 1.0f) {
		if (outvec3 != 0) {
			*outvec3 = line.start + ab * t;
		}
		return true;
	}

	return false;
}

Vector<vec3> ClipEdgesToOBB(const Vector<line3>& edges, const OBB& obb) {
	Vector<vec3> result;
	result.Reserve(edges.GetCount() * 3);
	vec3 intersection;

	Vector<Plane> planes = GetPlanes(obb);

	for (int i = 0; i < planes.GetCount(); ++i) {
		for (int j = 0; j < edges.GetCount(); ++j) {
			if (ClipToPlane(planes[i], edges[j], &intersection)) {
				if (PointInOBB(intersection, obb)) {
					result.Add(intersection);
				}
			}
		}
	}

	return result;
}

float PenetrationDepth(const OBB& o1, const OBB& o2, const vec3& axis, bool* outShouldFlip) {
	Interval i1 = GetInterval(o1, Normalized(axis));
	Interval i2 = GetInterval(o2, Normalized(axis));

	if (!((i2.min <= i1.max) && (i1.min <= i2.max))) {
		return 0.0f; // No penerattion
	}

	float len1 = i1.max - i1.min;
	float len2 = i2.max - i2.min;
	float min = fminf(i1.min, i2.min);
	float max = fmaxf(i1.max, i2.max);
	float length = max - min;

	if (outShouldFlip != 0) {
		*outShouldFlip = (i2.min < i1.min);
	}

	return (len1 + len2) - length;
}

CollisionManifold FindCollisionFeatures(const OBB& A, const OBB& B) {
	CollisionManifold result; // Will return result of intersection!
	ResetCollisionManifold(&result);

	Sphere s1(A.position, Magnitude(A.size));
	Sphere s2(B.position, Magnitude(B.size));

	if (!SphereSphere(s1, s2)) {
		return result;
	}

	const auto& o1 = A.orientation;
	const auto& o2 = B.orientation;

	vec3 test[15] = {
		o1[0],
		o1[1],
		o1[2],
		o2[0],
		o2[1],
		o2[2]
	};

	for (int i = 0; i < 3; ++i) { // Fill out rest of axis
		test[6 + i * 3 + 0] = Cross(test[i], test[0]);
		test[6 + i * 3 + 1] = Cross(test[i], test[1]);
		test[6 + i * 3 + 2] = Cross(test[i], test[2]);
	}

	vec3* hitNormal = 0;
	bool shouldFlip;

	for (int i = 0; i < 15; ++i) {
		if (test[i][0] < 0.000001f) test[i][0] = 0.0f;
		if (test[i][1] < 0.000001f) test[i][1] = 0.0f;
		if (test[i][2] < 0.000001f) test[i][2] = 0.0f;
		if (MagnitudeSq(test[i])< 0.001f) {
			continue;
		}

		float depth = PenetrationDepth(A, B, test[i], &shouldFlip);
		if (depth <= 0.0f) {
			return result;
		}
		else if (depth < result.depth) {
			if (shouldFlip) {
				test[i] = test[i] * -1.0f;
			}
			result.depth = depth;
			hitNormal = &test[i];
		}
	}

	if (hitNormal == 0) {
		return result;
	}
	vec3 axis = Normalized(*hitNormal);

	Vector<line3> la, lb;
	GetEdges(B, lb);
	GetEdges(A, la);
	
	Vector<vec3> c1 = ClipEdgesToOBB(lb, A);
	Vector<vec3> c2 = ClipEdgesToOBB(la, B);
	result.contacts.Reserve(c1.GetCount() + c2.GetCount());
	result.contacts.Append(c1);
	result.contacts.Append(c2);

	Interval i = GetInterval(A, axis);
	float distance = (i.max - i.min)* 0.5f - result.depth * 0.5f;
	vec3 pointOnPlane = A.position + axis * distance;
	
	for (int i = result.contacts.GetCount() - 1; i >= 0; --i) {
		vec3 contact = result.contacts[i];
		result.contacts[i] = contact + (axis * Dot(axis, pointOnPlane - contact));
		
		// This bit is in the "There is more" section of the book
		for (int j = result.contacts.GetCount() - 1; j > i; --j) {
			if (MagnitudeSq(result.contacts[j] - result.contacts[i]) < 0.0001f) {
				result.contacts.Remove(j);
				break;
			}
		}
	}

	result.colliding = true;
	result.normal = axis;

	return result;
}

CollisionManifold FindCollisionFeatures(const Sphere& A, const Sphere& B) {
	CollisionManifold result; // Will return result of intersection!
	ResetCollisionManifold(&result);

	float r = A.radius + B.radius;
	vec3 d = B.position - A.position;

	if (MagnitudeSq(d) - r * r > 0 || MagnitudeSq(d) == 0.0f) {
		return result;
	}
	d.Normalize();

	result.colliding = true;
	result.normal = d;
	result.depth = fabsf(Magnitude(d) - r) * 0.5f;
	
	// dtp - Distance to intersection point
	float dtp = A.radius - result.depth;
	vec3 contact = A.position + d * dtp;
	
	result.contacts.Add(contact);

	return result;
}

CollisionManifold FindCollisionFeatures(const OBB& A, const Sphere& B) {
	CollisionManifold result; // Will return result of intersection!
	ResetCollisionManifold(&result);

	vec3 closest_pt = ClosestPoint(A, B.position);

	float distanceSq = MagnitudeSq(closest_pt - B.position);
	if (distanceSq > B.radius * B.radius) {
		return result;
	}

	vec3 normal;
	if (CMP(distanceSq, 0.0f)) {
		if (CMP(MagnitudeSq(closest_pt - A.position), 0.0f)) {
			return result;

		}
		// Closest point is at the center of the sphere
		normal = Normalized(closest_pt - A.position);
	}
	else {
		normal = Normalized(B.position - closest_pt);
	}

	vec3 outside_pt = B.position - normal * B.radius;

	float distance = Magnitude(closest_pt - outside_pt);

	result.colliding = true;
	result.contacts.Add(closest_pt + (outside_pt - closest_pt) * 0.5f);
	result.normal = normal;
	result.depth = distance * 0.5f;

	return result;
}


NAMESPACE_TOPSIDE_END
