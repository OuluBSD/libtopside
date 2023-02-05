#ifndef _LocalCtrl_LocalCtrl_h_
#define _LocalCtrl_LocalCtrl_h_


#include "Defs.h"

#ifndef flagGUI
	#error "LocalCtrl library requires GUI flag to be set"
#endif

#include "Compat.h"
#include "Util.h"
#include "Image.h"
#include "BlueBar.h"
#include "GrayBar.h"
#include "ToolMenu.h"
#include "PathCtrl.h"
#include "Container.h"
#include "TabMgrCtrl.h"
#include "GridCtrl.h"
#include "TimelineCtrl.h"


NAMESPACE_TOPSIDE_BEGIN

//#include <Local/Ctrl.inl>

void SetFileDialogDirectory(String path);


NAMESPACE_TOPSIDE_END


#endif
