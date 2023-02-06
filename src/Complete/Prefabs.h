#ifndef _Complete_Prefabs_h_
#define _Complete_Prefabs_h_

#if defined flagSDL2
	#define GUI_EON "deps/default_gui_app_sdl.eon"
	#define GUBO_EON "deps/default_gubo_app_sdl.eon"
#elif defined flagPOSIX
	#define GUI_EON "deps/default_gui_app_x11.eon"
	#define GUBO_EON "deps/default_gubo_app_x11.eon"
#else
	#error No eon file for GUI app on this platform.
#endif

#ifdef UPP_VERSION
	#warning TODO
#else

#define GUI_APP_MAIN \
void UserGuiMainFn_(); \
\
APP_INITIALIZE_STARTUP_(TS::DefaultSerialInitializer, TS::DefaultStartup) \
RENDER_APP_MAIN { \
	TS::Serial::Machine::WhenUserProgram << Callback(UserGuiMainFn_); \
	TS::DefaultRunner(0, "Gui App", GUI_EON);} \
\
void UserGuiMainFn_()

#define GUBO_APP_MAIN \
void UserGuiMainFn_(); \
\
APP_INITIALIZE_STARTUP_(TS::DefaultSerialInitializer, TS::DefaultStartup) \
RENDER_APP_MAIN { \
	TS::Serial::Machine::WhenUserProgram << Callback(UserGuiMainFn_); \
	TS::DefaultRunner(0, "Gui App", GUBO_EON);} \
\
void UserGuiMainFn_()

#endif

#endif
