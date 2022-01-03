#include "SoftPhysTests.h"


NAMESPACE_TOPSIDE_BEGIN


void ManyTest::Initialize() {
	TestBase::Initialize();

	phys.AddSpace(space);
	phys.rend_rand_clr = true;
	phys.impulse_iter = 8;
	phys.do_lin_proj = true;
	size_imgui_window = true;

	camera.SetTarget(vec3(3.75622f, 2.98255f, 0.0f));
	camera.SetZoom(12.0f);
	camera.SetRotation(vec2(-67.9312f, 19.8f));

	ResetDemo();
}

void ManyTest::ResetDemo() {
	space.Clear();
	phys.ClearConstraints();

	bodies.Clear();
	bodies.SetCount(2);

	bodies[0].type = RIGIDBODY_TYPE_BOX;
	bodies[0].position = vec3(0.5f, 6, 0);
#ifndef LINEAR_ONLY
	bodies[0].orientation = vec3(0.0f, 0.0f, 0.4f);
#endif

	bodies[1].type = RIGIDBODY_TYPE_BOX;
	bodies[1].position = vec3(0, 1, 0);
	bodies[1].mass = 5.0f;

	gnd.type = RIGIDBODY_TYPE_BOX;
	gnd.position = vec3(0, -0.5f, 0) * vec3(1, 0.5f, 1);
	gnd.box.size = vec3(50, 1, 50) * 0.25f;
	gnd.mass = 0.0f;
	gnd.SynchCollisionVolumes();

	for (auto& b : bodies) {
		b.SynchCollisionVolumes();
		space.Add(b);
	}
	space.Add(gnd);
}

void ManyTest::Update(float dt) {
	TestBase::Update(dt);


	phys.Update(dt);
}

void ManyTest::Refresh(GfxDataState& s) {
	TestBase::Refresh(s);
	
	phys.Refresh(s);
}


NAMESPACE_TOPSIDE_END
