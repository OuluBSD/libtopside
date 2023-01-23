#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


GeomInteraction3D::GeomInteraction3D() {
	ignore_mouse = false;
	hidden = false;
	pending_redraw = true;
	pending_layout = true;
	pending_fx_redraw = true;
	
}

bool GeomInteraction3D::Is3D() const {
	return true;
}

GeomInteraction3D* GeomInteraction3D::Get3D() {
	return this;
}

bool GeomInteraction3D::Redraw(bool only_pending) {
	TODO
}

GeomInteraction3D* GeomInteraction3D::At(int i) {
	TODO
}


NAMESPACE_TOPSIDE_END
