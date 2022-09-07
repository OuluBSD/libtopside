#ifndef _TemplatesCore_Defs_h_
#define _TemplatesCore_Defs_h_

NAMESPACE_TOPSIDE_BEGIN



#define ECS_CTX(dev, value, prefix) \
	using prefix##CoreT				= ScopeValDevCoreT<dev##value##Spec>; \
	using prefix##ExchangePoint		= prefix##MachT::ValExchangePoint; \
	using prefix##ExchangePointRef	= Ref<prefix##ExchangePoint, RefParent1<MetaExchangePoint>>; \
	using prefix##Sink				= prefix##CoreT::ValSink; \
	using prefix##Source			= prefix##CoreT::ValSource; \
	/*using prefix##System			= prefix##CoreT::ValSystem; \
	using prefix##SystemRef			= Ref<prefix##System, RefParent1<Machine>>;*/ \
	using prefix##SinkRef			= Ref<prefix##Sink, RefParent1<Entity>>; \
	using prefix##SourceRef			= Ref<prefix##Source, RefParent1<Entity>>;
#define IFACE_CTX_CLS(dev, value, prefix) ECS_CTX(dev, value, prefix)
#define IFACE(x) DEV_IFACE(x)
IFACE_LIST
#undef IFACE
#undef IFACE_CTX_CLS
#undef ECS_CTX


#define DEV(dev) \
	using dev##DevCoreT				= ScopeDevCoreT<dev##Spec>;
DEV_LIST
#undef DEV


typedef enum {
	#define IFACE(x) IFACE_##x##Source , IFACE_##x##Sink ,
	IFACE_LIST
	#undef IFACE
} IfaceType;



NAMESPACE_TOPSIDE_END

#endif
