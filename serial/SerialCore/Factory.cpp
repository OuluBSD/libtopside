#include "SerialCore.h"

NAMESPACE_SERIAL_BEGIN


class Factory {
	
public:
	
	// Interfaces
	struct Link : Moveable<Link> {
		TypeAtomCls dst_atom;
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
	
	
	// Atoms
	
	typedef AtomBase* (*NewFn)();
	struct AtomData : Moveable<AtomData> {
		NewFn new_fn;
		AtomActionFn action_fn;
		String name;
		TypeAtomCls cls;
		TypeCls rtti_cls;
		
		Vector<Link> sink_links;
		bool searched_sink_links = false;
	};
	typedef VectorMap<TypeAtomCls,AtomData> AtomMap;
	static AtomMap& AtomDataMap() {MAKE_STATIC(AtomMap, m); return m;}
	
	template <class T> static AtomBase* CreateAtom() {return new T();}
	template <class T> static bool MakeAtomAction(const TypeAtomCls& t, Eon::Action& act) {return T::MakeAction(t, act);}
	
	template <class T> static void RegisterAtom(SubAtomCls sub, ValDevCls sink, ValDevCls side, ValDevCls src) {
		AtomCls atom;
		atom.sink = sink;
		atom.side = side;
		atom.src  = src;
		TypeAtomCls cls = AsTypeAtomCls<T>(sub, atom);
		ASSERT(cls.IsValid());
		AtomData& d = AtomDataMap().GetAdd(cls);
		d.rtti_cls = AsTypeCls<T>();
		d.cls = cls;
		d.name = T::GetTypeName();
		d.new_fn = &CreateAtom<T>;
		d.action_fn = &MakeAtomAction<T>;
	}
	
	
	static void Dump();
	static const Vector<Link>& GetSinkAtoms(TypeAtomCls src_atom);
	static void GetAtomActions(const Eon::WorldState& src, Vector<Eon::Action>& acts);
	static void RefreshLinks(AtomData& d);
	
	
	
};

NAMESPACE_SERIAL_END
