#ifndef _AtomHandle_Handle_h_
#define _AtomHandle_Handle_h_


NAMESPACE_PARALLEL_BEGIN


class HandleEventsBase :
	public Atom
{
	String						target;
	EnvStateRef					state;
	int							prev_iter = -1;
	static HandleEventsBase*	active;
	
public:
	RTTI_DECL1(HandleEventsBase, Atom);
	
	HandleEventsBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			Recv(int sink_ch, const Packet& in) override;
	bool			Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void			Finalize(RealtimeSourceConfig& cfg) override;
	void			Visit(RuntimeVisitor& vis) override {vis.VisitThis<Atom>(this); vis & state;}
	
	
	static Callback1<HandleEventsBase*>	WhenInitialize;
	static HandleEventsBase* Active() {return active;}
	
	EnvStateRef& State() {return state;}
	
};


#if defined flagSCREEN
class HandleVideoBase :
	public Atom
{
	struct Binder;
	
	static Array<Binder> binders;
	static HandleVideoBase* active;
	
	String					target;
	EnvStateRef				state;
	int						prev_iter = -1;
	ValDevCls				src_type;
	//ProgDraw				pd;
	
	bool					draw_mem = false;
	bool					add_ecs = false;
	bool					dbg_info = false;
	int						dbg_win_id = 0;
	#if IS_UPP_CORE && defined flagGUI
	WindowSystemRef			wins;
	#endif
	Gu::SurfaceSystemRef	surfs;
	int						screen_id = -1;
	int						add_count = 0;
	
	DrawCommand* ProcessWindow(Binder& b, DrawCommand* begin);
	void ProcessWindowCommands(Binder& b, DrawCommand* begin, DrawCommand* end);
	
	//void			RedrawScreen();
	
public:
	RTTI_DECL1(HandleVideoBase, Atom);
	
	HandleVideoBase();
	
	bool			IsScreenMode() const {return screen_id >= 0;}
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Stop() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			Recv(int sink_ch, const Packet& in) override;
	void			Finalize(RealtimeSourceConfig& cfg) override;
	bool			Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void			Visit(RuntimeVisitor& vis) override;
	
	//void			AddWindow3D(Binder&, Geom2DComponent&);
	//void			RemoveWindow3D(Binder&, Handle::Geom2DComponent&);
	bool			IsActive() const;
	
	void AddBinders();
	void AddBinderActive(Binder& b);
	
	static void AddBinder(BinderIfaceVideo* iface);
	static void RemoveBinder(BinderIfaceVideo* iface);
	
	static Callback1<HandleVideoBase*>	WhenInitialize;
	
	
};
#endif


#if 0
class HandleOglBase :
	public OglBufferBase
{
	Vector<BinderIfaceOgl*> binders;
	
public:
	RTTI_DECL1(HandleOglBase, OglBufferBase);
	
	HandleOglBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			Recv(int sink_ch, const Packet& in) override;
	bool			Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void			Visit(RuntimeVisitor& vis) override {}
	
	void AddBinder(BinderIfaceOgl* iface);
	void RemoveBinder(BinderIfaceOgl* iface);
	
	static Callback1<HandleOglBase*>	WhenInitialize;
	
};
#endif


NAMESPACE_PARALLEL_END

#endif
