#ifndef _TemplatesMach_ValSpec_h_
#define _TemplatesMach_ValSpec_h_

NAMESPACE_TOPSIDE_BEGIN





class CommonValueBase : RTTIBase {
public:
	RTTI_DECL0(CommonValueBase);
};


class CommonStreamBase : RTTIBase {
public:
	RTTI_DECL0(CommonStreamBase);
};


class CommonSystemBase : RTTIBase {
public:
	RTTI_DECL0(CommonSystemBase);
};


class CommonSinkBase : RTTIBase {
public:
	RTTI_DECL0(CommonSinkBase);
};



using ModelSample = MultiSample4<SpaceSample,VertexSample,TexLocSample,BoneSample>;
using AVSample = MultiSample2<SoundSample,LightSampleFD>;






// Declare value classes
#define IFACE_CTX(value, format, sample) \
	struct value##Spec : RTTIBase {\
		RTTI_DECL0(value##Spec) \
		static String GetName() {return #value;}\
		using FormatBase		= format < sample >; \
		using ValueBase			= TS::CommonValueBase; \
		using StreamBase		= TS::CommonStreamBase; \
		using SystemBase		= TS::CommonSystemBase; \
		using SinkBase			= TS::CommonSinkBase; \
	}; \
	using value##T = ScopeValMachT<value##Spec>; \
	using value##Packet = value##T::Packet; \
	using value##Format = value##T::Format; \
	inline value##Packet Create##value##Packet(off32 off) {return value##T::CreatePacket(off);}
IFACE_CTX_LIST;
#undef IFACE_CTX



NAMESPACE_TOPSIDE_END

#endif
