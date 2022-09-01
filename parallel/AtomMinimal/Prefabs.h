#ifndef _AtomMinimal_Prefabs_h_
#define _AtomMinimal_Prefabs_h_

NAMESPACE_TOPSIDE_BEGIN




#define CONSOLE_APP_(x) CONSOLE_APP_MAIN {TS::SimpleSerialApp<x>();}
#define RENDER_APP_(x) RENDER_APP_MAIN {TS::SimpleSerialApp<x>();}
#define GUI_APP_(x) SERIAL_APP_MAIN {TS::SimpleSerialApp<x>();}
#define APP_INITIALIZE_(x) \
	NAMESPACE_UPP \
	INITBLOCK_(AppInitStartup) {TS::Serial::Machine::WhenInitialize << callback(x);} \
	END_UPP_NAMESPACE
#define APP_STARTUP_(x) \
	NAMESPACE_UPP \
	INITBLOCK_(AppInitStartup) {TS::Serial::Machine::WhenPreFirstUpdate << callback(x);} \
	END_UPP_NAMESPACE
#define APP_INITIALIZE_STARTUP_(init, startup) \
	NAMESPACE_UPP \
	INITBLOCK_(AppInitStartup) {TS::Serial::Machine::WhenInitialize << callback(init); TS::Serial::Machine::WhenPreFirstUpdate << callback(startup);} \
	END_UPP_NAMESPACE
#define APP_INITIALIZE_STARTUP_2(init, startup, x) \
	NAMESPACE_UPP \
	INITBLOCK_(AppInitStartup) {TS::Serial::Machine::WhenInitialize << callback(init); TS::Serial::Machine::WhenPreFirstUpdate << callback(startup); TS::Serial::Machine::WhenPreFirstUpdate << callback(x);} \
	END_UPP_NAMESPACE
#define APP_INITIALIZE_STARTUP2_2_ECS(init, startup0, startup1, ecs_gui) \
	NAMESPACE_UPP \
	INITBLOCK_(AppInitStartup) {TS::Serial::Machine::WhenInitialize << callback(init); TS::Serial::Machine::WhenPreFirstUpdate << callback(startup0); TS::Serial::Machine::WhenPreFirstUpdate << callback(startup1); TS::Ecs::Engine::WhenGuiProgram << Callback(ecs_gui);} \
	END_UPP_NAMESPACE
#define APP_INITIALIZE_STARTUP2_2(init, startup0, startup1) \
	NAMESPACE_UPP \
	INITBLOCK_(AppInitStartup) {TS::Serial::Machine::WhenInitialize << callback(init); TS::Serial::Machine::WhenPreFirstUpdate << callback(startup0); TS::Serial::Machine::WhenPreFirstUpdate << callback(startup1);} \
	END_UPP_NAMESPACE
#define APP_DEFAULT_GFX_(x) \
	NAMESPACE_UPP \
	INITBLOCK_(AppDefaultGfx) {TS::Serial::GetAppFlags().gfx = TS::AppFlags::x;} \
	END_UPP_NAMESPACE
#define ECS_INITIALIZE_STARTUP_(init, startup) \
	NAMESPACE_UPP \
	INITBLOCK_(EscInitStartup) {TS::Ecs::Engine::WhenInitialize << callback(init); TS::Ecs::Engine::WhenPreFirstUpdate << callback(startup);} \
	END_UPP_NAMESPACE
#define ECS_INITIALIZE_STARTUP__(x, init, startup) \
	NAMESPACE_UPP \
	INITBLOCK_(x) {TS::Ecs::Engine::WhenInitialize << callback(init); TS::Ecs::Engine::WhenPreFirstUpdate << callback(startup);} \
	END_UPP_NAMESPACE



NAMESPACE_TOPSIDE_END

#endif
