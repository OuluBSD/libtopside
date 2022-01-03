#include "SoftPhysTests.h"


NAMESPACE_TOPSIDE_BEGIN


TestBase::TestBase() {
	show_help = false;
	mouseLeftDown = false;
	mouseRightDown = false;
	mouseMiddleDown = false;
	mouseDelta = vec2(0.0f, 0.0f);
	mousePos = vec2(0.0f, 0.0f);
	size = vec2(0.0f, 0.0f);
	configHelpWindow = true;
}

void TestBase::Initialize() {
	Resize(640, 480);
}

void TestBase::Resize(int width, int height) {
	camera.Perspective(60.0f, (float)width / (float)height, 0.01f, 1000.0f);
	size = vec2(width, height);
}

void TestBase::Update(float dt) {
	if (mouseRightDown) {
		camera.Rotate(mouseDelta, dt);
	}
	else if (mouseMiddleDown) {
		camera.Zoom(mouseDelta[1], dt);
	}
	else if (mouseLeftDown) {
		camera.Pan(mouseDelta, dt);
	}

	// Update the camera position
	camera.Update(dt);
}

void TestBase::SetMouseState(bool left, bool middle, bool right, const vec2& delta, const vec2& mouse) {
	mouseLeftDown = left;
	mouseMiddleDown = middle;
	mouseRightDown = right;
	mouseDelta = delta;
	mousePos = mouse;
}

void TestBase::Refresh(GfxDataState& s) {
	FixedFunctionOrigin();
}



NAMESPACE_TOPSIDE_END
