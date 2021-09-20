#ifndef _SerialCore_Atom_h_
#define _SerialCore_Atom_h_

NAMESPACE_SERIAL_BEGIN


class AtomBase;
namespace Script {
class WorldState;
class Plan;
}



template <class T> inline SideStatus MakeSide(const AtomTypeCls& from_type, const Script::WorldState& from, const AtomTypeCls& to_type, const Script::WorldState& to) {Panic("Unimplemented"); NEVER();}
template <class T> inline RefT_Loop<T> AtomBase_Static_As(AtomBase*) {return RefT_Loop<T>();}

class AtomBase :
	public Destroyable,
	public Enableable,
	virtual public PacketForwarder,
	public RefScopeEnabler<AtomBase,Loop>
{
	
	
public:
	using AtomBaseRef = Ref<AtomBase, RefParent1<Loop>>;
	
	
	#ifdef flagDEBUG
	bool dbg_async_race = false;
	#endif
	
protected:
	struct CustomerData {
		RealtimeSourceConfig	cfg;
		off32_gen				gen;
		Array<Script::Plan>		plans;
		Index<dword>			unfulfilled_offsets;
		int						max_unfulfilled = 5;
		
		CustomerData();
		~CustomerData();
	};
	
	
	Mutex					lock;
	LinkedList<Packet>		consumed_packets;
	PacketConsumer			consumer;
	int						packets_forwarded = 0;
	int						side_sink = -1, side_src = -1;
	AtomBaseRef				side_sink_conn, side_src_conn, driver_conn;
	RealtimeSourceConfig*	last_cfg = 0;
	
	
	void					ForwardAtom(FwdScope& fwd) override;
	void					ForwardExchange(FwdScope& fwd) override;
	void					ForwardDriver(FwdScope& fwd);
	void					ForwardCustomer(FwdScope& fwd);
	void					ForwardSource(FwdScope& fwd);
	void					ForwardSink(FwdScope& fwd);
	void					ForwardConverter(FwdScope& fwd);
	void					ForwardSideSink(FwdScope& fwd);
	void					ForwardSideSource(FwdScope& fwd);
	void					ForwardConsumed(FwdScope& fwd);
	void					ForwardSourceBuffer(FwdScope& fwd, PacketBuffer& sink_buf);
	
	void					ForwardVoidSink(FwdScope& fwd);
	bool					ForwardMem(void* mem, size_t mem_size);
	
	void					BaseVisit(RuntimeVisitor& vis) {vis & side_sink_conn & side_src_conn & driver_conn;}
	
public:
	virtual AtomTypeCls GetType() const = 0;
	virtual void CopyTo(AtomBase* atom) const = 0;
	virtual void Visit(RuntimeVisitor& vis) = 0;
	virtual void VisitSource(RuntimeVisitor& vis) = 0;
	virtual void VisitSink(RuntimeVisitor& vis) = 0;
	virtual void ClearSinkSource() = 0;
	virtual InterfaceSourceRef GetSource() = 0;
	virtual InterfaceSinkRef GetSink() = 0;
	virtual InterfaceSideSourceRef GetSideSource() = 0;
	virtual InterfaceSideSinkRef GetSideSink() = 0;
	virtual bool InitializeAtom(const Script::WorldState& ws) = 0;
	virtual void UninitializeAtom() = 0;
	
	virtual bool AltInitialize(const Script::WorldState& ws) {return true;}
	virtual void AltUninitialize() {}
	virtual void AltUpdate(double dt) {}
	virtual void AltForward(FwdScope& fwd) {Panic("AltForward not implemented");}
	virtual void AltStorePacket(Packet& p) {Panic("AltStorePacket not implemented");}
	virtual bool AltIsReady(ValDevCls vd) {return true;}
	virtual bool AltPostInitialize() {return true;}
	
	virtual void IntervalSinkProcess() {Panic("IntervalSinkProcess not implemented");}
	virtual bool IsConsumedPartialPacket() {return 0;}
	
	virtual bool Initialize(const Script::WorldState& ws) {return true;}
	virtual void Uninitialize() {}
	virtual void Update(double dt) {AltUpdate(dt);}
	virtual void Forward(FwdScope& fwd) {AltForward(fwd);}
	virtual bool PostInitialize() {return AltPostInitialize();}
	virtual String ToString() const;
	virtual void LoadPacket(const Packet& p) {}
	virtual void StorePacket(Packet& p) {AltStorePacket(p);}
	virtual bool IsReady(ValDevCls vd) {return AltIsReady(vd);}
	virtual CustomerData* GetCustomerData() {return 0;}
	virtual RealtimeSourceConfig& GetConfig() {if (last_cfg) return *last_cfg; Panic("Unimplemented"); NEVER();}
	virtual void UpdateConfig(double dt) {Panic("Unimplemented"); NEVER();}
	virtual void AddPlan(Script::Plan& sp) {}
	virtual bool PassLinkSideSink(AtomBaseRef sink) {return true;}
	virtual bool PassLinkSideSource(AtomBaseRef src) {return true;}
	
	int						GetSideSinkId() {return side_sink;}
	int						GetSideSrcId() {return side_src;}
	//AtomBaseRef				GetLinkedSideSink() {return side_sink_conn;}
	void					SetSideSinkId(int i) {ASSERT(side_sink < 0); side_sink = i;}
	void					SetSideSrcId(int i) {ASSERT(side_src < 0); side_src = i;}
	bool					LinkSideSink(AtomBaseRef sink);
	bool					LinkSideSource(AtomBaseRef src);
	
	void					PacketConsumed(const Packet& p);
	void					PacketsConsumed(const LinkedList<Packet>& v);
	
	//static SideStatus MakeSide(const AtomTypeCls& from_type, const Script::WorldState& from, const AtomTypeCls& to_type, const Script::WorldState& to) {Panic("The class have not implemented MakeSide"); return SIDE_NOT_ACCEPTED;}
	
	ValCls GetValSpec() const {return GetType().iface.side.val;}
	bool IsValSpec(ValCls t) const {return t == GetType().iface.side.val;}
	
	static bool AllowDuplicates() {return false;}
	
	Machine& GetMachine();
	void UninitializeDeep();
	void PostContinueForward();
	
	
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
	//RefT_Loop<ValSource>	AsSource();
	//RefT_Loop<ValSink>	AsSink();
	
	
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
	
	
	
	Callback2<AtomBase&, Packet&>			WhenEnterStorePacket;
	Callback1<Packet&>						WhenEnterCreatedEmptyPacket;
	
	Callback1<Packet&>						WhenLeaveStorePacket;
	Callback								WhenLeaveCreatedEmptyPacket;
	
};




template<
	typename T,
	class SinkT=DefaultInterfaceSink,
	class SourceT=DefaultInterfaceSource,
	class SideT=VoidSideSinkInterface
>
struct Atom :
	virtual public AtomBase,
	public SinkT,
	public SourceT,
	public SideT
{
public:
	using AtomT = Atom<T, SinkT, SourceT, SideT>;
	RTTI_DECL4(AtomT, AtomBase, SinkT, SourceT, SideT)
	
	bool InitializeAtom(const Script::WorldState& ws) override {
		return SinkT::Initialize() && SourceT::Initialize() && SideT::Initialize();
	}
	
	void UninitializeAtom() override {
		SinkT::Uninitialize();
		SourceT::Uninitialize();
		SideT::Uninitialize();
	}
	
	void ClearSinkSource() override {
		SinkT::ClearSink();
		SourceT::ClearSource();
		SideT::ClearSide();
	}
	
	void Visit(RuntimeVisitor& vis) override {
		//vis.VisitThis<AtomBase>(this);
		BaseVisit(vis);
		vis.VisitThis<SinkT>(this);
		vis.VisitThis<SourceT>(this);
		vis.VisitThis<SideT>(this);
	}
	
	void CopyTo(AtomBase* target) const override {
		ASSERT(target->GetType() == GetType());
	    
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
	
	InterfaceSideSourceRef GetSideSource() override {
		InterfaceSideSource* src = CastPtr<InterfaceSideSource>(this);
		return src ? InterfaceSideSourceRef(GetParentUnsafe(), src) : InterfaceSideSourceRef();
	}
	
	InterfaceSideSinkRef GetSideSink() override {
		InterfaceSideSink* sink = CastPtr<InterfaceSideSink>(this);
		return sink ? InterfaceSideSinkRef(GetParentUnsafe(), sink) : InterfaceSideSinkRef();
	}
	
	AtomBase* AsAtomBase() override {return static_cast<AtomBase*>(this);}
	void ClearSink() override {TODO}
	void ClearSource() override {TODO}
	
	
	static SerialTypeCls::Type GetSerialType() {return SerialTypeCls::CUSTOM_ATOM;}
	
	
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
	RefT_Loop<AtomT> Get() {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator it = AtomMapBase::Find(AsSerialTypeCls<AtomT>());
		ASSERT(!IS_EMPTY_SHAREDPTR(it));
		if (it.IsEmpty())
			THROW(Exc("Could not find atom " + AsTypeString<AtomT>()));
		
		return it->AsRef<AtomT>();
	}
	
	template<typename AtomT>
	RefT_Loop<AtomT> Find() {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator it = AtomMapBase::Find(AsSerialTypeCls<AtomT>());
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
		AtomMapBase::Iterator it = AtomMapBase::Find(type);
		ASSERT_(IS_EMPTY_SHAREDPTR(it) || AtomT::AllowDuplicates(), "Cannot have duplicate componnets");
		AtomMapBase::Add(type, atom);
	}
	
	template<typename AtomT>
	void Remove(AtomStoreRef s) {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator iter = AtomMapBase::Find(AsSerialTypeCls<AtomT>());
		ASSERT_(iter, "Tried to remove non-existent atom");
		
		iter.value().AltUninitialize();
		iter.value().Uninitialize();
		//iter.value().Destroy();
		
		ReturnAtom(*s, iter.value.GetItem()->value.Detach());
		AtomMapBase::Remove(iter);
	}
	
	void AddBase(AtomBase* atom) {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		AtomTypeCls type = atom->GetType();
		ASSERT(type.IsValid());
		//AtomMapBase::Iterator it = AtomMapBase::Find(type);
		AtomMapBase::Add(type, atom);
	}
	
	#undef IS_EMPTY_SHAREDPTR
	
};

NAMESPACE_SERIAL_END

#endif
