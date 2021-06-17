#ifndef _EcsCore_Factory_h_
#define _EcsCore_Factory_h_

NAMESPACE_TOPSIDE_BEGIN


class EcsFactory {
	
public:
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
	
	
	
	typedef ComponentBase* (*NewFn)();
	typedef bool (*ActionFn)(Eon::Action& act);
	struct CompData : Moveable<CompData> {
		NewFn new_fn;
		ActionFn action_fn;
		String name;
		TypeCls cls;
		TypeCls sink, src, src_sink;
		
		Vector<Link> sink_links;
		bool searched_sink_links = false;
	};
	static VectorMap<TypeCls,CompData>& CompDataMap() {static VectorMap<TypeCls,CompData> m; return m;}
	
	template <class T> static ComponentBase* New() {return new T();}
	template <class T> static bool MakeAction(Eon::Action& act) {return T::MakeAction(act);}
	
	template <class T> static void RegisterComponent() {
		CompData& d = CompDataMap().GetAdd(AsTypeCls<T>());
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
		d.new_fn = &New<T>;
		d.action_fn = &MakeAction<T>;
		{
			T o;
			d.sink = ((InterfaceSinkBase*)&o)->GetSinkCls();
			d.src = ((InterfaceSourceBase*)&o)->GetSourceCls();
			d.src_sink = ((InterfaceSourceBase*)&o)->GetSinkCls();
		}
	}
	
	
	static void Dump();
	static const Vector<Link>& GetSinkComponents(TypeCls src_comp);
	static void GetComponentActions(const Eon::WorldState& src, const Vector<Link>& sink_links, Vector<Eon::Action>& acts);
	
};


NAMESPACE_TOPSIDE_END

#endif
