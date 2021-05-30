#ifndef _TemplatesLib_Context_h_
#define _TemplatesLib_Context_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Dev>
struct ContextLibT {
	using DevCtx		= Dev;
	using Ctx			= typename Dev::Value;
	using C				= Ctx;
	using Mach			= ContextMachT<Dev>;
	using Ecs			= ContextEcsT<Dev>;
	using Format = typename Ctx::Format;
	using ValueBase = typename Ctx::ValueBase;
	using StreamBase = typename Ctx::StreamBase;
	using Value = typename Mach::Value;
	using CtxStream = typename Mach::Stream;
	using ExchangePoint = typename Mach::ExchangePoint;
	using SimpleBufferedValue = typename Mach::SimpleBufferedValue;
	using SimpleBufferedStream = typename Mach::SimpleBufferedStream;
	using BaseSink = typename Ecs::BaseSink;
	using BaseSource = typename Ecs::BaseSource;
	
	
	#define RTTI_CTX_LIB_INPUT_COMP(comp, src) \
			RTTI_DECL_2(comp, Component<comp>, src, Ctx::GetName() + #comp)
	
	class InputComponent :
		public Component<InputComponent>,
		public BaseSource
	{
		RTTI_CTX_LIB_INPUT_COMP(InputComponent, BaseSource)
		VIS_COMP_1_0(Base)
		COPY_PANIC(InputComponent)
		IFACE_GENERIC
		void Visit(RuntimeVisitor& vis) override {}
		
		
		struct LocalBase : public SimpleBufferedValue {
			
		};
		
		struct LocalStream : public SimpleBufferedStream {
			RTTI_DECL1(LocalStream, SimpleBufferedStream)
			InputComponent& par;
			LocalStream(InputComponent* par) :
				par(*par),
				SimpleBufferedStream(par->value) {}
			bool			IsOpen() const override;
			bool			Open(int fmt_idx) override;
			void			Close() override {par.value.Clear();}
			bool			IsEof() override {return false;}
			bool			ReadFrame() override {return par.ReadFrame();}
			bool			ProcessFrame() override {return par.ProcessDeviceFrame();}
			bool			ProcessOtherFrame() override {return false;}
			void			ClearPacketData() override {}
			bool			LoadFileAny(String path) override;
		};
		
		LocalBase			value;
		LocalStream			stream;
		
		
		bool				ReadFrame();
		bool				ProcessDeviceFrame();
		
	public:
		InputComponent() : stream(this) {}
		
		TypeCls GetContextType() const override {return AsTypeCls<C>();}
		bool IsContext(TypeCls t) const override {return AsTypeCls<C>() == t;}
		
		// BaseSource
		CtxStream&			GetStream(C*) override;
		void				BeginStream(C*) override;
		void				EndStream(C*) override;
		
	};
	
	
	
};


NAMESPACE_TOPSIDE_END

#endif
