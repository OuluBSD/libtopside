#ifndef _TemplatesMach_ValScope_h_
#define _TemplatesMach_ValScope_h_

NAMESPACE_TOPSIDE_BEGIN


class ConnectorBase;

template <class ValSpec>
struct ScopeValMachT {
	using FormatBase = typename ValSpec::FormatBase;
	using StreamBase = typename ValSpec::StreamBase;
	
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << ValSpec::GetName() << t;
		return s;
	}
	
	class Format : public FormatBase {
		RTTI_DECL_T1(Format, FormatBase)
		using FormatBase::FormatBase;
		
	public:
		String ToString() const {return FormatBase::ToString();}
		TypeCls GetDevSpec() const {return FormatBase::GetDevSpec();}
		
		bool IsSame(const Format& f) {return FormatBase::IsSame(f);}
		bool operator ==(const Format& f) {return IsSame(f);}
		bool operator !=(const Format& f) {return !IsSame(f);}
		
		template <class DevSpec> void SetDefault() {FormatBase::template SetDefault<DevSpec>();}
	};
	
	using V = ValSpec;
	
	typedef dword PacketId;
	
	
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
		double				time;
		PacketId			id = 0;
		
	public:
		using Pool = RecyclerPool<PacketValue>;
		
		static const int def_sample_rate = Format::def_sample_rate;
		
		RTTI_DECL0(PacketValue);
		PacketValue() {}
		~PacketValue() {StopTracking(this);}
		
		Vector<byte>&			Data() {return data;}
		void					Set(Format fmt, off32 offset, double time) {this->fmt = fmt; this->offset = offset; this->time = time;}
		void					SetFormat(Format fmt) {this->fmt = fmt;}
		void					SetOffset(off32 offset) {this->offset = offset;}
		void					SetTime(double seconds) {time = seconds;}
		void					SetTrackingId(PacketId i) {id = i;}
		void					Clear() {data.SetCount(0); fmt.Clear(); offset.Clear(); time = 0; id = 0;}
		
		const Vector<byte>&		GetData() const {return data;}
		Format					GetFormat() const {return fmt;}
		off32					GetOffset() const {return offset;}
		double					GetTime() const {return time;}
		bool					IsOffset(const off32& o) const {return offset.value == o.value;}
		int						GetSizeBytes() const {return data.GetCount();}
		int						GetSizeTotalSamples() const {return data.GetCount() / fmt.GetSampleSize();}
		int						GetSizeChannelSamples() const {return data.GetCount() / (fmt.GetArea() * fmt.GetSampleSize());}
		void					CheckTracking(TrackerInfo info);
		void					StopTracking(TrackerInfo info);
		PacketId				GetTrackingId() const {return id;}
		bool					HasTrackingId() const {return id != 0;}
		
		String					ToString() const;
		
		template <class T> T& SetData() {
			data.SetCount(sizeof(T));
			byte* b = &data[0];
			memset(b,0, sizeof(T));
			return *(T*)b;
		}
		
		template <class T> T& GetData() {
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
	
	static Packet CreatePacket() {
		PacketValue* obj = PacketValue::Pool::StaticPool().New();
		RecRefBase* base = RecRefBase::Pool::StaticPool().New();
		base->SetObj(obj);
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
		off32 offset;
		
		void Clear();
		void Reset();
		void Step();
	};

};


NAMESPACE_TOPSIDE_END

#endif
