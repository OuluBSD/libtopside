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

#define DEV_FULL_LIST \
	DEV(Center, , ctr) \
	DEV(Accel, Accel, acl) \
	DEV(Net, Net, net) \
	DEV(Perma, Perma, prm)

#define DEV_IFACE(value) \
	IFACE_CTX_CLS(Center,	value,	value) \
	IFACE_CTX_CLS(Accel,	value,	Accel##value) \
	IFACE_CTX_CLS(Net,		value,	Net##value) \
	IFACE_CTX_CLS(Perma,	value,	Perma##value)


#define CLS_DEVMACH				ScopeDevMachT<DevSpec>
#define TMPL_VALMACH(x)	template <class ValSpec> x ScopeValMachT<ValSpec>::
#define TMPL_VALCORE(x)	template <class ValSpec> x ScopeValCoreT<ValSpec>::
#define TMPL_VALLIB(x)	template <class ValSpec> x ScopeValLibT<ValSpec>::
#define TMPL_DEVMACH(x)	template <class DevSpec> x ScopeDevMachT<DevSpec>::
#define TMPL_DEVCORE(x)	template <class DevSpec> x ScopeDevCoreT<DevSpec>::
#define TMPL_DEVLIB(x)	template <class DevSpec> x ScopeDevLibT<DevSpec>::
#define TMPL_VALDEVMACH(x)	template <class ValDevSpec> x ScopeValDevMachT<ValDevSpec>::
#define TMPL_VALDEVCORE(x)	template <class ValDevSpec> x ScopeValDevCoreT<ValDevSpec>::
#define TMPL_VALDEVLIB(x)	template <class ValDevSpec> x ScopeValDevLibT<ValDevSpec>::
#define TMPL_CONVDEVLIB(x)	template <class ValSpec, class FromDevSpec, class ToDevSpec> x ScopeConvDevLibT<ValSpec,FromDevSpec,ToDevSpec>::
#define USING_VALMACH(x) using x = typename ScopeValMachT<ValSpec>::x;
#define USING_VALCORE(x) using x = typename ScopeValCoreT<ValSpec>::x;
#define USING_VALLIB(x) using x = typename ScopeValLibT<ValSpec>::x;
#define USING_DEVMACH(x) using x = typename ScopeDevMachT<DevSpec>::x;
#define USING_DEVCORE(x) using x = typename ScopeDevCoreT<DevSpec>::x;
#define USING_DEVLIB(x) using x = typename ScopeDevLibT<DevSpec>::x;
#define USING_VALDEVMACH(x) using x = typename ScopeValDevMachT<ValDevSpec>::x;
#define USING_VALDEVCORE(x) using x = typename ScopeValDevCoreT<ValDevSpec>::x;
#define USING_VALDEVLIB(x) using x = typename ScopeValDevLibT<ValDevSpec>::x;




NAMESPACE_TOPSIDE_BEGIN

class InterfaceSinkBase;
class Entity;
class EntityStore;
class Pool;

NAMESPACE_TOPSIDE_END

#endif
