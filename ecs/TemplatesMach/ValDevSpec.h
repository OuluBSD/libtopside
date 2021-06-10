#ifndef _TemplatesMach_ValDevSpec_h_
#define _TemplatesMach_ValDevSpec_h_


NAMESPACE_TOPSIDE_BEGIN





template <class DevSpec, class ValSpec>
struct VD : RTTIBase
{
	RTTI_DECL0(VD)
	static String GetName() {return DevSpec::GetName() + ValSpec::GetName();}
	static String GetPrefix() {return DevSpec::GetPrefix() + ValSpec::GetName();}
	using Val = ValSpec;
	using Dev = DevSpec;
};


// Declare dev context classes
#define IFACE_CTX_CLS(dev, value, prefix) using dev##value##Spec = VD<dev##Spec, value##Spec>;
#define IFACE(value) DEV_IFACE(value)
IFACE_LIST;
#undef IFACE
#undef IFACE_CTX_CLS








#define DEV_VALUE_CTX(dev, value, prefix, format, sample) \
	using prefix##MachT						= ScopeValDevMachT<dev##value##Spec>; \
	using prefix							= prefix##MachT::Value; \
	using prefix##Proxy						= prefix##MachT::Proxy; \
	using prefix##VolatileBuffer			= prefix##MachT::VolatileBuffer; \
	using prefix##Stream					= prefix##MachT::Stream; \
	using prefix##StreamRef					= Ref<prefix##Stream,RefParent1<ComponentBase>>; \
	using prefix##PacketConsumer			= prefix##MachT::PacketConsumer; \
	using prefix##PacketProducer			= prefix##MachT::PacketProducer; \
	using prefix##Ex						= prefix##MachT::Ex; \
	using prefix##Proxy						= prefix##MachT::Proxy; \
	using prefix##PacketBuffer				= prefix##MachT::PacketBuffer; \
	using Simple##prefix					= prefix##MachT::SimpleValue; \
	using SimpleBuffered##prefix			= prefix##MachT::SimpleBufferedValue; \
	using Simple##prefix##Stream			= prefix##MachT::SimpleStream; \
	using SimpleBuffered##prefix##Stream	= prefix##MachT::SimpleBufferedStream;

#define IFACE_CTX(value,	format,		sample) \
	DEV_VALUE_CTX(Center,	value, value,			format, sample) \
	DEV_VALUE_CTX(Accel,	value, Accel##value,	format, sample) \
	DEV_VALUE_CTX(Net,		value, Net##value,		format, sample) \
	DEV_VALUE_CTX(Perma,	value, Perma##value,	format, sample)
IFACE_CTX_LIST
#undef IFACE_CTX
#undef DEV_VALUE_CTX



#define AUDCTX ((AudioSpec*)0)
#define AudCtx AudioSpec*

#define VIDCTX ((VideoSpec*)0)
#define VidCtx VideoSpec*

#define DISCTX ((DisplaySpec*)0)
#define DisCtx DisplaySpec*

#define MDLCTX ((ModelSpec*)0)
#define MdlCtx ModelSpec*

#define STCCTX ((StaticSpec*)0)
#define StcCtx StaticSpec*

#define EVCTX ((EventSpec*)0)
#define EvCtx EventSpec*

#define MIDCTX ((MidiSpec*)0)
#define MidCtx MidiSpec*

#define HUMCTX ((HumanSpec*)0)
#define HumCtx HumanSpec*

#define ORDCTX ((OrderSpec*)0)
#define OrdCtx OrderSpec*

#define RCPCTX ((ReceiptSpec*)0)
#define RcpCtx ReceiptSpec*



NAMESPACE_TOPSIDE_END


#endif
