/*#if defined(flagSCREEN)
	#if defined(flagGUI)
		#define GUIPLATFORM_KEYCODES_INCLUDE       <VirtualGui3D/Keys.h>
		#define GUIPLATFORM_INCLUDE                <VirtualGui3D/VirtualGui3D.h>
		#define VIRTUALGUI 1
	    #if !defined(UPP_VERSION)
	        #define GUIPLATFORM_VIRTUALGUI_BACKEND_INCLUDE     <SDL2GUI3D/DrawBackend.h>
	        #define GUIPLATFORM_VIRTUALGUI_INCLUDE             <SDL2GUI3D/SDL2GUI3D.h>
	        #define HAVE_SDL2 1
	    #endif
	#else
		#define NONCTRLPLATFORM_BACKEND_INCLUDE     <ScreenSDL2/DrawBackend.h>
		#define NONCTRLPLATFORM_INCLUDE             <ScreenSDL2/ScreenSDL2.h>
		#define HAVE_SDL2 1
	#endif
#else
	#define NONCTRLPLATFORM_BACKEND_INCLUDE         <NonScreen/DrawBackend.h>
	#define NONCTRLPLATFORM_INCLUDE                 <NonScreen/NonScreen.h>
#endif
*/
#define NONCTRLPLATFORM_BACKEND_INCLUDE         <StaticInterface/DrawBackend.h>
#define NONCTRLPLATFORM_INCLUDE                 <StaticInterface/Screen.h>
