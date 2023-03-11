#ifndef _GuboCore_Defs_h_
#define _GuboCore_Defs_h_




#define NAMESPACE_GUBO_NAME		Gu
#define GUBO					Gu
#define NAMESPACE_GUBO_BEGIN	\
	static_assert(!is_in_parallel, "already in gubo"); \
	namespace TS { namespace NAMESPACE_GUBO_NAME {
#define NAMESPACE_GUBO_END		}}


#if IS_TS_CORE
#define HAVE_VIRTUALGUI 1

#if HAVE_VIRTUALGUI
	#define GUIPLATFORM_KEYCODES_INCLUDE       <VirtualGui3D/Keys.h>
	#define GUIPLATFORM_INCLUDE                <VirtualGui3D/VirtualGui3D.h>
	#define VIRTUALGUI 1
#else
	#define GUIPLATFORM_INCLUDE                <StaticInterface/Screen.h>
#endif
#endif


#if IS_TS_CORE
#ifndef GUIPLATFORM_INCLUDE
	#error Build flags prevents GuboCore usage. Probably GUI flag is not set and GuboCore.h is included indirectly.
#else
	#include GUIPLATFORM_INCLUDE
#endif
#endif



#if defined LIBTOPSIDE && defined flagGUI
	#define HAVE_WINDOWSYSTEM 1
	#include <VirtualGui3D/VirtualGui3D.h>
#endif


#endif
