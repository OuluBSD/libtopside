#ifndef _SoftPhysTests_ManyTest_h_
#define _SoftPhysTests_ManyTest_h_


NAMESPACE_TOPSIDE_BEGIN


class ManyTest : public TestBase {
	
protected:
	PhysicsSystem phys;
	Space space;
	Array<RigidbodyVolume> bodies;
	RigidbodyVolume gnd;

	bool size_imgui_window;
	
protected:
	void ResetDemo();
	
public:
	void Initialize(int width, int height) override;
	void Update(float dt) override;
	void Render() override;
	
};


NAMESPACE_TOPSIDE_END


#endif
