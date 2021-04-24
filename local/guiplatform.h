#ifdef flagVIRTUALGUI3D
#define GUIPLATFORM_KEYCODES_INCLUDE <VirtualGui3D/Keys.h>
#define GUIPLATFORM_INCLUDE          <VirtualGui3D/VirtualGui3D.h>
#define VIRTUALGUI 1
#endif

#ifdef flagVIRTUALGUI3DALT
#define GUIPLATFORM_KEYCODES_INCLUDE <VirtualGui3DAlt/Keys.h>
#define GUIPLATFORM_INCLUDE          <VirtualGui3DAlt/VirtualGuiAlt.h>
#define VIRTUALGUI 1
#endif

#ifdef flagSDL2GUI3DALT
#define GUIPLATFORM_VIRTUALGUI_BACKEND_INCLUDE     <SDL2GUI3DAlt/DrawBackend.h>
#endif

#if !defined flagGUI && defined flagALTCORE
	#if defined(flagSDL2)
		#define NONGUIPLATFORM_BACKEND_INCLUDE     <NonGUISDL2/DrawBackend.h>
		#define NONGUIPLATFORM_INCLUDE             <NonGUISDL2/NonGUISDL2.h>
	#else
		#define NONGUIPLATFORM_BACKEND_INCLUDE     <NonGUI/DrawBackend.h>
		#define NONGUIPLATFORM_INCLUDE             <NonGUI/NonGUI.h>
	#endif
#endif
