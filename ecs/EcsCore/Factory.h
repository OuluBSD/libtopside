#ifndef _EcsCore_Factory_h_
#define _EcsCore_Factory_h_

NAMESPACE_ECS_BEGIN


class Factory {
	
public:
	
	// Components
	
	typedef ComponentBase* (*NewFn)();
	struct CompData : Moveable<CompData> {
		NewFn new_fn;
		String name;
		TypeCls cls;
		TypeCls rtti_cls;
	};
	typedef VectorMap<TypeCls,CompData> CompMap;
	static CompMap& CompDataMap() {MAKE_STATIC(CompMap, m); return m;}
	
	template <class T> static ComponentBase* CreateComp() {return new T();}
	
	template <class T> static void RegisterComponent(TypeCls cls) {
		CompData& d = CompDataMap().GetAdd(cls);
		d.rtti_cls = AsTypeCls<T>();
		d.cls = cls;
		d.name = T::GetTypeName();
		d.new_fn = &CreateComp<T>;
	}
	
	static void Dump();
	
	
};

#define REG_EXT(type, subcomp, sink_d,sink_v, side_d,side_v, src_d,src_v) {\
	Ecs::TypeExtCls c; \
	c.sink.dev = Ecs::DevCls::sink_d; \
	c.sink.val = Ecs::ValCls::sink_v; \
	c.side.dev = Ecs::DevCls::side_d; \
	c.side.val = Ecs::ValCls::side_v; \
	c.src.dev = Ecs::DevCls::src_d; \
	c.src.val = Ecs::ValCls::src_v; \
	c.sub = Ecs::SubTypeCls::subcomp; \
	Ecs::Factory::RegisterExtension<type>(c, ValDevCls()); \
}

#define REG_EXT_(type, subcomp, sink_d,sink_v, side_d,side_v, src_d,src_v, sc_d,sc_v, is_multi_conn) {\
	Ecs::TypeExtCls c; \
	c.sink.dev = Ecs::DevCls::sink_d; \
	c.sink.val = Ecs::ValCls::sink_v; \
	c.side.dev = Ecs::DevCls::side_d; \
	c.side.val = Ecs::ValCls::side_v; \
	c.src.dev = Ecs::DevCls::src_d; \
	c.src.val = Ecs::ValCls::src_v; \
	c.sub = Ecs::SubTypeCls::subcomp; \
	c.multi_conn = is_multi_conn; \
	ValDevCls side_vd(Ecs::DevCls::sc_d, Ecs::ValCls::sc_v); \
	Ecs::Factory::RegisterExtension<type>(c, side_vd); \
}


NAMESPACE_ECS_END

#endif
