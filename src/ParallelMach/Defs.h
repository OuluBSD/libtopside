#ifndef _ParallelMach_Defs_h_
#define _ParallelMach_Defs_h_

#if defined(flagWIN32) && defined(flagGUI)
	#define PARALLEL_APP_MAIN_(arg_fn) \
	void GuiMainFn_(); \
	\
	int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmdline, int show) {\
		::UPP::SetWin32Instances(hinst, hprev, show); \
		char chr[512]; GetModuleFileNameA(NULL, chr, 512); \
		::UPP::AppInit__(0, (const char **)cmdline); \
		TS::SingleMachine().Run(GuiMainFn_, arg_fn); \
		::UPP::AppExit__(); \
		return ::UPP::GetExitCode(); \
	} \
	\
	void GuiMainFn_()
#else
	#define PARALLEL_APP_MAIN_(arg_fn) \
	void GuiMainFn_(); \
	\
	extern "C" int main(int argc, char *argv[]) {\
		::UPP::AppInit__(argc, (const char **)argv); \
		TS::SingleMachine().Run(GuiMainFn_, arg_fn); \
		::UPP::AppExit__(); \
		return ::UPP::GetExitCode(); \
	} \
	\
	void GuiMainFn_()
#endif

#define ECS_APP_MAIN			PARALLEL_APP_MAIN_(::TS::Serial::MachineEcsInit)
#define RENDER_APP_MAIN			PARALLEL_APP_MAIN_(0)

#define DEFAULT_ECS_APP_MAIN \
	ECS_INITIALIZE_DEFAULT_INTERNAL_EON_(TS::BindEcsToParallel) \
	ECS_APP_MAIN

#if defined flagMSC && !defined flagUWP
	#define CXX2A_STATIC_ASSERT(x, y) static_assert(x, y)
#else
	#define CXX2A_STATIC_ASSERT(x, y)
#endif


#define LOOP_PREFAB_BEGIN(x) \
struct x##_ : RTTIBase {RTTI_DECL0(x##_)}; \
\
struct x : \
	x##_, \
	SpacePrefab<

#define LOOP_PREFAB_END \
> { \
	 \
    static Atoms Make(Space& e) \
    { \
        auto atoms = SpacePrefab::Make(e); \
		return atoms; \
    } \
};


#endif
