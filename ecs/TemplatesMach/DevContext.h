#ifndef _TemplatesMach_DevContext_h_
#define _TemplatesMach_DevContext_h_

NAMESPACE_TOPSIDE_BEGIN



template <class DevCtx>
struct ContextDevT {
	
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << DevCtx::GetName() << t;
		return s;
	}
	
	class Stream : RTTIBase
	{
	public:
		RTTI_DECL_T0(Stream)
		
		template<class Ctx> using State = typename ContextDataT<Ctx>::StreamState;
		
		
		// Generic
		Time time;
		TimeStop total_time;
		int time_us = 0;
		
		
		template<class Ctx> State<Ctx>& Get();
		
		// Context states & formats
		#define IFACE(cls, var) \
			State<cls##Context> var; \
			template<> State<cls##Context>& Get<cls##Context>() {return var;}
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





#define DEV(x) \
	using x##T = ContextDevT<x##Context>; \
	using x##Stream = ContextDevT<x##Context>::Stream;
DEV_LIST
#undef DEV


NAMESPACE_TOPSIDE_END

#endif
