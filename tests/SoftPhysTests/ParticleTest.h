#ifndef _SoftPhysTests_ParticleTest_h_
#define _SoftPhysTests_ParticleTest_h_


NAMESPACE_TOPSIDE_BEGIN


class ParticleTest : public TestBase {
	
protected:
	PhysicsSystem phys;
	Space space;
	int numParticles;
	Array<Particle> particles;
	Vector<float> deltaTimes;

	float lastFrameTime;
	bool size_imgui_window;
	
protected:
	void ResetDemo();
	
public:
	inline ParticleTest() : TestBase(), size_imgui_window(true) { }

	void Initialize() override;
	void Update(float dt) override;
	void Refresh(GfxDataState& s) override;

	float Random(float min, float max);
	vec3 Random(vec3 min, vec3 max);
	
	
};


NAMESPACE_TOPSIDE_END


#endif
