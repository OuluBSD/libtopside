#ifndef _LocalCtrl_LocalCtrl_h_
#define _LocalCtrl_LocalCtrl_h_


#include "Defs.h"

#ifndef flagCTRL
	#error "LocalCtrl library requires CTRL flag to be set"
#endif

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
