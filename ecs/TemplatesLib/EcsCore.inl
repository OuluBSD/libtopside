NAMESPACE_TOPSIDE_BEGIN

#define IFACE_(x, post)\
	inline RefT_Entity<x##post> Entity::Find##x##post() {\
		InterfaceVisitor<x##post> vis; \
		vis.StopWhenFound(); \
		Visit##post##s(vis); \
		x##post* last = vis.GetLast(); \
		if (last) \
			return last->AsRefT(); \
		return RefT_Entity<x##post>();\
	}
#define IFACE(x) IFACE_(x, Source) IFACE_(x, Sink)
IFACE_LIST
#undef IFACE
#undef IFACE_



#define IFACE(x) \
template<> inline RefT_Entity<x##Source> ComponenBase_Static_As(ComponentBase* c) {return c->As##x##Source();} \
template<> inline RefT_Entity<x##Sink>   ComponenBase_Static_As(ComponentBase* c) {return c->As##x##Sink();}
IFACE_LIST
#undef IFACE

NAMESPACE_TOPSIDE_END
