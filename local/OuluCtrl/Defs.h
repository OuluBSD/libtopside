#ifndef _OuluCtrl_Defs_h_
#define _OuluCtrl_Defs_h_


#ifndef flagGUI
	#error <OuluCtrl/OuluCtrl.h> should only be included, when GUI flag is set.
#endif

#ifdef flagWIN32
	#define GLEW_STATIC 1
#endif
#include <GL/glew.h>

#if HAVE_GLUT
	#include <GL/freeglut.h>
#endif


#include <Oulu/Oulu.h>

#ifdef flagALTCORE
	#include <CtrlLibAlt/CtrlLib.h>
	#ifdef flagSDL2GUI3DALT
		#include <SDL2GUI3DAlt/SDL2GUI3DAlt.h>
	#endif
#else
	#include <CtrlLib/CtrlLib.h>
	#ifdef flagSDL2GUI3D
		#include <SDL2GUI3D/SDL2GUI3D.h>
	#endif
#endif


#endif
