#include <CtrlCore/CtrlCore.h>
#include <Local/Local.h>


NAMESPACE_UPP


Ctrl* Absolute2DInterface::GetCtrl() {
	if (!proxy)
		return 0;
	return proxy->GetCtrl();
}

void Absolute2DProxy::SetTarget(Absolute2DInterface& iface) {
	if (o) {
		o->proxy = 0;
		o = 0;
	}
	ASSERT(!iface.proxy);
	o = &iface;
	iface.proxy = this;
}



Gubo* Absolute3DInterface::GetGubo() {
	if (!proxy)
		return 0;
	return proxy->GetGubo();
}

void Absolute3DProxy::SetTarget(Absolute3DInterface& iface) {
	if (o) {
		o->proxy = 0;
		o = 0;
	}
	ASSERT(!iface.proxy);
	o = &iface;
	iface.proxy = this;
}



END_UPP_NAMESPACE

