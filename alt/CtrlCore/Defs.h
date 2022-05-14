#ifndef _CtrlCore_Defs_h_
#define _CtrlCore_Defs_h_


#include <Draw/Draw.h>
#include <Local/Local.h>

#ifndef GUIPLATFORM_INCLUDE
	#error Build flags prevents CtrlCore usage. Probably CTRL flag is not set and CtrlCore.h is included indirectly.
#else
	#include GUIPLATFORM_INCLUDE
#endif


#define GUI_APP_MAIN \
void UserGuiMainFn_(); \
\
INITBLOCK_(main_program) {TS::Ecs::Engine::WhenGuiProgram << Callback(UserGuiMainFn_);} \
APP_INITIALIZE_STARTUP_(TS::DefaultSerialInitializer, TS::DefaultStartup) \
RENDER_APP_MAIN {TS::DefaultRunner("Gui App");} \
\
void UserGuiMainFn_()


#endif
