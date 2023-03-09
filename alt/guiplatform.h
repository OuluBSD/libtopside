#define GUIPLATFORM_BACKEND_INCLUDE         <StaticInterface/DrawBackend.h>
#define flagVIRTUALGUI

#define HAVE_VIRTUALGUI 1

#if HAVE_VIRTUALGUI
	#define GUIPLATFORM_KEYCODES_INCLUDE       <VirtualGui3D/Keys.h>
	#define GUIPLATFORM_INCLUDE                <VirtualGui3D/VirtualGui3D.h>
	#define VIRTUALGUI 1
#else
	#define GUIPLATFORM_INCLUDE                <StaticInterface/Screen.h>
#endif
