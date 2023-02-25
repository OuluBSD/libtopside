#include "CtrlLib.h"

NAMESPACE_UPP_BEGIN


HeaderCtrl::HeaderCtrl() {
	/*Reset();
	NoWantFocus();
	sb.AutoHide();
	sb.SetLine(StdFont()['Y']);
	autohidesb = true;
	sb.WhenScroll = THISBACK(Scroll);
	WhenScroll = THISBACK(WScroll);
	sb.WhenVisibility = THISBACK(ScrollVisibility);
	BackPaintHint();*/
}

HeaderCtrl& HeaderCtrl::Invisible(bool inv)
{
	invisible = inv;
	if(InFrame() && GetParent())
		RefreshParentLayout();
	return *this;
}


NAMESPACE_UPP_END
