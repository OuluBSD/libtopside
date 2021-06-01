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



#define IFACE(x) \
template<> inline RefT_Entity<x##Source> ComponentBase_Static_As(ComponentBase* c) {x##Source* p = CastPtr<x##Source>(c); if (p) return p->AsRef<x##Source>(); return RefT_Entity<x##Source>();} \
template<> inline RefT_Entity<x##Sink>   ComponentBase_Static_As(ComponentBase* c) {x##Sink* p = CastPtr<x##Sink>(c); if (p) return p->AsRef<x##Sink>(); return RefT_Entity<x##Sink>();}
IFACE_LIST
#undef IFACE

NAMESPACE_TOPSIDE_END
