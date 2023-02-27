#include "CtrlLib.h"

NAMESPACE_UPP



SeparatorCtrl::SeparatorCtrl() {
	
}

Size SeparatorCtrl::GetMinSize() const {
	TODO
}

void SeparatorCtrl::Paint(Draw& w) {
	TODO
}




StaticRect::StaticRect() {
	
}

Size StaticRect::GetMinSize() const {
	TODO
}

void StaticRect::Paint(Draw& w) {
	TODO
}

StaticRect& StaticRect::Background(const Color& chvalue) {
	clr = chvalue;
	return *this;
}




END_UPP_NAMESPACE
