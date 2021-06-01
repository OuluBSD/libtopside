#ifndef _TemplatesMach_ValDefs_h_
#define _TemplatesMach_ValDefs_h_

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

#define IFACE_VAR_LIST \
	IFACE(Audio,	aud) \
	IFACE(Model,	mdl) \
	IFACE(Static,	stc) \
	IFACE(Photo,	pho) \
	IFACE(Video,	vid) \
	IFACE(Display,	dpy) \
	IFACE(Event,	ev) \
	IFACE(Midi,		mid) \
	IFACE(Human,	hum)

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






// Make value context classes
#define IFACE_CTX(value, format, sample) \
	using value##Format = format < sample >; \
	class value##Context : RTTIBase { \
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



NAMESPACE_TOPSIDE_END

#endif
