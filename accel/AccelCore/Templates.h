#ifndef _AccelCore_Templates_h_
#define _AccelCore_Templates_h_


NAMESPACE_TOPSIDE_BEGIN


class ConnectorBase;

template <class Ctx>
struct ContextAccelT {
	using C = Ctx;
	using Format = typename Ctx::Format;
	using ValueBase = typename Ctx::ValueBase;
	using StreamBase = typename Ctx::StreamBase;
	using CustomSystemBase = typename Ctx::CustomSystemBase;
	using CustomSinkBase = typename Ctx::CustomSinkBase;
	using Value = typename ContextT<Ctx>::Value;
	using Stream = typename ContextT<Ctx>::Stream;
	using ExchangePoint = typename ContextT<Ctx>::ExchangePoint;
	using BaseSource = typename ContextEcsT<Ctx>::Source;
	using BaseSink = typename ContextEcsT<Ctx>::Sink;
	
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
		
		virtual Stream&				GetStream(C*) = 0;
		virtual void				BeginStream(C*) = 0;
		virtual void				EndStream(C*) = 0;
		
	private:
		RealtimeSourceConfig		cfg;
		
	};
	
	
	class PipeComponent :
		public Component<PipeComponent>,
		public AccelSource,
		public AccelSink
	{
		RTTI_COMP2(PipeComponent, AccelSource, AccelSink)
		VIS_COMP_1_1(Accel, Accel)
		COPY_PANIC(PipeComponent)
		IFACE_GENERIC
		void Visit(RuntimeVisitor& vis) override {}
	public:
		
		// AccelSink
		Format				GetFormat(C*) override;
		Value&				GetValue(C*) override;
		
		// AccelSource
		Stream&				GetStream(C*) override;
		void				BeginStream(C*) override;
		void				EndStream(C*) override;
		
	};
	
	
	class ConvertInputComponent :
		public Component<ConvertInputComponent>,
		public BaseSource,
		public AccelSink
	{
		RTTI_COMP2(ConvertInputComponent, BaseSource, AccelSink)
		VIS_COMP_1_1(Base, Accel)
		COPY_PANIC(ConvertInputComponent)
		IFACE_GENERIC
		void Visit(RuntimeVisitor& vis) override {}
	public:
		
		// AccelSink
		Format				GetFormat(C*) override;
		Value&				GetValue(C*) override;
		
		// BaseSource
		Stream&				GetStream(C*) override;
		void				BeginStream(C*) override;
		void				EndStream(C*) override;
		
	};
	
	
	class ConvertOutputComponent :
		public Component<ConvertOutputComponent>,
		public AccelSource,
		public BaseSink
	{
		RTTI_COMP2(ConvertOutputComponent, AccelSource, BaseSink)
		VIS_COMP_1_1(Accel, Base)
		COPY_PANIC(ConvertOutputComponent)
		IFACE_GENERIC
		void Visit(RuntimeVisitor& vis) override {}
	public:
		
		// BaseSink
		Format				GetFormat(C*) override;
		Value&				GetValue(C*) override;
		
		// AccelSource
		Stream&				GetStream(C*) override;
		void				BeginStream(C*) override;
		void				EndStream(C*) override;
		
	};
	
	
	#if 0
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
		void			UpdateTexBuffers() override;
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
	
	#endif
	
};


NAMESPACE_TOPSIDE_END


#endif
