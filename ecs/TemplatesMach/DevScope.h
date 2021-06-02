#ifndef _TemplatesMach_DevScope_h_
#define _TemplatesMach_DevScope_h_

NAMESPACE_TOPSIDE_BEGIN




// Specifier
#define DEV(x, pre, var) struct x##Spec {\
	static String GetName() {return #x;}\
	static String GetPrefix() {return #pre;}\
	using ComponentConfBase = x##ComponentConfBase; \
	using ComponentBase = x##ComponentBase; \
};
DEV_FULL_LIST
#undef DEV



// A hack for GCC to enable template specialization inside template
template <class Stream, class ValSpec>
	typename ScopeValMachT<ValSpec>::StreamState&
		ContextDevMachT_Stream_Get(Stream* s);
#define IFACE(cls, var) \
template <class Stream> \
	typename ScopeValMachT<cls##Spec>::StreamState& \
		ContextDevMachT_Stream_Get(Stream* s) {return s->var;}
IFACE_VAR_LIST
#undef IFACE


template <class DevSpec>
struct ContextDevMachT {
	using Spec = DevSpec;
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << Spec::GetName() << t;
		return s;
	}
	
	
	class Format : RTTIBase {
		RTTI_DECL_T0(Format)
		
		
	};
	
	
	struct ComponentConf :
		public DevSpec::ComponentConfBase
	{
		
	};
	
	
	
	
	struct SinkBase : RTTIBase {
		RTTI_DECL_T0(SinkBase)
		
	};
	

	
	
	
	// This class enables device to process all interface types at once, like
	// when OpenGL shader processes all types of data in single pipeline.
	class ExchangePoint :
		public TS::ExchangePoint
	{
		ConnectorBase* conn = 0;
		off32 offset;
		bool use_consumer = false;
		bool dbg_offset_is_set = false;
		
	public:
		RTTI_DECL_T1(ExchangePoint, TS::ExchangePoint)
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
	
	
	
	
	class Ex;
	
	class Value :
		RTTIBase,
		virtual public RealtimeStream
	{
		
	public:
		RTTI_DECL_T1(Value, RealtimeStream)
		Value() = default;
		virtual ~Value() = default;
		
		virtual void Exchange(Ex& e) = 0;
		virtual int GetQueueSize() const = 0;
		virtual Format GetFormat() const = 0;
		virtual bool IsQueueFull() const = 0;
		
	};
	
	
	
	
	class SystemBase : RTTIBase
	{
	public:
		RTTI_DECL_T0(SystemBase)
		
	};
	
	
	class Stream : RTTIBase
	{
	public:
		RTTI_DECL_T0(Stream)
		
		template<class ValSpec> using State = typename ScopeValMachT<ValSpec>::StreamState;
		
		
		// Generic
		Time time;
		TimeStop total_time;
		int time_us = 0;
		
		
		template<class ValSpec> State<ValSpec>& Get() {return ContextDevMachT_Stream_Get<Stream, ValSpec>(this);}
		
		// Context states & formats
		#define IFACE(cls, var) \
			State<cls##Spec> var;
		IFACE_VAR_LIST
		#undef IFACE
		
		
		void Clear() {
			time.Set(0);
			total_time.Reset();
			time_us = 0;
			
			#define IFACE(cls, var) var.Clear();
			IFACE_VAR_LIST
			#undef IFACE
		}
		
		void Reset() {
			total_time.Reset();
			time_us = 0;
			#define IFACE(cls, var) var.Reset();
			IFACE_VAR_LIST
			#undef IFACE
		}
		
		/*
		// Controller
		Point mouse, mouse_toycompat_drag, mouse_toycompat_click;
		
		
		
		// Video
		SystemDraw* draw = 0;
		Size video_size;
		Point video_offset;
		TimeStop vframe_time;
		double vtotal_seconds = 0;
		int vframes = 0;
		double fps_limit = 60;
		int depth = 0;
		
		
		AccelStream() {Clear();}
		void Clear();
		void Reset();
		*/
	};
};



NAMESPACE_TOPSIDE_END

#endif
