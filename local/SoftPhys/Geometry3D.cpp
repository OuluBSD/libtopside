#include "Internal.h"


NAMESPACE_SOFTPHYS_BEGIN


void AccelerateMesh(Mesh& mesh) {
	if (mesh.accelerator != 0) {
		return;
	}

	vec3 min = mesh.vertices[0];
	vec3 max = mesh.vertices[0];

	for (int i = 1; i < mesh.triangle_count * 3; ++i) {
		min[0] = fminf(mesh.vertices[i][0], min[0]);
		min[1] = fminf(mesh.vertices[i][1], min[1]);
		min[2] = fminf(mesh.vertices[i][2], min[2]);
	
		max[0] = fmaxf(mesh.vertices[i][0], max[0]);
		max[1] = fmaxf(mesh.vertices[i][1], max[1]);
		max[2] = fmaxf(mesh.vertices[i][2], max[2]);
	}

	mesh.accelerator = new BVHNode();
	mesh.accelerator->bounds = FromMinMax(min, max);
	mesh.accelerator->children = 0;
	mesh.accelerator->triangle_count = mesh.triangle_count;
	mesh.accelerator->triangles = new int[mesh.triangle_count];
	for (int i = 0; i < mesh.triangle_count; ++i) {
		mesh.accelerator->triangles[i] = i;
	}

	SplitBVHNode(mesh.accelerator, mesh, 3);
}

void SplitBVHNode(BVHNode* node, const Mesh& model, int depth) {
	if (depth-- <= 0) { // Decrements depth
		return;
	}

	if (node->children == 0) {
		// Only split if this node contains triangles
		if (node->triangle_count > 0) {
			node->children = new BVHNode[8];

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
	}

	// If this node was just split
	if (node->children != 0 && node->triangle_count > 0) {
		for (int i = 0; i < 8; ++i) { // For each child
			// Count how many triangles each child will contain
			node->children[i].triangle_count = 0;
			for (int j = 0; j < node->triangle_count; ++j) {
				const tri3& t = model.triangles[node->triangles[j]];
				if (TriangleAABB(t, node->children[i].bounds)) {
					node->children[i].triangle_count += 1;
				}
			}
			if (node->children[i].triangle_count == 0) {
				continue;
			}
			node->children[i].triangles = new int[node->children[i].triangle_count];
			int index = 0; // Add the triangles in the new child arrau
			for (int j = 0; j < node->triangle_count; ++j) {
				const tri3& t = model.triangles[node->triangles[j]];
				if (TriangleAABB(t, node->children[i].bounds)) {
					node->children[i].triangles[index++] = node->triangles[j];
				}
			}
		}

		node->triangle_count = 0;
		delete[] node->triangles;
		node->triangles = 0;

		// Recurse
		for (int i = 0; i < 8; ++i) {
			SplitBVHNode(&node->children[i], model, depth);
		}
	}
}

void FreeBVHNode(BVHNode* node) {
	if (node->children != 0) {
		for (int i = 0; i < 8; ++i) {
			FreeBVHNode(&node->children[i]);
		}
		delete[] node->children;
		node->children = 0;
	}

	if (node->triangle_count != 0 || node->triangles != 0) {
		delete[] node->triangles;
		node->triangles = 0;
		node->triangle_count = 0;
	}
}

bool MeshAABB(const Mesh& mesh, const AABB& aabb) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.triangle_count; ++i) {
			if (TriangleAABB(mesh.triangles[i], aabb)) {
				return true;
			}
		}
	}
	else {
		LinkedList<BVHNode*> toProcess;
		toProcess.AddFirst(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.IsEmpty()) {
			BVHNode* iterator = toProcess.PopFirst();

			if (iterator->triangle_count >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->triangle_count; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TriangleAABB(mesh.triangles[iterator->triangles[i]], aabb)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (AABBAABB(iterator->children[i].bounds, aabb)) {
						toProcess.AddFirst(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool Linetest(const Mesh& mesh, const line3& line) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.triangle_count; ++i) {
			if (Linetest(mesh.triangles[i], line)) {
				return true;
			}
		}
	}
	else {
		LinkedList<BVHNode*> toProcess;
		toProcess.AddFirst(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.IsEmpty()) {
			BVHNode* iterator = toProcess.PopFirst();

			if (iterator->triangle_count >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->triangle_count; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (Linetest(mesh.triangles[iterator->triangles[i]], line)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (Linetest(iterator->children[i].bounds, line)) {
						toProcess.AddFirst(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool MeshSphere(const Mesh& mesh, const Sphere& sphere) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.triangle_count; ++i) {
			if (TriangleSphere(mesh.triangles[i], sphere)) {
				return true;
			}
		}
	}
	else {
		LinkedList<BVHNode*> toProcess;
		toProcess.AddFirst(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.IsEmpty()) {
			BVHNode* iterator = toProcess.PopFirst();

			if (iterator->triangle_count >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->triangle_count; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TriangleSphere(mesh.triangles[iterator->triangles[i]], sphere)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (SphereAABB(sphere, iterator->children[i].bounds)) {
						toProcess.AddFirst(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool MeshOBB(const Mesh& mesh, const OBB& obb) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.triangle_count; ++i) {
			if (TriangleOBB(mesh.triangles[i], obb)) {
				return true;
			}
		}
	}
	else {
		LinkedList<BVHNode*> toProcess;
		toProcess.AddFirst(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.IsEmpty()) {
			BVHNode* iterator = toProcess.PopFirst();

			if (iterator->triangle_count >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->triangle_count; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TriangleOBB(mesh.triangles[iterator->triangles[i]], obb)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (AABBOBB(iterator->children[i].bounds, obb)) {
						toProcess.AddFirst(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool MeshPlane(const Mesh& mesh, const Plane& plane) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.triangle_count; ++i) {
			if (TrianglePlane(mesh.triangles[i], plane)) {
				return true;
			}
		}
	}
	else {
		LinkedList<BVHNode*> toProcess;
		toProcess.AddFirst(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.IsEmpty()) {
			BVHNode* iterator = toProcess.PopFirst();

			if (iterator->triangle_count >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->triangle_count; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TrianglePlane(mesh.triangles[iterator->triangles[i]], plane)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (AABBPlane(iterator->children[i].bounds, plane)) {
						toProcess.AddFirst(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

bool MeshTriangle(const Mesh& mesh, const tri3& triangle) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.triangle_count; ++i) {
			if (TriangleTriangle(mesh.triangles[i], triangle)) {
				return true;
			}
		}
	}
	else {
		LinkedList<BVHNode*> toProcess;
		toProcess.AddFirst(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.IsEmpty()) {
			BVHNode* iterator = toProcess.PopFirst();

			if (iterator->triangle_count >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->triangle_count; ++i) {
					// Triangle indices in BVHNode index the mesh
					if (TriangleTriangle(mesh.triangles[iterator->triangles[i]], triangle)) {
						return true;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					if (TriangleAABB(triangle, iterator->children[i].bounds)) {
						toProcess.AddFirst(&iterator->children[i]);
					}
				}
			}
		}
	}
	return false;
}

float Raycast(const Mesh& mesh, const Ray& ray) {
	return MeshRay(mesh, ray);
}

float Raycast(const Model& mesh, const Ray& ray) {
	return ModelRay(mesh, ray);
}

float MeshRay(const Mesh& mesh, const Ray& ray) {
	if (mesh.accelerator == 0) {
		for (int i = 0; i < mesh.triangle_count; ++i) {
			RaycastResult raycast;
			Raycast(mesh.triangles[i], ray, &raycast);
			float result = raycast.t;
			if (result >= 0) {
				return result;
			}
		}
	}
	else {
		LinkedList<BVHNode*> toProcess;
		toProcess.AddFirst(mesh.accelerator);

		// Recursivley walk the BVH tree
		while (!toProcess.IsEmpty()) {
			BVHNode* iterator = toProcess.PopFirst();

			if (iterator->triangle_count >= 0) {
				// Iterate trough all triangles of the node
				for (int i = 0; i < iterator->triangle_count; ++i) {
					// Triangle indices in BVHNode index the mesh
					RaycastResult raycast;
					Raycast(mesh.triangles[iterator->triangles[i]], ray, &raycast);
					float r = raycast.t;
					if (r >= 0) {
						return r;
					}
				}
			}

			if (iterator->children != 0) {
				for (int i = 8 - 1; i >= 0; --i) {
					// Only push children whos bounds intersect the test geometry
					RaycastResult raycast;
					Raycast(iterator->children[i].bounds, ray, &raycast);
					if (raycast.t >= 0) {
						toProcess.AddFirst(&iterator->children[i]);
					}
				}
			}
		}
	}
	return -1;
}

void Model::SetContent(Mesh* mesh) {
	content = mesh;
	if (content != 0) {
		vec3 min = mesh->vertices[0];
		vec3 max = mesh->vertices[0];

		for (int i = 1; i < mesh->triangle_count * 3; ++i) {
			min[0] = fminf(mesh->vertices[i][0], min[0]);
			min[1] = fminf(mesh->vertices[i][1], min[1]);
			min[2] = fminf(mesh->vertices[i][2], min[2]);

			max[0] = fmaxf(mesh->vertices[i][0], max[0]);
			max[1] = fmaxf(mesh->vertices[i][1], max[1]);
			max[2] = fmaxf(mesh->vertices[i][2], max[2]);
		}
		bounds = FromMinMax(min, max);
	}
}

mat4 GetWorldMatrix(const Model& model) {
	mat4 translation = Translation(model.position);
	mat4 rotation = AxesMat(model.rotation[0], model.rotation[1], model.rotation[2]);
	mat4 localMat = translation * rotation /* * Scale */;
	
	mat4 parentMat;
	if (model.parent != 0) {
		parentMat = GetWorldMatrix(*model.parent);
	}

	return parentMat * localMat;
}

OBB GetOBB(const Model& model) {
	mat4 world = GetWorldMatrix(model);
	AABB aabb = model.GetBounds();
	OBB obb;

	obb.size = aabb.size;
	obb.position = MultiplyVector(aabb.position, world);
	obb.orientation = Cut(world, 3, 3);

	return obb;
}

float ModelRay(const Model& model, const Ray& ray) {
	mat4 world = GetWorldMatrix(model);
	mat4 inv = Inverse(world);
	Ray local;
	local.origin = MultiplyVector(ray.origin, inv);
	local.direction = MultiplyVector(ray.direction, inv);
	local.NormalizeDirection();
	if (model.GetMesh() != 0) {
		return MeshRay(*(model.GetMesh()), local);
	}
	return -1;
}

bool Linetest(const Model& model, const line3& line) {
	mat4 world = GetWorldMatrix(model);
	mat4 inv = Inverse(world);
	line3 local;
	local.start = MultiplyVector(line.start, inv);
	local.end = MultiplyVector(line.end, inv);
	if (model.GetMesh() != 0) {
		return Linetest(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelSphere(const Model& model, const Sphere& sphere) {
	mat4 world = GetWorldMatrix(model);
	mat4 inv = Inverse(world);
	Sphere local;
	local.position = MultiplyVector(sphere.position, inv);
	if (model.GetMesh() != 0) {
		return MeshSphere(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelAABB(const Model& model, const AABB& aabb) {
	mat4 world = GetWorldMatrix(model);
	mat4 inv = Inverse(world);
	OBB local;
	local.size = aabb.size;
	local.position = MultiplyVector(aabb.position, inv);
	local.orientation = Cut(inv, 3, 3);
	if (model.GetMesh() != 0) {
		return MeshOBB(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelOBB(const Model& model, const OBB& obb) {
	mat4 world = GetWorldMatrix(model);
	mat4 inv = Inverse(world);
	OBB local;
	local.size = obb.size;
	local.position = MultiplyVector(obb.position, inv);
	local.orientation = Cut(inv, 3, 3) * obb.orientation;
	if (model.GetMesh() != 0) {
		return MeshOBB(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelPlane(const Model& model, const Plane& plane) {
	mat4 world = GetWorldMatrix(model);
	mat4 inv = Inverse(world);
	Plane local;
	local.normal = MultiplyVector(plane.normal, inv);
	local.distance = plane.distance;
	if (model.GetMesh() != 0) {
		return MeshPlane(*(model.GetMesh()), local);
	}
	return false;
}

bool ModelTriangle(const Model& model, const tri3& triangle) {
	mat4 world = GetWorldMatrix(model);
	mat4 inv = Inverse(world);
	tri3 local;
	local.a = MultiplyVector(triangle.a, inv);
	local.b = MultiplyVector(triangle.b, inv);
	local.c = MultiplyVector(triangle.c, inv);
	if (model.GetMesh() != 0) {
		return MeshTriangle(*(model.GetMesh()), local);
	}
	return false;
}


NAMESPACE_SOFTPHYS_END
