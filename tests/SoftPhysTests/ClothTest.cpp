#include "SoftPhysTests.h"


NAMESPACE_TOPSIDE_BEGIN


void ClothTest::Initialize() {
	TestBase::Initialize();

	phys.AddSpace(space);
	
	float val[] = { 0.5f, 1.0f, -1.5f, 0.0f };
	
	size_imgui_window = true;

	camera.SetTarget(vec3(3.75622f, 2.98255f, 0.0f));
	camera.SetZoom(9.0f);
	camera.SetRotation(vec2(-67.9312f, 19.8f));

	num_part = 15;
	part_dist = 0.2f;
	k = -3.0f;
	d = 0.0f;
	ground.size = vec3(10.0f, 0.1f, 10.0f);

	ResetDemo();
}

float ClothTest::Random(float min, float max) {
	if (max < min) {
		float t = min;
		min = max;
		max = t;
	}

	float random = ((float)rand()) / (float)RAND_MAX;

	float range = max - min;
	return (random*range) + min;
}

void ClothTest::ResetDemo() {
	//phys.ClearRigidbodys();
	phys.ClearConstraints();
	phys.ClearSprings();
	phys.ClearCloths();
	renderObjects.Clear();

	cloth.Initialize(num_part, part_dist, vec3(0, 6, 0));
	cloth.SetStructuralSprings(k, d);
	cloth.SetBendSprings(k, d);
	cloth.SetShearSprings(k, d);
	phys.AddCloth(&cloth);

	phys.AddConstraint(ground);
	renderObjects.SetCount(4);

	float d = 0.5f;
	renderObjects[0].position = vec3( d, 2.4f,  d);
	renderObjects[1].position = vec3(-d, 2.3f,  d);
	renderObjects[2].position = vec3(-d, 2.4f, -d);
	renderObjects[3].position = vec3( d, 2.3f, -d);

	for (int i = 0; i < 4; ++i) {
		renderObjects[i].size = vec3(0.3f, 0.5f, 0.3f);
		phys.AddConstraint(renderObjects[i]);
		renderObjects[i].size = vec3(0.1f, 0.5f, 0.1f);
	}
}

void ClothTest::Update(float dt) {
	TestBase::Update(dt);

	phys.Update(dt);
}

void ClothTest::Refresh(GfxDataState& s) {
	TestBase::Refresh(s);
	
	phys.Refresh(s);
}


NAMESPACE_TOPSIDE_END
