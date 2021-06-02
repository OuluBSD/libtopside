#ifndef _AccelCore_Defs_h_
#define _AccelCore_Defs_h_

NAMESPACE_TOPSIDE_BEGIN


#define ECS_CTX(dev, value, prefix) \
	using prefix##AccelT = ContextAccelT<dev##value##Spec>; \
	using prefix##PipeComponent = prefix##AccelT::PipeComponent;
#define IFACE_CTX_CLS(dev, value, prefix) ECS_CTX(dev, value, prefix)
#define IFACE(x) DEV_IFACE(x)
IFACE_LIST
#undef IFACE
#undef IFACE_CTX_CLS
#undef ECS_CTX



#define DEV_CONV_CTX(from, to, value) \
	using Conv##from##to##value##T = ContextConvT<from##value##Spec, to##value##Spec>; \
	using Convert##from##to##value##Component = Conv##from##to##value##T::ConvertComponent; \
	using Convert##from##to##value##ComponentRef = Ref<Conv##from##to##value##T::ConvertComponent, RefParent1<Entity>>;
#define IFACE(value) \
	DEV_CONV_CTX(Center, Accel, value) \
	DEV_CONV_CTX(Accel, Center, value)
IFACE_LIST
#undef IFACE
#undef DEV_CONV_CTX



#define IFACE(x) \
template<> inline RefT_Entity<Accel##x##Source> ComponentBase_Static_As<Accel##x##Source>(ComponentBase* c) {\
	Accel##x##Source* ptr = CastPtr<Accel##x##Source>(c); \
	return ptr ? ptr->AsRef<Accel##x##Source>() : RefT_Entity<Accel##x##Source>(); \
} \
template<> inline RefT_Entity<Accel##x##Sink>   ComponentBase_Static_As<Accel##x##Sink>(ComponentBase* c) {\
	Accel##x##Sink* ptr = CastPtr<Accel##x##Sink>(c); \
	return ptr ? ptr->AsRef<Accel##x##Sink>() : RefT_Entity<Accel##x##Sink>(); \
}
IFACE_LIST
#undef IFACE


NAMESPACE_TOPSIDE_END

#endif
