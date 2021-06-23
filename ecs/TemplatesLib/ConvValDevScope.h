#ifndef _TemplatesLib_ConvValDevScope_h_
#define _TemplatesLib_ConvValDevScope_h_

#if 0

NAMESPACE_ECS_BEGIN



template <class ValSpec, class FromDevSpec, class ToDevSpec>
struct ScopeConvValDevLibT {
	using V = ValSpec;
	using Data = ScopeValMachT<V>;
	using Format = typename Data::Format;
	using Packet = typename Data::Packet;
	
	using From = VD<FromDevSpec, ValSpec>;
	using FMach = ScopeValDevMachT<From>;
	using FCore = ScopeValDevCoreT<From>;
	using FDevMach = ScopeDevMachT<FromDevSpec>;
	using FDevCore = ScopeDevCoreT<FromDevSpec>;
	using FDevLib = ScopeDevLibT<FromDevSpec>;
	using FromValue = typename FMach::Value;
	using FromStream = typename FMach::Stream;
	using FromSimpleBufferedValue = typename FMach::SimpleBufferedValue;
	using FromSimpleBufferedStream = typename FMach::SimpleBufferedStream;
	using FromSource = typename FCore::ValSource;
	using FromSink = typename FCore::ValSink;
	using FromComponent = typename FDevLib::StageComponent;
	using FromComponentConf = typename FDevMach::StageComponentConf;
	
	using To = VD<ToDevSpec, ValSpec>;
	using TMach = ScopeValDevMachT<To>;
	using TCore = ScopeValDevCoreT<To>;
	using TDevMach = ScopeDevMachT<ToDevSpec>;
	using TDevCore = ScopeDevCoreT<ToDevSpec>;
	using TDevLib = ScopeDevLibT<ToDevSpec>;
	using ToValue = typename TMach::Value;
	using ToStream = typename TMach::Stream;
	using ToSimpleBufferedValue = typename TMach::SimpleBufferedValue;
	using ToSimpleBufferedStream = typename TMach::SimpleBufferedStream;
	using ToSource = typename TCore::ValSource;
	using ToSink = typename TCore::ValSink;
	using ToComponent = typename TDevLib::StageComponent;
	using ToComponentConf = typename TDevMach::StageComponentConf;
	
	class ConvertComponent;
	
	static String TypeStringT(const char* t) {
		String s;
		s << From::GetPrefix() << "2" << To::GetPrefix() << t;
		return s;
	}
	
	
	
	
	class ConvertExt : public ComponentExtBase {
		
	public:
		RTTI_DECL1(ConvertExt, ComponentExtBase);
		using Ext = ConvertExt;
		using Component = ConvertComponent;
		
	};
	
	class ConvertComponent :
		public Component<ConvertComponent, FromSink, ToSource, ConvertExt>,
		public ToComponent
	{
	public:
		using ComponentT = Component<ConvertComponent, FromSink, ToSource, ConvertExt>;
		RTTI_DECL_2(ConvertComponent, ComponentT, ToComponent, To::GetName() + "ConvertComponent")
		COPY_PANIC(ConvertComponent)
		IFACE_GENERIC
		COMP_DEF_VISIT
		COMP_MAKE_ACTION_BEGIN
			COMP_MAKE_ACTION_FALSE_TO_TRUE(FromDevSpec::GetNameLower() + "." + ToDevSpec::GetNameLower() + ".conv")
		COMP_MAKE_ACTION_END
		
	private:
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
		LocalSink			sink_value;
		LocalSource			src_value;
		LocalStream			stream;
		
	public:
		ConvertComponent() : stream(this) {}
		
		void				Initialize() override;
		void				Uninitialize() override;
		TypeCls				GetValSpec() const override {return AsTypeCls<V>();}
		
		// ValSink
		FromValue&			GetValue(V*) override;
		
		// DevSource
		ToStream&			GetStream(V*) override;
		
		bool				IsValSpec(TypeCls t) const override {return AsTypeCls<V>() == t;}
		bool				LoadAsInput(const StageComponentConf& in) override;
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


NAMESPACE_ECS_END

#endif
#endif
