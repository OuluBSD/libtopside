#include "OuluCtrl.h"


NAMESPACE_OULU_BEGIN


TabMgrCtrl::TabMgrCtrl() {
	ParentCtrl::Add(tabs.SizePos());
	
}
	
void TabMgrCtrl::Updated() {
	for (Ctrl& c : ctrls)
		c.Updated();
}


NAMESPACE_OULU_END
