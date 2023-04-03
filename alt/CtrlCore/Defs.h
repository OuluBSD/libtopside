#ifndef _CtrlCore_Defs_h_
#define _CtrlCore_Defs_h_


#include <Draw/Draw.h>
#include <Local/Local.h>

#ifndef GUIPLATFORM_INCLUDE
	#error Build flags prevents CtrlCore usage. Probably GUI flag is not set and CtrlCore.h is included indirectly.
#else
	#include GUIPLATFORM_INCLUDE
#endif



#if defined LIBTOPSIDE && defined flagGUI
	#define HAVE_WINDOWSYSTEM 1
	#include <VirtualGui3D/VirtualGui3D.h>
#endif


#if defined(flagWIN32) && defined(flagGUI)
	#define GUI_APP_MAIN \
	void GuiMainFn_(); \
	\
	int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmdline, int show) {\
		::UPP::SetWin32Instances(hinst, hprev, show); \
		char chr[512]; GetModuleFileNameA(NULL, chr, 512); \
		::UPP::AppInit__(0, (const char **)cmdline); \
		GuiMainFn_(); \
		::UPP::AppExit__(); \
		return ::UPP::GetExitCode(); \
	} \
	\
	void GuiMainFn_()
#else
	#define GUI_APP_MAIN \
	void GuiMainFn_(); \
	\
	extern "C" int main(int argc, char *argv[]) {\
		::UPP::AppInit__(argc, (const char **)argv); \
		GuiMainFn_(); \
		::UPP::AppExit__(); \
		return ::UPP::GetExitCode(); \
	} \
	\
	void GuiMainFn_()
#endif


#endif
