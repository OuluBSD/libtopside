#ifndef _LocalCtrl_Defs_h_
#define _LocalCtrl_Defs_h_


#ifndef flagGUI
	#error <LocalCtrl/LocalCtrl.h> should only be included, when GUI flag is set.
#endif

#include <Local/Before.h>

#if UPP_OLD_VERSION || (defined flagWIN32 && defined flagGCC)
	#define GLEW_STATIC 1
	#include <ports/glew/glew.h>
#else
	#include <GL/glew.h>
#endif

#if HAVE_GLUT
	#include <GL/freeglut.h>
#endif


#include <Local/Local.h>

#include <CtrlLib/CtrlLib.h>

#if IS_UPP_CORE
	#ifndef flagGUI
		#define flagGUI
	#endif
#endif

#ifdef GUIPLATFORM_VIRTUALGUI_INCLUDE
	#include GUIPLATFORM_VIRTUALGUI_INCLUDE
#endif


#endif
