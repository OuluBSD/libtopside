#ifndef _TemplatesCore_ValDevScope_h_
#define _TemplatesCore_ValDevScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class ValDevSpec>
struct ScopeValDevCoreT {
	using ValSpec			= typename ValDevSpec::Val;
	using DevSpec			= typename ValDevSpec::Dev;
	using Data				= ScopeValMachT<ValSpec>;
	using Mach				= ScopeValDevMachT<ValDevSpec>;
	using V					= ValSpec;
	using Format			= typename Data::Format;
	using ValueBase			= typename ValSpec::ValueBase;
	using StreamBase		= typename ValSpec::StreamBase;
	using SystemBase		= typename ValSpec::SystemBase;
	using SinkBase			= typename ValSpec::SinkBase;
	using Value				= typename Mach::Value;
	using CtxStream			= typename Mach::Stream;
	using ValExchangePoint	= typename Mach::ValExchangePoint;
	
	
	class ValSink :
		public InterfaceSink<ValSink>,
		public SinkBase,
		RTTIBase
	{
	public:
		RTTI_DECL_2(ValSink, InterfaceSink<ValSink>, SinkBase, ValDevSpec::GetName() + "Sink")
		TypeId GetValDevSpec() override {return TypeId(AsTypeCls<ValSink>());}
		
		
		TypeCls						GetDevSpec() const override {return AsTypeCls<DevSpec>();}
		virtual Format				GetFormat(V*) = 0;
		virtual Value&				GetValue(V*) = 0;
		
	};
	
	class ValSource :
		public InterfaceSource<ValSource, ValSink>,
		RTTIBase
	{
		using InterfaceSourceT = InterfaceSource<ValSource, ValSink>;
		
	public:
		RTTI_DECL_1(ValSource, InterfaceSourceT, ValDevSpec::GetName() + "Source")
		TypeId GetValDevSpec() override {return TypeId(AsTypeCls<ValSource>());}
		
		using ExPt = ValExchangePoint;
		using Sink = ScopeValDevCoreT::ValSink;
		
		
		void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
		const RealtimeSourceConfig&	Cfg() const {return cfg;}
		void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}
		
		TypeCls						GetDevSpec() const override {return AsTypeCls<DevSpec>();}
		virtual CtxStream&			GetStream(V*) = 0;
		virtual void				BeginStream(V*) = 0;
		virtual void				EndStream(V*) = 0;
		
	private:
		RealtimeSourceConfig		cfg;
		
	};
	
	using ValSourceRef			= Ref<ValSource,		RefParent1<Entity>>;
	using ValSinkRef			= Ref<ValSink,			RefParent1<Entity>>;
	using ValExchangePointRef	= Ref<ValExchangePoint,	RefParent1<MetaExchangePoint>>;
	
	
	#define RTTI_CTX_SYS(sys, base) \
			RTTI_DECL_2(sys, System<sys>, base, ValDevSpec::GetName() + #sys)
	
	class ValSystem :
		public System<ValSystem>,
		public SystemBase
	{
		LinkedList<ValSourceRef> srcs;
		LinkedList<ValSinkRef> sinks;
		LinkedList<ValExchangePointRef> expts;
		
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
		RTTI_CTX_SYS(ValSystem, SystemBase)
	    SYS_CTOR(ValSystem)
		
		void Add(ValSourceRef src);
		void Add(ValSinkRef sink);
		void Add(ValExchangePointRef sink);
		void Remove(ValSourceRef src);
		void Remove(ValSinkRef sink);
		void Remove(ValExchangePointRef sink);
		
		static inline Callback& WhenUninit() {static Callback cb; return cb;}
		
	};
	
	#undef RTTI_CTX_SYS
	
};


NAMESPACE_TOPSIDE_END

#endif
