#include <CtrlCore/CtrlCore.h>
#include <Local/Local.h>


NAMESPACE_UPP


Ctrl* AbsoluteWindowInterface::GetWindowCtrl() {
	if (!proxy)
		return 0;
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

