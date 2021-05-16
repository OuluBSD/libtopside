#if defined(flagGUI)
	#define GUIPLATFORM_KEYCODES_INCLUDE <VirtualGui3D/Keys.h>
	#define GUIPLATFORM_INCLUDE          <VirtualGui3D/VirtualGui3D.h>
	#define VIRTUALGUI 1
    #if !defined(flagUPP)
        #define GUIPLATFORM_VIRTUALGUI_BACKEND_INCLUDE     <SDL2GUI3D/DrawBackend.h>
        #define HAVE_SDL2 1
    #endif
#else
	#if defined(flagSDL2)
		#define NONGUIPLATFORM_BACKEND_INCLUDE     <NonGUISDL2/DrawBackend.h>
		#define NONGUIPLATFORM_INCLUDE             <NonGUISDL2/NonGUISDL2.h>
	#else
		#define NONGUIPLATFORM_BACKEND_INCLUDE     <NonGUI/DrawBackend.h>
		#define NONGUIPLATFORM_INCLUDE             <NonGUI/NonGUI.h>
	#endif
#endif
