#ifndef _ParallelLib_ParallelLib_h_
#define _ParallelLib_ParallelLib_h_

#include <ParallelCore/ParallelCore.h>
#include <Geometry/Geometry.h>

#ifdef flagGUI
	#include <GuboLib/GuboLib.h>
#endif

#if IS_UPP_CORE
#include <CtrlLib/CtrlLib.h>
#endif

#include "Base.h"
#include "BaseAudio.h"
#include "BaseVideo.h"
#include "RegistrySystem.h"

#ifdef flagGUI
#include "HandleTypes.h"
#include "FrameT.h"
#include "ScopeT.h"
#include "HandleSystemT.h"
#endif

#endif
