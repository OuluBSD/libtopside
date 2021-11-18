#ifndef _AtomComplete_AtomShell_h_
#define _AtomComplete_AtomShell_h_


NAMESPACE_TOPSIDE_BEGIN

void DefaultStartup();
void DefaultRunner(String app_name, String override_eon_file="", VectorMap<String,Object>* extra_args=0);
bool DefaultInitializer();
void DefaultSerialInitializer();

NAMESPACE_TOPSIDE_END


#ifdef flagSCREEN

#define DEFAULT_ATOMSHELL_(title_str) \
	APP_INITIALIZE_STARTUP_(TS::DefaultSerialInitializer, TS::DefaultStartup) \
	RENDER_APP_MAIN {TS::DefaultRunner(title_str);}

#else

#define DEFAULT_ATOMSHELL_(title_str) \
	APP_INITIALIZE_STARTUP_(TS::DefaultSerialInitializer, TS::DefaultStartup) \
	CONSOLE_APP_MAIN {TS::DefaultRunner(title_str);}

#endif

#define DEFAULT_ATOMSHELL DEFAULT_ATOMSHELL_("AtomShell")



#endif
