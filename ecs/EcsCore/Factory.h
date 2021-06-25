#ifndef _EcsCore_Factory_h_
#define _EcsCore_Factory_h_

NAMESPACE_ECS_BEGIN


class Factory {
	
public:
	
	// Interfaces
	struct Link : Moveable<Link> {
		EcsTypeCls dst_comp;
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
	
	typedef bool (*ActionFn)(ValDevCls vd, Eon::Action& act);
	typedef ComponentExtBase* (*NewExt)();
	struct ExtData : Moveable<ExtData> {
		NewExt new_fn;
		ActionFn action_fn;
		String name;
		EcsTypeCls cls;
		
		Vector<Link> sink_links;
		bool searched_sink_links = false;
	};
	template <class T> static ComponentExtBase* CreateExt() {return new T();}
	
	
	
	// Components
	
	typedef ComponentBase* (*NewFn)();
	struct CompData : Moveable<CompData> {
		VectorMap<EcsTypeCls,ExtData> ext;
		NewFn new_fn;
		ActionFn action_fn;
		String name;
		EcsTypeCls cls;
		ValDevCls sink, side, src;
		TypeCls rtti_cls;
		
		Vector<Link> sink_links;
		bool searched_sink_links = false;
	};
	typedef VectorMap<EcsTypeCls,CompData> CompMap;
	static CompMap& CompDataMap() {MAKE_STATIC(CompMap, m); return m;}
	
	template <class T> static ComponentBase* CreateComp() {return new T();}
	template <class T> static bool MakeAction(ValDevCls vd, Eon::Action& act) {return T::MakeAction(vd, act);}
	
	template <class T> static void RegisterComponent(DevCls dev, ValCls sink, ValCls side, ValCls src) {
		EcsTypeCls cls = AsEcsTypeCls<T>(dev, side);
		CompData& d = CompDataMap().GetAdd(cls);
		d.rtti_cls = AsTypeCls<T>();
		d.cls = cls;
		d.name = T::GetTypeName();
		d.new_fn = &CreateComp<T>;
		d.action_fn = &MakeAction<T>;
		{
			T o;
			d.sink = ValDevCls(dev, sink);
			d.side = ValDevCls(dev, side);
			d.src = ValDevCls(dev, src);
			ASSERT(d.sink.IsValid());
			ASSERT(d.side.IsValid());
			ASSERT(d.src.IsValid());
		}
	}
	
	template <class T> static void RegisterExtension(DevCls dev, ValCls val) {
		using Component = typename T::Component;
		EcsTypeCls ct = AsEcsTypeCls<Component>(dev, val);
		CompData& d = CompDataMap().GetAdd(ct);
		EcsTypeCls t = AsEcsTypeCls<T>(dev, val);
		ExtData& e = d.ext.GetAdd(t);
		e.cls = t;
		e.name = T::GetTypeName();
		e.new_fn = &CreateExt<T>;
		e.action_fn = &MakeAction<T>;
	}
	
	static void Dump();
	static const Vector<Link>& GetSinkComponents(EcsTypeCls src_comp);
	static void GetComponentActions(const Eon::WorldState& src, Vector<Eon::Action>& acts);
	static void RefreshLinks(CompData& d);
	
	
	
};



template <class Main, class Base> inline
ComponentBase* ComponentStoreT<Main,Base>::CreateComponentTypeCls(TypeCompCls cls) {
	auto it = Factory::producers.Find(cls.side);
	if (!it) {
		auto new_fn = Ecs::Factory::CompDataMap().Get(cls.side).new_fn;
		std::function<Base*()> p([new_fn] { return new_fn();});
		std::function<void(Base*)> r([] (Base* b){ delete b;});
		Factory::producers.Add(cls.side) = p;
		Factory::refurbishers.Add(cls.side) = r;
	}
	
	return CreateComponent(cls);
}

NAMESPACE_ECS_END

#endif
