#ifndef _Geometry_Geom3D_h_
#define _Geometry_Geom3D_h_

NAMESPACE_TOPSIDE_BEGIN



struct CollisionManifold : Moveable<CollisionManifold> {
	bool colliding;
	vec3 normal;
	float depth;
	Vector<vec3> contacts;
	
	
	//SOFTPHYS_RENDER_COMMON
};
void ResetCollisionManifold(CollisionManifold* result);

void ResetRaycastResult(RaycastResult* outResult);

vec3 Intersection(Plane p1, Plane p2, Plane p3);

typedef vec3 Point3D;
typedef line3 Line3D;
typedef Ray Ray3D;
typedef AABB Rectangle3D;
typedef Interval Interval3D;

Stream& operator<<(Stream& os, const line3& shape);
Stream& operator<<(Stream& os, const Ray& shape);
Stream& operator<<(Stream& os, const Sphere& shape);
Stream& operator<<(Stream& os, const AABB& shape);
Stream& operator<<(Stream& os, const OBB& shape);
Stream& operator<<(Stream& os, const Plane& shape);
Stream& operator<<(Stream& os, const tri3& shape);

float Length(const line3& line);
float LengthSq(const line3& line);
Ray FromPoints(const vec3& from, const vec3& to);
vec3 GetMin(const AABB& aabb);
vec3 GetMax(const AABB& aabb);
AABB FromMinMax(const vec3& min, const vec3& max);
float PlaneEquation(const vec3& point, const Plane& plane);
float PlaneEquation(const Plane& plane, const vec3& point);

bool PointInSphere(const vec3& point, const Sphere& sphere);
bool PointInAABB(const vec3& point, const AABB& aabb);
bool PointInOBB(const vec3& point, const OBB& obb);
bool PointOnPlane(const vec3& point, const Plane& plane);
bool PointOnLine(const vec3& point, const line3& line);
bool PointOnRay(const vec3& point, const Ray& ray);

bool PointInPlane(const vec3& point, const Plane& plane);
bool PointInLine(const vec3& point, const line3& line);
bool PointInRay(const vec3& point, const Ray& ray);
bool ContainsPoint(const Sphere& sphere, const vec3& point);
bool ContainsPoint(const vec3& point, const Sphere& sphere);
bool ContainsPoint(const AABB& aabb, const vec3& point);
bool ContainsPoint(const vec3& point, const AABB& aabb);
bool ContainsPoint(const vec3& point, const OBB& obb);
bool ContainsPoint(const OBB& obb, const vec3& point);
bool ContainsPoint(const vec3& point, const Plane& plane);
bool ContainsPoint(const Plane& plane, const vec3& point);
bool ContainsPoint(const vec3& point, const line3& line);
bool ContainsPoint(const line3& line, const vec3& point);
bool ContainsPoint(const vec3& point, const Ray& ray);
bool ContainsPoint(const Ray& ray, const vec3& point);

vec3 ClosestPoint(const Sphere& sphere, const vec3& point);
vec3 ClosestPoint(const AABB& aabb, const vec3& point);
vec3 ClosestPoint(const OBB& obb, const vec3& point);
vec3 ClosestPoint(const Plane& plane, const vec3& point);
vec3 ClosestPoint(const line3& line, const vec3& point);
vec3 ClosestPoint(const Ray& ray, const vec3& point);

vec3 ClosestPoint(const vec3& point, const Sphere& sphere);
vec3 ClosestPoint(const vec3& point, const AABB& aabb);
vec3 ClosestPoint(const vec3& point, const OBB& obb);
vec3 ClosestPoint(const vec3& point, const Plane& plane);
vec3 ClosestPoint(const vec3& point, const line3& line);
vec3 ClosestPoint(const vec3& point, const Ray& ray);
vec3 ClosestPoint(const vec3& p, const tri3& t);

Interval GetInterval(const AABB& aabb, const vec3& axis);
Interval GetInterval(const OBB& obb, const vec3& axis);
Interval GetInterval(const tri3& triangle, const vec3& axis);

bool OverlapOnAxis(const AABB& aabb, const OBB& obb, const vec3& axis);
bool OverlapOnAxis(const OBB& obb1, const OBB& obb2, const vec3& axis);
bool OverlapOnAxis(const AABB& aabb, const tri3& triangle, const vec3& axis);
bool OverlapOnAxis(const OBB& obb, const tri3& triangle, const vec3& axis);
bool OverlapOnAxis(const tri3& t1, const tri3& t2, const vec3& axis);

bool SphereSphere(const Sphere& s1, const Sphere& s2);
bool SphereAABB(const Sphere& sphere, const AABB& aabb);
bool SphereOBB(const Sphere& sphere, const OBB& obb);
bool SpherePlane(const Sphere& sphere, const Plane& plane);
bool AABBAABB(const AABB& aabb1, const AABB& aabb2);
bool AABBOBB(const AABB& aabb, const OBB& obb);
bool AABBPlane(const AABB& aabb, const Plane& plane);
bool OBBOBB(const OBB& obb1, const OBB& obb2);
bool OBBPlane(const OBB& obb, const Plane& plane);
bool PlanePlane(const Plane& plane1, const Plane& plane2);

#define AABBSphere(aabb, sphere) \
	SphereAABB(Sphere, AABB)
#define OBBSphere(obb, sphere) \
	SphereOBB(sphere, obb)
#define PlaneSphere(plane, sphere) \
	SpherePlane(sphere, plane)
#define OBBAABB(obb, aabb) \
	AABBOBB(aabb, obb)
#define PlaneAABB(plane, aabb) \
	AABBPlane(aabb, plane)
#define PlaneOBB(plane, obb) \
	OBBPlane(obb, plane)

bool Raycast(const Sphere& sphere, const Ray& ray, RaycastResult* outResult);
bool Raycast(const AABB& aabb, const Ray& ray, RaycastResult* outResult);
bool Raycast(const OBB& obb, const Ray& ray, RaycastResult* outResult);
bool Raycast(const Plane& plane, const Ray& ray, RaycastResult* outResult);
bool Raycast(const tri3& triangle, const Ray& ray, RaycastResult* outResult);

bool Linetest(const Sphere& sphere, const line3& line);
bool Linetest(const AABB& aabb, const line3& line);
bool Linetest(const OBB& obb, const line3& line);
bool Linetest(const Plane& plane, const line3& line);
bool Linetest(const tri3& triangle, const line3& line);

bool Raycast(const Ray& ray, const Sphere& sphere, RaycastResult* outResult);
bool Raycast(const Ray& ray, const AABB& aabb, RaycastResult* outResult);
bool Raycast(const Ray& ray, const OBB& obb, RaycastResult* outResult);
bool Raycast(const Ray& ray, const Plane& plane, RaycastResult* outResult);
bool Linetest(const line3& line, const Sphere& sphere);
bool Linetest(const line3& line, const AABB& aabb);
bool Linetest(const line3& line, const OBB& obb);
bool Linetest(const line3& line, const Plane& plane);

vec3 BarycentricOptimized(const vec3& p, const tri3& t);
vec3 Centroid(const tri3& t);

bool PointInTriangle(const vec3& p, const tri3& t);
Plane FromTriangle(const tri3& t);
vec3 ClosestPoint(const tri3& t, const vec3& p);
bool TriangleSphere(const tri3& t, const Sphere& s);
bool TriangleAABB(const tri3& t, const AABB& a);
bool TriangleOBB(const tri3& t, const OBB& o);
bool TriangleTriangle(const tri3& t1, const tri3& t2);
bool TriangleTriangleRobust(const tri3& t1, const tri3& t2);
bool TrianglePlane(const tri3& t, const Plane& p); 

#define SphereTriangle(s, t) \
	TriangleSphere(t, s)
#define AABBTriangle(a, t) \
	TriangleAABB(t, a)
#define OBBTriangle(o, t) \
	TriangleOBB(t, o)
#define PlaneTriangle(p, t) \
	TrianglePlane(t, p)

// A - Edge 0, vec3 0
// B - Edge 0, vec3 1
// C - Edge 1, vec3 0
// D - Edge 1, vec3 1
vec3 SatCrossEdge(const vec3& a, const vec3& b, const vec3& c, const vec3& d);
vec3 Barycentric(const vec3& p, const tri3& t);


vec3 Unproject(const vec3& viewport_pt, const vec2& viewportOrigin, const vec2& viewportSize, const mat4& view, const mat4& projection);
Ray GetPickRay(const vec2& viewport_pt, const vec2& viewportOrigin, const vec2& viewportSize, const mat4& view, const mat4& projection);


Vector<vec3> GetVertices(const OBB& obb);
void GetEdges(const OBB& obb, Vector<line3>& edges);
Vector<Plane> GetPlanes(const OBB& obb);
bool ClipToPlane(const Plane& plane, const line3& line, vec3* outvec3);
Vector<vec3> ClipEdgesToOBB(const Vector<line3>& edges, const OBB& obb);
float PenetrationDepth(const OBB& o1, const OBB& o2, const vec3& axis, bool* outShouldFlip);

CollisionManifold FindCollisionFeatures(const Sphere& A, const Sphere& B);
CollisionManifold FindCollisionFeatures(const OBB& A, const Sphere& B);
CollisionManifold FindCollisionFeatures(const OBB& A, const OBB& B);


NAMESPACE_TOPSIDE_END

#endif
