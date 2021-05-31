#ifndef _TemplatesMach_Defs_h_
#define _TemplatesMach_Defs_h_


NAMESPACE_TOPSIDE_BEGIN


#define IFACE_LIST \
	IFACE(Audio) \
	IFACE(Model) \
	IFACE(Static) \
	IFACE(Photo) \
	IFACE(Video) \
	IFACE(Display) \
	IFACE(Event) \
	IFACE(Midi) \
	IFACE(Human)

#define DEV_LIST \
	DEV(Center) \
	DEV(Accel) \
	DEV(Net) \
	DEV(Perma)

#define DEV_IFACE(value) \
	IFACE_CTX_CLS(Center,	value,	value) \
	IFACE_CTX_CLS(Accel,	value,	Accel##value) \
	IFACE_CTX_CLS(Net,		value,	Net##value) \
	IFACE_CTX_CLS(Perma,	value,	Perma##value)

#define IFACE_CTX_LIST \
	IFACE_CTX(Audio,		TD1TimeSeries,			SoundSample) \
	IFACE_CTX(Model,		TD1OnceMulti4,			ModelSample) \
	IFACE_CTX(Static,		TD3Once,				MaterialSample) \
	IFACE_CTX(Photo,		TD2Once,				LightSampleFD) \
	IFACE_CTX(Video,		TD2TimeSeries,			LightSampleFD) \
	IFACE_CTX(Display,		TD2TimeSeries,			LightSampleFD) \
	IFACE_CTX(Event,		TD1SparseTimeSeries,	EventSample) \
	IFACE_CTX(Midi,			TD1SparseTimeSeries,	MidiSample) \
	IFACE_CTX(Human,		TD1SparseTimeSeries,	HumanSample)
	
	/*
	IFACE_CTX(Media,		AVTimeSeries,			AVSample) \
	IFACE_CTX(AudioFD,		T2DTimeSeries,			SoundSampleFD) \
	IFACE_CTX(Image,		T2D,					LightSampleFD) \
	IFACE_CTX(ImageFD,		T2DFD,					LightSampleFD) \
	IFACE_CTX(VideoFD,		T2DTimeSeriesFD,		LightSampleFD) \
	IFACE_CTX(Vertices,		T1D,					SpaceSample) \
	IFACE_CTX(Triangles,	T1D,					VertexSample) \
	IFACE_CTX(Skeleton,		T1D,					BoneSample) \
	IFACE_CTX(Physics,		T1DSparseTimeSeries,	PhysicsSample) \
	IFACE_CTX(Volumetric,	T3D,					MaterialSample) \
	IFACE_CTX(VolumetricFD,	T3DFD,					MaterialSampleFD)*/

// e.g. CPU context
class CenterContext {
	
	
};

// e.g. GPU context
class AccelContext {
	
	
};

// e.g. exchange over tcp connection
class NetContext {
	
	
};

// e.g. file system storage
class PermaContext {
	
	
};



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




/*
struct DummyValueBase			: RTTIBase {RTTI_DECL0(DummyValueBase)};
struct DummyStreamBase			: RefScopeEnabler<DummyStreamBase,ComponentBase> {RTTI_DECL_R0(DummyStreamBase)};
struct DummyCustomSystemBase	: RTTIBase {RTTI_DECL0(DummyCustomSystemBase)};
struct DummyCustomSinkBase		: RTTIBase {RTTI_DECL0(DummyCustomSinkBase)};

struct HumanCustomSinkBase : RTTIBase {
	RTTI_DECL0(HumanCustomSinkBase)
	virtual ViewableRef GetViewable();
	virtual TransformRef GetTransform();
};

class Audio;
class Video;
class AudioStream;
class VideoStream;

struct AVBase : RTTIBase {
	RTTI_DECL0(AVBase)
	virtual Audio& GetAudio() {THROW(Exc("pure function called"));}
	virtual Video& GetVideo() {THROW(Exc("pure function called"));}
};

struct AVStreamBase : RTTIBase {
	RTTI_DECL0(AVStreamBase)
	
	virtual AudioStream& GetAudioStream() {THROW(Exc("pure function called"));}
	virtual VideoStream& GetVideoStream() {THROW(Exc("pure function called"));}
};*/



// Make value context classes
#define IFACE_CTX(value, format, sample) \
	using value##Format = format < sample >; \
	class value##Context: RTTIBase { \
		public: \
		RTTI_DECL0(value##Context) \
		static constexpr const char* Name = #value; \
		static String GetName() {return #value;} \
		using Format			= value##Format; \
		using Ctx				= value##Context; \
		using ValueBase			= Topside::CommonValueBase; \
		using StreamBase		= Topside::CommonStreamBase; \
		using SystemBase		= Topside::CommonSystemBase; \
		using SinkBase			= Topside::CommonSinkBase; \
	};
IFACE_CTX_LIST;
#undef IFACE_CTX



// Make data context classes
#define IFACE_CTX(value, format, sample) \
	using value##T = ContextDataT<value##Context>; \
	using value##Packet = value##T::Packet; \
	inline value##Packet Create##value##Packet() {return value##T::CreatePacket();}
IFACE_CTX_LIST;
#undef IFACE_CTX



// Make dev context classes
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
