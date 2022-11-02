#ifndef _Complete_Prefabs_h_
#define _Complete_Prefabs_h_

#define GUI_APP_MAIN \
void UserGuiMainFn_(); \
\
APP_INITIALIZE_STARTUP_(TS::DefaultSerialInitializer, TS::DefaultStartup) \
ECS_APP_MAIN { \
	TS::Ecs::Engine::WhenGuiProgram << Callback(UserGuiMainFn_); \
	TS::DefaultRunner(0, "Gui App", "default_gui.eon");} \
\
void UserGuiMainFn_()

#endif
