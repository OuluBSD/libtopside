#ifndef _TemplatesLib_ConvDevScope_h_
#define _TemplatesLib_ConvDevScope_h_

NAMESPACE_TOPSIDE_BEGIN



template <class ValSpec, class FromDevSpec, class ToDevSpec>
struct ScopeConvDevLibT {
	using V = ValSpec;
	using Data = ScopeValMachT<V>;
	using Format = typename Data::Format;
	using Packet = typename Data::Packet;
	
	using From = VD<FromDevSpec, ValSpec>;
	using FMach = ScopeValDevMachT<From>;
	using FCore = ScopeValDevCoreT<From>;
	using FDevMach = ScopeDevMachT<FromDevSpec>;
	using FDevLib = ScopeDevLibT<FromDevSpec>;
	using FromValue = typename FMach::Value;
	using FromStream = typename FMach::Stream;
	using FromSimpleBufferedValue = typename FMach::SimpleBufferedValue;
	using FromSimpleBufferedStream = typename FMach::SimpleBufferedStream;
	using FromSource = typename FCore::ValSource;
	using FromSink = typename FCore::ValSink;
	using FromComponent = typename FDevLib::DevComponent;
	using FromComponentConf = typename FDevMach::DevComponentConf;
	
	using To = VD<ToDevSpec, ValSpec>;
	using TMach = ScopeValDevMachT<To>;
	using TCore = ScopeValDevCoreT<To>;
	using TDevMach = ScopeDevMachT<ToDevSpec>;
	using TDevLib = ScopeDevLibT<ToDevSpec>;
	using ToValue = typename TMach::Value;
	using ToStream = typename TMach::Stream;
	using ToSimpleBufferedValue = typename TMach::SimpleBufferedValue;
	using ToSimpleBufferedStream = typename TMach::SimpleBufferedStream;
	using ToSource = typename TCore::ValSource;
	using ToSink = typename TCore::ValSink;
	using ToComponent = typename TDevLib::DevComponent;
	using ToComponentConf = typename TDevMach::DevComponentConf;
	
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
		//public FromComponent,
		public ToComponent
	{
		RTTI_DECL_4(ConvertComponent, Component<ConvertComponent>,
					FromSink, ToSource/*, FromComponent*/, ToComponent,
					To::GetName() + "ConvertComponent")
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
		
		void				Initialize() override;
		void				Uninitialize() override;
		TypeCls				GetValSpecType() const override {return AsTypeCls<V>();}
		
		
		// ValSink
		Format				GetFormat(V*) override;
		FromValue&			GetValue(V*) override;
		
		// DevSource
		ToStream&			GetStream(V*) override;
		void				BeginStream(V*) override;
		void				EndStream(V*) override;
		
		bool				IsValSpec(TypeCls t) const override {return AsTypeCls<V>() == t;}
		bool				LoadAsInput(const ToComponentConf& in) override;
		//bool				LoadAsInput(const FromComponentConf& in) override;
		void				PreProcess() override;
		void				UpdateDevBuffers() override {
			//FromComponent::template UpdateDevBuffersValT<ValSpec>();
			ToComponent::template UpdateDevBuffersValT<ValSpec>();
		}
		bool				IsEmptyStream() const override {return src_value.IsEmpty() && sink_value.IsEmpty();}
		void				ClearStream() override {src_value.ClearBuffer(); sink_value.ClearBuffer();}
		void				Forward(FwdScope& fwd) override;
		void				ForwardExchange(FwdScope& fwd) override;
		
	};
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
