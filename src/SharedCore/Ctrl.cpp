#include <CtrlCore/CtrlCore.h>
#include <Local/Local.h>


NAMESPACE_UPP


Ctrl* AbsoluteWindowInterface::GetWindowCtrl() {
	ASSERT(proxy);
	return proxy->GetWindowCtrl();
}

void AbsoluteWindowProxy::SetTarget(AbsoluteWindowInterface& iface) {
	if (o) {
		o->proxy = 0;
		o = 0;
	}
	ASSERT(!iface.proxy);
	o = &iface;
	iface.proxy = this;
}


END_UPP_NAMESPACE

