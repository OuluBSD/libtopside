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
		ScopeDevMachT_Stream_Get(Stream* s);
#define IFACE(cls, var) \
template <class Stream> \
	typename ScopeValMachT<cls##Spec>::StreamState& \
		ScopeDevMachT_Stream_Get(Stream* s) {return s->var;}
IFACE_VAR_LIST
#undef IFACE


template <class DevSpec>
struct ScopeDevMachT {
	using Spec = DevSpec;
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << Spec::GetName() << t;
		return s;
	}
	
	
	class DevFormat : RTTIBase {
		RTTI_DECL_T0(DevFormat)
		
		
	};
	
	
	struct DevComponentConf :
		public DevSpec::ComponentConfBase
	{
		
	};
	
	
	
	
	/*struct DevSinkBase : RTTIBase {
		RTTI_DECL_T0(DevSinkBase)
		
	};*/
	

	
	
	
	// This class enables device to process all interface types at once, like
	// when OpenGL shader processes all types of data in single pipeline.
	/*class DevExchangePoint :
		public ExchangePoint
	{
		ConnectorBase* conn = 0;
		off32 offset;
		bool use_consumer = false;
		bool dbg_offset_is_set = false;
		
	public:
		RTTI_DECL_T1(DevExchangePoint, ExchangePoint)
		typedef DevExchangePoint CLASSNAME;
		DevExchangePoint() {}
		~DevExchangePoint() {Deinit();}
		
		void Init(ConnectorBase* conn);
		void Deinit();
		void Update(double dt) override {Update0(dt);} // hack: call non-virtual to prevent linking error
		void Update0(double);
		
		void SetOffset(off32 o) {offset = o; dbg_offset_is_set = true;}
		void UseConsumer(bool b=true) {use_consumer = b;}
		void Destroy() {conn = 0;}
		
		off32 GetOffset() const {return offset;}
		
	};*/
	
	
	/*class Ex;
	
	class DevValue :
		RTTIBase,
		virtual public RealtimeStream
	{
		
	public:
		RTTI_DECL_T1(DevValue, RealtimeStream)
		DevValue() = default;
		virtual ~DevValue() = default;
		
		virtual void Exchange(Ex& e) = 0;
		virtual int GetQueueSize() const = 0;
		virtual DevFormat GetFormat() const = 0;
		virtual bool IsQueueFull() const = 0;
		
	};*/
	
	
	
	
	class DevSystemBase : RTTIBase
	{
	public:
		RTTI_DECL_T0(DevSystemBase)
		
	};
	
	
	class DevStream : RTTIBase
	{
	public:
		RTTI_DECL_T0(DevStream)
		
		template<class ValSpec> using State = typename ScopeValMachT<ValSpec>::StreamState;
		
		
		// Generic
		Time time;
		TimeStop total_time;
		int time_us = 0;
		
		
		template<class ValSpec> State<ValSpec>& Get() {return ScopeDevMachT_Stream_Get<DevStream, ValSpec>(this);}
		
		// Context states & formats
		#define IFACE(cls, var) \
			State<cls##Spec> var;
		IFACE_VAR_LIST
		#undef IFACE
		
		
		virtual int				GetActiveFormatIdx() const {return 0;}
		virtual int				GetFormatCount() const {return 1;}
		virtual bool			FindClosestFormat(const DevFormat& fmt, int& idx) {idx = 0; return true;}
		virtual bool			LoadFileAny(String path) {return false;}
		
		void Clear();
		void Reset();
		
		
		
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