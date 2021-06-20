#ifndef _TemplatesCore_DevContext_h_
#define _TemplatesCore_DevContext_h_

NAMESPACE_TOPSIDE_BEGIN


template <class DevSpec>
struct ScopeDevCoreT {
	using Mach				= ScopeDevMachT<DevSpec>;
	using D					= DevSpec;
	using DevFormat			= typename Mach::DevFormat;
	//using DevStream			= typename Mach::DevStream;
	
	
	template <class ValSpec> static typename ScopeValMachT<ValSpec>::Format GetDefaultFormat();
	
	/*
	using DevExchangePoint	= typename Mach::DevExchangePoint;
	
	class DevSink :
		public InterfaceSink<DevSink>,
		public DevSinkBase,
		RTTIBase
	{
	public:
		RTTI_DECL_2(DevSink, InterfaceSink<DevSink>, DevSinkBase, DevSpec::GetName() + "Sink")
		TypeId GetValDevSpec() override {return TypeId(AsTypeCls<DevSink>());}
		
		virtual DevFormat			GetFormat(D*) = 0;
		virtual DevValue&			GetValue(D*) = 0;
		
	};
	
	class DevSource :
		public InterfaceSource<DevSource, DevSink>,
		RTTIBase
	{
		using InterfaceSourceT = InterfaceSource<DevSource, DevSink>;
		
	public:
		RTTI_DECL_1(DevSource, InterfaceSourceT, DevSpec::GetName() + "Source")
		TypeId GetValDevSpec() override {return TypeId(AsTypeCls<DevSource>());}
		
		using ExPt = DevExchangePoint;
		using Sink = ScopeDevCoreT::DevSink;
		
		void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
		const RealtimeSourceConfig&	Cfg() const {return cfg;}
		void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}
		
		virtual DevStream&			GetStream(D*) = 0;
		virtual void				BeginStream(D*) = 0;
		virtual void				EndStream(D*) = 0;
		
	private:
		RealtimeSourceConfig		cfg;
		
	};
	
	using DevSourceRef			= Ref<DevSource,		RefParent1<Entity>>;
	using DevSinkRef			= Ref<DevSink,			RefParent1<Entity>>;
	
	using DevExchangePointRef	= Ref<DevExchangePoint,	RefParent1<MetaExchangePoint>>;
	*/
	
};


NAMESPACE_TOPSIDE_END

#endif
