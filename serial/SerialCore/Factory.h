#ifndef _SerialCore_Factory_h_
#define _SerialCore_Factory_h_



NAMESPACE_SERIAL_BEGIN

namespace Script {
class Action;
}

class Factory {
	
public:
	
	// Interfaces
	struct Link : Moveable<Link> {
		AtomTypeCls		dst_atom;
		ValDevTuple		iface;
		ValDevCls		common_vd;
	};
	
	struct IfaceData : Moveable<IfaceData> {
		TypeCls			cls;
		ValDevCls		vd;
		String			name;
	};
	typedef VectorMap<ValDevTuple,IfaceData> IfaceMap;
	static IfaceMap& IfaceLinkDataMap() {MAKE_STATIC(IfaceMap, m); return m;}
	
	template <class T> static void RegisterInterfaceLink(DevCls dev, ValCls val) {
		ValDevCls vd(dev,val);
		IfaceData& d = IfaceLinkDataMap().GetAdd(vd);
		d.cls = AsTypeCls<T>();
		d.name = T::GetTypeName();
		d.vd.dev = dev;
		d.vd.val = val;
		MetaDirectoryBase::RegisterExchangePoint<T>();
	}
	
	
	
	
	
	// Atoms
	
	typedef AtomBase* (*NewFn)();
	typedef bool (*AtomActionFn)(const AtomTypeCls& t, Script::Action& act);
	typedef SideStatus (*SideFn)(const AtomTypeCls& from_type, const Script::WorldState& from, const AtomTypeCls& to_type, const Script::WorldState& to);
	struct AtomData : Moveable<AtomData> {
		NewFn			new_fn;
		AtomActionFn	action_fn;
		String			name;
		AtomTypeCls		cls;
		TypeCls			rtti_cls;
		SideFn			side_fn;
		
		Vector<Link>	sink_links;
		bool			searched_sink_links = false;
	};
	typedef VectorMap<AtomTypeCls,AtomData> AtomMap;
	static AtomMap& AtomDataMap() {MAKE_STATIC(AtomMap, m); return m;}
	
	template <class T> static AtomBase* CreateAtom() {return new T();}
	template <class T> static bool MakeAtomAction(const AtomTypeCls& t, Script::Action& act) {return T::MakeAction(t, act);}
	template <class T> static SideStatus MakeSide(const AtomTypeCls& from_type, const Script::WorldState& from, const AtomTypeCls& to_type, const Script::WorldState& to) {return T::MakeSide(from_type, from, to_type, to);}
	
	template <class T> static void RegisterAtom() {
		AtomTypeCls cls = T::GetAtomType();
		ASSERT(cls.IsValid());
		AtomData& d = AtomDataMap().GetAdd(cls);
		d.rtti_cls = AsTypeCls<T>();
		d.cls = cls;
		d.name = T::GetTypeName();
		d.new_fn = &CreateAtom<T>;
		d.action_fn = &MakeAtomAction<T>;
		d.side_fn = &MakeSide<T>;
	}
	
	static LinkedList<AtomTypeCls>& GetAtomTypes() {static LinkedList<AtomTypeCls> l; return l;}
	
	static void Dump();
	static const Vector<Link>& GetSinkAtoms(AtomTypeCls src_atom);
	static void RefreshLinks(AtomData& d);
	
	
	
};

NAMESPACE_SERIAL_END

#endif
