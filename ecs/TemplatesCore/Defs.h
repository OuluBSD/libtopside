#ifndef _TemplatesCore_Defs_h_
#define _TemplatesCore_Defs_h_

NAMESPACE_TOPSIDE_BEGIN



#define ECS_CTX(dev, value, prefix) \
	using prefix##EcsT				= ContextEcsT<dev##value##Context>; \
	using prefix##ExchangePoint		= prefix##MachT::ExchangePoint; \
	using prefix##ExchangePointRef	= Ref<prefix##ExchangePoint, RefParent1<MetaExchangePoint>>; \
	using prefix##Sink				= prefix##EcsT::BaseSink; \
	using prefix##Source			= prefix##EcsT::BaseSource; \
	using prefix##System			= prefix##EcsT::System; \
	using prefix##SystemRef			= Ref<prefix##System, RefParent1<Machine>>; \
	using prefix##SinkRef			= Ref<prefix##Sink, RefParent1<Entity>>; \
	using prefix##SourceRef			= Ref<prefix##Source, RefParent1<Entity>>;
#define IFACE_CTX_CLS(dev, value, prefix) ECS_CTX(dev, value, prefix)
#define IFACE(x) DEV_IFACE(x)
IFACE_LIST
#undef IFACE
#undef IFACE_CTX_CLS
#undef ECS_CTX


#define DEV(dev) \
	using dev##DevEcsT				= ContextDevEcsT<dev##Context>; \
	using dev##System				= ContextDevEcsT<dev##Context>::System;
DEV_LIST
#undef DEV


typedef enum {
	#define IFACE(x) IFACE_##x##Source , IFACE_##x##Sink ,
	IFACE_LIST
	#undef IFACE
} IfaceType;



NAMESPACE_TOPSIDE_END

#endif
