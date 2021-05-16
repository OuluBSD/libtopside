#ifndef _OuluCtrl_OuluCtrl_h_
#define _OuluCtrl_OuluCtrl_h_

#ifndef flagGUI
	#error "OuluCtrl library requires GUI flag to be set"
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


NAMESPACE_OULU_BEGIN


void SetFileDialogDirectory(String path);


NAMESPACE_OULU_END


#endif
