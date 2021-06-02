#ifndef _TemplatesCore_DevContext_h_
#define _TemplatesCore_DevContext_h_

NAMESPACE_TOPSIDE_BEGIN


template <class DevSpec>
struct ScopeDevCoreT {
	using Mach			= ScopeDevMachT<DevSpec>;
	using D				= DevSpec;
	using SinkBase		= typename Mach::SinkBase;
	using Format		= typename Mach::Format;
	using ExchangePoint	= typename Mach::ExchangePoint;
	using CtxStream		= typename Mach::Stream;
	
	
	class ValSink :
		public InterfaceSink<ValSink>,
		public SinkBase,
		RTTIBase
	{
	public:
		RTTI_DECL_2(ValSink, InterfaceSink<ValSink>, SinkBase, DevSpec::GetName() + "Sink")
		TypeId GetProviderType() override {return TypeId(AsTypeCls<ValSink>());}
		
		virtual Format			GetFormat(D*) = 0;
		virtual Value&			GetValue(D*) = 0;
		
	};
	
	class ValSource :
		public InterfaceSource<ValSource, ValSink>,
		RTTIBase
	{
		using InterfaceSourceT = InterfaceSource<ValSource, ValSink>;
		
	public:
		RTTI_DECL_1(ValSource, InterfaceSourceT, DevSpec::GetName() + "Source")
		TypeId GetProviderType() override {return TypeId(AsTypeCls<ValSource>());}
		
		using ExPt = ExchangePoint;
		using SinkClass = ScopeDevCoreT::ValSink;
		
		void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
		const RealtimeSourceConfig&	Cfg() const {return cfg;}
		void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}
		
		virtual CtxStream&			GetStream(D*) = 0;
		virtual void				BeginStream(D*) = 0;
		virtual void				EndStream(D*) = 0;
		
	private:
		RealtimeSourceConfig		cfg;
		
	};
	
	using SourceRef			= Ref<ValSource,		RefParent1<Entity>>;
	using SinkRef			= Ref<ValSink,			RefParent1<Entity>>;
	using ExchangePointRef	= Ref<ExchangePoint,	RefParent1<MetaExchangePoint>>;
	
	
};


NAMESPACE_TOPSIDE_END

#endif
