#ifndef _EcsCore_Templates_h_
#define _EcsCore_Templates_h_

NAMESPACE_TOPSIDE_BEGIN





template <class Ctx, class EcsCtx>
struct ContextEcsT {
	using C = Ctx;
	using Format = typename Ctx::Format;
	using ValueBase = typename Ctx::ValueBase;
	using StreamBase = typename Ctx::StreamBase;
	using CustomSystemBase = typename EcsCtx::CustomSystemBase;
	using Value = typename ContextT<Ctx>::Value;
	using Stream = typename ContextT<Ctx>::Stream;
	
	
	class Sink : public InterfaceSink<Sink> {
	public:
		TypeId GetProviderType() override {return TypeId(typeid(Sink));}
		
		virtual Format			GetFormat(C&) = 0;
		virtual Value&			GetValue(C&) = 0;
		
	};
	
	class Source : public InterfaceSource<Source, Sink> {
	public:
		TypeId GetProviderType() override {return TypeId(typeid(Source));}
		
		using ExPt = ExchangePoint;
		
		void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
		const RealtimeSourceConfig&	Cfg() const {return cfg;}
		void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}
		
		virtual Stream&				GetStream(C&) = 0;
		virtual void				BeginStream(C&) = 0;
		virtual void				EndStream(C&) = 0;
		
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

struct DummyCustomSystemBase {};

#define ECS_CTX(x, sys_base) \
	struct x##EcsContext { \
		static constexpr const char* Name = #x; \
		using CustomSystemBase = sys_base; \
		static x##EcsContext& Static() {return Single<x##EcsContext>();} \
	}; \
	using x##EcsT = ContextEcsT<x##Context, x##EcsContext>; \
	using x##ExchangePoint = x##T::ExchangePoint; \
	using x##ExchangePointRef = Ref<x##ExchangePoint, RefParent1<MetaExchangePoint>>; \
	using x##Sink = x##EcsT::Sink; \
	using x##Source = x##EcsT::Source; \
	using x##System = x##EcsT::System; \
	using x##SinkRef = Ref<x##Sink, RefParent1<Entity>>; \
	using x##SourceRef = Ref<x##Source, RefParent1<Entity>>;



ECS_CTX(Human,			DummyCustomSystemBase)
ECS_CTX(Audio,			DummyCustomSystemBase)
ECS_CTX(Video,			DummyCustomSystemBase)
ECS_CTX(Media,			DummyCustomSystemBase)
ECS_CTX(Display,		DisplaySystemBase)
ECS_CTX(Static,			DummyCustomSystemBase)
ECS_CTX(Model,			DummyCustomSystemBase)
ECS_CTX(Device,			DummyCustomSystemBase)
ECS_CTX(Physics,		PhysicsSystemBase)
ECS_CTX(Scripting,		DummyCustomSystemBase)
ECS_CTX(Accelerator,	DummyCustomSystemBase)


NAMESPACE_TOPSIDE_END

#endif
