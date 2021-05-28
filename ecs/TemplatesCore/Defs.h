#ifndef _TemplatesCore_Defs_h_
#define _TemplatesCore_Defs_h_

NAMESPACE_TOPSIDE_BEGIN



#define ECS_CTX(x) \
	using x##EcsT = ContextEcsT<x##Context>; \
	using x##ExchangePoint = x##T::ExchangePoint; \
	using x##ExchangePointRef = Ref<x##ExchangePoint, RefParent1<MetaExchangePoint>>; \
	using x##Sink = x##EcsT::BaseSink; \
	using x##Source = x##EcsT::BaseSource; \
	using x##System = x##EcsT::System; \
	using x##SystemRef = Ref<x##System, RefParent1<Machine>>; \
	using x##SinkRef = Ref<x##Sink, RefParent1<Entity>>; \
	using x##SourceRef = Ref<x##Source, RefParent1<Entity>>;



#define IFACE(x) ECS_CTX(x)
IFACE_LIST
#undef IFACE



typedef enum {
	#define IFACE(x) IFACE_##x##Source , IFACE_##x##Sink ,
	IFACE_LIST
	#undef IFACE
} IfaceType;



NAMESPACE_TOPSIDE_END

#endif
