#ifndef _SoftPhysTests_TestBase_h_
#define _SoftPhysTests_TestBase_h_

NAMESPACE_TOPSIDE_BEGIN


class TestBase {
	TestBase(const TestBase&);
	TestBase& operator=(const TestBase);
	
protected:
	bool show_help;
	bool mouseLeftDown;
	bool mouseRightDown;
	bool mouseMiddleDown;
	vec2 mouseDelta;
	vec2 mousePos;
	vec2 size;
	bool configHelpWindow;
	
public:
	OrbitCamera camera;

	TestBase();
	inline virtual ~TestBase() { }

	virtual void Initialize();
	virtual void Resize(int width, int height);
	virtual void Refresh(GfxDataState& s);
	virtual void Update(float dt);
	
	
	void SetMouseState(bool left, bool middle, bool right, const vec2& delta, const vec2& mouse);
	
	
};


NAMESPACE_TOPSIDE_END


#endif
