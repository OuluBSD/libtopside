#ifndef _EcsCore_Factory_h_
#define _EcsCore_Factory_h_

NAMESPACE_TOPSIDE_BEGIN


class EcsFactory {
	
public:
	
	// Interfaces
	struct Link : Moveable<Link> {
		TypeCls dst_comp, iface_src, iface_sink;
	};
	
	struct IfaceData : Moveable<IfaceData> {
		TypeCls cls;
		TypeCls expt_type;
		TypeCls sink_cls;
		String name;
	};
	static VectorMap<TypeCls,IfaceData>& SourceDataMap() {static VectorMap<TypeCls,IfaceData> m; return m;}
	static VectorMap<TypeCls,IfaceData>& SinkDataMap()   {static VectorMap<TypeCls,IfaceData> m; return m;}
	
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
		d.sink_cls = 0;
	}
	
	
	
	
	// Component Extensions
	
	typedef bool (*ActionFn)(Eon::Action& act);
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
		TypeCls cls;
		TypeCls sink, src, src_sink;
		
		Vector<Link> sink_links;
		bool searched_sink_links = false;
	};
	static VectorMap<TypeCls,CompData>& CompDataMap() {static VectorMap<TypeCls,CompData> m; return m;}
	
	template <class T> static ComponentBase* CreateComp() {return new T();}
	template <class T> static bool MakeAction(Eon::Action& act) {return T::MakeAction(act);}
	
	template <class T> static void RegisterComponent() {
		CompData& d = CompDataMap().GetAdd(AsTypeCls<T>());
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
		d.new_fn = &CreateComp<T>;
		d.action_fn = &MakeAction<T>;
		{
			T o;
			d.sink = ((InterfaceSinkBase*)&o)->GetSinkCls();
			d.src = ((InterfaceSourceBase*)&o)->GetSourceCls();
			d.src_sink = ((InterfaceSourceBase*)&o)->GetSinkCls();
		}
	}
	
	template <class T> static void RegisterExtension() {
		using Component = typename T::Component;
		CompData& d = CompDataMap().GetAdd(AsTypeCls<Component>());
		TypeCls t = AsTypeCls<T>();
		ExtData& e = d.ext.GetAdd(t);
		e.cls = t;
		e.name = T::GetTypeName();
		e.new_fn = &CreateExt<T>;
		e.action_fn = &MakeAction<T>;
	}
	
	static void Dump();
	static const Vector<Link>& GetSinkComponents(TypeCls src_comp);
	static void GetComponentActions(const Eon::WorldState& src, Vector<Eon::Action>& acts);
	static void RefreshLinks(CompData& d);
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
