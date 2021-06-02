#ifndef _TemplatesMach_Defs_h_
#define _TemplatesMach_Defs_h_


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


#endif
