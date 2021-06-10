#ifndef _EcsCore_Factory_h_
#define _EcsCore_Factory_h_

NAMESPACE_TOPSIDE_BEGIN


class EcsFactory {
	
public:
	struct IfaceData : Moveable<IfaceData> {
		TypeCls cls;
		String name;
	};
	static VectorMap<TypeCls,IfaceData>& IfaceDataMap() {static VectorMap<TypeCls,IfaceData> m; return m;}
	
	template <class T> static void RegisterInterface() {
		IfaceData& d = IfaceDataMap().GetAdd(AsTypeCls<T>());
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
	}
	
	typedef ComponentBase* (*NewFn)();
	struct CompData : Moveable<CompData> {
		NewFn new_fn;
		String name;
		TypeCls cls;
		Vector<TypeCls> sinks, srcs, src_sinks;
		
		Vector<TypeCls> sink_comps;
		bool searched_sink_comps = false;
	};
	static VectorMap<TypeCls,CompData>& CompDataMap() {static VectorMap<TypeCls,CompData> m; return m;}
	
	template <class T> static ComponentBase* New() {return new T();}
	
	template <class T> static void RegisterComponent() {
		CompData& d = CompDataMap().GetAdd(AsTypeCls<T>());
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
		d.new_fn = &New<T>;
		{
			T o;
			CollectInterfacesVisitor vis;
			o.VisitSources(vis);
			o.VisitSinks(vis);
			for (InterfaceSinkBaseRef& r : vis.sink_ifaces) {
				d.sinks.Add(r->GetSinkCls());
			}
			for (InterfaceSourceBaseRef& r : vis.src_ifaces) {
				d.srcs.Add(r->GetSourceCls());
				d.src_sinks.Add(r->GetSinkCls());
			}
		}
	}
	
	static void Dump();
	static const Vector<TypeCls>& GetSinkComponents(TypeCls src_comp);
	static void GetComponentActions(const Eon::WorldState& src, TypeCls sink_comp, Vector<Eon::Action>& acts);
	
};


NAMESPACE_TOPSIDE_END

#endif
