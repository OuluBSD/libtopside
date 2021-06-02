#ifndef _AccelCore_Context_h_
#define _AccelCore_Context_h_


NAMESPACE_TOPSIDE_BEGIN


class ConnectorBase;

template <class Dev>
struct ContextAccelT {
	using DevCtx		= Dev;
	using Ctx			= typename Dev::Value;
	using C				= Ctx;
	using ToCtx			= Ctx;
	using Format = typename Ctx::Format;
	using ValueBase = typename Ctx::ValueBase;
	using StreamBase = typename Ctx::StreamBase;
	using SystemBase = typename Ctx::SystemBase;
	using Value = typename ScopeValDevMachT<Dev>::Value;
	using CtxStream = typename ScopeValDevMachT<Dev>::Stream;
	using ExchangePoint = typename ScopeValDevMachT<Dev>::ExchangePoint;
	using SimpleBufferedValue = typename ScopeValDevMachT<Dev>::SimpleBufferedValue;
	using SimpleBufferedStream = typename ScopeValDevMachT<Dev>::SimpleBufferedStream;
	using Ex = typename ScopeValDevMachT<Dev>::Ex;
	using ValSource = typename ScopeValDevEcsT<Dev>::ValSource;
	using ValSink = typename ScopeValDevEcsT<Dev>::ValSink;
	using System = typename ScopeValDevEcsT<Dev>::System;
	
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << Dev::GetPrefix() << t;
		return s;
	}
	
	
	
	/*
	class AccelSink :
		public InterfaceSink<AccelSink>,
		RTTIBase
	{
	public:
		RTTI_DECL1(AccelSink, InterfaceSink<AccelSink>)
		TypeId GetProviderType() override {return TypeId(AsTypeCls<AccelSink>());}
		
		virtual Format			GetFormat(C*) = 0;
		virtual Value&			GetValue(C*) = 0;
		
	};
	
	class AccelSource :
		public InterfaceSource<AccelSource, AccelSink>,
		RTTIBase
	{
		using InterfaceSourceT = InterfaceSource<AccelSource, AccelSink>;
		
	public:
		RTTI_DECL1(AccelSource, InterfaceSourceT)
		TypeId GetProviderType() override {return TypeId(AsTypeCls<AccelSource>());}
		
		using ExPt = ExchangePoint;
		using SinkClass = ContextAccelT::AccelSink;
		
		void						Update(double dt, bool buffer_full) {cfg.Update(dt, buffer_full);}
		const RealtimeSourceConfig&	Cfg() const {return cfg;}
		void						SetOffset(off32 begin, off32 end) {cfg.SetOffset(begin, end);}
		
		virtual CtxStream&			GetStream(C*) = 0;
		virtual void				BeginStream(C*) = 0;
		virtual void				EndStream(C*) = 0;
		
	private:
		RealtimeSourceConfig		cfg;
		
	};
	
	class AccelExchangePoint : public ExchangePointT<ValSource, ValSink, System> {
	public:
		RTTI_DECL1(AccelExchangePoint, ExchangePointT);
		void Init(ConnectorBase* conn);
		void Deinit();
	};
	*/
	
	
	
	
	#define RTTI_ACCEL_CTX_COMP(comp, src, sink) \
			RTTI_DECL_4(comp, Component<comp>, \
					src, sink, AccelComponent, \
					ToCtx::GetName() + #comp)
	
	class PipeComponent :
		public Component<PipeComponent>,
		public ValSource,
		public ValSink,
		public AccelComponent
	{
		RTTI_ACCEL_CTX_COMP(PipeComponent, ValSource, ValSink)
		VIS_COMP_1_1(Base, Base)
		COPY_PANIC(PipeComponent)
		IFACE_GENERIC
		void Visit(RuntimeVisitor& vis) override {}
		
	public:
		
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
			bool			IsOpen() const override;
			bool			Open(int fmt_idx) override;
			void			Close() override;
			bool			IsEof() override;
			bool			ReadFrame() override;
			bool			ProcessFrame() override;
			bool			ProcessOtherFrame() override;
			void			ClearPacketData() override;
		};
		LocalSinkValue		sink_value;
		LocalSourceValue	src_value;
		LocalStream			stream;
		
		PipeComponent() : stream(this) {}
		void				Initialize() override {AccelComponent::Initialize();}
		void				Uninitialize() override {AccelComponent::Uninitialize();}
		TypeCls				GetValSpecType() const override {return AsTypeCls<C>();}
		
		// AccelSink
		Format				GetFormat(C*) override;
		Value&				GetValue(C*) override;
		
		// AccelSource
		CtxStream&			GetStream(C*) override;
		void				BeginStream(C*) override;
		void				EndStream(C*) override;
		
		bool				IsValSpec(TypeCls t) const override {return AsTypeCls<C>() == t;}
		bool				LoadAsInput(const AcceleratorHeader& in) override;
		void				UpdateTexBuffers() override {UpdateTexBuffersT<Ctx>();}
		bool				IsEmptyStream() const override {return src_value.IsEmpty() && sink_value.IsEmpty();}
		void				ClearStream() override {src_value.ClearBuffer(); sink_value.ClearBuffer();}
		
	};
	
	
};



template <class From, class To>
struct ContextConvT {
	using FromDevCtx = From;
	using FromCtx = typename From::Value;
	using F = FromCtx;
	using FromSource = typename ScopeValDevEcsT<From>::ValSource;
	using FromSink = typename ScopeValDevEcsT<From>::ValSink;
	using FromFormat = typename From::Value::Format;
	using FromValue = typename ScopeValDevMachT<From>::Value;
	using FromStream = typename ScopeValDevMachT<From>::Stream;
	using FromSimpleBufferedValue = typename ScopeValDevMachT<From>::SimpleBufferedValue;
	using FromSimpleBufferedStream = typename ScopeValDevMachT<From>::SimpleBufferedStream;
	
	using ToDevCtx = To;
	using ToCtx = typename To::Value;
	using T = ToCtx;
	using ToSource = typename ScopeValDevEcsT<To>::ValSource;
	using ToSink = typename ScopeValDevEcsT<To>::ValSink;
	using ToFormat = typename To::Value::Format;
	using ToValue = typename ScopeValDevMachT<To>::Value;
	using ToStream = typename ScopeValDevMachT<To>::Stream;
	using ToSimpleBufferedValue = typename ScopeValDevMachT<To>::SimpleBufferedValue;
	using ToSimpleBufferedStream = typename ScopeValDevMachT<To>::SimpleBufferedStream;
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << From::GetPrefix() << "2" << To::GetPrefix() << t;
		return s;
	}
	
	class ConvertComponent :
		public Component<ConvertComponent>,
		public FromSink,
		public ToSource,
		public AccelComponent
	{
		RTTI_ACCEL_CTX_COMP(ConvertComponent, FromSink, ToSource)
		VIS_COMP_1_1(To, From)
		COPY_PANIC(ConvertComponent)
		IFACE_GENERIC
		void Visit(RuntimeVisitor& vis) override {}
		
		
		struct LocalSink : FromSimpleBufferedValue {
			
		};
		struct LocalSource : ToSimpleBufferedValue {
			
		};
		class LocalStream :
			public ToSimpleBufferedStream,
			RTTIBase
		{
		public:
			ConvertComponent& par;
			RTTI_DECL_T1(LocalStream, ToSimpleBufferedStream);
			LocalStream(ConvertComponent* p) : par(*p), ToSimpleBufferedStream(p->src_value) {}
			bool			IsOpen() const override;
			bool			Open(int fmt_idx) override;
			void			Close() override;
			bool			IsEof() override;
			bool			ReadFrame() override;
			bool			ProcessFrame() override;
			bool			ProcessOtherFrame() override;
			void			ClearPacketData() override;
		};
		LocalSink sink_value;
		LocalSource src_value;
		LocalStream stream;
		
	public:
		ConvertComponent() : stream(this) {}
		
		void				Initialize() override {AccelComponent::Initialize();}
		void				Uninitialize() override {AccelComponent::Uninitialize();}
		TypeCls				GetValSpecType() const override {return AsTypeCls<T>();}
		
		// ValSink
		FromFormat			GetFormat(F*) override;
		FromValue&			GetValue(F*) override;
		
		// AccelSource
		ToStream&			GetStream(T*) override;
		void				BeginStream(T*) override;
		void				EndStream(T*) override;
		
		bool				IsValSpec(TypeCls t) const override {return AsTypeCls<T>() == t;}
		bool				LoadAsInput(const AcceleratorHeader& in) override;
		void				PreProcess() override;
		void				UpdateTexBuffers() override {UpdateTexBuffersT<ToCtx>();}
		bool				IsEmptyStream() const override {return src_value.IsEmpty() && sink_value.IsEmpty();}
		void				ClearStream() override {src_value.ClearBuffer(); sink_value.ClearBuffer();}
		
	};
	
	
	/*
	
	class ConvertOutputComponent :
		public Component<ConvertOutputComponent>,
		public ToSink,
		public FromSource,
		public AccelComponent
	{
		RTTI_ACCEL_CTX_COMP(ConvertOutputComponent, ToSink, FromSource)
		VIS_COMP_1_1(From, To)
		COPY_PANIC(ConvertOutputComponent)
		IFACE_GENERIC
		void Visit(RuntimeVisitor& vis) override {}
		
		struct LocalValue : public FromSimpleBufferedValue {
			RTTI_DECL1(LocalValue, FromSimpleBufferedValue)
			ConvertOutputComponent& par;
			LocalValue(ConvertOutputComponent* par) : par(*par) {}
			
		};
		struct LocalStream : public FromSimpleBufferedStream {
			RTTI_DECL1(LocalStream, FromSimpleBufferedStream)
			ConvertOutputComponent& par;
			LocalStream(ConvertOutputComponent* par) : par(*par), FromSimpleBufferedStream(par->value) {}
			bool			IsOpen() const override {return par.IsOpen();}
			bool			Open(int fmt_idx) override {ASSERT(fmt_idx == 0); return par.Open();}
			void			Close() override {par.Close();}
			bool			IsEof() override {return !par.IsOpen();}
			bool			ReadFrame() override {return par.ReadFrame();}
			bool			ProcessFrame() override {return par.ProcessFrame();}
			bool			ProcessOtherFrame() override {return false;}
			void			ClearPacketData() override {par.ClearPacketData();}
		};
		
		LocalValue		value;
		LocalStream		stream;
	public:
		
		ConvertOutputComponent() : stream(this), value(this) {}
		
		void				Initialize() override {AccelComponent::Initialize();}
		void				Uninitialize() override {AccelComponent::Uninitialize();}
		TypeCls				GetValSpecType() const override {return AsTypeCls<F>();}
		
		// AccelSink
		ToFormat			GetFormat(T*) override;
		ToValue&			GetValue(T*) override;
		
		// ValSource
		FromStream&			GetStream(F*) override;
		void				BeginStream(F*) override;
		void				EndStream(F*) override;
		
		bool IsValSpec(TypeCls t) const override {return AsTypeCls<F>() == t;}
		bool LoadAsInput(const AcceleratorHeader& in) override {return false;}
		bool ReadFrame();
		bool ProcessFrame();
		void ClearPacketData();
	};
	
	
	class SourceComponent :
		public Component<Source>,
		public AccelComponent,
		public DisplaySource,
		public AcceleratorSink
	{
		RTTI_COMP3(Source, AccelComponent, DisplaySource, AcceleratorSink)
		VIS_COMP_1_1(Display, Accelerator)
	private:
		void			Reset() override;
		void			PreProcess() override;
		void			PostProcess() override;
		void			Event(const CtrlEvent& e) override;
		bool			LoadResources() override;
		bool			Accept(ExchangeSinkProviderRef sink, CookieRef& src_c, CookieRef& sink_c) override;
		ComponentBase&	GetECS() override {return *this;}
		bool			RequiresShaderCode() const override {return true;}
		//AccelVideoInput*	FindVideoInput(String path);
		void			Visit(RuntimeVisitor& vis) override {}
		
	private:
		struct LocalDisplay : public SimpleBufferedDisplay {
			RTTI_DECL1(LocalDisplay, SimpleBufferedDisplay)
			Source& par;
			LocalDisplay(Source* par) : par(*par) {}
			
		};
		struct LocalDisplayStream : public SimpleBufferedDisplayStream {
			RTTI_DECL1(LocalDisplayStream, DisplayStream)
			Source& par;
			LocalDisplayStream(Source* par) : par(*par), SimpleBufferedDisplayStream(par->dvalue) {}
			bool			IsOpen() const override {return par.IsOpen();}
			bool			Open(int fmt_idx) override {ASSERT(fmt_idx == 0); return par.Open();}
			void			Close() override {par.Close();}
			bool			IsEof() override {return !par.IsOpen();}
			bool			ReadFrame() override {return par.ReadFrame();}
			bool			ProcessFrame() override {return par.ProcessFrame();}
			bool			ProcessOtherFrame() override {return false;}
			void			ClearPacketData() override {par.ClearPacketData();}
		};
		
		LocalDisplay		dvalue;
		LocalDisplayStream	dstream;
		
		
	public:
		COPY_PANIC(Source);
		IFACE_CB(DisplaySource);
		IFACE_CB(AcceleratorSink);
		IFACE_GENERIC;
		
		Source() : AccelComponent(FUSION_DISPLAY_SOURCE), dvalue(this), dstream(this) {}
		
		bool				ReadFrame();
		bool				ProcessFrame();
		void				ClearPacketData();
		
		void				Initialize() override;
		void				Uninitialize() override;
		
		// DisplaySource
		DisplayStream&		GetStream(DisCtx) override;
		void				BeginStream(DisCtx) override;
		void				EndStream(DisCtx) override;
		
		// AcceleratorSink
		AcceleratorFormat	GetFormat(AccCtx) override {TODO}
		Accelerator&		GetValue(AccCtx) override {TODO}
		
		void				SetVideoSize(Size sz);
		void				SetFPS(int fps);
		
	};
	
	*/
	
};


NAMESPACE_TOPSIDE_END


#endif
