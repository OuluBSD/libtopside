#ifndef _SoftPhys_Geometry3D_
#define _SoftPhys_Geometry3D_


NAMESPACE_SOFTPHYS_BEGIN


typedef vec3 Point;

struct Line : Moveable<Line> {
	Point start;
	Point end;

	inline Line() {}
	inline Line(const Point& s, const Point& e) :
		start(s), end(e) { }
};

using Line_ = Wrap<Line>;

struct Triangle : Moveable<Triangle> {
	union {
		struct {
			Point a;
			Point b;
			Point c;
		};
		struct {
			Point p1;
			Point p2;
			Point p3;
		};

		Point points[3];
		float values[9];
	};
	
	inline Triangle() { }
	inline Triangle(const Point& _p1, const Point& _p2, const Point& _p3) :
		a(_p1), b(_p2), c(_p3) { }
};

struct BVHNode : Moveable<BVHNode> {
	AABB bounds;
	BVHNode* children;
	int numTriangles;
	int* triangles;

	BVHNode() : children(0), numTriangles(0), triangles(0) {}
};

struct Mesh : Moveable<Mesh> {
	int numTriangles;
	union {
		Triangle* triangles;
		Point* vertices;
		float* values;
	};
	BVHNode* accelerator;

	Mesh() : numTriangles(0), values(0), accelerator(0) {}
};

class Model {
protected:
	Mesh* content;
	AABB bounds;
public:
	vec3 position;
	vec3 rotation;
	bool flag;
	Model* parent;

	inline Model() : parent(0), content(0), flag(false) { }
	inline Mesh* GetMesh() const {
		return content;
	}
	inline AABB GetBounds() const {
		return bounds;
	}

	void SetContent(Mesh* mesh);
};


struct CollisionManifold : Moveable<CollisionManifold> {
	bool colliding;
	vec3 normal;
	float depth;
	Vector<vec3> contacts;
	
	
	SOFTPHYS_RENDER_COMMON
};
void ResetCollisionManifold(CollisionManifold* result);

void ResetRaycastResult(RaycastResult* outResult);

Point Intersection(Plane p1, Plane p2, Plane p3);

typedef vec3 Point3D;
typedef Line Line3D;
typedef Ray Ray3D;
typedef AABB Rectangle3D;
typedef Interval Interval3D;

Stream& operator<<(Stream& os, const Line& shape);
Stream& operator<<(Stream& os, const Ray& shape);
Stream& operator<<(Stream& os, const Sphere& shape);
Stream& operator<<(Stream& os, const AABB& shape);
Stream& operator<<(Stream& os, const OBB& shape);
Stream& operator<<(Stream& os, const Plane& shape);
Stream& operator<<(Stream& os, const Triangle& shape);

float Length(const Line& line);
float LengthSq(const Line& line);
Ray FromPoints(const Point& from, const Point& to);
vec3 GetMin(const AABB& aabb);
vec3 GetMax(const AABB& aabb);
AABB FromMinMax(const vec3& min, const vec3& max);
float PlaneEquation(const Point& point, const Plane& plane);
float PlaneEquation(const Plane& plane, const Point& point);

bool PointInSphere(const Point& point, const Sphere& sphere);
bool PointInAABB(const Point& point, const AABB& aabb);
bool PointInOBB(const Point& point, const OBB& obb);
bool PointOnPlane(const Point& point, const Plane& plane);
bool PointOnLine(const Point& point, const Line& line);
bool PointOnRay(const Point& point, const Ray& ray);

bool PointInPlane(const Point& point, const Plane& plane);
bool PointInLine(const Point& point, const Line& line);
bool PointInRay(const Point& point, const Ray& ray);
bool ContainsPoint(const Sphere& sphere, const Point& point);
bool ContainsPoint(const Point& point, const Sphere& sphere);
bool ContainsPoint(const AABB& aabb, const Point& point);
bool ContainsPoint(const Point& point, const AABB& aabb);
bool ContainsPoint(const Point& point, const OBB& obb);
bool ContainsPoint(const OBB& obb, const Point& point);
bool ContainsPoint(const Point& point, const Plane& plane);
bool ContainsPoint(const Plane& plane, const Point& point);
bool ContainsPoint(const Point& point, const Line& line);
bool ContainsPoint(const Line& line, const Point& point);
bool ContainsPoint(const Point& point, const Ray& ray);
bool ContainsPoint(const Ray& ray, const Point& point);

Point ClosestPoint(const Sphere& sphere, const Point& point);
Point ClosestPoint(const AABB& aabb, const Point& point);
Point ClosestPoint(const OBB& obb, const Point& point);
Point ClosestPoint(const Plane& plane, const Point& point);
Point ClosestPoint(const Line& line, const Point& point);
Point ClosestPoint(const Ray& ray, const Point& point);

Point ClosestPoint(const Point& point, const Sphere& sphere);
Point ClosestPoint(const Point& point, const AABB& aabb);
Point ClosestPoint(const Point& point, const OBB& obb);
Point ClosestPoint(const Point& point, const Plane& plane);
Point ClosestPoint(const Point& point, const Line& line);
Point ClosestPoint(const Point& point, const Ray& ray);
Point ClosestPoint(const Point& p, const Triangle& t);

Interval GetInterval(const AABB& aabb, const vec3& axis);
Interval GetInterval(const OBB& obb, const vec3& axis);
Interval GetInterval(const Triangle& triangle, const vec3& axis);

bool OverlapOnAxis(const AABB& aabb, const OBB& obb, const vec3& axis);
bool OverlapOnAxis(const OBB& obb1, const OBB& obb2, const vec3& axis);
bool OverlapOnAxis(const AABB& aabb, const Triangle& triangle, const vec3& axis);
bool OverlapOnAxis(const OBB& obb, const Triangle& triangle, const vec3& axis);
bool OverlapOnAxis(const Triangle& t1, const Triangle& t2, const vec3& axis);

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
bool Raycast(const Triangle& triangle, const Ray& ray, RaycastResult* outResult);

bool Linetest(const Sphere& sphere, const Line& line);
bool Linetest(const AABB& aabb, const Line& line);
bool Linetest(const OBB& obb, const Line& line);
bool Linetest(const Plane& plane, const Line& line);
bool Linetest(const Triangle& triangle, const Line& line);

bool Raycast(const Ray& ray, const Sphere& sphere, RaycastResult* outResult);
bool Raycast(const Ray& ray, const AABB& aabb, RaycastResult* outResult);
bool Raycast(const Ray& ray, const OBB& obb, RaycastResult* outResult);
bool Raycast(const Ray& ray, const Plane& plane, RaycastResult* outResult);
bool Linetest(const Line& line, const Sphere& sphere);
bool Linetest(const Line& line, const AABB& aabb);
bool Linetest(const Line& line, const OBB& obb);
bool Linetest(const Line& line, const Plane& plane);

vec3 BarycentricOptimized(const Point& p, const Triangle& t);
vec3 Centroid(const Triangle& t);

bool PointInTriangle(const Point& p, const Triangle& t);
Plane FromTriangle(const Triangle& t);
Point ClosestPoint(const Triangle& t, const Point& p);
bool TriangleSphere(const Triangle& t, const Sphere& s);
bool TriangleAABB(const Triangle& t, const AABB& a);
bool TriangleOBB(const Triangle& t, const OBB& o);
bool TriangleTriangle(const Triangle& t1, const Triangle& t2);
bool TriangleTriangleRobust(const Triangle& t1, const Triangle& t2);
bool TrianglePlane(const Triangle& t, const Plane& p); 

#define SphereTriangle(s, t) \
	TriangleSphere(t, s)
#define AABBTriangle(a, t) \
	TriangleAABB(t, a)
#define OBBTriangle(o, t) \
	TriangleOBB(t, o)
#define PlaneTriangle(p, t) \
	TrianglePlane(t, p)

// A - Edge 0, Point 0
// B - Edge 0, Point 1
// C - Edge 1, Point 0
// D - Edge 1, Point 1
vec3 SatCrossEdge(const vec3& a, const vec3& b, const vec3& c, const vec3& d);
vec3 Barycentric(const Point& p, const Triangle& t);

void AccelerateMesh(Mesh& mesh);
void SplitBVHNode(BVHNode* node, const Mesh& model, int depth);
void FreeBVHNode(BVHNode* node);

bool Linetest(const Mesh& mesh, const Line& line);
bool MeshSphere(const Mesh& mesh, const Sphere& sphere);
bool MeshAABB(const Mesh& mesh, const AABB& aabb);
bool MeshOBB(const Mesh& mesh, const OBB& obb);
bool MeshPlane(const Mesh& mesh, const Plane& plane);
bool MeshTriangle(const Mesh& mesh, const Triangle& triangle);
float MeshRay(const Mesh& mesh, const Ray& ray);
float Raycast(const Mesh& mesh, const Ray& ray);
float Raycast(const Model& mesh, const Ray& ray);

mat4 GetWorldMatrix(const Model& model);
OBB GetOBB(const Model& model);

float ModelRay(const Model& model, const Ray& ray);
bool Linetest(const Model& model, const Line& line);
bool ModelSphere(const Model& model, const Sphere& sphere);
bool ModelAABB(const Model& model, const AABB& aabb);
bool ModelOBB(const Model& model, const OBB& obb);
bool ModelPlane(const Model& model, const Plane& plane);
bool ModelTriangle(const Model& model, const Triangle& triangle);

vec3 Unproject(const vec3& viewportPoint, const vec2& viewportOrigin, const vec2& viewportSize, const mat4& view, const mat4& projection);
Ray GetPickRay(const vec2& viewportPoint, const vec2& viewportOrigin, const vec2& viewportSize, const mat4& view, const mat4& projection);


Vector<Point> GetVertices(const OBB& obb);
void GetEdges(const OBB& obb, Vector<Line>& edges);
Vector<Plane> GetPlanes(const OBB& obb);
bool ClipToPlane(const Plane& plane, const Line& line, Point* outPoint);
Vector<Point> ClipEdgesToOBB(const Vector<Line>& edges, const OBB& obb);
float PenetrationDepth(const OBB& o1, const OBB& o2, const vec3& axis, bool* outShouldFlip);

CollisionManifold FindCollisionFeatures(const Sphere& A, const Sphere& B);
CollisionManifold FindCollisionFeatures(const OBB& A, const Sphere& B);
CollisionManifold FindCollisionFeatures(const OBB& A, const OBB& B);


NAMESPACE_SOFTPHYS_END

#endif
