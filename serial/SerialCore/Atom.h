#ifndef _SerialCore_Atom_h_
#define _SerialCore_Atom_h_

NAMESPACE_SERIAL_BEGIN


class AtomBase;
namespace Eon {class WorldState;}


template <class T> inline RefT_Loop<T> AtomBase_Static_As(AtomBase*) {return RefT_Loop<T>();}

class AtomBase :
	public Destroyable,
	public Enableable,
	virtual public PacketForwarder,
	public RefScopeEnabler<AtomBase,Loop>
{
protected:
	friend class Loop;
	
public:
	virtual TypeCompCls GetType() const = 0;
	virtual void SetType(const TypeCompCls& cls) = 0;
	virtual void CopyTo(AtomBase* component) const = 0;
	virtual void Visit(RuntimeVisitor& vis) = 0;
	virtual void VisitSource(RuntimeVisitor& vis) = 0;
	virtual void VisitSink(RuntimeVisitor& vis) = 0;
	virtual void ClearSinkSource() = 0;
	virtual InterfaceSourceRef GetSource() = 0;
	virtual InterfaceSinkRef GetSink() = 0;
	virtual void Initialize() {};
	virtual void Uninitialize() {};
	virtual String ToString() const;
	virtual bool SetExtension(AtomExtBase* ext) {return false;}
	virtual void ClearExtension() {}
	virtual AtomExtBaseRef GetExtension() {return AtomExtBaseRef();}
	virtual int GetSideIn() {return -1;}
	virtual int GetSideOut() {return -1;}
	virtual void SetSideIn(int i) {Panic("Unimplemented");}
	virtual void SetSideOut(int i) {Panic("Unimplemented");}
	virtual bool LinkSideIn(AtomBaseRef in) {Panic("Unimplemented"); return false;}
	virtual bool LinkSideOut(AtomBaseRef out) {Panic("Unimplemented"); return false;}
	virtual void Forward(FwdScope& fwd) = 0;
	virtual void LoadPacket(const Packet& p) {}
	virtual void StorePacket(Packet& p) {Panic("StorePacket not implemented");}
	virtual bool IsReady(ValDevCls vd) {return true;}
	
	static SideStatus MakeSide(const TypeExtCls& from_type, const Eon::WorldState& from, const TypeExtCls& to_type, const Eon::WorldState& to) {Panic("The class have not implemented MakeSide"); return SIDE_NOT_ACCEPTED;}
	
	ValCls GetValSpec() const {return GetType().side.vd.val;}
	bool IsValSpec(ValCls t) const {return t == GetType().side.vd.val;}
	
	AtomExtBaseRef SetExtensionTypeCls(TypeExtCls ext);
	
	static bool AllowDuplicates() {return false;}
	
	Machine& GetMachine();
	void UninitializeWithExt();
	
	
public:
	RTTI_DECL_R3(AtomBase, Destroyable, Enableable, PacketForwarder)
	AtomBase();
	virtual ~AtomBase();
	
	LoopRef GetLoop();
	
	//InterfaceSourceRef FindSource(ValDevCls t);
	//InterfaceSinkRef FindSink(ValDevCls t);
	
	template <class T> RefT_Loop<T> As() {return AtomBase_Static_As<T>(this);}
	
	/*#define IFACE(x) \
	RefT_Loop<x##Source> As##x##Source() {return As<x##Source>();} \
	RefT_Loop<x##Sink>   As##x##Sink()   {return As<x##Sink>();}
	IFACE_LIST
	#undef IFACE*/
	RefT_Loop<ValSource>	AsSource();
	RefT_Loop<ValSink>	AsSink();
	
	
	template <class S, class R>
	void AddToSystem(R ref) {
		Ref<S> sys = GetMachine().Get<S>();
		if (sys)
			sys->Add(ref);
	}
	
	template <class S, class R>
	void RemoveFromSystem(R ref) {
		Ref<S> sys = GetMachine().Get<S>();
		if (sys)
			sys->Remove(ref);
	}
	
	
	template <class ValDevSpec, class T> bool LinkManually(T& o, String* err_msg=0);
	
};




template<typename T>
struct Atom :
	public AtomBase
{
public:
	RTTI_DECL1(Atom<T>, AtomBase)
	using AtomT = Atom<T>;

	void CopyTo(AtomBase* target) const override {
		ASSERT(target->GetType() == GetType());
	    
		*static_cast<T*>(target) = *static_cast<const T*>(this);
	}
	
};


#define ATOM_RTTI(x)  RTTI_DECL1(x, Atom<x>)

using AtomMapBase	= RefEcsTypeMapIndirect<AtomBase>;
using AtomRefMap	= ArrayMap<TypeCompCls,Ref<AtomBase>>;

class AtomMap : public AtomMapBase {
	
	void ReturnAtom(AtomStore& s, AtomBase* c);
	
public:
	
	AtomMap() {}
	
	#define IS_EMPTY_SHAREDPTR(x) (x.IsEmpty())
	
	void Dump();
	
	template<typename AtomT>
	RefT_Loop<AtomT> Get() {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator it = AtomMapBase::Find(AsEcsTypeCls<AtomT>());
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		if (it.IsEmpty())
			THROW(Exc("Could not find component " + AsTypeString<AtomT>()));
		
		return it->AsRef<AtomT>();
	}
	
	template<typename AtomT>
	RefT_Loop<AtomT> Find() {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator it = AtomMapBase::Find(AsEcsTypeCls<AtomT>());
		if (IS_EMPTY_SHAREDPTR(it))
			return Null;
		else
			return it->AsRef<AtomT>();
	}
	
	template<typename AtomT>
	void Add(AtomT* component) {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		TypeCompCls type = component->GetType();
		ASSERT(type.IsValid());
		AtomMapBase::Iterator it = AtomMapBase::Find(type);
		ASSERT_(IS_EMPTY_SHAREDPTR(it) || AtomT::AllowDuplicates(), "Cannot have duplicate componnets");
		AtomMapBase::Add(type, component);
	}
	
	template<typename AtomT>
	void Remove(AtomStoreRef s) {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator iter = AtomMapBase::Find(AsEcsTypeCls<AtomT>());
		ASSERT_(iter, "Tried to remove non-existent component");
		
		iter.value().UninitializeWithExt();
		iter.value().Destroy();
		
		ReturnAtom(*s, iter.value.GetItem()->value.Detach());
		AtomMapBase::Remove(iter);
	}
	
	void AddBase(AtomBase* component) {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		TypeCompCls type = component->GetType();
		AtomMapBase::Iterator it = AtomMapBase::Find(type);
		AtomMapBase::Add(type, component);
	}
	
	#undef IS_EMPTY_SHAREDPTR
	
};

NAMESPACE_SERIAL_END

#endif
