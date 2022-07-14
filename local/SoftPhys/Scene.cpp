#include "Internal.h"


NAMESPACE_SOFTPHYS_BEGIN


void Scene::AddModel(Model* model) {
	VectorFindAdd(objects, model);
}

void Scene::RemoveModel(Model* model) {
	VectorRemoveKey(objects, model);
}

void Scene::UpdateModel(Model* model) {
	// Stub
}

Vector<Model*> Scene::FindChildren(const Model* model) {
	Vector<Model*> result;

	for (int i = 0, size = objects.GetCount(); i < size; ++i) {
		if (objects[i] == 0 || objects[i] == model) {
			continue;
		}

		Model* iterator = objects[i]->parent;
		if (iterator != 0) {
			if (iterator == model) {
				result.Add(objects[i]);
				continue;
			}
			iterator = iterator->parent;
		}
	}

	return result;
}

Model* Scene::Raycast(const Ray& ray) {
	if (octree != 0) {
		// :: lets the compiler know to look outside class scope
		return SOFTPHYS::Raycast(octree, ray);
	}

	Model* result = 0;
	float result_t = -1;

	for (int i = 0, size = objects.GetCount(); i < size; ++i) {
		float t = ModelRay(*objects[i], ray);
		if (result == 0 && t >= 0) {
			result = objects[i];
			result_t = t;
		}
		else if (result != 0 && t < result_t) {
			result = objects[i];
			result_t = t;
		}
	}

	return result;
}

Vector<Model*> Scene::Query(const Sphere& sphere) {
	if (octree != 0) {
		// :: lets the compiler know to look outside class scope
		return SOFTPHYS::Query(octree, sphere);
	}

	Vector<Model*> result;
	for (int i = 0, size = objects.GetCount(); i < size; ++i) {
		OBB bounds = GetOBB(*objects[i]);
		if (SphereOBB(sphere, bounds)) {
			result.Add(objects[i]);
		}
	}
	return result;
}

Vector<Model*> Scene::Query(const AABB& aabb) {
	if (octree != 0) {
		// :: lets the compiler know to look outside class scope
		return SOFTPHYS::Query(octree, aabb);
	}

	Vector<Model*> result;
	for (int i = 0, size = objects.GetCount(); i < size; ++i) {
		OBB bounds = GetOBB(*objects[i]);
		if (AABBOBB(aabb, bounds)) {
			result.Add(objects[i]);
		}
	}
	return result;
}

void SplitTree(OctreeNode* node, int depth) {
	if (depth-- <= 0) { // Decrements depth
		return;
	}

	if (node->children == 0) {
		node->children = new OctreeNode[8];

		vec3 c = node->bounds.position;
		vec3 e = node->bounds.size *0.5f;

		node->children[0].bounds = AABB(c + vec3(-e[0], +e[1], -e[2]), e);
		node->children[1].bounds = AABB(c + vec3(+e[0], +e[1], -e[2]), e);
		node->children[2].bounds = AABB(c + vec3(-e[0], +e[1], +e[2]), e);
		node->children[3].bounds = AABB(c + vec3(+e[0], +e[1], +e[2]), e);
		node->children[4].bounds = AABB(c + vec3(-e[0], -e[1], -e[2]), e);
		node->children[5].bounds = AABB(c + vec3(+e[0], -e[1], -e[2]), e);
		node->children[6].bounds = AABB(c + vec3(-e[0], -e[1], +e[2]), e);
		node->children[7].bounds = AABB(c + vec3(+e[0], -e[1], +e[2]), e);
	}

	if (node->children != 0 && node->models.GetCount() > 0) {
		for (int i = 0; i < 8; ++i) { // For each child
			for (int j = 0, size = node->models.GetCount(); j < size; ++j) {
				OBB bounds = GetOBB(*node->models[j]);
				if (AABBOBB(node->children[i].bounds, bounds)) {
					node->children[i].models.Add(node->models[j]);
				}
			}
		}
		node->models.Clear();

		// Recurse
		for (int i = 0; i < 8; ++i) {
			SplitTree(&(node->children[i]), depth);
		}
	}
}

void Insert(OctreeNode* node, Model* model) {
	OBB bounds = GetOBB(*model);
	if (AABBOBB(node->bounds, bounds)) {
		if (node->children == 0) {
			node->models.Add(model);
		}
		else {
			for (int i = 0; i < 8; ++i) {
				Insert(&(node->children[i]), model);
			}
		}
	}
}

void Remove(OctreeNode* node, Model* model) {
	if (node->children == 0) {
		VectorRemoveKey(node->models, model);
	}
	else {
		for (int i = 0; i < 8; ++i) {
			Remove(&(node->children[i]), model);
		}
	}
}

void Update(OctreeNode* node, Model* model) {
	Remove(node, model);
	Insert(node, model);
}

Model* FindClosest(const Vector<Model*>& set, const Ray& ray) {
	if (set.GetCount() == 0) {
		return 0;
	}

	Model* closest = 0;
	float closest_t = -1;

	for (int i = 0, size = set.GetCount(); i < size; ++i) {
		float this_t = ModelRay(*set[i], ray);

		if (this_t < 0) {
			continue;
		}

		if (closest_t < 0 || this_t < closest_t) {
			closest_t = this_t;
			closest = set[i];
		}
	}

	return closest;
}

Model* Raycast(OctreeNode* node, const Ray& ray) {
	RaycastResult raycast;
	Raycast(node->bounds, ray, &raycast);
	float t = raycast.t;

	if (t >= 0) {
		if (node->children == 0) {
			return FindClosest(node->models, ray);
		}
		else {
			Vector<Model*> results;
			for (int i = 0; i < 8; ++i) {
				Model* result = Raycast(&(node->children[i]), ray);
				if (result != 0) {
					results.Add(result);
				}
			}
			return FindClosest(results, ray);
		}
	}

	return 0;
}

Vector<Model*> Query(OctreeNode* node, const Sphere& sphere) {
	Vector<Model*> result;

	if (SphereAABB(sphere, node->bounds)) {
		if (node->children == 0) {
			for (int i = 0, size = node->models.GetCount(); i < size; ++i) {
				OBB bounds = GetOBB(*(node->models[i]));
				if (SphereOBB(sphere, bounds)) {
					result.Add(node->models[i]);
				}
			}
		}
		else {
			for (int i = 0; i < 8; ++i) {
				Vector<Model*> child = Query(&(node->children[i]), sphere);
				if (child.GetCount() > 0) {
					result.Append(child);
				}
			}
		}
	}

	return result;
}

Vector<Model*> Query(OctreeNode* node, const AABB& aabb) {
	Vector<Model*> result;

	if (AABBAABB(aabb, node->bounds)) {
		if (node->children == 0) {
			for (int i = 0, size = node->models.GetCount(); i < size; ++i) {
				OBB bounds = GetOBB(*(node->models[i]));
				if (AABBOBB(aabb, bounds)) {
					result.Add(node->models[i]);
				}
			}
		}
		else {
			for (int i = 0; i < 8; ++i) {
				Vector<Model*> child = Query(&(node->children[i]), aabb);
				if (child.GetCount() > 0) {
					result.Append(child);
				}
			}
		}
	}

	return result;
}

bool Scene::Accelerate(const vec3& position, float size) {
	if (octree != 0) {
		return false;
	}

	vec3 min(position[0] - size, position[1] - size, position[2] - size);
	vec3 max(position[0] + size, position[1] + size, position[2] + size);

	// Construct tree root
	octree = new OctreeNode();
	octree->bounds = FromMinMax(min, max);
	octree->children = 0;
	for (int i = 0, size = objects.GetCount(); i < size; ++i) {
		octree->models.Add(objects[i]);
	}

	// Create tree
	SplitTree(octree, 5);
	return true;
}

Vector<Model*> Scene::Cull(const Frustum& f) {
	Vector<Model*> result;

	for (int i = 0, size = objects.GetCount(); i < size; ++i) {
		objects[i]->flag = false;
	}

	if (octree == 0) {
		for (int i = 0, size = objects.GetCount(); i < size; ++i) {
			OBB bounds = GetOBB(*(objects[i]));
			if (f.Intersects(bounds)) {
				result.Add(objects[i]);
			}
		}
	}
	else {
		LinkedList<OctreeNode*> nodes;
		nodes.Add(octree);

		while (nodes.GetCount() > 0) {
			OctreeNode* active = nodes.PopFirst();

			// Has child nodes
			if (active->children != 0) {
				for (int i = 0; i < 8; ++i) {
					AABB bounds = active->children[i].bounds;
					if (f.Intersects(bounds)) {
						nodes.Add(&active->children[i]);
					}
				}
			}
			else { // Is leaf node
				for (int i = 0, size = active->models.GetCount(); i < size; ++i) {
					if (!active->models[i]->flag) {
						OBB bounds = GetOBB(*(active->models[i]));
						if (f.Intersects(bounds)) {
							active->models[i]->flag = true;
							result.Add(active->models[i]);
						}
					}
				}
			}
		}
	}

	return result;
}


NAMESPACE_SOFTPHYS_END
