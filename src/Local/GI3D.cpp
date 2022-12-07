#include "Local.h"

NAMESPACE_TOPSIDE_BEGIN


GeomInteraction3D::GeomInteraction3D() {
	
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


NAMESPACE_TOPSIDE_END
