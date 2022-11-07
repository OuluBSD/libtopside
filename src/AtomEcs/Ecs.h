#ifndef _AtomEcs_Ecs_h_
#define _AtomEcs_Ecs_h_


NAMESPACE_PARALLEL_BEGIN


class EcsEventsBase :
	public Atom
{
	String						target;
	EnvStateRef					state;
	int							prev_iter = -1;
	static EcsEventsBase*		latest;
	
public:
	RTTI_DECL1(EcsEventsBase, Atom);
	
	EcsEventsBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			Recv(int sink_ch, const Packet& in) override;
	bool			Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void			Finalize(RealtimeSourceConfig& cfg) override;
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this); vis & state;}
	
	
	static Callback1<EcsEventsBase*>	WhenInitialize;
	static EcsEventsBase* Latest() {return latest;}
	
	EnvStateRef& State() {return state;}
	
};


#if defined flagSCREEN
class EcsVideoBase :
	public Atom
{
	static Vector<BinderIfaceVideo*> binders;
	String					target;
	EnvStateRef				state;
	int						prev_iter = -1;
	ValDevCls				src_type;
	ProgDraw				pd;
	
	bool					draw_mem = false;
	EntitySystemRef			ents;
	#ifdef flagGUI
	Ecs::WindowSystemRef	wins;
	#endif
	int						screen_id = 0;
	
public:
	RTTI_DECL1(EcsVideoBase, Atom);
	
	EcsVideoBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Stop() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			Recv(int sink_ch, const Packet& in) override;
	bool			Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void			Visit(RuntimeVisitor& vis) override;
	
	static void AddBinder(BinderIfaceVideo* iface);
	static void RemoveBinder(BinderIfaceVideo* iface);
	
	static Callback1<EcsVideoBase*>	WhenInitialize;
	
	ProgDraw& GetProgDraw() {return pd;}
	
};
#endif


#if 0
class EcsOglBase :
	public OglBufferBase
{
	Vector<BinderIfaceOgl*> binders;
	
public:
	RTTI_DECL1(EcsOglBase, OglBufferBase);
	
	EcsOglBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			Recv(int sink_ch, const Packet& in) override;
	bool			Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void			Visit(RuntimeVisitor& vis) override {}
	
	void AddBinder(BinderIfaceOgl* iface);
	void RemoveBinder(BinderIfaceOgl* iface);
	
	static Callback1<EcsOglBase*>	WhenInitialize;
	
};
#endif


NAMESPACE_PARALLEL_END

#endif
