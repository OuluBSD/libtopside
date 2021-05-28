#ifndef _TemplatesLib_Context_h_
#define _TemplatesLib_Context_h_

NAMESPACE_TOPSIDE_BEGIN


template <class Ctx>
struct ContextLibT {
	using C = Ctx;
	using Format = typename Ctx::Format;
	using ValueBase = typename Ctx::ValueBase;
	using StreamBase = typename Ctx::StreamBase;
	using CustomSystemBase = typename Ctx::CustomSystemBase;
	using Value = typename ContextT<Ctx>::Value;
	using CtxStream = typename ContextT<Ctx>::Stream;
	using ExchangePoint = typename ContextT<Ctx>::ExchangePoint;
	using BaseSink = typename ContextEcsT<Ctx>::BaseSink;
	using BaseSource = typename ContextEcsT<Ctx>::BaseSource;
	
	
	
	class InputComponent :
		public Component<InputComponent>,
		public BaseSource
	{
		RTTI_COMP1(InputComponent, BaseSource)
		VIS_COMP_1_0(Base)
		COPY_PANIC(InputComponent)
		IFACE_GENERIC
		void Visit(RuntimeVisitor& vis) override {}
		
	public:
		
		
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
