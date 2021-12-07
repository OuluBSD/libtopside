#ifndef _AtomLocal_Ecs_h_
#define _AtomLocal_Ecs_h_


NAMESPACE_SERIAL_BEGIN


class EcsEventsBase :
	virtual public AtomBase
{
	Vector<BinderIfaceEvents*> binders;
	String			target;
	EnvStateRef		state;
	int				prev_iter = -1;
	
public:
	RTTI_DECL0(EcsEventsBase);
	
	EcsEventsBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			ProcessPackets(PacketIO& io) override;
	void			Visit(RuntimeVisitor& vis) override {}
	
	void AddBinder(BinderIfaceEvents* iface);
	void RemoveBinder(BinderIfaceEvents* iface);
	
	static Callback1<EcsEventsBase*>	WhenInitialize;
	
};


class EcsVideoBase :
	virtual public AtomBase
{
	Vector<BinderIfaceVideo*> binders;
	String			target;
	EnvStateRef		state;
	int				prev_iter = -1;
	ValDevCls		src_type;
	ProgDraw		pd;
	ImageDraw		id;
	StateDraw		sd;
	CpuFramebufferState	cpu_state;
	#if HAVE_OPENGL
	OglFramebufferState	ogl_state;
	OglShaderPipeline ogl_pipe;
	#endif
	
	static EcsVideoBase* latest;
	
public:
	RTTI_DECL0(EcsVideoBase);
	
	EcsVideoBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			ProcessPackets(PacketIO& io) override;
	void			Visit(RuntimeVisitor& vis) override {}
	
	void AddBinder(BinderIfaceVideo* iface);
	void RemoveBinder(BinderIfaceVideo* iface);
	
	static Callback1<EcsVideoBase*>	WhenInitialize;
	static EcsVideoBase& Latest();
	
};


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
	bool			ProcessPackets(PacketIO& io) override;
	void			Visit(RuntimeVisitor& vis) override {}
	
	void AddBinder(BinderIfaceOgl* iface);
	void RemoveBinder(BinderIfaceOgl* iface);
	
	static Callback1<EcsOglBase*>	WhenInitialize;
	
};
#endif


NAMESPACE_SERIAL_END

#endif
