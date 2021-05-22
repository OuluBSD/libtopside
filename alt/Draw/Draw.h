#ifndef _DrawAlt_Draw_h_
#define _DrawAlt_Draw_h_

#include <Core/Core.h>
#include <guiplatform.h>

#ifdef GUIPLATFORM_VIRTUALGUI_BACKEND_INCLUDE
	#include GUIPLATFORM_VIRTUALGUI_BACKEND_INCLUDE
#endif

#ifdef NONCTRLPLATFORM_BACKEND_INCLUDE
	#include NONCTRLPLATFORM_BACKEND_INCLUDE
#endif

#include "Image.h"
#include "Font.h"
#include "DrawClasses.h"
#include "SDraw.h"
#include "Chameleon.h"

#ifdef NONCTRLPLATFORM_INCLUDE
	#include NONCTRLPLATFORM_INCLUDE
#endif



NAMESPACE_UPP


END_UPP_NAMESPACE

#endif
