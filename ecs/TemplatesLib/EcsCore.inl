NAMESPACE_TOPSIDE_BEGIN

#define IFACE_(x, post)\
	inline RefT_Entity<x##post> Entity::Find##x##post() {\
		InterfaceVisitor<x##post> vis; \
		vis.StopWhenFound(); \
		Visit##post##s(vis); \
		x##post* last = vis.GetLast(); \
		if (last) \
			return last->AsRef<x##post>(); \
		return RefT_Entity<x##post>();\
	}
#define IFACE(x) IFACE_(x, Source) IFACE_(x, Sink)
IFACE_LIST
#undef IFACE
#undef IFACE_



#define IFACE_CTX_CLS(dev, val, prefix) \
template<> inline RefT_Entity<prefix##Source> ComponentBase_Static_As(ComponentBase* c) {\
	prefix##Source* p = CastPtr<prefix##Source>(c);\
	if (p) return p->AsRef<prefix##Source>();\
	return RefT_Entity<prefix##Source>();\
}\
template<> inline RefT_Entity<prefix##Sink>   ComponentBase_Static_As(ComponentBase* c) {\
	prefix##Sink* p = CastPtr<prefix##Sink>(c);\
	if (p) return p->AsRef<prefix##Sink>();\
	return RefT_Entity<prefix##Sink>();\
}
#define IFACE(x) DEV_IFACE(x)
IFACE_LIST
#undef IFACE
#undef IFACE_CTX_CLS

NAMESPACE_TOPSIDE_END
