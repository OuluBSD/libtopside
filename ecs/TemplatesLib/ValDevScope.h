#ifndef _TemplatesLib_ValDevScope_h_
#define _TemplatesLib_ValDevScope_h_

NAMESPACE_TOPSIDE_BEGIN


template <class ValDevSpec>
struct ScopeValDevLibT {
	using ValSpec		= typename ValDevSpec::Val;
	using DevSpec		= typename ValDevSpec::Dev;
	using ValMach		= ScopeValMachT<ValSpec>;
	using Mach			= ScopeValDevMachT<ValDevSpec>;
	using Core			= ScopeValDevCoreT<ValDevSpec>;
	using V				= ValSpec;
	using Packet		= typename ValMach::Packet;
	using Format		= typename Mach::Format;
	using ValueBase		= typename Mach::ValueBase;
	using StreamBase	= typename Mach::StreamBase;
	using Value			= typename Mach::Value;
	using CtxStream		= typename Mach::Stream;
	using ValExchangePoint		= typename Mach::ValExchangePoint;
	using SimpleValue			= typename Mach::SimpleValue;
	using SimpleBufferedValue	= typename Mach::SimpleBufferedValue;
	using SimpleStream			= typename Mach::SimpleStream;
	using SimpleBufferedStream	= typename Mach::SimpleBufferedStream;
	using ValSink				= typename Core::ValSink;
	using ValSource				= typename Core::ValSource;
	using DevCompConf			= typename ScopeDevMachT<DevSpec>::StageComponentConf;
	using StageComponent		= typename ScopeDevLibT<DevSpec>::StageComponent;
	
	using OrderValDevSpec		= VD<DevSpec, OrderSpec>;
	using OrderMach				= ScopeValDevMachT<OrderValDevSpec>;
	using OrderCore				= ScopeValDevCoreT<OrderValDevSpec>;
	using DevOrderFormat		= typename OrderMach::Format;
	using DevOrder				= typename OrderMach::Value;
	using DevSimpleOrder		= typename OrderMach::SimpleValue;
	using DevOrderSink			= typename OrderCore::ValSink;
	
	using ReceiptValDevSpec			= VD<DevSpec, ReceiptSpec>;
	using ReceiptMach				= ScopeValDevMachT<ReceiptValDevSpec>;
	using ReceiptCore				= ScopeValDevCoreT<ReceiptValDevSpec>;
	using DevReceiptFormat			= typename ReceiptMach::Format;
	using DevReceipt				= typename ReceiptMach::Value;
	using DevReceiptStream			= typename ReceiptMach::Stream;
	using DevSimpleReceipt			= typename ReceiptMach::SimpleValue;
	using DevSimpleReceiptStream	= typename ReceiptMach::SimpleStream;
	using DevReceiptSource			= typename ReceiptCore::ValSource;
	
	class InputComponent;
	class OutputComponent;
	class PipeComponent;
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << ValDevSpec::GetPrefix() << t;
		return s;
	}
	
	
	
	
	
	class InputExt : public ComponentExtBase {
		
	public:
		RTTI_DECL1(InputExt, ComponentExtBase);
		using Ext = InputExt;
		using Component = InputComponent;
		
	};
	
	class InputComponent :
		public Component<InputComponent, DevOrderSink, ValSource, InputExt>
	{
	public:
		using ComponentT = Component<InputComponent, DevOrderSink, ValSource, InputExt>;
		RTTI_DECL_1(InputComponent, ComponentT, ValDevSpec::GetName() + "InputComponent")
		COPY_PANIC(InputComponent)
		IFACE_GENERIC
		COMP_DEF_VISIT
		COMP_MAKE_ACTION_BEGIN
			COMP_MAKE_ACTION_FALSE_TO_TRUE(
				ToLower(DevSpec::GetName()) + "." +
				ToLower(ValSpec::GetName()) + "." +
				"src")
		COMP_MAKE_ACTION_END
		
	private:
		struct LocalSinkValue : public DevSimpleOrder {
			InputComponent& par;
			
			LocalSinkValue(InputComponent* par) : par(*par) {}
			void StorePacket(OrderPacket& p) override {TODO}
		};
		
		struct LocalSourceValue : public SimpleValue {
			void StorePacket(Packet& p) {}
		};
		
		struct LocalSourceStream : public SimpleStream {
			InputComponent& par;
			AudioPacketConsumer consumer;
			
			RTTI_DECL1(LocalSourceStream, SimpleStream)
			LocalSourceStream(InputComponent* par) :
				par(*par),
				SimpleStream(par->src_value) {}
			
		};
		
		LocalSinkValue		sink_value;
		LocalSourceValue	src_value;
		LocalSourceStream	src_stream;
		
		
		bool				ReadFrame();
		bool				ProcessDeviceFrame();
		
	public:
		InputComponent() : sink_value(this), src_stream(this) {}
		
		void				Forward(FwdScope& fwd) override;
		void				ForwardExchange(FwdScope& fwd) override;
		
		TypeCls GetValSpec() const override {return AsTypeCls<V>();}
		bool IsValSpec(TypeCls t) const override {return AsTypeCls<V>() == t;}
		
		// DevOrderSink
		DevOrderFormat		GetFormat(OrdCtx) override {TODO}
		DevOrder&			GetValue(OrdCtx) override {return sink_value;}
		
		// ValSource
		CtxStream&			GetStream(V*) override {return src_stream;}
		void				BeginStream(V*) override {TODO}
		void				EndStream(V*) override {TODO}
		
	};
	
	
	class OutputExt : public ComponentExtBase {
		
	public:
		RTTI_DECL1(OutputExt, ComponentExtBase);
		using Ext = OutputExt;
		using Component = OutputComponent;
		
	};
	
	class OutputComponent :
		public Component<OutputComponent, ValSink, DevReceiptSource, OutputExt>
	{
	public:
		using ComponentT = Component<OutputComponent, ValSink, DevReceiptSource, OutputExt>;
		RTTI_DECL_1(OutputComponent, ComponentT, ValDevSpec::GetName() + "OutputComponent")
		COPY_PANIC(OutputComponent)
		IFACE_GENERIC
		COMP_DEF_VISIT
		COMP_MAKE_ACTION_BEGIN
			COMP_MAKE_ACTION_FALSE_TO_TRUE(
				ToLower(DevSpec::GetName()) + "." +
				ToLower(ValSpec::GetName()) + "." +
				"sink")
		COMP_MAKE_ACTION_END
		
	private:
		struct LocalSinkValue : public SimpleBufferedValue {
			OutputComponent& par;
			
			LocalSinkValue(OutputComponent* par) : par(*par) {}
		};
		
		struct LocalSourceValue : public DevSimpleReceipt {
			void StorePacket(ReceiptPacket& p) {}
		};
		
		struct LocalSourceStream : public DevSimpleReceiptStream {
			OutputComponent& par;
			AudioPacketConsumer consumer;
			
			RTTI_DECL1(LocalSourceStream, DevSimpleReceiptStream)
			LocalSourceStream(OutputComponent* par) :
				par(*par),
				DevSimpleReceiptStream(par->src_value) {}
			
		};
		
		
		LocalSinkValue			sink_value;
		LocalSourceValue		src_value;
		LocalSourceStream		src_stream;
		RealtimeSourceConfig*	cfg = 0;
		Mutex					lock;
		LinkedList<Packet>		consumed_packets;
		
		
		
	public:
		OutputComponent() : sink_value(this), src_stream(this) {}
		
		void				Forward(FwdScope& fwd) override;
		void				ForwardExchange(FwdScope& fwd) override;
		
		TypeCls GetValSpec() const override {return AsTypeCls<V>();}
		bool IsValSpec(TypeCls t) const override {return AsTypeCls<V>() == t;}
		
		// ValSink
		Format				GetFormat(V*) override {TODO}
		Value&				GetValue(V*) override {return sink_value;}
		
		// DevReceiptSource
		DevReceiptStream&	GetStream(RcpCtx) override {return src_stream;}
		void				BeginStream(RcpCtx) override {TODO}
		void				EndStream(RcpCtx) override {TODO}
		bool				ReadFrame() {TODO}
		bool				ProcessFrame() {TODO}
		bool				ProcessDeviceFrame() {TODO}
		
	};
	
	
	class PipeExt : public ComponentExtBase {
		
	public:
		RTTI_DECL1(PipeExt, ComponentExtBase);
		using Ext = PipeExt;
		using Component = PipeComponent;
		
	};
	
	class PipeComponent :
		public Component<PipeComponent, ValSink, ValSource, PipeExt>,
		public StageComponent
	{
	public:
		using ComponentT = Component<PipeComponent, ValSink, ValSource, PipeExt>;
		RTTI_DECL_2(PipeComponent, ComponentT, StageComponent, ValDevSpec::GetName() + "DevCustomerComponent")
		COPY_PANIC(PipeComponent)
		IFACE_GENERIC
		COMP_DEF_VISIT
		COMP_MAKE_ACTION_BEGIN
			// TODO Probably should decrease count of allowed pipes, otherwise actionplanner creates
			// these infinitely.
			//COMP_MAKE_ACTION_REQ_TRUE(DevSpec::GetNameLower() + "." + ValSpec::GetNameLower() + ".pipe")
		COMP_MAKE_ACTION_END
		
	private:
		class LocalSinkValue : public SimpleBufferedValue {
		public:
			RTTI_DECL_T1(LocalSinkValue, SimpleBufferedValue)
		};
		
		class LocalSourceValue : public SimpleBufferedValue {
		public:
			RTTI_DECL_T1(LocalSourceValue, SimpleBufferedValue)
		};
		
		// TODO: select source/sink format based on cheap troughput/storage using template arg
		class LocalStream :
			public SimpleBufferedStream,
			RTTIBase
		{
		public:
			PipeComponent& par;
			RTTI_DECL_T1(LocalStream, SimpleBufferedStream);
			LocalStream(PipeComponent* p) : par(*p), SimpleBufferedStream(p->src_value) {}
			bool			IsOpen() const override {TODO}
			bool			Open(int fmt_idx) override {TODO}
			void			Close() override {TODO}
			bool			IsEof() override {TODO}
			bool			ReadFrame() override {TODO}
			bool			ProcessFrame() override {TODO}
			bool			ProcessOtherFrame() override {TODO}
			void			ClearPacketData() override {TODO}
		};
		LocalSinkValue		sink_value;
		LocalSourceValue	src_value;
		LocalStream			stream;
		
	public:
		PipeComponent() : stream(this) {}
		
		// ComponentBase
		void				Initialize() override;
		void				Uninitialize() override;
		TypeCls				GetValSpec() const override {return AsTypeCls<V>();}
		bool				IsValSpec(TypeCls t) const override {return AsTypeCls<V>() == t;}
		bool				RequiresDeviceProgram() const override {return true;}
		
		// DevSink
		Format				GetFormat(V*) override;
		Value&				GetValue(V*) override;
		
		// DevSource
		CtxStream&			GetStream(V*) override;
		void				BeginStream(V*) override;
		void				EndStream(V*) override;
		
		// StageComponent
		bool				LoadAsInput(const DevCompConf& in) override;
		void				UpdateDevBuffers() override {StageComponent::template UpdateDevBuffersValT<ValSpec>();}
		bool				IsEmptyStream() const override {return src_value.IsEmpty() && sink_value.IsEmpty();}
		void				ClearStream() override {src_value.ClearBuffer(); sink_value.ClearBuffer();}
		void				Forward(FwdScope& fwd) override;
		void				ForwardExchange(FwdScope& fwd) override;
		
	};
	
};



#if 0
template <class ValDevSpec>
struct ScopeValDevLibOrderT {
	using ValSpec		= typename ValDevSpec::Val;
	using DevSpec		= typename ValDevSpec::Dev;
	using ValMach		= ScopeValMachT<ValSpec>;
	using Mach			= ScopeValDevMachT<ValDevSpec>;
	using Core			= ScopeValDevCoreT<ValDevSpec>;
	
	using R				= ReceiptSpec;
	using RVD			= VD<DevSpec,ReceiptSpec>;
	using RMach			= ScopeValDevMachT<RVD>;
	using RCore			= ScopeValDevCoreT<RVD>;
	using RFormat		= typename RMach::Format;
	using RCtxStream	= typename RMach::Stream;
	using RValue		= typename RMach::Value;
	using RSink			= typename RCore::ValSink;
	using RSource		= typename RCore::ValSource;
	
	using O				= OrderSpec;
	using OVD			= VD<DevSpec,OrderSpec>;
	using OMach			= ScopeValDevMachT<OVD>;
	using OCore			= ScopeValDevCoreT<OVD>;
	using OFormat		= typename OMach::Format;
	using OCtxStream	= typename OMach::Stream;
	using OValue		= typename OMach::Value;
	using OSink			= typename OCore::ValSink;
	using OSource		= typename OCore::ValSource;
	
	
	class DevCustomerComponent :
		public Component<DevCustomerComponent, RSink, OSource>,
	{
	public:
		using ComponentT = Component<DevCustomerComponent, RSink, OSource>;
		RTTI_DECL_1(DevCustomerComponent, ComponentT, ValDevSpec::GetName() + "DevCustomerComponent")
		COPY_PANIC(DevCustomerComponent)
		IFACE_GENERIC
		COMP_DEF_VISIT
		COMP_MAKE_ACTION_BEGIN
			//TODO
		COMP_MAKE_ACTION_END
		
	public:
		DevCustomerComponent() {}
		
		// ComponentBase
		void				Initialize() override;
		void				Uninitialize() override;
		TypeCls				GetValSpec() const override {return AsTypeCls<O>();}
		bool				IsValSpec(TypeCls t) const override {return AsTypeCls<O>() == t;}
		
		// ReceiptSink
		RFormat				GetFormat(R*) override;
		RValue&				GetValue(R*) override;
		
		// OrderSource
		OCtxStream&			GetStream(O*) override;
		void				BeginStream(O*) override;
		void				EndStream(O*) override;
		
	};
	
	
};
#endif


NAMESPACE_TOPSIDE_END

#endif
