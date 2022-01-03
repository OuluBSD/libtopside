#ifndef _SoftPhysTests_ClothTest_h_
#define _SoftPhysTests_ClothTest_h_


NAMESPACE_TOPSIDE_BEGIN


class ClothTest : public TestBase {
	
protected:
	PhysicsSystem phys;
	Space space;
	Cloth cloth;
	OBB_ ground;
	Vector<OBB_> renderObjects;

	int num_part;
	float part_dist;
	float k;
	float d;

	bool size_imgui_window;
	
protected:
	void ResetDemo();
	float Random(float min, float max);
	
public:
	inline ClothTest() : TestBase(), size_imgui_window(true) { }

	void Initialize() override;
	void Update(float dt) override;
	void Refresh(GfxDataState& s) override;
	
};


NAMESPACE_TOPSIDE_END


#endif
