#ifndef _EcsCore_Factory_h_
#define _EcsCore_Factory_h_

NAMESPACE_ECS_BEGIN


class Factory {
	
public:
	
	// Interfaces
	struct Link : Moveable<Link> {
		TypeCompCls dst_comp;
		ValDevCls iface;
	};
	
	struct IfaceData : Moveable<IfaceData> {
		TypeCls cls;
		TypeCls expt_type;
		ValDevCls vd;
		String name;
	};
	typedef VectorMap<ValDevCls,IfaceData> IfaceMap;
	static IfaceMap& SourceDataMap() {MAKE_STATIC(IfaceMap, m); return m;}
	static IfaceMap& SinkDataMap()   {MAKE_STATIC(IfaceMap, m); return m;}
	
	template <class T> static void RegisterInterfaceSource(DevCls dev, ValCls val) {
		ValDevCls vd(dev,val);
		IfaceData& d = SourceDataMap().GetAdd(vd);
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
		d.expt_type = AsTypeCls<typename T::ExPt>();
		d.vd.dev = dev;
		d.vd.val = val;
		MetaExchangePoint::RegisterExchangePoint<typename T::ExPt>();
	}
	
	template <class T> static void RegisterInterfaceSink(DevCls dev, ValCls val) {
		ValDevCls vd(dev,val);
		IfaceData& d = SinkDataMap().GetAdd(vd);
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
		d.expt_type = 0;
		d.vd.dev = dev;
		d.vd.val = val;
	}
	
	
	
	
	// Component Extensions
	
	typedef bool (*ActionFn)(const TypeCompCls& t, Eon::Action& act);
	typedef ComponentExtBase* (*NewExt)();
	struct ExtData : Moveable<ExtData> {
		NewExt new_fn;
		ActionFn action_fn;
		String name;
		TypeExtCls cls;
		
		Vector<Link> sink_links;
		bool searched_sink_links = false;
	};
	template <class T> static ComponentExtBase* CreateExt() {return new T();}
	
	
	
	// Components
	
	typedef ComponentBase* (*NewFn)();
	struct CompData : Moveable<CompData> {
		VectorMap<TypeExtCls,ExtData> ext;
		NewFn new_fn;
		ActionFn action_fn;
		String name;
		TypeCompCls cls;
		TypeCls rtti_cls;
		
		Vector<Link> sink_links;
		bool searched_sink_links = false;
	};
	typedef VectorMap<TypeCompCls,CompData> CompMap;
	static CompMap& CompDataMap() {MAKE_STATIC(CompMap, m); return m;}
	
	template <class T> static ComponentBase* CreateComp() {return new T();}
	template <class T> static bool MakeAction(const TypeCompCls& t, Eon::Action& act) {return T::MakeAction(t, act);}
	
	template <class T> static void RegisterComponent(SubCompCls sub, ValDevCls sink, ValDevCls side, ValDevCls src) {
		CompCls comp;
		comp.sink = sink;
		comp.side = side;
		comp.src  = src;
		TypeCompCls cls = AsTypeCompCls<T>(sub, comp);
		ASSERT(cls.IsValid());
		CompData& d = CompDataMap().GetAdd(cls);
		d.rtti_cls = AsTypeCls<T>();
		d.cls = cls;
		d.name = T::GetTypeName();
		d.new_fn = &CreateComp<T>;
		d.action_fn = &MakeAction<T>;
	}
	
	static LinkedList<TypeExtCls>& GetExtTypes() {static LinkedList<TypeExtCls> l; return l;}
	
	template <class T> static void RegisterExtension(TypeExtCls c) {
		c.ext = GetExtTypes().GetCount();
		ASSERT(c.IsValid());
		GetExtTypes().Add(c);
		TypeCompCls comp = AsTypeCompCls(c);
		CompData& d = CompDataMap().GetAdd(comp);
		ExtData& e = d.ext.GetAdd(c);
		e.cls = c;
		e.name = T::GetTypeName();
		e.new_fn = &CreateExt<T>;
		e.action_fn = &MakeAction<T>;
	}
	
	static void Dump();
	static const Vector<Link>& GetSinkComponents(TypeCompCls src_comp);
	static void GetComponentActions(const Eon::WorldState& src, Vector<Eon::Action>& acts);
	static void RefreshLinks(CompData& d);
	
	
	
};

#define REG_EXT(type, subcomp, sink_d,sink_v, side_d,side_v, src_d,src_v) {\
	Ecs::TypeExtCls c; \
	c.sink.dev = Ecs::DevCls::sink_d; \
	c.sink.val = Ecs::ValCls::sink_v; \
	c.side.dev = Ecs::DevCls::side_d; \
	c.side.val = Ecs::ValCls::side_v; \
	c.src.dev = Ecs::DevCls::src_d; \
	c.src.val = Ecs::ValCls::src_v; \
	c.sub = Ecs::SubCompCls::subcomp; \
	Ecs::Factory::RegisterExtension<type>(c); \
}


NAMESPACE_ECS_END

#endif
