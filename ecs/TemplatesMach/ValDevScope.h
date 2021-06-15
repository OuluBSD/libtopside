#ifndef _TemplatesMach_ValDevScope_h_
#define _TemplatesMach_ValDevScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class ValDevSpec>
struct ScopeValDevMachT {
	using ValSpec		= typename ValDevSpec::Val;
	using DevSpec		= typename ValDevSpec::Dev;
	using ValMach		= ScopeValMachT<ValSpec>;
	using V				= ValSpec;
	using ValueBase		= typename ValSpec::ValueBase;
	using StreamBase	= typename ValSpec::StreamBase;
	using Format		= typename ValMach::Format;
	using PacketValue	= typename ValMach::PacketValue;
	using Packet		= typename ValMach::Packet;
	using PacketBuffer	= typename ValMach::PacketBuffer;
	using RecRefBase	= typename ValMach::RecRefBase;
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << ValDevSpec::GetPrefix() << t;
		return s;
	}
	
	class Ex;
	
	class Value :
		public ValueBase,
		virtual public RealtimeStream
	{
		bool locked = false;
		
	public:
		RTTI_DECL_T2(Value, ValueBase, RealtimeStream)
		Value() = default;
		virtual ~Value() = default;
		
		virtual void Exchange(Ex& e) = 0;
		virtual int GetQueueSize() const = 0;
		virtual Format GetFormat() const = 0;
		virtual bool IsQueueFull() const = 0;
		virtual PacketBuffer& GetBuffer() = 0;
		
		void Lock() {ASSERT(!locked); locked = true;}
		void Unlock() {ASSERT(locked); locked = false;}
		bool IsLocked() const {return locked;}
	};
	
	
	class ValExchangePoint :
		public ValExchangePointBase
	{
		ConnectorBase* conn = 0;
		bool use_consumer = true;
		
	public:
		RTTI_DECL_T1(ValExchangePoint, ValExchangePointBase)
		typedef ValExchangePoint CLASSNAME;
		ValExchangePoint() {}
		~ValExchangePoint() {Deinit();}
		
		void Init(MetaExchangePoint* conn) override;
		void Deinit();
		void ForwardSetup(FwdScope& fwd) override;
		void Forward(FwdScope& fwd) override;
		void ForwardExchange(FwdScope& fwd) override;
		
		void UseConsumer(bool b=true) {use_consumer = b;}
		void Destroy() {conn = 0;}
		
		
	};
	
	using ValExchangePointRef = Ref<ValExchangePoint>;
	
	
	class Ex :
		public ExchangeBase
	{
		bool storing = false;
		ValExchangePoint* expt = 0;
		Value* src = 0;
		Value* sink = 0;
		const RealtimeSourceConfig* src_conf = 0;
		
	public:
		RTTI_DECL_T1(Ex, ExchangeBase)
		Ex(ValExchangePoint* expt) : expt(expt) {}
		Ex(ValExchangePoint& expt) : expt(&expt) {}
		
		Value&						Sink() const {return *sink;}
		Value&						Source() const {return *src;}
		const RealtimeSourceConfig&	SourceConfig() const {ASSERT(src_conf); return *src_conf;}
		ValExchangePoint			GetExchangePoint() {return *expt;}
		virtual bool				IsLoading() override {return !storing;}
		virtual bool				IsStoring() override {return storing;}
		
		void	SetLoading(Value& src, const RealtimeSourceConfig& conf) {storing = false; this->src = &src; this->sink = 0; src_conf = &conf;}
		void	SetStoring(Value& sink, const RealtimeSourceConfig& conf) {storing = true; this->src = 0; this->sink = &sink; src_conf = &conf;}
		
	};
	
	
	class Proxy :
		public Value
	{
		Value* o = 0;
		
	public:
		RTTI_DECL_T1(Proxy, Value)
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
	
	
	class SimpleValue;
	
	
	class PacketProducer :
		RTTIBase
	{
		PacketBuffer*		src = 0;
		PacketBuffer*		dst = 0;
		bool				dst_realtime = false;
		bool				tmp_realtime = false;
		int					internal_written_bytes;
		int					packet_count;
		int					packet_limit;
		Packet				last;
		
	public:
		RTTI_DECL_T0(PacketProducer)
		PacketProducer() {}
		
		void		SetSource(PacketBuffer& src)		{this->src = &src;}
		void		SetSource(Value& src)				{this->src = &src.GetBuffer();}
		void		SetDestination(PacketBuffer& dst, int packet_limit)	{this->dst = &dst; this->packet_limit = packet_limit;}
		void		SetDestination(Value& dst, int packet_limit)		{this->dst = &dst.GetBuffer(); this->packet_limit = packet_limit;}
		void		SetDestinationRealtime(bool b)		{dst_realtime = b;}
		void		ClearDestination()					{dst = 0;}
		
		
		void		ProduceAll(bool blocking=false);
		bool		ProducePacket();
		bool		IsFinished() const;
		bool		IsEmptySource() const {return src == 0;}
		int			GetLastMemoryBytes() const {return internal_written_bytes;}
		int			GetCount() const {return packet_count;}
		off32		PickLastOffset() {off32 o = last->GetOffset(); last.Clear(); return o;}
		
		operator bool() const {return IsFinished();}
		
	};
	
	
	class PacketConsumer :
		RTTIBase
	{
		
		PacketBuffer*	src_buf = 0;
		int				leftover_size = 0;
		Packet			leftover;
		
		Format			dst_fmt;
		PacketBuffer*	dst_buf = 0;
		int				dst_buf_limit = 0;
		void*			dst_mem = 0;
		byte*			dst_iter = 0;
		byte*			dst_iter_end = 0;
		int				dst_size = 0;
		bool			dst_realtime = 0;
		
		int				internal_written_bytes;
		
		void Consume(Packet& p, int data_shift);
		
	public:
		RTTI_DECL_T0(PacketConsumer)
		PacketConsumer() {}
		
		void		SetSource(PacketBuffer& src);
		void		SetDestination(const Format& fmt, void* dst, int src_dst_size);
		void		SetDestination(const Format& fmt, PacketBuffer& dst, int limit);
		void		SetDestinationRealtime(bool b) {dst_realtime = b;}
		void		ClearDestination();
		void		ClearLeftover() {leftover_size = 0; leftover.Clear();}
		
		void		ConsumeAll(bool blocking=false);
		bool		ConsumePacket();
		bool		IsFinished() const;
		bool		IsEmptySource() const {return src_buf == 0;}
		bool		HasLeftover() const {return leftover_size != 0;}
		int			GetLastMemoryBytes() const {return internal_written_bytes;}
		int			GetCount() const {return consumed_packets.GetCount();}
		
		operator bool() const {return IsFinished();}
		
		
		LinkedList<Packet>		consumed_packets;
		
	};
	
	
	/*class VolatileBuffer :
		public Value,
		public RealtimePacketBuffer<Packet>
	{
		Format fmt;
		One<PacketConsumer> consumer;
		
		#if DEBUG_REALTIME
		off32 dbg_offset;
		#endif
		
	public:
		RTTI_DECL_T1(VolatileBuffer, Value)
		using Buffer = RealtimePacketBuffer<Packet>;
		
		VolatileBuffer() = default;
		
		#if DEBUG_REALTIME
		Packet Get(off32 offset) {
			Packet p = Buffer::Get(offset);
			if (p.IsEmpty()) {
				RTLOG("error: got empty packet in VolatileBuffer<" << Ctx::Name << ">");
			}
			return p;
		}
		void Put(const Packet& p, bool realtime) {
			off32 off = p->GetOffset();
			ASSERT(off == dbg_offset);
			dbg_offset.value = off.value + 1;
			Buffer::Put(p, realtime);
		}
		#endif
		
		void		SetFormat(Format fmt, int samples=2) {this->fmt = fmt; Buffer::SetLimit(samples);}
		
		void		Exchange(Ex& e)			override;
		int			GetQueueSize() const	override {return Buffer::GetQueueSize();}
		Format		GetFormat() const		override {return fmt;}
		bool		IsQueueFull() const		override {return Buffer::IsQueueFull();}
		
	};*/
	
	
	class Stream :
		public virtual RealtimeStream,
		public StreamBase
	{
		
	public:
		RTTI_DECL_T2(Stream, RealtimeStream, StreamBase)
		
		virtual ~Stream() {}
		
		virtual bool			IsOpen() const = 0;
		virtual bool			Open(int fmt_idx) = 0;
		virtual void			Close() = 0;
		virtual Value&			Get() = 0;
		virtual void			FillBuffer() = 0;
		virtual void			DropBuffer() = 0;
		virtual Format			GetFormat(int i) const = 0;
		
		virtual int				GetActiveFormatIdx() const {return 0;}
		virtual int				GetFormatCount() const {return 1;}
		virtual bool			FindClosestFormat(const Format& fmt, int& idx) {idx = 0; return true;}
		virtual bool			LoadFileAny(String path) {return false;}
		
		Format GetActiveFormat() const {return GetFormat(GetActiveFormatIdx());}
		
	};
	
	
	class SimpleValue :
		public Value
	{
		Format			fmt;
		double			time = 0;
		PacketBuffer	buf;
		int				packet_limit = 2;
		
	public:
		RTTI_DECL_T1(SimpleValue, Value)
		void			Exchange(Ex& e) override;
		int				GetQueueSize() const override;
		Format			GetFormat() const override;
		bool			IsQueueFull() const override;
		PacketBuffer&	GetBuffer() override {return buf;}
		virtual void	StorePacket(Packet& p) = 0;
		Packet			Pick();
		void			SetFormat(Format fmt) {this->fmt = fmt;}
		void			SetLimit(int i) {packet_limit = i;}
		void			AddPacket(Packet& p) {GetBuffer().Add(p);}
	};
	
	
	class SimpleBufferedValue :
		public Value
	{
		
	protected:
		ArrayMap<void*, off32> sink_offsets;
		PacketProducer	producer;
		PacketConsumer	consumer;
		PacketBuffer	buf;
		int				min_buf_samples = std::max<int>(1, 3 * Format::def_sample_rate);
		dword			exchange_count = 0;
		Format			fmt;
		
	public:
		RTTI_DECL_T1(SimpleBufferedValue, Value)
		void			Exchange(Ex& e) override;
		int				GetQueueSize() const override;
		Format			GetFormat() const override;
		bool			IsQueueFull() const override;
		PacketBuffer&	GetBuffer() override {return buf;}
		int				GetQueueTotalSamples() const;
		int				GetQueueChannelSamples() const;
		void			ClearBuffer() {buf.Clear();}
		bool			IsEmpty() const {return buf.IsEmpty();}
		//int			GetMinBufferSamples() const {return fmt.GetSampleRate() * 2;}
		//void			FillBuffersNull();
		void			Visit(RuntimeVisitor& vis) {}
		void			DropBuffer();
		void			AddPacket(Packet p) {buf.Add(p);}
		void			SetFormat(Format f) {fmt = f;}
		void			SetMinBufSamples(int i) {min_buf_samples = i;}
		
	};
	
	
	class SimpleStream :
		public Stream
	{
		Value* ptr = 0;
	public:
		RTTI_DECL_T1(SimpleStream, Stream)
		SimpleStream() {}
		SimpleStream(Value& v) : ptr(&v) {}
		void			Set(Value& v) {ptr = &v;}
		bool			IsOpen() const override {return true;}
		bool			Open(int fmt_idx) override {ASSERT(fmt_idx == 0); return true;}
		void			Close() override {}
		Value&			Get() override {ASSERT(ptr); return *ptr;}
		void			FillBuffer() override {}
		void			DropBuffer() override {}
		int				GetActiveFormatIdx() const override {return 0;}
		int				GetFormatCount() const override {return 1;}
		Format			GetFormat(int i) const override {return ptr->GetFormat();}
		bool			FindClosestFormat(const Format& fmt, int& idx) override {idx = 0; return true;}
		
	};
	
	
	class SimpleBufferedStream :
		public Stream
	{
		SimpleBufferedValue* ptr = 0;
		bool skip_drop = false;
	public:
		RTTI_DECL_T1(SimpleBufferedStream, Stream)
		SimpleBufferedStream() {}
		SimpleBufferedStream(SimpleBufferedValue& v) : ptr(&v) {}
		void			SetSkipDrop(bool b=true) {skip_drop = b;}
		void			Set(SimpleBufferedValue& v) {ptr = &v;}
		Value&			Get() override {ASSERT(ptr); return *ptr;}
		void			FillBuffer() override;
		void			DropBuffer() override {if (!skip_drop) ptr->DropBuffer();}
		int				GetActiveFormatIdx() const override {return 0;}
		int				GetFormatCount() const override {return 1;}
		Format			GetFormat(int i) const override {return ptr->GetFormat();}
		bool			FindClosestFormat(const Format& fmt, int& idx) override {idx = 0; return true;}
		virtual bool	IsEof() = 0;
		virtual bool	ReadFrame() = 0;
		virtual bool	ProcessFrame() = 0;
		virtual bool	ProcessOtherFrame() = 0;
		virtual void	ClearPacketData() = 0;
	};
	
	
	static bool Convert(const Format& src_fmt, const byte* src, const Format& dst_fmt, byte* dst);
	static bool Convert(const Packet& src, Packet& dst);
	
};


NAMESPACE_TOPSIDE_END

#endif
