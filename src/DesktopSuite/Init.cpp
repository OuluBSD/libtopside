#include "DesktopSuite.h"


INITBLOCK_(DesktopSuite) {
	using namespace TS;
	
	DesktopFactory::Register<GuiTesterApp>("guitester");
	
	Ecs::Engine::Register<Ecs::DesktopSuiteSystem>("desktop");
	
}
