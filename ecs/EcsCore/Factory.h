#ifndef _EcsCore_Factory_h_
#define _EcsCore_Factory_h_

NAMESPACE_ECS_BEGIN


class Factory {
	
public:
	
	// Interfaces
	struct Link : Moveable<Link> {
		TypeCls dst_comp, iface_src, iface_sink;
	};
	
	struct IfaceData : Moveable<IfaceData> {
		TypeCls cls;
		TypeCls expt_type;
		ValDevCls sink_cls;
		String name;
	};
	typedef VectorMap<ValDevCls,IfaceData> IfaceMap;
	static IfaceMap& SourceDataMap() {MAKE_STATIC(IfaceMap, m); return m;}
	static IfaceMap& SinkDataMap()   {MAKE_STATIC(IfaceMap, m); return m;}
	
	template <class T> static void RegisterInterfaceSource() {
		IfaceData& d = SourceDataMap().GetAdd(AsTypeCls<T>());
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
		d.expt_type = AsTypeCls<typename T::ExPt>();
		d.sink_cls = AsTypeCls<typename T::Sink>();
		MetaExchangePoint::RegisterExchangePoint<typename T::ExPt>();
	}
	
	template <class T> static void RegisterInterfaceSink() {
		IfaceData& d = SinkDataMap().GetAdd(AsTypeCls<T>());
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
		d.expt_type = 0;
		d.sink_cls = Null;
	}
	
	
	
	
	// Component Extensions
	
	typedef bool (*ActionFn)(ValDevCls vd, Eon::Action& act);
	typedef ComponentExtBase* (*NewExt)();
	struct ExtData : Moveable<ExtData> {
		NewExt new_fn;
		ActionFn action_fn;
		String name;
		TypeCls cls;
		
		Vector<Link> sink_links;
		bool searched_sink_links = false;
	};
	template <class T> static ComponentExtBase* CreateExt() {return new T();}
	
	
	
	// Components
	
	typedef ComponentBase* (*NewFn)();
	struct CompData : Moveable<CompData> {
		VectorMap<TypeCls,ExtData> ext;
		NewFn new_fn;
		ActionFn action_fn;
		String name;
		ValDevCls vd;
		TypeCls cls;
		ValDevCls sink, src, src_sink;
		
		Vector<Link> sink_links;
		bool searched_sink_links = false;
	};
	typedef VectorMap<EcsTypeCls,CompData> CompMap;
	static CompMap& CompDataMap() {MAKE_STATIC(CompMap, m); return m;}
	
	template <class T> static ComponentBase* CreateComp() {return new T();}
	template <class T> static bool MakeAction(ValDevCls vd, Eon::Action& act) {return T::MakeAction(vd, act);}
	
	template <class T> static void RegisterComponent(DevCls dev, ValCls val) {
		CompData& d = CompDataMap().GetAdd(AsEcsTypeCls<T>(dev, val));
		d.vd.dev = dev;
		d.vd.val = val;
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
		d.new_fn = &CreateComp<T>;
		d.action_fn = &MakeAction<T>;
		{
			T o;
			d.sink = ((InterfaceSink*)&o)->GetSinkCls();
			d.src = ((InterfaceSource*)&o)->GetSourceCls();
			d.src_sink = ((InterfaceSource*)&o)->GetSinkCls();
		}
	}
	
	template <class T> static void RegisterExtension() {
		TODO
		/*using Component = typename T::Component;
		CompData& d = CompDataMap().GetAdd(AsTypeCls<Component>());
		TypeCls t = AsTypeCls<T>();
		ExtData& e = d.ext.GetAdd(t);
		e.cls = t;
		e.name = T::GetTypeName();
		e.new_fn = &CreateExt<T>;
		e.action_fn = &MakeAction<T>;*/
	}
	
	static void Dump();
	static const Vector<Link>& GetSinkComponents(EcsTypeCls src_comp);
	static void GetComponentActions(const Eon::WorldState& src, Vector<Eon::Action>& acts);
	static void RefreshLinks(CompData& d);
	
	
	
};



template <class Main, class Base> inline
ComponentBase* ComponentStoreT<Main,Base>::CreateComponentTypeCls(EcsTypeCls key) {
	auto it = Factory::producers.Find(key);
	if (!it) {
		auto new_fn = Ecs::Factory::CompDataMap().Get(key).new_fn;
		std::function<Base*()> p([new_fn] { return new_fn();});
		std::function<void(Base*)> r([] (Base* b){ delete b;});
		Factory::producers.Add(key) = p;
		Factory::refurbishers.Add(key) = r;
	}
	
	return CreateComponent(key);
}

NAMESPACE_ECS_END

#endif
