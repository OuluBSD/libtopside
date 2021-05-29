#ifndef _AccelCore_Defs_h_
#define _AccelCore_Defs_h_

NAMESPACE_TOPSIDE_BEGIN


#define ACCEL_CTX(x) \
	using x##AccelT = ContextAccelT<x##Context>; \
	using Accel##x##Source = x##AccelT::AccelSource; \
	using Accel##x##Sink = x##AccelT::AccelSink; \
	using Accel##x##SourceRef = Ref<Accel##x##Source, RefParent1<Entity>>; \
	using Accel##x##SinkRef = Ref<Accel##x##Sink, RefParent1<Entity>>; \
	using Accel##x##PipeComponent = x##AccelT::PipeComponent; \
	using Accel##x##ConvertInputComponent = x##AccelT::ConvertInputComponent; \
	using Accel##x##ConvertOutputComponent = x##AccelT::ConvertOutputComponent; \
	using Accel##x##ConvertInputComponentRef = Ref<x##AccelT::ConvertInputComponent, RefParent1<Entity>>; \
	using Accel##x##ConvertOutputComponentRef = Ref<x##AccelT::ConvertOutputComponent, RefParent1<Entity>>; \
	


#define IFACE(x) ACCEL_CTX(x)
IFACE_LIST
#undef IFACE

#undef ACCEL_CTX





#define IFACE(x) \
template<> inline RefT_Entity<Accel##x##Source> ComponenBase_Static_As(ComponentBase* c) {\
	Accel##x##Source* ptr = CastPtr<Accel##x##Source>(c); \
	return ptr ? ptr->AsRef<Accel##x##Source>() : RefT_Entity<Accel##x##Source>(); \
} \
template<> inline RefT_Entity<Accel##x##Sink>   ComponenBase_Static_As(ComponentBase* c) {\
	Accel##x##Sink* ptr = CastPtr<Accel##x##Sink>(c); \
	return ptr ? ptr->AsRef<Accel##x##Sink>() : RefT_Entity<Accel##x##Sink>(); \
}
IFACE_LIST
#undef IFACE


NAMESPACE_TOPSIDE_END

#endif
