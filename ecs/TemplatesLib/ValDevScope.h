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
	using Format		= typename Mach::Format;
	using ValueBase		= typename Mach::ValueBase;
	using StreamBase	= typename Mach::StreamBase;
	using Value			= typename Mach::Value;
	using CtxStream		= typename Mach::Stream;
	using ValExchangePoint		= typename Mach::ValExchangePoint;
	using SimpleBufferedValue	= typename Mach::SimpleBufferedValue;
	using SimpleBufferedStream	= typename Mach::SimpleBufferedStream;
	using ValSink		= typename Core::ValSink;
	using ValSource		= typename Core::ValSource;
	using DevCompConf	= typename ScopeDevMachT<DevSpec>::DevComponentConf;
	using DevComponent	= typename ScopeDevLibT<DevSpec>::DevComponent;
	
	#define RTTI_CTX_LIB_INPUT_COMP(comp, src) \
			RTTI_DECL_2(comp, Component<comp>, src, ValDevSpec::GetName() + #comp)
	
	static const char* TypeStringT(const char* t) {
		thread_local static String s;
		s.Clear();
		s << ValDevSpec::GetPrefix() << t;
		return s;
	}
	
	class InputComponent :
		public Component<InputComponent>,
		public ValSource
	{
		RTTI_CTX_LIB_INPUT_COMP(InputComponent, ValSource)
		VIS_COMP_1_0(Val)
		COPY_PANIC(InputComponent)
		IFACE_GENERIC
		void Visit(RuntimeVisitor& vis) override {}
		
		
		struct LocalValue : public SimpleBufferedValue {
			
		};
		
		struct LocalStream : public SimpleBufferedStream {
			RTTI_DECL1(LocalStream, SimpleBufferedStream)
			InputComponent& par;
			LocalStream(InputComponent* par) :
				par(*par),
				SimpleBufferedStream(par->value) {}
			bool			IsOpen() const override;
			bool			Open(int fmt_idx) override;
			void			Close() override {par.value.ClearBuffer();}
			bool			IsEof() override {return false;}
			bool			ReadFrame() override {return par.ReadFrame();}
			bool			ProcessFrame() override {return par.ProcessDeviceFrame();}
			bool			ProcessOtherFrame() override {return false;}
			void			ClearPacketData() override {}
			bool			LoadFileAny(String path) override;
		};
		
		LocalValue			value;
		LocalStream			stream;
		
		
		bool				ReadFrame();
		bool				ProcessDeviceFrame();
		
	public:
		InputComponent() : stream(this) {}
		
		TypeCls GetValSpecType() const override {return AsTypeCls<V>();}
		bool IsValSpec(TypeCls t) const override {return AsTypeCls<V>() == t;}
		
		// ValSource
		CtxStream&			GetStream(V*) override;
		void				BeginStream(V*) override;
		void				EndStream(V*) override;
		
	};
	
	
	
	#define RTTI_DEV_CTX_COMP(comp, src, sink) \
			RTTI_DECL_4(comp, Component<comp>, \
					src, sink, DevComponent, \
					DevSpec::GetName() + #comp)
	
	class PipeComponent :
		public Component<PipeComponent>,
		public ValSource,
		public ValSink,
		public DevComponent
	{
		RTTI_DEV_CTX_COMP(PipeComponent, ValSource, ValSink)
		VIS_COMP_1_1(Val, Val)
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
		
		// ComponentBase
		void				Initialize() override {DevComponent::Initialize();}
		void				Uninitialize() override {DevComponent::Uninitialize();}
		TypeCls				GetValSpecType() const override {return AsTypeCls<V>();}
		bool				IsValSpec(TypeCls t) const override {return AsTypeCls<V>() == t;}
		
		// DevSink
		Format				GetFormat(V*) override;
		Value&				GetValue(V*) override;
		
		// DevSource
		CtxStream&			GetStream(V*) override;
		void				BeginStream(V*) override;
		void				EndStream(V*) override;
		
		// DevComponent
		bool				LoadAsInput(const DevCompConf& in) override;
		void				UpdateTexBuffers() override {DevComponent::template UpdateTexBuffersValT<ValSpec>();}
		bool				IsEmptyStream() const override {return src_value.IsEmpty() && sink_value.IsEmpty();}
		void				ClearStream() override {src_value.ClearBuffer(); sink_value.ClearBuffer();}
		
	};
	
	
};


NAMESPACE_TOPSIDE_END

#endif
