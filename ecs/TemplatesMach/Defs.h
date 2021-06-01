#ifndef _TemplatesMach_Defs_h_
#define _TemplatesMach_Defs_h_


NAMESPACE_TOPSIDE_BEGIN





// Declare data context classes
#define IFACE_CTX(value, format, sample) \
	using value##T = ContextDataT<value##Context>; \
	using value##Packet = value##T::Packet; \
	inline value##Packet Create##value##Packet() {return value##T::CreatePacket();}
IFACE_CTX_LIST;
#undef IFACE_CTX



// Declare dev context classes
#define IFACE_CTX_CLS(dev, value, prefix) \
	struct dev##value##Context { \
		static String GetPrefix() {return #prefix;} \
		using Value = value##Context; \
		using Dev = dev##Context; \
	};
#define IFACE(value) DEV_IFACE(value)
IFACE_LIST;
#undef IFACE
#undef IFACE_CTX_CLS








#define DEV_VALUE_CTX(dev, value, prefix, format, sample) \
	using prefix##MachT						= ContextMachT<dev##value##Context>; \
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



#define AUDCTX ((AudioContext*)0)
#define AudCtx AudioContext*

#define VIDCTX ((VideoContext*)0)
#define VidCtx VideoContext*

#define DISCTX ((DisplayContext*)0)
#define DisCtx DisplayContext*

#define MDLCTX ((ModelContext*)0)
#define MdlCtx ModelContext*

#define STCCTX ((StaticContext*)0)
#define StcCtx StaticContext*

#define EVCTX ((EventContext*)0)
#define EvCtx EventContext*

#define MIDCTX ((MidiContext*)0)
#define MidCtx MidiContext*

#define HUMCTX ((HumanContext*)0)
#define HumCtx HumanContext*



NAMESPACE_TOPSIDE_END


#endif
