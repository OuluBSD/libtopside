#ifndef _AtomMinimal_AtomShell_h_
#define _AtomMinimal_AtomShell_h_


NAMESPACE_TOPSIDE_BEGIN

void DefaultStartup();
void DefaultRunner(bool main_loop, String app_name, String override_eon_file="", VectorMap<String,Object>* extra_args=0, const char* extra_str=0);
void DefaultRunnerStop();
bool DefaultInitializer(bool skip_eon_file);
void DefaultSerialInitializer();
void DefaultSerialInitializer0(bool skip_eon_file=false);
void DefaultSerialInitializerInternalEon();
void DebugMainLoop();
void DebugMainLoop(Serial::Machine& mach, bool (*fn)(void*)=0, void* arg=0);

struct SerialLoaderBase {
	
	virtual ~SerialLoaderBase() {}
	virtual String LoadFile(String file_path) = 0;
	
};

struct SerialLoaderFactory {
	typedef SerialLoaderBase*(*NewFn)();
	struct Loader : Moveable<Loader> {
		NewFn fn;
		
	};
	
	static VectorMap<String,Loader>& GetLoaders() {static VectorMap<String,Loader> l; return l;}
	
	
	template <class T>
	static SerialLoaderBase* New() {return new T();}
	
	
	template <class T>
	static void Register(String file_ext) {
		Loader& l = GetLoaders().Add(file_ext);
		l.fn = &New<T>;
	}
	
	
	static String LoadFile(String file_path);
};



NAMESPACE_TOPSIDE_END


#define APP_INITIALIZE_DEFAULT \
	APP_INITIALIZE_STARTUP_(TS::DefaultSerialInitializer, TS::DefaultStartup)

#define APP_INITIALIZE_DEFAULT_INTERNAL_EON \
	APP_INITIALIZE_STARTUP_(TS::DefaultSerialInitializerInternalEon, TS::DefaultStartup)

#define APP_INITIALIZE_DEFAULT_INTERNAL_EON_(x) \
	APP_INITIALIZE_STARTUP_2(TS::DefaultSerialInitializerInternalEon, TS::DefaultStartup, x)



#define DEFAULT_ATOMSHELL_(title_str) \
	APP_INITIALIZE_DEFAULT \
	RENDER_APP_MAIN {TS::DefaultRunner(true, title_str);}

#define DEFAULT_ECS_SHELL_(title_str) \
	APP_INITIALIZE_STARTUP2_2(TS::DefaultSerialInitializer, TS::DefaultStartup, TS::BindEcsToSerial) \
	ECS_APP_MAIN {TS::DefaultRunner(true, title_str);}

#define DEFAULT_ECS_SHELL_EON(title_str, eon_path) \
	APP_INITIALIZE_STARTUP2_2(TS::DefaultSerialInitializer, TS::DefaultStartup, TS::BindEcsToSerial) \
	ECS_APP_MAIN {TS::DefaultRunner(true, title_str, eon_path);}


#define DEFAULT_ATOMSHELL DEFAULT_ATOMSHELL_("AtomShell")
#define DEFAULT_ECS_SHELL DEFAULT_ECS_SHELL_("EcsShell")



#endif
