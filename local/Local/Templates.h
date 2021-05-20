#ifndef _Local_Templates_h_
#define _Local_Templates_h_

NAMESPACE_TOPSIDE_BEGIN


class ConnectorBase;


template <class T>
class RealtimePacketBuffer {
	static const int BUFFER_COUNT = 2;
	static const int PACKET_LIMIT = 1024;
	
	RWMutex lock;
	LinkedList<T> packets[BUFFER_COUNT];
	int data_i = 0;
	int size_limit = 0;
	
	
public:
	RealtimePacketBuffer() {}
	
	void Dump() {
		LOG("RealtimePacketBuffer: active buf: " << data_i);
		for(int i = 0; i < BUFFER_COUNT; i++) {
			LinkedList<T>& l = packets[i];
			auto iter = l.begin();
			int j = 0;
			for(; iter; ++iter, ++j) {
				LOG("RealtimePacketBuffer: " << i << ": " << j << ": " << iter()->GetOffset().ToString());
			}
		}
	}
	void Clear() {
		lock.EnterWrite();
		for(int i = 0; i < BUFFER_COUNT; i++)
			packets[i].Clear();
		data_i = 0;
		size_limit = 0;
		lock.LeaveWrite();
	}
	void RemoveFirst(int count=1) {
		lock.EnterWrite();
		count = min(count, packets[data_i].GetCount());
		AUDIOLOG("RealtimePacketBuffer::RemoveFirst: " << IntStr(count));
		packets[data_i].RemoveFirst(count);
		lock.LeaveWrite();
	}
	
	void		SetLimit(int i) {size_limit = i;}
	
	int			GetQueueSize() const {return packets[data_i].GetCount();}
	bool		IsQueueFull() const {return packets[data_i].GetCount() >= size_limit;}
	bool		IsEmpty() const {return packets[data_i].IsEmpty();}
	
	int GetQueueSizeBytes() const {
		int sz = 0;
		for (auto iter = packets[data_i].begin(); iter; ++iter)
			sz += iter()->GetSizeBytes();
		return sz;
	}
	
	off32 GetOffset() const {
		LinkedList<T>& l = const_cast<LinkedList<T>&>(packets[data_i]);
		return l.IsEmpty() ? off32() : (*l.begin())->GetOffset();
	}
	
	T Get(off32 offset) {
		lock.EnterRead();
		ASSERT(data_i >= 0 && data_i < BUFFER_COUNT);
		LinkedList<T>& l = packets[data_i];
		if (l.IsEmpty()) {
			lock.LeaveRead();
			return T();
		}
		
		// Find given offset frame
		auto iter = l.begin();
		bool found = false;
		while (iter) {
			off32 iter_offset = iter()->GetOffset();
			if (iter_offset == offset) {
				found = true;
				break;
			}
			++iter;
		}
		if (!found) {
			lock.LeaveRead();
			return T();
		}
		
		T p = iter();
		lock.LeaveRead();
		
		return p;
	}
	
	void Put(const T& p, bool realtime) {
		lock.EnterWrite();
		if (realtime) {
			packets[data_i].Clear();
			data_i = (data_i + 1) % BUFFER_COUNT;
			LinkedList<T>& l = packets[data_i];
			ASSERT(l.IsEmpty());
			l.Add(p);
			ASSERT(size_limit > 0);
		}
		else {
			LinkedList<T>& l = packets[data_i];
			l.Add(p);
		}
		lock.LeaveWrite();
	}
	
};


template <class Ctx>
struct ContextT {
	using C = ContextT;
	using Format = typename Ctx::Format;
	using ValueBase = typename Ctx::ValueBase;
	using StreamBase = typename Ctx::StreamBase;
	
	class Ex;
	
	class Value :
		public ValueBase,
		virtual public RealtimeStream
	{
		
	public:
		Value() = default;
		virtual ~Value() = default;
		
		virtual void Exchange(Ex& e) = 0;
		virtual int GetQueueSize() const = 0;
		virtual Format GetFormat() const = 0;
		virtual bool IsQueueFull() const = 0;
		
	};
	
	
	class ExchangePoint : public Topside::ExchangePoint {
		ConnectorBase* conn = 0;
		off32 offset;
		bool use_consumer = false;
		bool dbg_offset_is_set = false;
		
	public:
		typedef ExchangePoint CLASSNAME;
		ExchangePoint() {}
		~ExchangePoint() {Deinit();}
		
		void Init(ConnectorBase* conn);
		void Deinit();
		void Update(double dt) override;
		void SetOffset(off32 o) {offset = o; dbg_offset_is_set = true;}
		void UseConsumer(bool b=true) {use_consumer = b;}
		void Destroy() {conn = 0;}
		
		off32 GetOffset() const {return offset;}
		
	};
	
	
	class Ex : public ExchangeBase {
		bool storing = false;
		ExchangePoint* expt = 0;
		Value* src = 0;
		Value* sink = 0;
		const RealtimeSourceConfig* src_conf = 0;
		off32 offset;
		
	public:
		Ex(ExchangePoint* expt) : expt(expt) {}
		
		Value&						Sink() const {return *sink;}
		Value&						Source() const {return *src;}
		const RealtimeSourceConfig&	SourceConfig() const {return *src_conf;}
		ExchangePoint&				GetExchangePoint() {return *expt;}
		off32						GetOffset() const {return offset;}
		virtual bool				IsLoading() {return !storing;}
		virtual bool				IsStoring() {return storing;}
		
		void	SetLoading(Value& src, const RealtimeSourceConfig& conf) {storing = false; this->src = &src; this->sink = 0; src_conf = &conf;}
		void	SetStoring(Value& sink, const RealtimeSourceConfig& conf) {storing = true; this->src = 0; this->sink = &sink; src_conf = &conf;}
		void	SetOffset(off32 packet_count);
		
	};
	
	
	class PacketValue : Moveable<PacketValue> {
		Vector<byte>		data;
		Format				fmt;
		off32				offset;
		double				time;
		
		
	public:
		
		using Pool = RecyclerPool<PacketValue>;
		
		PacketValue() {}
		
		Vector<byte>&			Data() {return data;}
		void					Set(Format fmt, off32 offset, double time) {this->fmt = fmt; this->offset = offset; this->time = time;}
		void					SetFormat(Format fmt) {this->fmt = fmt;}
		void					SetOffset(off32 offset) {this->offset = offset;}
		void					SetTime(double seconds) {time = seconds;}
		
		const Vector<byte>&		GetData() const {return data;}
		Format					GetFormat() const {return fmt;}
		off32					GetOffset() const {return offset;}
		double					GetTime() const {return time;}
		bool					IsOffset(const off32& o) const {return offset.value == o.value;}
		int						GetSizeBytes() const {return data.GetCount();}
		
	#if HAVE_OPENGL
		virtual bool PaintOpenGLTexture(int texture);
	#endif
		
	};
	
	
	using Packet			= SharedRecycler<PacketValue>;
	using PacketBuffer		= LinkedList<Packet>;
	using RecRefBase		= RecyclerRefBase<PacketValue>;
	
	static Packet CreatePacket() {
		PacketValue* obj = PacketValue::Pool::StaticPool().New();
		RecRefBase* base = RecRefBase::Pool::StaticPool().New();
		base->SetObj(obj);
		return Packet(obj, base);
	}
	
	
	class Proxy : public Value {
		Value* o = 0;
		
	public:
		Proxy() = default;
		Proxy(Value* o) : o(o) {}
		
		void Set(Value* o) {this->o = o;}
		
		operator bool() const {return o != 0;}
		void Exchange(Ex& e) override {if (o) o->Exchange(e);}
		int GetQueueSize() const override {if (o) return o->GetQueueSize(); return 0;}
		Format GetFormat() const override {if (o) return o->GetFormat(); return Format();}
		bool IsQueueFull() const override {if (o) return o->IsQueueFull(); return 0;}
		
	};
	
	
	class VolatileBuffer;
	
	
	class PacketProducer {
		PacketBuffer*		src = 0;
		VolatileBuffer*		dst = 0;
		off32				offset;
		bool				dst_realtime = false;
		
	public:
		PacketProducer() {}
		
		void		SetOffset(off32 offset) {this->offset = offset;}
		void		SetSource(PacketBuffer& src) {this->src = &src;}
		void		SetDestination(VolatileBuffer& dst) {this->dst = &dst;}
		void		SetDestinationRealtime(bool b) {dst_realtime = b;}
		void		ClearDestination() {dst = 0;}
		
		
		void		ProduceAll(bool blocking=false);
		bool		ProducePacket();
		bool		IsFinished() const;
		bool		IsEmptySource() const {return src == 0;}
		off32		GetOffset() const {return offset;}
		
		operator bool() const {return IsFinished();}
		
	};
	
	
	class PacketConsumer {
		
		VolatileBuffer*	src = 0;
		off32			offset;
		int				leftover_size = 0;
		Packet			leftover;
		
		Format			dst_fmt;
		VolatileBuffer*	dst_buf = 0;
		void*			dst_mem = 0;
		byte*			dst_iter = 0;
		byte*			dst_iter_end = 0;
		int				dst_remaining = 0;
		bool			dst_realtime = 0;
		
		int				internal_count;
		
		void Consume(Packet& p, int data_shift);
		
	public:
		PacketConsumer() {}
		
		void		SetOffset(off32 offset) {ASSERT(!HasLeftover()); this->offset = offset;}
		void		SetSource(VolatileBuffer& src);
		void		SetDestination(const Format& fmt, void* dst, int src_dst_size);
		void		SetDestination(VolatileBuffer& dst);
		void		SetDestinationRealtime(bool b) {dst_realtime = b;}
		void		ClearDestination();
		void		ClearLeftover() {leftover_size = 0; leftover.Clear();}
		void		TestSetOffset(off32 offset);
		
		void		ConsumeAll(bool blocking=false);
		bool		ConsumePacket();
		bool		IsFinished() const;
		bool		IsEmptySource() const {return src == 0;}
		off32		GetOffset() const {return offset;}
		bool		HasLeftover() const {return leftover_size != 0;}
		
		operator bool() const {return IsFinished();}
		
	};
	
	
	class VolatileBuffer :
		public Value,
		public RealtimePacketBuffer<Packet>
	{
		Format preferred_fmt;
		One<PacketConsumer> consumer;
		
		#if DEBUG_REALTIME
		off32 dbg_offset;
		#endif
		
	public:
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
		
		void		SetSize(Format fmt, int frames) {preferred_fmt = fmt; Buffer::SetLimit(frames);}
		
		void		Exchange(Ex& e)	override;
		int			GetQueueSize() const	override {return Buffer::GetQueueSize();}
		Format		GetFormat() const		override {return preferred_fmt;}
		bool		IsQueueFull() const		override;
		
		
		
	};
	
	
	class Stream :
		public virtual RealtimeStream,
		public RefScopeEnabler<Stream,ComponentBase>,
		public StreamBase
	{
		
	public:
		using Parent = ComponentBase;
		
		virtual ~Stream() {}
		
		virtual bool			IsOpen() const = 0;
		virtual bool			Open(int fmt_idx) = 0;
		virtual void			Close() = 0;
		virtual Value&			Get() = 0;
		virtual void			FillBuffer() = 0;
		virtual void			DropBuffer() = 0;
		virtual int				GetActiveFormatIdx() const = 0;
		virtual int				GetFormatCount() const = 0;
		virtual Format			GetFormat(int i) const = 0;
		virtual bool			FindClosestFormat(const Format& fmt, int& idx) = 0;
		
		
		Format GetActiveFormat() const {return GetFormat(GetActiveFormatIdx());}
		
	};
	
	
	class SimpleStream :
		public Stream
	{
		Value* ptr = 0;
	public:
		void			Set(Value& v) {ptr = &v;}
		bool			IsOpen() const override {return true;}
		bool			Open(int fmt_idx) override {ASSERT(fmt_idx == 0); return true;}
		void			Close() override {}
		Value&			Get() override {return *ptr;}
		void			FillBuffer() override {}
		void			DropBuffer() override {}
		int				GetActiveFormatIdx() const override {return 0;}
		int				GetFormatCount() const override {return 1;}
		Format			GetFormat(int i) const override {return ptr->GetFormat();}
		bool			FindClosestFormat(const Format& fmt, int& idx) override {idx = 0; return true;}
	};
	
	
	static bool Convert(const Format& src_fmt, const byte* src, const Format& dst_fmt, byte* dst);
	static bool Convert(const Packet& src, Packet& dst);
	
};


#include "Templates.inl"


#define LOCAL_CTX(x, value_base, stream_base) \
	struct x##Context { \
		static constexpr const char* Name = #x; \
		using Format			= x##Format; \
		using Ctx				= x##Context; \
		using ValueBase			= value_base; \
		using StreamBase		= stream_base; \
		static x##Context& Static() {return Single<x##Context>();} \
	}; \
	using x##T = ContextT<x##Context>; \
	using x = x##T::Value; \
	using x##Proxy = x##T::Proxy; \
	using x##Proxy = x##T::Proxy; \
	using x##Packet = x##T::Packet; \
	using x##VolatileBuffer = x##T::VolatileBuffer; \
	using x##Stream = x##T::Stream; \
	using x##PacketConsumer = x##T::PacketConsumer; \
	using x##PacketProducer = x##T::PacketProducer; \
	using x##Ex = x##T::Ex; \
	using x##Proxy = x##T::Proxy; \
	using x##PacketBuffer = x##T::PacketBuffer; \
	using Simple##x##Stream = x##T::SimpleStream; \
	using x##StreamRef = Ref<x##Stream,RefParent1<ComponentBase>>; \
	x##Packet Create##x##Packet() {return x##T::CreatePacket();}


struct DummyValueBase {};
struct DummyStreamBase {};

NAMESPACE_TOPSIDE_END

#endif
