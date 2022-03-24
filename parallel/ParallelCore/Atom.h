#ifndef _SerialCore_Atom_h_
#define _SerialCore_Atom_h_

NAMESPACE_TOPSIDE_BEGIN
namespace Serial {

namespace Script {
class WorldState;
class Plan;
}

}
NAMESPACE_TOPSIDE_END


NAMESPACE_PARALLEL_BEGIN
using namespace Serial;

class AtomBase;

template <class T> inline SideStatus MakeSide(const AtomTypeCls& src_type, const Script::WorldState& from, const AtomTypeCls& sink_type, const Script::WorldState& to) {Panic("Unimplemented"); NEVER();}
template <class T> inline RefT_Space<T> AtomBase_Static_As(AtomBase*) {return RefT_Space<T>();}

class AtomBase :
	public Destroyable,
	public Enableable,
	public PacketForwarderData,
	public RefScopeEnabler<AtomBase, MetaSpaceBase>
{
	
	
public:
	using AtomBaseRef = Ref<AtomBase, AtomParent>;
	
	
protected:
	friend class Serial::ScriptLoopLoader;
	friend class Serial::Loop;
	
	int						id = -1;
	
	void					SetId(int i) {id = i;}
	
protected:
	friend class Serial::LinkBase;
	
	Mutex					fwd_lock;
	IfaceConnTuple			iface;
	
	
public:
	
	struct CustomerData {
		RealtimeSourceConfig	cfg;
		off32_gen				gen;
		
		CustomerData();
		~CustomerData();
	};
	
	
public:
	virtual AtomTypeCls		GetType() const = 0;
	virtual void			CopyTo(AtomBase* atom) const = 0;
	virtual void			Visit(RuntimeVisitor& vis) = 0;
	virtual void			Uninitialize() = 0;
	virtual void			UninitializeAtom() = 0;
	virtual bool			InitializeAtom(const Script::WorldState& ws) = 0;
	virtual void			VisitSource(RuntimeVisitor& vis) = 0;
	virtual void			VisitSink(RuntimeVisitor& vis) = 0;
	
	virtual void			Update(double dt) {}
	virtual String			ToString() const;
	virtual bool			IsReady(PacketIO& io) {return true;}
	virtual void			UpdateConfig(double dt) {Panic("Unimplemented"); NEVER();}
	
	void					AddAtomToUpdateList();
	void					RemoveAtomFromUpdateList();
	
	static SideStatus MakeSide(const AtomTypeCls& src_type, const Script::WorldState& from, const AtomTypeCls& sink_type, const Script::WorldState& to) {
		ValDevCls common_vd = src_type.iface.src.GetCommon(sink_type.iface.sink);
		if (common_vd.IsValid())
			return SIDE_ACCEPTED;
		else
			return SIDE_NOT_ACCEPTED;
	}

	
	Machine&				GetMachine();
	void					UninitializeDeep();
	void					SetInterface(const IfaceConnTuple& iface);
	const IfaceConnTuple&	GetInterface() const;
	
public:
	RTTI_DECL_R3(AtomBase, Destroyable, Enableable, PacketForwarderData)
	AtomBase();
	virtual ~AtomBase();
	
	
	SpaceRef	GetSpace();
	Space&		GetParent();
	int			GetId() const {return id;}
	
	template <class T> RefT_Space<T> As() {return AtomBase_Static_As<T>(this);}
	
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




template<
	typename T,
	class SinkT=DefaultInterfaceSink,
	class SourceT=DefaultInterfaceSource
>
struct Atom :
	virtual public AtomBase,
	public SinkT,
	public SourceT
{
public:
	using AtomT = Atom<T, SinkT, SourceT>;
	RTTI_DECL3(AtomT, AtomBase, SinkT, SourceT)
	
	bool InitializeAtom(const Script::WorldState& ws) override {
		return SinkT::Initialize() && SourceT::Initialize();
	}
	
	void UninitializeAtom() override {
		SinkT::Uninitialize();
		SourceT::Uninitialize();
	}
	
	void ClearSinkSource() override {
		SinkT::ClearSink();
		SourceT::ClearSource();
	}
	
	void Visit(RuntimeVisitor& vis) override {
		vis.VisitThis<SinkT>(this);
		vis.VisitThis<SourceT>(this);
	}
	
	void VisitSource(RuntimeVisitor& vis) override {
		vis.VisitThis<SourceT>(this);
	}
	
	void VisitSink(RuntimeVisitor& vis) override {
		vis.VisitThis<SinkT>(this);
	}

	void CopyTo(AtomBase* target) const override {
		ASSERT(target->GetType() == ((AtomBase*)this)->GetType());
	    
	    TODO
		//*static_cast<T*>(target) = *static_cast<const T*>(this);
	}
	
	
	InterfaceSourceRef GetSource() override {
		InterfaceSource* src = static_cast<InterfaceSource*>(this);
		ASSERT(src);
		return InterfaceSourceRef(GetParentUnsafe(), src);
	}
	
	InterfaceSinkRef GetSink() override {
		InterfaceSink* sink = static_cast<InterfaceSink*>(this);
		ASSERT(sink);
		return InterfaceSinkRef(GetParentUnsafe(), sink);
	}
	
	AtomBase* AsAtomBase() override {return static_cast<AtomBase*>(this);}
	void ClearSink() override {TODO}
	void ClearSource() override {TODO}
	
	
	static ParallelTypeCls::Type GetSerialType() {return ParallelTypeCls::CUSTOM_ATOM;}
	
	
};


#define ATOM_RTTI(x)  RTTI_DECL1(x, Atom<x>)

using AtomMapBase	= RefAtomTypeMapIndirect<AtomBase>;
using AtomRefMap	= ArrayMap<AtomTypeCls,Ref<AtomBase>>;

class AtomMap : public AtomMapBase {
	
	void ReturnAtom(AtomStore& s, AtomBase* c);
	
public:
	
	AtomMap() {}
	
	#define IS_EMPTY_SHAREDPTR(x) (x.IsEmpty())
	
	void Dump();
	
	template<typename AtomT>
	RefT_Space<AtomT> Get() {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator it = AtomMapBase::Find(AsParallelTypeCls<AtomT>());
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		if (it.IsEmpty())
			THROW(Exc("Could not find atom " + AsTypeString<AtomT>()));
		
		return it->AsRef<AtomT>();
	}
	
	template<typename AtomT>
	RefT_Space<AtomT> Find() {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator it = AtomMapBase::Find(AsParallelTypeCls<AtomT>());
		if (IS_EMPTY_SHAREDPTR(it))
			return Null;
		else
			return it->AsRef<AtomT>();
	}
	
	template<typename AtomT>
	void Add(AtomT* atom) {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomTypeCls type = atom->GetType();
		ASSERT(type.IsValid());
		AtomMapBase::Add(type, atom);
	}
	
	template<typename AtomT>
	void Remove(AtomStoreRef s) {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator iter = AtomMapBase::Find(AsParallelTypeCls<AtomT>());
		ASSERT_(iter, "Tried to remove non-existent atom");
		
		TODO //iter.value().Uninitialize();
		
		//iter.value().Destroy();
		
		ReturnAtom(*s, iter.value.GetItem()->value.Detach());
		AtomMapBase::Remove(iter);
	}
	
	void AddBase(AtomBase* atom) {
		AtomTypeCls type = atom->GetType();
		ASSERT(type.IsValid());
		//AtomMapBase::Iterator it = AtomMapBase::Find(type);
		AtomMapBase::Add(type, atom);
	}
	
	#undef IS_EMPTY_SHAREDPTR
	
};

NAMESPACE_PARALLEL_END

#endif
