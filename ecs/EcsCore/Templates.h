#ifndef _EcsCore_Templates_h_
#define _EcsCore_Templates_h_

NAMESPACE_TOPSIDE_BEGIN





template <class Ctx>
struct ContextEcsT {
	using C = Ctx;
	using Format = typename Ctx::Format;
	using ValueBase = typename Ctx::ValueBase;
	using StreamBase = typename Ctx::StreamBase;
	using CustomSystemBase = typename Ctx::CustomSystemBase;
	using CustomSinkBase = typename Ctx::CustomSinkBase;
	using Value = typename ContextT<Ctx>::Value;
	using Stream = typename ContextT<Ctx>::Stream;
	using ExchangePoint = typename ContextT<Ctx>::ExchangePoint;
	
	
	class Sink :
		public InterfaceSink<Sink>,
		public CustomSinkBase
	{
	public:
		TypeId GetProviderType() override {return TypeId(typeid(Sink));}
		
		virtual Format			GetFormat(C*) = 0;
		virtual Value&			GetValue(C*) = 0;
		
	};
	
	class Source : public InterfaceSource<Source, Sink> {
	public:
		TypeId GetProviderType() override {return TypeId(typeid(Source));}
		
		using ExPt = ExchangePoint;
		using Sink = ContextEcsT::Sink;
		
		void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
		const RealtimeSourceConfig&	Cfg() const {return cfg;}
		void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}
		
		virtual Stream&				GetStream(C*) = 0;
		virtual void				BeginStream(C*) = 0;
		virtual void				EndStream(C*) = 0;
		
	private:
		RealtimeSourceConfig		cfg;
		
	};
	
	using SourceRef			= Ref<Source,			RefParent1<Entity>>;
	using SinkRef			= Ref<Sink,				RefParent1<Entity>>;
	using ExchangePointRef	= Ref<ExchangePoint, RefParent1<MetaExchangePoint>>;
	
	class System :
		public Topside::System<System>,
		public CustomSystemBase
	{
		Ref<EntityStore> ents;
		LinkedList<SourceRef> srcs;
		LinkedList<SinkRef> sinks;
		LinkedList<ExchangePointRef> expts;
		
		void Visit(RuntimeVisitor& vis) override {
			vis & ents
				&& srcs
				&& sinks
				&& expts;
		}
	protected:
	    bool Initialize() override;
	    void Start() override;
	    void Update(double dt) override;
	    void Stop() override;
	    void Uninitialize() override;
	    
	public:
	    SYS_CTOR(System)
		
		void Add(SourceRef src);
		void Add(SinkRef sink);
		void Add(ExchangePointRef sink);
		void Remove(SourceRef src);
		void Remove(SinkRef sink);
		void Remove(ExchangePointRef sink);
		
		static inline Callback& WhenUninit() {static Callback cb; return cb;}
		
	};
	
};


struct PhysicsGlobalVariables {
	vec3 gravity;
};

class PhysicsSystemBase {
public:
	PhysicsGlobalVariables var;
	
};

class DisplaySystemBase {
	Size screen_sz;
public:
	Size GetVirtualScreenSize() const{return screen_sz;}
	void SetVirtualScreenSize(Size sz) {screen_sz = sz;}
	
};


#define ECS_CTX(x) \
	using x##EcsT = ContextEcsT<x##Context>; \
	using x##ExchangePoint = x##T::ExchangePoint; \
	using x##ExchangePointRef = Ref<x##ExchangePoint, RefParent1<MetaExchangePoint>>; \
	using x##Sink = x##EcsT::Sink; \
	using x##Source = x##EcsT::Source; \
	using x##System = x##EcsT::System; \
	using x##SinkRef = Ref<x##Sink, RefParent1<Entity>>; \
	using x##SourceRef = Ref<x##Source, RefParent1<Entity>>;



#define IFACE(x) ECS_CTX(x)
IFACE_LIST
#undef IFACE



typedef enum {
	#define IFACE(x) IFACE_##x##Source , IFACE_##x##Sink ,
	IFACE_LIST
	#undef IFACE
} IfaceType;



template <class T>
class InterfaceVisitor : public RuntimeVisitor {
	TypeId match_type;
	T* last = 0;
	bool stop_when_found = false;
	
	
	bool OnEntry(TypeId type, void* mem, LockedScopeRefCounter* ref) override {
		if (type == match_type) {
			last = (T*)mem;
			if (stop_when_found) {
				BreakOut();
				return false;
			}
			else return OnInterfaceEntry(*(T*)mem);
		}
		return true;
	}
	void OnExit() override {}
	void OnRef(TypeId type, void* mem, LockedScopeRefCounter* ref) override {}
	
public:
	InterfaceVisitor() : match_type(typeid(T)) {}
	
	
	T* GetLast() const {return last;}
	void StopWhenFound(bool b=true) {stop_when_found = b;}
	
	virtual bool OnInterfaceEntry(T& o) {return true;}
	
};



NAMESPACE_TOPSIDE_END

#endif
