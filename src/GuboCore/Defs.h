#ifndef _GuboCore_Defs_h_
#define _GuboCore_Defs_h_


#include <Draw/Draw.h>
#include <Local/Local.h>

#if IS_TS_CORE
#define HAVE_VIRTUALGUI 1

#if HAVE_VIRTUALGUI
	#define GUIPLATFORM_KEYCODES_INCLUDE       <GuboCore/Keys.h>
	#define GUIPLATFORM_INCLUDE                <GuboCore/VirtualGui3D.h>
	#define VIRTUALGUI 1
#else
	#define GUIPLATFORM_INCLUDE                <StaticInterface/Screen.h>
#endif
#endif



#ifndef GUIPLATFORM_INCLUDE
	#error Build flags prevents GuboCore usage. Probably GUI flag is not set and GuboCore.h is included indirectly.
#else
	#include GUIPLATFORM_INCLUDE
#endif



#if defined LIBTOPSIDE && defined flagGUI
	#define HAVE_WINDOWSYSTEM 1
	#include <GuboCore/VirtualGui3D.h>
#endif


#endif
