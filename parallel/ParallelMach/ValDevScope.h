#ifndef _ParallelMach_ValDevScope_h_
#define _ParallelMach_ValDevScope_h_


NAMESPACE_PARALLEL_BEGIN


class Ex;

class Value :
	virtual public RealtimeStream
{
	bool locked = false;
	
public:
	RTTI_DECL1(Value, RealtimeStream)
	Value() = default;
	virtual ~Value() = default;
	
	virtual void Exchange(Ex& e) = 0;
	virtual void SetFormat(Format f) = 0;
	virtual void SetMinQueueSize(int i) = 0;
	virtual void SetMaxQueueSize(int i) = 0;
	virtual int GetQueueSize() const = 0;
	virtual int GetMinPackets() const = 0;
	virtual int GetMaxPackets() const = 0;
	virtual Format GetFormat() const = 0;
	virtual bool IsQueueFull() const = 0;
	virtual PacketBuffer& GetBuffer() = 0;
	
	void Lock() {ASSERT(!locked); locked = true;}
	void Unlock() {ASSERT(locked); locked = false;}
	bool IsLocked() const {return locked;}
};


class DefaultExchangePoint :
	public ExchangePoint
{
	Serial::Loop* loop = 0;
	
public:
	RTTI_DECL1(DefaultExchangePoint, ExchangePoint)
	typedef DefaultExchangePoint CLASSNAME;
	DefaultExchangePoint() {}
	~DefaultExchangePoint() {Deinit();}
	
	void Init(MetaSpaceBase* conn) override;
	void Deinit();
	void ForwardSetup(FwdScope& fwd) override;
	void ForwardAtom(FwdScope& fwd) override;
	void ForwardExchange(FwdScope& fwd) override;
	bool IsPacketStuck() override;
	
	void Destroy() {loop = 0;}
	
	
	Callback1<DefaultExchangePoint&> WhenEnterValExPtForward;
	
	Callback WhenLeaveValExPtForward;
	
};

using DefaultExchangePointRef	= Ref<DefaultExchangePoint,	RefParent1<MetaSpaceBase>>;


class Ex :
	public ExchangeBase
{
	DefaultExchangePoint* expt = 0;
	Value* src = 0;
	const RealtimeSourceConfig* src_conf = 0;
	
public:
	RTTI_DECL1(Ex, ExchangeBase)
	Ex(DefaultExchangePoint* expt) : expt(expt) {}
	Ex(DefaultExchangePoint& expt) : expt(&expt) {}
	
	Value&						Source() const {return *src;}
	const RealtimeSourceConfig&	SourceConfig() const {ASSERT(src_conf); return *src_conf;}
	DefaultExchangePoint&		GetExchangePoint() {return *expt;}
	
	void	Set(Value& src, const RealtimeSourceConfig& conf) {this->src = &src; src_conf = &conf;}
	
};


class Proxy :
	public Value
{
	Value* o = 0;
	
public:
	RTTI_DECL1(Proxy, Value)
	Proxy() = default;
	Proxy(Value* o) : o(o) {}
	
	void Set(Value* o) {this->o = o;}
	
	operator bool() const {return o != 0;}
	void Exchange(Ex& e) override {if (o) o->Exchange(e);}
	int GetQueueSize() const override {if (o) return o->GetQueueSize(); return 0;}
	Format GetFormat() const override {if (o) return o->GetFormat(); return Format();}
	bool IsQueueFull() const override {if (o) return o->IsQueueFull(); return 0;}
	PacketBuffer& GetBuffer() override {if (o) return o->GetBuffer(); PANIC("Empty proxy");}
};


class SimpleValue :
	public Value
{
	Format			fmt;
	double			time = 0;
	PacketBuffer	buf;
	int				min_packets = 1;
	int				max_packets = 2;
	
public:
	RTTI_DECL1(SimpleValue, Value)
	~SimpleValue() {/*LOG("dtor SimpleValue " << HexStr((void*)this));*/ ASSERT(buf.IsEmpty());}
	void			Visit(RuntimeVisitor& vis) {}
	void			Clear() override {/*LOG("clear SimpleValue " << HexStr((void*)this));*/ fmt.Clear(); time = 0; buf.Clear(); min_packets = 1; max_packets = 2;}
	void			Exchange(Ex& e) override;
	int				GetQueueSize() const override;
	Format			GetFormat() const override;
	bool			IsQueueFull() const override;
	PacketBuffer&	GetBuffer() override {return buf;}
	void			SetFormat(Format fmt) override {this->fmt = fmt;}
	void			SetMinQueueSize(int i) override {min_packets = i; max_packets = max(i, max_packets);}
	void			SetMaxQueueSize(int i) override {max_packets = i; min_packets = min(i, min_packets);}
	int				GetMinPackets() const override {return min_packets;}
	int				GetMaxPackets() const override {return max_packets;}
	Packet			Pick();
	void			AddPacket(Packet& p) {GetBuffer().Add(p);}
};



bool Convert(const Format& src_fmt, const byte* src, const Format& dst_fmt, byte* dst);
bool Convert(const Packet& src, Packet& dst, bool keep_tracking=true);


NAMESPACE_PARALLEL_END

#endif
