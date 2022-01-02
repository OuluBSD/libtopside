#ifndef _SoftPhysTests_TestBase_h_
#define _SoftPhysTests_TestBase_h_

NAMESPACE_TOPSIDE_BEGIN


class TestBase {
	Serial::OOSDL2::Context ctx;
	Serial::OOSDL2::OglScreen screen;
	
	
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

	virtual void Initialize(int width, int height);
	virtual void Resize(int width, int height);
	virtual void Render();
	virtual void Update(float dt);
	virtual void Shutdown();
	
	void RenderBegin();
	void RenderEnd();
	
	void SetMouseState(bool left, bool middle, bool right, const vec2& delta, const vec2& mouse);
	
	
};


NAMESPACE_TOPSIDE_END


#endif
