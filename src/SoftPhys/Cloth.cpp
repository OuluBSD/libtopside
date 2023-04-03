#include "Internal.h"


NAMESPACE_SOFTPHYS_BEGIN


void Cloth::Initialize(int grid_sz, float distance, const vec3& position) {
	float k = -1.0f;
	float b = 0.0f;
	clothSize = (float)grid_sz;

	verts.Clear();
	structural.Clear();
	shear.Clear();
	bend.Clear();

	verts.SetCount(grid_sz * grid_sz);
	float halfSize = (float)(grid_sz - 1) * 0.5f;

	if (grid_sz < 3) {
		grid_sz = 3;
	}

	// Create vertices
	for (int x = 0; x < grid_sz; ++x) {
		for (int z = 0; z < grid_sz; ++z) {
			int i = z * grid_sz + x;

			float x_pos = ((float)x + position[0] - halfSize) * distance;
			float z_pos = ((float)z + position[2] - halfSize) * distance;

			verts[i].SetPosition(vec3(x_pos, position[1], z_pos));
			verts[i].SetMass(1.0f);
			verts[i].SetBounce(0.0f);
			verts[i].SetFriction(0.9f);
		}
	}

	// Create left to right structural springs
	for (int x = 0; x < grid_sz; ++x) {
		for (int z = 0; z < grid_sz - 1; ++z) {
			int i = z * grid_sz + x;
			int j = (z + 1) * grid_sz + x;

			float rest = Magnitude(verts[i].GetPosition() - verts[j].GetPosition());
			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			structural.Add(spring);
		}
	}

	// Create up and down structural springs
	for (int x = 0; x < grid_sz - 1; ++x) {
		for (int z = 0; z < grid_sz; ++z) {
			int i = z * grid_sz + x;
			int j = z * grid_sz + (x + 1);

			float rest = Magnitude(verts[i].GetPosition() - verts[j].GetPosition());
			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			structural.Add(spring);
		}
	}

	// Create left to right shear springs
	for (int x = 0; x < grid_sz - 1; ++x) {
		for (int z = 0; z < grid_sz - 1; ++z) {
			int i = z * grid_sz + x;
			int j = (z + 1) * grid_sz + (x + 1);

			float rest = Magnitude(verts[i].GetPosition() - verts[j].GetPosition());
			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			shear.Add(spring);
		}
	}

	// Create right to left shear springs
	for (int x = 1; x < grid_sz; ++x) {
		for (int z = 0; z < grid_sz - 1; ++z) {
			int i = z * grid_sz + x;
			int j = (z + 1) * grid_sz + (x - 1);

			float rest = Magnitude(verts[i].GetPosition() - verts[j].GetPosition());
			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			shear.Add(spring);
		}
	}
	
	// Create left to right bend springs
	for (int x = 0; x < grid_sz; ++x) {
		for (int z = 0; z < grid_sz - 2; ++z) {
			int i = z * grid_sz + x;
			int j = (z + 2) * grid_sz + x;

			float rest = Magnitude(verts[i].GetPosition() - verts[j].GetPosition());
			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			bend.Add(spring);
		}
	}

	// Create up and down bend springs
	for (int x = 0; x < grid_sz - 2; ++x) {
		for (int z = 0; z < grid_sz; ++z) {
			int i = z * grid_sz + x;
			int j = z * grid_sz + (x + 2);

			float rest = Magnitude(verts[i].GetPosition() - verts[j].GetPosition());
			Spring spring(k, b, rest);
			spring.SetParticles(&verts[i], &verts[j]);
			bend.Add(spring);
		}
	}
}

void Cloth::SetStructuralSprings(float k, float b) {
	for (int i = 0, size = structural.GetCount(); i < size; ++i) {
		structural[i].SetConstants(k, b);
	}
}

void Cloth::SetShearSprings(float k, float b) {
	for (int i = 0, size = shear.GetCount(); i < size; ++i) {
		shear[i].SetConstants(k, b);
	}
}

void Cloth::SetBendSprings(float k, float b) {
	for (int i = 0, size = bend.GetCount(); i < size; ++i) {
		bend[i].SetConstants(k, b);
	}
}

void Cloth::SetParticleMass(float mass) {
	for (int i = 0, size = verts.GetCount(); i < size; ++i) {
		verts[i].SetMass(mass);
	}
}

void Cloth::ApplyForces() {
	for (int i = 0, size = verts.GetCount(); i < size; ++i) {
		verts[i].ApplyForces();
	}
}

void Cloth::Update(float dt) {
	for (int i = 0, size = verts.GetCount(); i < size; ++i) {
		verts[i].Update(dt);
	}
}

void Cloth::SolveConstraints(const Vector<OBB_>& constraints) {
	for (int i = 0, size = verts.GetCount(); i < size; ++i) {
		verts[i].SolveConstraints(constraints);
	}
}

void Cloth::ApplySpringForces(float dt) {
	for (int i = 0, size = structural.GetCount(); i < size; ++i) {
		structural[i].ApplyForce(dt);
	}
	for (int i = 0, size = shear.GetCount(); i < size; ++i) {
		shear[i].ApplyForce(dt);
	}
	for (int i = 0, size = bend.GetCount(); i < size; ++i) {
		bend[i].ApplyForce(dt);
	}
}


NAMESPACE_SOFTPHYS_END
