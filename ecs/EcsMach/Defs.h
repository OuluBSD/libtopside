#ifndef _EcsMech_Defs_h_
#define _EcsMech_Defs_h_


#if defined(flagWIN32)
	#define GUI_APP_MAIN_(gui) \
	void GuiMainFn_(); \
	\
	int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmdline, int show) {\
		::SetWin32Instances(hinst, hprev, show); \
		char chr[512]; GetModuleFileNameA(NULL, chr, 512); \
		::UPP::AppInit__(0, (const char **)cmdline); \
		TS::SingleMachine().Run(gui, GuiMainFn_); \
		::UPP::AppExit__(); \
		return ::UPP::GetExitCode(); \
	} \
	\
	void GuiMainFn_()
#else
	#define GUI_APP_MAIN_(gui) \
	void GuiMainFn_(); \
	\
	extern "C" int main(int argc, char *argv[]) {\
		::UPP::AppInit__(argc, (const char **)argv); \
		TS::SingleMachine().Run(gui, GuiMainFn_); \
		::UPP::AppExit__(); \
		return ::UPP::GetExitCode(); \
	} \
	\
	void GuiMainFn_()
#endif

#define GUI_APP_MAIN			GUI_APP_MAIN_(true)
#define RENDER_APP_MAIN			GUI_APP_MAIN_(false)


#ifdef flagMSC
	#define CXX2A_STATIC_ASSERT(x, y) static_assert(x, y)
#else
	#define CXX2A_STATIC_ASSERT(x, y)
#endif


#endif
