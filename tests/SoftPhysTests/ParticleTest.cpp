#include "SoftPhysTests.h"


NAMESPACE_TOPSIDE_BEGIN


extern double GetMilliseconds();
 
void ParticleTest::Initialize() {
	TestBase::Initialize();
	
	phys.AddSpace(space);
	
	float val[] = { 0.5f, 1.0f, -1.5f, 0.0f };
	
	numParticles = 50;
	size_imgui_window = true;
	lastFrameTime = GetMilliseconds();

	camera.SetTarget(vec3(3.75622f, 2.98255f, 0.0f));
	camera.SetZoom(9.0f);
	camera.SetRotation(vec2(-67.9312f, 19.8f));

	ResetDemo();
}

void ParticleTest::ResetDemo() {
	particles.Clear();
	particles.Reserve(numParticles);

	space.Clear();
	phys.ClearConstraints();


	OBB_ ground;
	ground.size = vec3(10.0f, 0.15f, 10.0f);

	OBB_ obb1;
	obb1.position = vec3(0.0f, 1.86f, -1.92f);
	obb1.orientation = Rotation3x3(30.716f, 0.0f, 0.0f);
	obb1.size = vec3(2.0f, 0.15f, 2.0f);

	OBB_ obb2;
	obb2.position = vec3(-1.0f, 3.6f, 1.2f);
	obb2.orientation = Rotation3x3(-33.964f, -24.233f, 9.128f);
	obb2.size = vec3(2.0f, 0.15f, 2.0f);

	OBB_ obb3;
	obb3.position = vec3(0.0f, 3.93f, -2.27f);
	obb3.orientation = Rotation3x3(24.702f, 0.0f, 0.0f);
	obb3.size = vec3(2.0f, 0.15f, 0.7817011f);

	phys.AddConstraint(ground);
	phys.AddConstraint(obb1);
	phys.AddConstraint(obb2);
	phys.AddConstraint(obb3);

	vec3 spawnPos = vec3(-0.5f, 6.5f, -1.01f);
	vec3 spawnSize = vec3(3.8505f, 2, 4.034834f);
	vec3 spawnMin = spawnPos - spawnSize;
	vec3 spawnMax = spawnPos + spawnSize;
	
	particles.SetCount(numParticles);
	for (Particle& p : particles) {
		p.SetPosition(Random(spawnMin, spawnMax));
		p.SetBounce(Random(0, 1));
		space.Add(p);
	}

	/* Debug
	particles.Add(Particle());
	particles[0].SetPosition(vec3(-1.07645, 7.29192, 0.292606));
	phys.AddRigidbody(&particles[0]);
	*/
}

void ParticleTest::Update(float dt) {
	TestBase::Update(dt);

	double thisFrameTime = GetMilliseconds();
	deltaTimes.Add(float(thisFrameTime - lastFrameTime));
	if (deltaTimes.GetCount() > 120) {
		deltaTimes.Remove(0, deltaTimes.GetCount() - 120);
	}
	lastFrameTime = thisFrameTime;

	phys.Update(dt);

	// This next part isn't really needed. It's just in place
	// in case the simulation becomes unstable and something
	// falls below the floor of the world!
	for (Particle& p : particles) {
		vec3 position = p.GetPosition();
		if (position[1] < -5.0f) {
			position[1] = -5.0f;
			p.SetPosition(position);
		}
	}
}

float ParticleTest::Random(float min, float max) {
	if (max < min) {
		float t = min;
		min = max;
		max = t;
	}

	float random = ((float)rand()) / (float)RAND_MAX;

	float range = max - min;
	return (random*range) + min;
}

vec3 ParticleTest::Random(vec3 min, vec3 max) {
	vec3 result;
	for(int i = 0; i < 3; i++)
		result[i] = Random(min[i], max[i]);
	return result;
}

void ParticleTest::Refresh(GfxDataState& s) {
	TestBase::Refresh(s);
	
	phys.Refresh(s);
}


NAMESPACE_TOPSIDE_END
