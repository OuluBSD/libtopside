#ifndef _EcsLib_Defs_h_
#define _EcsLib_Defs_h_


NAMESPACE_UPP

#ifndef ECS_MAIN


bool Open_NonGUI_ECS();
void Close_NonGUI_ECS();

#if 0
	#ifndef UPP_VERSION
		#if defined(flagWIN32)
			#define ECS_MAIN \
			void ConsoleMainFn_(); \
			\
			int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hprev, LPSTR cmdline, int show) {\
				::SetWin32Instances(hinst, hprev, show); \
				char chr[512]; GetModuleFileNameA(NULL, chr, 512); \
				::UPP::AppInit__(0, (const char **)cmdline, 0); \
				if (Open_NonGUI_ECS()) { \
					ConsoleMainFn_(); \
					Close_NonGUI_ECS(); \
				} \
				::UPP::AppExit__(); \
				return ::Upp::GetExitCode(); \
			} \
			\
			void ConsoleMainFn_()
		#else
			#define ECS_MAIN \
			void ConsoleMainFn_(); \
			\
			extern "C" int main(int argc, char *argv[]) {\
				::UPP::AppInit__(argc, (const char **)argv); \
				if (Open_NonGUI_ECS()) { \
					ConsoleMainFn_(); \
					Close_NonGUI_ECS(); \
				} \
				::UPP::AppExit__(); \
				return ::Upp::GetExitCode(); \
			} \
			\
			void ConsoleMainFn_()
		#endif
	#endif
#endif
		
#define ECS_MAIN \
	void EcsMainFn_(); \
	\
	CONSOLE_APP_MAIN {\
		if (Open_NonGUI_ECS()) { \
			EcsMainFn_(); \
			Close_NonGUI_ECS(); \
		} \
	} \
	\
	void EcsMainFn_()


#define CONSOLE_ECS_APP_(x) ECS_MAIN {Topside::SimpleEntityApp<x>();}


#endif

END_UPP_NAMESPACE


#endif
