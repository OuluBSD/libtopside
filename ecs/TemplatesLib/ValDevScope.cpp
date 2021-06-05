#include "TemplatesLib.h"

NAMESPACE_TOPSIDE_BEGIN


ValExchangePointBase* ValExchangePointBase::Create(TypeCls t) {
	#define IFACE_CTX_CLS(dev, val, prefix) \
		if (t == AsTypeCls<VD<dev##Spec, val##Spec>>()) \
			return new ScopeValDevMachT<VD<dev##Spec, val##Spec>>::ValExchangePoint();
	#define IFACE(x) DEV_IFACE(x)
	IFACE_LIST
	#undef IFACE
	#undef IFACE_CTX_CLS
	ASSERT_(false, "Invalid TypeCls arg in ValExchangePointBase::Create");
	return 0;
}


NAMESPACE_TOPSIDE_END
