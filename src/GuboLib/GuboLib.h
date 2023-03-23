#ifndef _GuboLib_GuboLib_h_
#define _GuboLib_GuboLib_h_

#include <GuboCore/GuboCore.h>
#include <Geometry/Geometry.h>
#include <ParallelLib/ParallelLib.h>

#if IS_UPP_CORE
NAMESPACE_TOPSIDE_BEGIN

struct VirtualGui3D : RTTIBase {
	RTTI_DECL0(VirtualGui3D)
	
	virtual bool        Poll(UPP::CtrlEvent& e) = 0;
	virtual Size        GetSize() = 0;
	virtual void        SetTitle(String title) = 0;
	virtual SystemDraw& BeginDraw() = 0;
	virtual void        CommitDraw() = 0;
	virtual uint32      GetTickCount() = 0;
	virtual void        WaitEvent(int ms) = 0;
	virtual void        WakeUpGuiThread() = 0;
	virtual bool        IsWaitingEvent() = 0;
	
};

NAMESPACE_TOPSIDE_END
#endif

#include "CoordinateSystem.h"

#include "StaticGubo.h"
#include "Push.h"

#include "HandleTypes.h"
#include "HandleT.h"
#include "ScopeT.h"
#include "HandleSystemT.h"

#include "Atom.h"

#endif
