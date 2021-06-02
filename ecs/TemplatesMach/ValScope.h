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
	
	struct Format : public FormatBase {
		RTTI_DECL_T1(Format, FormatBase)
		
		using FormatBase::FormatBase;
	};
	
	using V = ValSpec;
	
	
	class PacketValue :
		RTTIBase,
		Moveable<PacketValue>
	{
		Vector<byte>		data;
		Format				fmt;
		off32				offset;
		double				time;
		
		
	public:
		using Pool = RecyclerPool<PacketValue>;
		
		static const int def_sample_rate = Format::def_sample_rate;
		
		RTTI_DECL0(PacketValue);
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
		int						GetSizeTotalSamples() const {return data.GetCount() / fmt.GetSampleSize();}
		int						GetSizeChannelSamples() const {return data.GetCount() / (fmt.GetArea() * fmt.GetSampleSize());}
		
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
	
	
	
	struct StreamState : RTTIBase {
		RTTI_DECL0(StreamState)
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
	};

};


NAMESPACE_TOPSIDE_END

#endif
