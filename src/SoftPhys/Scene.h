#ifndef _SoftPhys_Scene_
#define _SoftPhys_Scene_


NAMESPACE_SOFTPHYS_BEGIN


typedef struct OctreeNode {
	AABB bounds;
	OctreeNode* children;
	Vector<Model*> models;

	inline OctreeNode() : children(0) {}
	inline ~OctreeNode() {
		if (children != 0) {
			delete[] children;
		}
	}
} OctreeNode;

class Scene {
	
protected:
	Vector<Model*> objects;
	OctreeNode* octree;
	
private:
	Scene(const Scene&);
	Scene& operator=(const Scene&);
	
public:
	inline Scene() : octree(0) {}
	inline ~Scene() {
		if (octree != 0) {
			delete octree;
		}
	}

	void AddModel(Model* model);
	void RemoveModel(Model* model);
	void UpdateModel(Model* model);
	Vector<Model*> FindChildren(const Model* model);

	Model* Raycast(const Ray& ray);
	Vector<Model*> Query(const Sphere& sphere);
	Vector<Model*> Query(const AABB& aabb);

	bool Accelerate(const vec3& position, float size);
	Vector<Model*> Cull(const Frustum& f);
	
};

void SplitTree(OctreeNode* node, int depth);

void Insert(OctreeNode* node, Model* model);
void Remove(OctreeNode* node, Model* model);
void Update(OctreeNode* node, Model* model);

Model* FindClosest(const Vector<Model*>& set, const Ray& ray);
Model* Raycast(OctreeNode* node, const Ray& ray);
Vector<Model*> Query(OctreeNode* node, const Sphere& sphere);
Vector<Model*> Query(OctreeNode* node, const AABB& aabb);


NAMESPACE_SOFTPHYS_END

#endif
