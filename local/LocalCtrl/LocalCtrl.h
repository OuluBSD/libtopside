#ifndef _LocalCtrl_LocalCtrl_h_
#define _LocalCtrl_LocalCtrl_h_

#ifndef flagGUI
	#error "LocalCtrl library requires GUI flag to be set"
#endif

#include "Defs.h"
#include "Compat.h"
#include "Image.h"
#include "BlueBar.h"
#include "GrayBar.h"
#include "ToolMenu.h"
#include "PathCtrl.h"
#include "Container.h"
#include "TabMgrCtrl.h"


NAMESPACE_TOPSIDE_BEGIN


void SetFileDialogDirectory(String path);


NAMESPACE_TOPSIDE_END


#endif
