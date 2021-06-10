#ifndef _EcsCore_Factory_h_
#define _EcsCore_Factory_h_

NAMESPACE_TOPSIDE_BEGIN


class EcsFactory {
	
public:
	typedef ComponentBase* (*NewFn)();
	struct CompData : Moveable<CompData> {
		NewFn new_fn;
		String name;
	};
	static VectorMap<TypeCls,CompData>& NewCompFns() {static VectorMap<TypeCls,CompData> m; return m;}
	
	template <class T> static ComponentBase* New() {return new T();}
	
	template <class T> static void RegisterComponent() {
		CompData& d = NewCompFns().GetAdd(AsTypeCls<T>());
		d.name = T::GetTypeName();
		d.new_fn = &New<T>;
	}
	
	static void Dump();
	static int  FindSinkComponents(TypeCls src_comp, Vector<TypeCls>& sink_comps);
	static void GetComponentActions(TypeCls sink_comp, const Eon::WorldState& src, Vector<Eon::Action>& acts);
	
};


NAMESPACE_TOPSIDE_END

#endif
