#ifndef _TemplatesMach_Defs_h_
#define _TemplatesMach_Defs_h_


NAMESPACE_TOPSIDE_BEGIN


#define LOCAL_CTX(x, format, sample, value_base, stream_base, sys_base, sink_base) \
	using x##Format = format < sample >; \
	class x##Context: RTTIBase { \
		public: \
		RTTI_DECL0(x##Context) \
		static constexpr const char* Name = #x; \
		using Format			= x##Format; \
		using Ctx				= x##Context; \
		using ValueBase			= value_base; \
		using StreamBase		= stream_base; \
		using CustomSystemBase	= sys_base; \
		using CustomSinkBase	= sink_base; \
	}; \
	using x##T = ContextT<x##Context>; \
	using x = x##T::Value; \
	using x##Proxy = x##T::Proxy; \
	using x##Proxy = x##T::Proxy; \
	using x##Packet = x##T::Packet; \
	using x##VolatileBuffer = x##T::VolatileBuffer; \
	using x##Stream = x##T::Stream; \
	using x##PacketConsumer = x##T::PacketConsumer; \
	using x##PacketProducer = x##T::PacketProducer; \
	using x##Ex = x##T::Ex; \
	using x##Proxy = x##T::Proxy; \
	using x##PacketBuffer = x##T::PacketBuffer; \
	using Simple##x = x##T::SimpleValue; \
	using SimpleBuffered##x = x##T::SimpleBufferedValue; \
	using Simple##x##Stream = x##T::SimpleStream; \
	using SimpleBuffered##x##Stream = x##T::SimpleBufferedStream; \
	using x##StreamRef = Ref<x##Stream,RefParent1<ComponentBase>>; \
	inline x##Packet Create##x##Packet() {return x##T::CreatePacket();}



struct DummyValueBase			: RTTIBase {RTTI_DECL0(DummyValueBase)};
struct DummyStreamBase			: RefScopeEnabler<DummyStreamBase,ComponentBase> {RTTI_DECL_R0(DummyStreamBase)};
struct DummyCustomSystemBase	: RTTIBase {RTTI_DECL0(DummyCustomSystemBase)};
struct DummyCustomSinkBase		: RTTIBase {RTTI_DECL0(DummyCustomSinkBase)};




/*
E.g.
 - sound:					T1DTimeSeries<SoundSample>
 - video:					2DTimeSeries<LightSampleFD>
 - image:					2D<LightSampleFD>
 - 3D-model:
	- vertices:				1D<SpaceSample>
	- triangles:			1D<VertexSample>
	- tex-points:			1D<TexLocSample>
	- skeleton bones:		1D<BoneSample>
 - sound fft:				1DTimeSeries<SoundSampleFD>
 - image fft:				2DFD<LightSampleFD>
 - video fft:				2DTimeSeriesFD<LightSampleFD>
 - dev-input:				1DSparseTimeSeries<DeviceSample>
 - physics:					1DSparseTimeSeries<PhysicsSample>
 - 3d volumetric:			3D<MaterialSample>
 - 3d vol fft:				3D<MaterialSampleFD>
 - 3d vol skeleton:			(vertices + bones)
 */


using ModelSample = MultiSample4<SpaceSample,VertexSample,TexLocSample,BoneSample>;
using AVSample = MultiSample2<SoundSample,LightSampleFD>;

#define IFACE_CTX_LIST \
	IFACE_CTX(Audio,		TD1TimeSeries,			SoundSample) \
	IFACE_CTX(Model,		TD1OnceMulti4,			ModelSample) \
	IFACE_CTX(Static,		TD3Once,				MaterialSample) \
	IFACE_CTX(Photo,		TD2Once,				LightSampleFD) \
	IFACE_CTX(Video,		TD2TimeSeries,			LightSampleFD) \
	IFACE_CTX(Display,		TD2TimeSeries,			LightSampleFD) \
	IFACE_CTX(Device,		TD1SparseTimeSeries,	DeviceSample) \
	IFACE_CTX(Midi,			TD1SparseTimeSeries,	MidiSample) \
	/* skip Human here */
	/* skip Media here */
	
	/*IFACE_CTX(AudioFD,		T2DTimeSeries,			SoundSampleFD) \
	IFACE_CTX(Image,		T2D,					LightSampleFD) \
	IFACE_CTX(ImageFD,		T2DFD,					LightSampleFD) \
	IFACE_CTX(VideoFD,		T2DTimeSeriesFD,		LightSampleFD) \
	IFACE_CTX(Vertices,		T1D,					SpaceSample) \
	IFACE_CTX(Triangles,	T1D,					VertexSample) \
	IFACE_CTX(Skeleton,		T1D,					BoneSample) \
	IFACE_CTX(Physics,		T1DSparseTimeSeries,	PhysicsSample) \
	IFACE_CTX(Volumetric,	T3D,					MaterialSample) \
	IFACE_CTX(VolumetricFD,	T3DFD,					MaterialSampleFD)*/



#define IFACE_LIST \
	IFACE(Audio) \
	IFACE(Model) \
	IFACE(Static) \
	IFACE(Photo) \
	IFACE(Video) \
	IFACE(Display) \
	IFACE(Device) \
	IFACE(Midi) \
	IFACE(Human) \
	IFACE(Media) \



#define IFACE_CTX(x,y,z) \
	LOCAL_CTX(x,y,z, DummyValueBase, DummyStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
IFACE_CTX_LIST
#undef IFACE

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

#define DEVCTX ((DeviceContext*)0)
#define DevCtx DeviceContext*

#define MIDCTX ((MidiContext*)0)
#define MidCtx MidiContext*





struct HumanCustomSinkBase :
	RTTIBase
{
	RTTI_DECL0(HumanCustomSinkBase)
	virtual ViewableRef GetViewable();
	virtual TransformRef GetTransform();
};
LOCAL_CTX(Human, TD1SparseTimeSeries, HumanSample, DummyValueBase, DummyStreamBase, DummyCustomSystemBase, HumanCustomSinkBase)
#define HUMCTX ((HumanContext*)0)
#define HumCtx HumanContext*





struct AVBase :
	RTTIBase
{
	RTTI_DECL0(AVBase)
	virtual Audio& GetAudio() = 0;
	virtual Video& GetVideo() = 0;
};

struct AVStreamBase :
	RTTIBase
{
	RTTI_DECL0(AVStreamBase)
	
	virtual AudioStream& GetAudioStream() = 0;
	virtual VideoStream& GetVideoStream() = 0;
};
LOCAL_CTX(Media, AVTimeSeries, AVSample, AVBase, AVStreamBase, DummyCustomSystemBase, DummyCustomSinkBase)
#define MEDCTX ((MediaContext*)0)
#define MedCtx MediaContext*



NAMESPACE_TOPSIDE_END


#endif
