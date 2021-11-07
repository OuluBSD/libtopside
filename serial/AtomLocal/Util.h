#ifndef _AtomLocal_Util_h_
#define _AtomLocal_Util_h_

NAMESPACE_SERIAL_BEGIN


class CustomerBase :
	virtual public AtomBase
{
	int			packet_count = 0;
	int			packet_thrds = 0;
	off32_gen	off_gen;
	
protected:
	friend class Loop;
	using CustomerData = AtomBase::CustomerData;
	
	One<CustomerData>		customer;
	
public:
	RTTI_DECL0(CustomerBase);
	
	RTSrcConfig* GetConfig() override {ASSERT(customer); return customer ? &customer->cfg : 0;}
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	void Forward(FwdScope& fwd) override;
	bool IsLoopComplete(FwdScope& fwd) override {return fwd.GetPos() > 0;}
	void Visit(RuntimeVisitor& vis) override {}
	bool ProcessPackets(PacketIO& io) override;
	void UpdateConfig(double dt) override;
	
};


class JoinerBase :
	virtual public AtomBase
{
	byte scheduler_iter = 1;
	
public:
	JoinerBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	
	
};


class SplitterBase :
	virtual public AtomBase
{
	
public:
	SplitterBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	void Visit(RuntimeVisitor& vis) override {}
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	
	
};

#ifdef flagGUI

class OglShaderBase :
	public OglBufferBase
{
	bool is_audio = false;
	
public:
	RTTI_DECL1(OglShaderBase, OglBufferBase);
	
	OglShaderBase();
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<OglBufferBase>(this);}
	
	
};

class OglTextureBase :
	public OglBufferBase
{
	bool			loading_cubemap = false;
	Array<Packet>	cubemap;
	
public:
	RTTI_DECL1(OglTextureBase, OglBufferBase);
	
	OglTextureBase();
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<OglBufferBase>(this);}
	bool NegotiateSinkFormat(int sink_ch, const Format& new_fmt) override;
	
	
};

class OglFboReaderBase :
	public OglBufferBase
{
public:
	RTTI_DECL1(OglFboReaderBase, OglBufferBase);
	
	OglFboReaderBase();
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	bool NegotiateSinkFormat(int sink_ch, const Format& new_fmt) override;
	
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<OglBufferBase>(this);}
	
};

#endif


class TestEventSrcBase :
	virtual public AtomBase
{
	
public:
	RTTI_DECL0(TestEventSrcBase);
	
	TestEventSrcBase();
	bool Initialize(const Script::WorldState& ws) override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool ProcessPackets(PacketIO& io) override;
	void Visit(RuntimeVisitor& vis) override {}
	
	
};


enum EventStateKey {
	KEYBOARD_PRESSED,
	KEYBOARD_STATE_ITER,
	
	SCREEN0_SIZE,
	SCREEN0_OFFSET,
	
	
	MOUSE_EVENT_BASE = 0x1000,
	
	#define MOUSE_EVENT(x) MOUSE_##x = MOUSE_EVENT_BASE + Ctrl::x,
	
	MOUSE_EVENT(BUTTON)
	MOUSE_EVENT(ACTION)

	MOUSE_EVENT(MOUSEENTER)
	MOUSE_EVENT(MOUSEMOVE)
	MOUSE_EVENT(MOUSELEAVE)
	MOUSE_EVENT(CURSORIMAGE)
	MOUSE_EVENT(MOUSEWHEEL)

	MOUSE_EVENT(DOWN)
	MOUSE_EVENT(UP)
	MOUSE_EVENT(DOUBLE)
	MOUSE_EVENT(REPEAT)
	MOUSE_EVENT(DRAG)
	MOUSE_EVENT(HOLD)
	MOUSE_EVENT(TRIPLE)
	MOUSE_EVENT(PEN)
	MOUSE_EVENT(PENLEAVE)

	MOUSE_EVENT(LEFTDOWN)
	MOUSE_EVENT(LEFTDOUBLE)
	MOUSE_EVENT(LEFTREPEAT)
	MOUSE_EVENT(LEFTUP)
	MOUSE_EVENT(LEFTDRAG)
	MOUSE_EVENT(LEFTHOLD)
	MOUSE_EVENT(LEFTTRIPLE)

	MOUSE_EVENT(MIDDLEDOWN)
	MOUSE_EVENT(MIDDLEDOUBLE)
	MOUSE_EVENT(MIDDLEREPEAT)
	MOUSE_EVENT(MIDDLEUP)
	MOUSE_EVENT(MIDDLEDRAG)
	MOUSE_EVENT(MIDDLEHOLD)
	MOUSE_EVENT(MIDDLETRIPLE)
	
	MOUSE_EVENT(RIGHTDOWN)
	MOUSE_EVENT(RIGHTDOUBLE)
	MOUSE_EVENT(RIGHTREPEAT)
	MOUSE_EVENT(RIGHTUP)
	MOUSE_EVENT(RIGHTDRAG)
	MOUSE_EVENT(RIGHTHOLD)
	MOUSE_EVENT(RIGHTTRIPLE)
	
	#undef MOUSE_EVENT
	
	MOUSE_EVENT_END = 0x1FFF,
	
	MOUSE_TOUCOMPAT_DRAG,
	MOUSE_TOUCOMPAT_CLICK,
	
};


class EventStateBase :
	virtual public AtomBase
{
	static const int key_tex_w = 256;
	static const int key_tex_h = 256;
	
	typedef FixedArray<bool, 256> KeyVec;
	
	String			target;
	EnvStateRef		state;
	
public:
	RTTI_DECL0(EventStateBase);
	
	EventStateBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			ProcessPackets(PacketIO& io) override;
	void			Visit(RuntimeVisitor& vis) override {vis & state;}
	
	void			Event(const CtrlEvent& e);
	void			LeftDown(Point p, dword keyflags);
	void			LeftUp(Point p, dword keyflags);
	void			MouseMove(Point p, dword keyflags);
	bool			Key(dword key, int count);
	void			SetBool(dword key, bool b) {state->SetBool(key, b);}
	
	bool			GetBool(dword key) {return state->GetBool(key);}
	EnvState&		GetState() const;
	
};


NAMESPACE_SERIAL_END

#endif
