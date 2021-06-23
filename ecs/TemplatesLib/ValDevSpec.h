#ifndef _TemplatesLib_ValDevSpec_h_
#define _TemplatesLib_ValDevSpec_h_

#if 0
NAMESPACE_ECS_BEGIN

/*#define DEV_VALUE_CTX(dev, value, prefix, format, sample) \
	/*using prefix##LibOrderT					= ScopeValDevLibT<VD<dev##Spec, value##Spec>>;*/ \
	/*using prefix##CustomerComponent			= prefix##LibOrderT::DevCustomerComponent;*/ \
	using prefix##DevLibT					= ScopeValDevLibT<VD<dev##Spec, value##Spec>>; \
	using prefix##InputComponent			= prefix##DevLibT::InputComponent; \
	using prefix##OutputComponent			= prefix##DevLibT::OutputComponent; \
	using prefix##InputExt					= prefix##DevLibT::InputExt; \
	using prefix##OutputExt					= prefix##DevLibT::OutputExt; \
	\
	/*PREFAB_BEGIN(prefix##Customer) \
		prefix##CustomerComponent \
	PREFAB_END*/

#define IFACE_CTX(value,	format,		sample) \
	DEV_VALUE_CTX(Center,	value, value,			format, sample) \
	DEV_VALUE_CTX(Accel,	value, Accel##value,	format, sample) \
	DEV_VALUE_CTX(Net,		value, Net##value,		format, sample) \
	DEV_VALUE_CTX(Perma,	value, Perma##value,	format, sample)
IFACE_CTX_ORDER_LIST
#undef IFACE_CTX*/


NAMESPACE_ECS_END

#endif
#endif
