#ifndef _SerialMach_Link_h_
#define _SerialMach_Link_h_

NAMESPACE_SERIAL_BEGIN


class LinkBase :
	virtual public PacketForwarder,
	public RefScopeEnabler<LinkBase, MetaDirectoryBase>
{
	Parallel::AtomBaseRef atom;
	
	
public:
	#ifdef flagDEBUG
	bool dbg_async_race = false;
	#endif
	
	
protected:
	friend class Serial::ScriptLoopLoader;
	friend class Serial::Loop;
	
	int						id = -1;
	
	void					SetId(int i) {id = i;}
	
	void					SetPrimarySink(LinkBaseRef b) {prim_link_sink = b;}
	void					SetPrimarySource(LinkBaseRef b) {prim_link_src = b;}
	
protected:
	struct Exchange : RTTIBase {
		LinkBaseRef				other;
		int						local_ch_i = -1;
		int						other_ch_i = -1;
		
		RTTI_DECL0(Exchange);
		void Clear() {other.Clear(); local_ch_i = -1; other_ch_i = -1;}
		void Visit(RuntimeVisitor& vis) {vis & other;}
	};
	
	
	RealtimeSourceConfig*	last_cfg = 0;
	int						packets_forwarded = 0;
	int						skipped_fwd_count = 0;
	LinkedList<Exchange>	side_sink_conn, side_src_conn;
	LinkBaseRef				prim_link_sink, prim_link_src;
	
	void					BaseVisit(RuntimeVisitor& vis) {vis | side_sink_conn | side_src_conn; vis & prim_link_sink & prim_link_src;}
	bool					IsAllSideSourcesFull(const Vector<int>& src_chs);
	bool					IsAnySideSourceFull(const Vector<int>& src_chs);
	bool					IsPrimarySourceFull();
	
public:
	virtual bool			Initialize(const Script::WorldState& ws) {return true;}
	virtual void			Uninitialize() {}
	virtual bool			ForwardAsyncMem(byte* mem, int size) {Panic("ForwardAsyncMem unimplemented"); return false;}
	virtual bool			IsConsumedPartialPacket() {return 0;}
	virtual void			Forward(FwdScope& fwd) {}
	virtual bool			PostInitialize() {return true;}
	virtual bool			ProcessPackets(PacketIO& io);
	virtual bool			IsReady(PacketIO& io) {return atom->IsReady(io);}
	virtual bool			PassLinkSideSink(LinkBaseRef sink) {return true;}
	virtual bool			PassLinkSideSource(LinkBaseRef src) {return true;}
	
	virtual void			Visit(RuntimeVisitor& vis) = 0;
	virtual void			ClearSinkSource() = 0;
	virtual ISourceRef		GetSource() = 0;
	virtual ISinkRef		GetSink() = 0;
	virtual RTSrcConfig*	GetConfig() {return last_cfg;}
	
	void					ForwardAsync();
	Packet					InitialPacket(int src_ch, off32 off);
	Packet					ReplyPacket(int src_ch, const Packet& in);
	Packet					ReplyPacket(int src_ch, const Packet& in, Packet content);
	int						FindSourceWithValDev(ValDevCls vd);
	
	LinkBaseRef				GetLinkedSideSink()   {ASSERT(side_sink_conn.GetCount() == 1); return side_sink_conn.First().other;}
	LinkBaseRef				GetLinkedSideSource() {ASSERT(side_src_conn.GetCount()  == 1); return side_src_conn.First().other;}
	bool					LinkSideSink(LinkBaseRef sink, int local_ch_i, int other_ch_i);
	bool					LinkSideSource(LinkBaseRef src, int local_ch_i, int other_ch_i);
	
	bool					NegotiateSourceFormat(int src_ch, const Format& fmt);
	virtual bool			NegotiateSinkFormat(int sink_ch, const Format& new_fmt) {return false;}
	
	int						GetSinkPacketCount();
	int						GetSourcePacketCount();
	void					PostContinueForward();
	void					SetPrimarySinkQueueSize(int i);
	String					GetInlineConnectionsString() const;
	String					ToString() const;
	AtomTypeCls				GetType() const;
	
	
	void					Clear();
	
	bool					IsPacketStuck() override;
	bool					IsLoopComplete(FwdScope& fwd) override {return false;}
	void					ForwardAtom(FwdScope& fwd) override;
	void					ForwardExchange(FwdScope& fwd) override;
	//void					ForwardDriver(FwdScope& fwd);
	void					ForwardPipe(FwdScope& fwd);
	void					ForwardSideConnections();
	
public:
	RTTI_DECL_R1(LinkBase, PacketForwarder)
	LinkBase();
	virtual ~LinkBase();
	
	
	
	
	Callback2<LinkBase&, PacketIO&>			WhenEnterProcessPackets;
	Callback2<LinkBase&, PacketIO&>			WhenLeaveProcessPackets;
	
};

//using LinkBaseRef = Ref<LinkBase>;



template<
	typename Atom
>
struct Link :
	virtual public LinkBase
{
public:
	using LinkT = Link<Atom>;
	RTTI_DECL1(LinkT, LinkBase)
	
	void Visit(RuntimeVisitor& vis) override {
		BaseVisit(vis);
	}
	
	
	
	static ParallelTypeCls::Type GetSerialType() {return Atom::GetSerialType();}
	
	
};


NAMESPACE_SERIAL_END

#endif
