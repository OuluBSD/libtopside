#ifndef _SerialCore_Atom_h_
#define _SerialCore_Atom_h_

NAMESPACE_SERIAL_BEGIN


class AtomBase;
namespace Script {
class WorldState;
class Plan;
}

template <class T> inline SideStatus MakeSide(const AtomTypeCls& src_type, const Script::WorldState& from, const AtomTypeCls& sink_type, const Script::WorldState& to) {Panic("Unimplemented"); NEVER();}
template <class T> inline RefT_Loop<T> AtomBase_Static_As(AtomBase*) {return RefT_Loop<T>();}

class AtomBase :
	public Destroyable,
	public Enableable,
	virtual public PacketForwarder,
	public RefScopeEnabler<AtomBase, MetaDirectoryBase>
{
	
	
public:
	using AtomBaseRef = Ref<AtomBase, AtomParent>;
	
	
	#ifdef flagDEBUG
	bool dbg_async_race = false;
	#endif
	
protected:
	friend class ScriptLoopLoader;
	
	int						id = -1;
	
	void SetId(int i) {id = i;}
	
protected:
	struct CustomerData {
		RealtimeSourceConfig	cfg;
		off32_gen				gen;
		
		CustomerData();
		~CustomerData();
	};
	
	struct Exchange : RTTIBase {
		AtomBaseRef				other;
		int						local_ch_i = -1;
		int						other_ch_i = -1;
		
		RTTI_DECL0(Exchange);
		void Clear() {other.Clear(); local_ch_i = -1; other_ch_i = -1;}
		void Visit(RuntimeVisitor& vis) {vis & other;}
	};
	
	Mutex					fwd_lock;
	int						packets_forwarded = 0;
	int						skipped_fwd_count = 0;
	AtomBaseRef				driver_conn;
	RealtimeSourceConfig*	last_cfg = 0;
	IfaceConnTuple			iface;
	LinkedList<Exchange>	side_sink_conn, side_src_conn;
	
	void					ForwardAtom(FwdScope& fwd) override;
	void					ForwardExchange(FwdScope& fwd) override;
	void					ForwardDriver(FwdScope& fwd);
	void					ForwardPipe(FwdScope& fwd);
	void					ForwardSideConnections();
	
	bool					IsPacketStuck() override;
	bool					IsLoopComplete(FwdScope& fwd) override {return false;}
	void					BaseVisit(RuntimeVisitor& vis) {vis | side_sink_conn | side_src_conn; vis & driver_conn;}
	bool					IsAllSideSourcesFull(const Vector<int>& src_chs);
	bool					IsAnySideSourceFull(const Vector<int>& src_chs);
	bool					IsPrimarySourceFull();
	
public:
	virtual AtomTypeCls		GetType() const = 0;
	virtual void			CopyTo(AtomBase* atom) const = 0;
	virtual void			Visit(RuntimeVisitor& vis) = 0;
	virtual void			VisitSource(RuntimeVisitor& vis) = 0;
	virtual void			VisitSink(RuntimeVisitor& vis) = 0;
	virtual void			ClearSinkSource() = 0;
	virtual ISourceRef		GetSource() = 0;
	virtual ISinkRef		GetSink() = 0;
	virtual bool			InitializeAtom(const Script::WorldState& ws) = 0;
	virtual void			UninitializeAtom() = 0;
	
	virtual bool			ForwardAsyncMem(byte* mem, int size) {Panic("ForwardAsyncMem unimplemented"); return false;}
	virtual bool			IsConsumedPartialPacket() {return 0;}
	virtual bool			Initialize(const Script::WorldState& ws) {return true;}
	virtual void			Uninitialize() {}
	virtual void			Update(double dt) {}
	virtual void			Forward(FwdScope& fwd) {}
	virtual bool			PostInitialize() {return true;}
	virtual String			ToString() const;
	virtual bool			ProcessPackets(PacketIO& io);
	virtual bool			IsReady(PacketIO& io) {return true;}
	virtual RTSrcConfig*	GetConfig() {return last_cfg;}
	virtual void			UpdateConfig(double dt) {Panic("Unimplemented"); NEVER();}
	
	virtual bool			PassLinkSideSink(AtomBaseRef sink) {return true;}
	virtual bool			PassLinkSideSource(AtomBaseRef src) {return true;}
	
	void					ForwardAsync();
	Packet					InitialPacket(int src_ch, off32 off);
	Packet					ReplyPacket(int src_ch, const Packet& in);
	Packet					ReplyPacket(int src_ch, const Packet& in, Packet content);
	int						FindSourceWithValDev(ValDevCls vd);
	
	AtomBaseRef				GetLinkedSideSink()   {ASSERT(side_sink_conn.GetCount() == 1); return side_sink_conn.First().other;}
	AtomBaseRef				GetLinkedSideSource() {ASSERT(side_src_conn.GetCount()  == 1); return side_src_conn.First().other;}
	void					SetInterface(const IfaceConnTuple& iface);
	const IfaceConnTuple&	GetInterface() const {return iface;}
	bool					LinkSideSink(AtomBaseRef sink, int local_ch_i, int other_ch_i);
	bool					LinkSideSource(AtomBaseRef src, int local_ch_i, int other_ch_i);
	
	int						GetSinkPacketCount();
	int						GetSourcePacketCount();
	
	static SideStatus MakeSide(const AtomTypeCls& src_type, const Script::WorldState& from, const AtomTypeCls& sink_type, const Script::WorldState& to) {
		ValDevCls common_vd = src_type.iface.src.GetCommon(sink_type.iface.sink);
		if (common_vd.IsValid())
			return SIDE_ACCEPTED;
		else
			return SIDE_NOT_ACCEPTED;
	}

	
	Machine&				GetMachine();
	void					UninitializeDeep();
	void					PostContinueForward();
	String					GetInlineConnectionsString() const;
	
public:
	RTTI_DECL_R3(AtomBase, Destroyable, Enableable, PacketForwarder)
	AtomBase();
	virtual ~AtomBase();
	
	
	LoopRef		GetLoop();
	Loop&		GetParent() {return *((SP*)this)->GetParent().AsStatic<Loop>();}
	int			GetId() const {return id;}
	
	template <class T> RefT_Loop<T> As() {return AtomBase_Static_As<T>(this);}
	
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
	
	
	Callback2<AtomBase&, PacketIO&>			WhenEnterProcessPackets;
	Callback2<AtomBase&, PacketIO&>			WhenLeaveProcessPackets;
	
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
		//vis.VisitThis<AtomBase>(this);
		BaseVisit(vis);
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
		AtomMapBase::Add(type, atom);
	}
	
	template<typename AtomT>
	void Remove(AtomStoreRef s) {
		CXX2A_STATIC_ASSERT(AtomStore::IsAtom<AtomT>::value, "T should derive from Atom");
		
		AtomMapBase::Iterator iter = AtomMapBase::Find(AsSerialTypeCls<AtomT>());
		ASSERT_(iter, "Tried to remove non-existent atom");
		
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
