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
	bool Initialize(const Script::WorldState& ws) final;
	void Uninitialize() final;
	void Visit(RuntimeVisitor& vis) override {}
	bool IsReady(PacketIO& io) final;
	bool ProcessPackets(PacketIO& io) final;
	
	
};

#ifdef flagSCREEN

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
	using Filter = ShaderVar::Filter;
	using Wrap = ShaderVar::Wrap;
	
	bool			loading_cubemap = false;
	Filter			filter = ShaderVar::FILTER_LINEAR;
	Wrap			wrap = ShaderVar::WRAP_REPEAT;
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

namespace FboKbd {

static const int key_tex_w = 256;
static const int key_tex_h = 1;//256;
typedef FixedArray<byte, 256> KeyVec;

}


class EventStateBase :
	virtual public AtomBase
{
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


class OglKeyboardBase :
	public OglBufferBase
{
	String			target;
	EnvStateRef		state;
	
	
public:
	RTTI_DECL1(OglKeyboardBase, OglBufferBase);
	OglKeyboardBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			ProcessPackets(PacketIO& io) override;
	void			Visit(RuntimeVisitor& vis) override {}
	
};


class OglAudioBase :
	public OglBufferBase
{
	
public:
	RTTI_DECL1(OglAudioBase, OglBufferBase);
	OglAudioBase();
	
	bool			Initialize(const Script::WorldState& ws) override;
	bool			PostInitialize() override;
	void			Uninitialize() override;
	bool			IsReady(PacketIO& io) override;
	bool			ProcessPackets(PacketIO& io) override;
	bool			NegotiateSinkFormat(int sink_ch, const Format& new_fmt) override;
	void			Visit(RuntimeVisitor& vis) override {}
	
};


NAMESPACE_SERIAL_END

#endif
