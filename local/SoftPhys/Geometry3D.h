#ifndef _SoftPhys_Geometry3D_
#define _SoftPhys_Geometry3D_


NAMESPACE_SOFTPHYS_BEGIN



/*struct Line : Moveable<Line> {
	vec3 start;
	vec3 end;

	inline Line() {}
	inline Line(const vec3& s, const vec3& e) :
		start(s), end(e) { }
};*/

//using Line_ = Wrap<line3>;

/*struct Triangle : Moveable<Triangle> {
	union {
		struct {
			vec3 a;
			vec3 b;
			vec3 c;
		};
		struct {
			vec3 p1;
			vec3 p2;
			vec3 p3;
		};

		vec3 points[3];
		float values[9];
	};
	
	inline Triangle() { }
	inline Triangle(const vec3& _p1, const vec3& _p2, const vec3& _p3) :
		a(_p1), b(_p2), c(_p3) { }
};*/

struct BVHNode : Moveable<BVHNode> {
	AABB bounds;
	BVHNode* children;
	int triangle_count;
	int* triangles;

	BVHNode() : children(0), triangle_count(0), triangles(0) {}
};

struct Mesh : Moveable<Mesh> {
	int triangle_count;
	union {
		tri3* triangles;
		vec3* vertices;
		float* values;
	};
	BVHNode* accelerator;

	Mesh() : triangle_count(0), values(0), accelerator(0) {}
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

void AccelerateMesh(Mesh& mesh);
void SplitBVHNode(BVHNode* node, const Mesh& model, int depth);
void FreeBVHNode(BVHNode* node);

bool Linetest(const Mesh& mesh, const line3& line);
bool MeshSphere(const Mesh& mesh, const Sphere& sphere);
bool MeshAABB(const Mesh& mesh, const AABB& aabb);
bool MeshOBB(const Mesh& mesh, const OBB& obb);
bool MeshPlane(const Mesh& mesh, const Plane& plane);
bool MeshTriangle(const Mesh& mesh, const tri3& triangle);
float MeshRay(const Mesh& mesh, const Ray& ray);
float Raycast(const Mesh& mesh, const Ray& ray);
float Raycast(const Model& mesh, const Ray& ray);

mat4 GetWorldMatrix(const Model& model);
OBB GetOBB(const Model& model);

float ModelRay(const Model& model, const Ray& ray);
bool Linetest(const Model& model, const line3& line);
bool ModelSphere(const Model& model, const Sphere& sphere);
bool ModelAABB(const Model& model, const AABB& aabb);
bool ModelOBB(const Model& model, const OBB& obb);
bool ModelPlane(const Model& model, const Plane& plane);
bool ModelTriangle(const Model& model, const tri3& triangle);

NAMESPACE_SOFTPHYS_END

#endif
