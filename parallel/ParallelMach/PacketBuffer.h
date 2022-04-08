#ifndef _ParallelMach_PacketBuffer_h_
#define _ParallelMach_PacketBuffer_h_


NAMESPACE_PARALLEL_BEGIN


struct TrackerInfo {
	const RTTI* handler_cls = 0;
	const char* handler_fn = 0;
	const char* file = 0;
	int line = 0;
	
	TrackerInfo() {}
	TrackerInfo(const TrackerInfo& i) {*this = i;}
	TrackerInfo(const RTTI& o) {handler_cls = &o;}
	template <class T> TrackerInfo(const T* o) {handler_cls = &o->GetRTTI();}
	template <class T> TrackerInfo(const T* o, const char* file, int line) : handler_cls(&o->GetRTTI()), file(file), line(line) {}
	TrackerInfo(const char* fn, const char* file, int line) : handler_fn(fn), file(file), line(line) {}
	
	void operator=(const TrackerInfo& i) {
		handler_cls = i.handler_cls;
		handler_fn = i.handler_fn;
		file = i.file;
		line = i.line;
	}
	
	
	String ToString() const;
};



class PacketValue :
	RTTIBase,
	Moveable<PacketValue>
{
	Vector<byte>		data;
	Format				fmt;
	off32				offset;
	PacketId			id = 0;
	TypeCls				custom_data;
	uint64				route_descriptor = 0;
	
public:
	union {
		double				time;
		int64				seq;
	};
	
public:
	using Pool = RecyclerPool<PacketValue>;
	
	//static const int def_sample_rate = Format::def_sample_rate;
	
	
	RTTI_DECL0(PacketValue);
	PacketValue(off32 offset) : offset(offset) {custom_data = AsVoidTypeCls();}
	~PacketValue() {data.Clear(); StopTracking(this);}
	
	void					Pick(PacketValue& p);
	Vector<byte>&			Data() {return data;}
	void					Set(Format fmt, double time) {this->fmt = fmt; this->time = time;}
	void					SetFormat(Format fmt) {this->fmt = fmt;}
	void					SetTime(double seconds) {time = seconds;}
	void					SetTrackingId(PacketId i) {id = i;}
	void					Clear() {data.SetCount(0); fmt.Clear(); offset.Clear(); time = 0; id = 0; custom_data = AsVoidTypeCls();}
	void					SetOffset(off32 o) {offset = o;}
	void					AddRouteData(byte b) {route_descriptor <<= 8ULL; route_descriptor |= (uint64)b;}
	void					CopyRouteData(const PacketValue& v) {route_descriptor = v.route_descriptor;}
	
	const Vector<byte>&		GetData() const {return data;}
	Format					GetFormat() const {return fmt;}
	off32					GetOffset() const {return offset;}
	double					GetTime() const {return time;}
	bool					IsOffset(const off32& o) const {return offset.value == o.value;}
	int						GetSizeBytes() const {return data.GetCount();}
	int						GetSizeTotalSamples() const {return data.GetCount() / fmt.GetSampleSize();}
	int						GetSizeChannelSamples() const;
	void					CheckTracking(TrackerInfo info);
	void					StopTracking(TrackerInfo info);
	PacketId				GetTrackingId() const {return id;}
	bool					HasTrackingId() const {return id != 0;}
	bool					IsBuffered() const {return fmt.vd.val.type == ValCls::AUDIO;}
	hash_t					GetDataHash() const;
	uint64					GetRouteDescriptor() const {return route_descriptor;}
	
	
	String					ToString() const;
	String					ToStringWithHash() const;
	
	template <class T> T& SetData() {
		custom_data = AsTypeCls<T>();
		data.SetCount(sizeof(T));
		byte* b = &data[0];
		memset(b,0, sizeof(T));
		return *(T*)b;
	}
	
	template <class T> bool IsData() {return custom_data == AsTypeCls<T>();}
	bool IsCustomData() const {return custom_data != AsVoidTypeCls();}
	
	template <class T> T& GetData() {
		ASSERT(custom_data == AsTypeCls<T>());
		ASSERT(data.GetCount() == sizeof(T));
		byte* b = &data[0];
		return *(T*)b;
	}
	
#if HAVE_OPENGL
	virtual bool PaintOpenGLTexture(int texture);
#endif
	
};


using Packet			= SharedRecycler<PacketValue>;
using PacketBuffer		= LinkedList<Packet>;
using RecRefBase		= RecyclerRefBase<PacketValue>;

static Packet CreatePacket(off32 off) {
	PacketValue* obj = PacketValue::Pool::StaticPool().New(off);
	RecRefBase* base = RecRefBase::Pool::StaticPool().New();
	base->SetObj(obj);
	obj->SetOffset(off);
	return Packet(obj, base);
}


struct ValStreamState : RTTIBase {
	RTTI_DECL0(ValStreamState)
	Format fmt;
	TimeStop frame_time;
	double total_seconds = 0;
	double frame_seconds = 0;
	double last_sync_sec = 0;
	int frames = 0;
	int frames_after_sync = 0;
	int sink_frame = 0;
	bool is_sync = 0;
	
	void Clear();
	void Reset();
	void Step();
};


class AtomBase;

class PacketBufferParent :
	public RefScopeEnabler<PacketBufferParent, AtomBase>,
	RTTIBase
{
public:
	RTTI_DECL0(PacketBufferParent)
	
};


class Value;


struct PacketIO {
	
	struct Sink {
		Value*			val = 0;
		PacketBuffer*	buf = 0;
		Packet			p;
		bool			filled = false;
		bool			may_remove = false;
	};
	
	struct Source {
		Value*			val = 0;
		Packet			p;
		int				from_sink_ch = -1;
		bool			is_full = false;
	};
	
	dword			active_sink_mask = 0;
	dword			full_src_mask = 0;
	int				nonempty_sinks = 0;
	int				sink_count = 0;
	int				src_count = 0;
	Sink			sink[MAX_VDTUPLE_SIZE];
	Source			src[MAX_VDTUPLE_SIZE];
	
};


struct PacketBufferBase :
	public RefScopeEnabler<PacketBufferBase, PacketBufferParent>,
	RTTIBase
{
public:
	RTTI_DECL0(PacketBufferBase)
	
	PacketBuffer buf;
	int max_packets = 2;
	
	virtual void FillBuffer() = 0;
	virtual void Close() = 0;
	virtual void Clear() {buf.Clear();}
	bool	IsQueueFull() const {return buf.GetCount() >= max_packets;}
	bool	StorePacket(PacketValue& p);
	bool	StorePacket(PacketValue& p, double min_time);
	bool	HasPacketOverTime(double time) const;
	void	SetMinQueueSize(int i) {max_packets = i;}
	
};

struct PacketBufferBasePtr :
	RTTIBase
{
	Ref<PacketBufferBase> base;
	
	RTTI_DECL0(PacketBufferBasePtr)
	
	
};


NAMESPACE_PARALLEL_END



NAMESPACE_TOPSIDE_BEGIN
namespace Serial {

void PacketTracker_Track(const char* fn, const char* file, int line, PacketValue& p);
void PacketTracker_Checkpoint(const char* fn, const char* file, int line, PacketValue& p);
void PacketTracker_StopTracking(const char* fn, const char* file, int line, PacketValue& p);

}
NAMESPACE_TOPSIDE_END


#endif
