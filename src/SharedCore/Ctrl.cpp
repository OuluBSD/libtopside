#include <CtrlCore/CtrlCore.h>
#include <CuboidCore/CuboidCore.h>
#include <Local/Local.h>


NAMESPACE_UPP


GeomInteraction* AbsoluteInterface::GetProxy() const {
	return 0;
}



Ctrl* Absolute2DInterface::GetCtrl() {
	if (!proxy)
		return 0;
	return proxy->GetCtrl();
}

GeomInteraction2D* Absolute2DInterface::GetInteraction() {return GetCtrl();}




void Absolute2DProxy::SetTarget(Absolute2DInterface& iface) {
	if (o) {
		o->proxy = 0;
		o = 0;
	}
	ASSERT(!iface.proxy);
	o = &iface;
	iface.proxy = this;
}

Image Absolute2DProxy::OverrideCursor(const Image& m) {
	ASSERT(o);
	return o->OverrideCursor(m);
}

Image Absolute2DProxy::DefaultCursor() {
	ASSERT(o);
	return o->DefaultCursor();
}





Gubo* Absolute3DInterface::GetGubo() {
	if (!proxy)
		return 0;
	return proxy->GetGubo();
}

GeomInteraction3D* Absolute3DInterface::GetInteraction() {return GetGubo();}





void Absolute3DProxy::SetTarget(Absolute3DInterface& iface) {
	if (o) {
		o->proxy = 0;
		o = 0;
	}
	ASSERT(!iface.proxy);
	o = &iface;
	iface.proxy = this;
}

Image Absolute3DProxy::OverrideCursor(const Image& m) {
	ASSERT(o);
	return o->OverrideCursor(m);
}

Image Absolute3DProxy::DefaultCursor() {
	ASSERT(o);
	return o->DefaultCursor();
}




END_UPP_NAMESPACE

