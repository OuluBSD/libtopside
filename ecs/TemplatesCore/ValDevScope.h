#ifndef _TemplatesCore_ValDevScope_h_
#define _TemplatesCore_ValDevScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class ValDevSpec>
struct ScopeValDevEcsT {
	using ValSpec		= typename ValDevSpec::Value;
	using DevSpec		= typename ValDevSpec::Dev;
	using Data			= ScopeValMachT<ValSpec>;
	using Mach			= ScopeValDevMachT<ValDevSpec>;
	using C				= ValSpec;
	using Ctx			= typename Data::Context;
	using Format		= typename Data::Format;
	using ValueBase		= typename ValSpec::ValueBase;
	using StreamBase	= typename ValSpec::StreamBase;
	using SystemBase	= typename ValSpec::SystemBase;
	using SinkBase		= typename ValSpec::SinkBase;
	using Value			= typename Mach::Value;
	using CtxStream		= typename Mach::Stream;
	using ExchangePoint	= typename Mach::ExchangePoint;
	
	
	class BaseSink :
		public InterfaceSink<BaseSink>,
		public SinkBase,
		RTTIBase
	{
	public:
		RTTI_DECL_2(BaseSink, InterfaceSink<BaseSink>, SinkBase, Ctx::GetName() + "Sink")
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
		RTTI_DECL_1(BaseSource, InterfaceSourceT, Ctx::GetName() + "Source")
		TypeId GetProviderType() override {return TypeId(AsTypeCls<BaseSource>());}
		
		using ExPt = ExchangePoint;
		using SinkClass = ScopeValDevEcsT::BaseSink;
		
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
			RTTI_DECL_2(sys, TS::System<sys>, base, Ctx::GetName() + #sys)
	
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
