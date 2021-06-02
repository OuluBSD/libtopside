#ifndef _TemplatesCore_DevContext_h_
#define _TemplatesCore_DevContext_h_

NAMESPACE_TOPSIDE_BEGIN


template <class DevSpec>
struct ScopeDevEcsT {
	using Mach			= ContextDevMachT<DevSpec>;
	using C				= typename Mach::Context;
	using Ctx			= typename Mach::Context;
	using SinkBase		= typename Mach::SinkBase;
	using Format		= typename Mach::Format;
	using ExchangePoint	= typename Mach::ExchangePoint;
	using CtxStream		= typename Mach::Stream;
	using SystemBase	= typename Mach::SystemBase;
	
	
	struct ComponentGroup {
		
		
	};
	
	
	class BaseSink :
		public InterfaceSink<BaseSink>,
		public SinkBase,
		RTTIBase
	{
	public:
		RTTI_DECL_2(BaseSink, InterfaceSink<BaseSink>, SinkBase, DevSpec::GetName() + "Sink")
		TypeId GetProviderType() override {return TypeId(AsTypeCls<BaseSink>());}
		
		virtual Format			GetFormat(C*) = 0;
		virtual Value&			GetValue(C*) = 0;
		
	};
	
	class BaseSource :
		public InterfaceSource<BaseSource, BaseSink>,
		RTTIBase
	{
		using InterfaceSourceT = InterfaceSource<BaseSource, BaseSink>;
		
	public:
		RTTI_DECL_1(BaseSource, InterfaceSourceT, DevSpec::GetName() + "Source")
		TypeId GetProviderType() override {return TypeId(AsTypeCls<BaseSource>());}
		
		using ExPt = ExchangePoint;
		using SinkClass = ScopeDevEcsT::BaseSink;
		
		void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
		const RealtimeSourceConfig&	Cfg() const {return cfg;}
		void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}
		
		virtual CtxStream&			GetStream(C*) = 0;
		virtual void				BeginStream(C*) = 0;
		virtual void				EndStream(C*) = 0;
		
	private:
		RealtimeSourceConfig		cfg;
		
	};
	
	using SourceRef			= Ref<BaseSource,		RefParent1<Entity>>;
	using SinkRef			= Ref<BaseSink,			RefParent1<Entity>>;
	using ExchangePointRef	= Ref<ExchangePoint,	RefParent1<MetaExchangePoint>>;
	
	
	#define RTTI_CTX_SYS(sys, base) \
			RTTI_DECL_2(sys, TS::System<sys>, base, DevSpec::GetName() + #sys)
	
	class System :
		public TS::System<System>,
		public SystemBase
	{
		LinkedList<SourceRef> srcs;
		LinkedList<SinkRef> sinks;
		LinkedList<ExchangePointRef> expts;
		
		void Visit(RuntimeVisitor& vis) override {
			vis && srcs
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
		RTTI_CTX_SYS(System, SystemBase)
	    SYS_CTOR(System)
		
		void Add(SourceRef src);
		void Add(SinkRef sink);
		void Add(ExchangePointRef sink);
		void Remove(SourceRef src);
		void Remove(SinkRef sink);
		void Remove(ExchangePointRef sink);
		
		static inline Callback& WhenUninit() {static Callback cb; return cb;}
		
	};
	
	#undef RTTI_CTX_SYS
	
};


NAMESPACE_TOPSIDE_END

#endif
