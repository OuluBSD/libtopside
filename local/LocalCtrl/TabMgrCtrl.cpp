#include "LocalCtrl.h"


NAMESPACE_TOPSIDE_BEGIN


TabMgrCtrl::TabMgrCtrl() {
	ParentCtrl::Add(tabs.SizePos());
	
}
	
void TabMgrCtrl::Updated() {
	for (Ctrl& c : ctrls)
		c.Updated();
}


NAMESPACE_TOPSIDE_END
