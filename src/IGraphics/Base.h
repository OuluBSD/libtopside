#ifndef _IGraphics_Base_h_
#define _IGraphics_Base_h_

NAMESPACE_PARALLEL_BEGIN


template <class Gfx>
struct BufferBaseT :
	public Atom
{
	
protected:
	using Buffer = BufferT<Gfx>;
	
	RealtimeSourceConfig* last_cfg = 0;
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(BufferBaseT, Atom);
	
	void Visit(RuntimeVisitor& vis) override {vis % bf; vis.VisitThis<Atom>(this);}
	void Update(double dt) override {bf.Update(dt);}
	RealtimeSourceConfig* GetConfig() override {return last_cfg;}
	
	Buffer& GetBuffer() {return bf.GetBuffer();}
	
	
	GfxBufferFieldT<Gfx> bf;
};


template <class Gfx>
struct ShaderBaseT :
	public BufferBaseT<Gfx>
{
	
public:
	using ShaderBase = ShaderBaseT<Gfx>;
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(ShaderBase, BufferBase);
	
	ShaderBaseT() {}
	
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	bool Start() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	bool Recv(int sink_ch, const Packet& in) override;
	void Finalize(RealtimeSourceConfig& cfg) override;
	void Visit(RuntimeVisitor& vis) override {vis.VisitThis<BufferBase>(this);}
	
	
};


template <class Gfx>
struct TextureBaseT :
	public BufferBaseT<Gfx>
{
	using Filter = GVar::Filter;
	using Wrap = GVar::Wrap;
	
	bool			loading_cubemap = false;
	Filter			filter = GVar::FILTER_LINEAR;
	Wrap			wrap = GVar::WRAP_REPEAT;
	Array<Packet>	cubemap;
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(TextureBaseT, BufferBase);
	
	TextureBaseT() {}
	
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool Recv(int sink_ch, const Packet& in) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void Visit(RuntimeVisitor& vis) override;
	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override;
	
	
};



template <class Gfx>
struct FboReaderBaseT :
	public BufferBaseT<Gfx>
{
	using Buffer = BufferT<Gfx>;
	using BufferStage = BufferStageT<Gfx>;
	
	BufferStage* src_buf = 0;
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	using NativeFrameBufferConstRef = typename Gfx::NativeFrameBufferConstRef;
	RTTI_DECL1(FboReaderBaseT, BufferBase);
	
	FboReaderBaseT() {}
	
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool Recv(int sink_ch, const Packet& in) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override;
	void Visit(RuntimeVisitor& vis) override;
	
};




template <class Gfx>
struct KeyboardBaseT :
	public BufferBaseT<Gfx>
{
	String			target;
	EnvStateRef		state;
	
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(KeyboardBaseT, BufferBase);
	KeyboardBaseT() {}
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	void Visit(RuntimeVisitor& vis) override {vis & state;}
	
};


template <class Gfx>
struct AudioBaseT :
	public BufferBaseT<Gfx>
{
	
public:
	using BufferBase = BufferBaseT<Gfx>;
	RTTI_DECL1(AudioBaseT, BufferBase);
	AudioBaseT() {}
	
	bool Initialize(const Script::WorldState& ws) override;
	bool PostInitialize() override;
	void Uninitialize() override;
	bool IsReady(PacketIO& io) override;
	bool Recv(int sink_ch, const Packet& in) override;
	bool Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) override;
	bool NegotiateSinkFormat(Serial::Link& link, int sink_ch, const Format& new_fmt) override;
	void Visit(RuntimeVisitor& vis) override {}
	
};

#define GFXTYPE(x) \
	using x##ShaderBase = ShaderBaseT<x##Gfx>; \
	using x##TextureBase = TextureBaseT<x##Gfx>; \
	using x##FboReaderBase = FboReaderBaseT<x##Gfx>; \
	using x##KeyboardBase = KeyboardBaseT<x##Gfx>; \
	using x##AudioBase = AudioBaseT<x##Gfx>;
GFXTYPE_LIST
#undef GFXTYPE


NAMESPACE_PARALLEL_END

#endif
