#ifndef _AtomLocal_Generated_h_
#define _AtomLocal_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

#if defined flagSCREEN
class EcsEventsAtom : public EcsEventsBase {

public:
	RTTI_DECL1(EcsEventsAtom, EcsEventsBase)
	COPY_PANIC(EcsEventsAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ecs.system.events")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class EcsCpuVideoPipe : public EcsVideoBase {

public:
	RTTI_DECL1(EcsCpuVideoPipe, EcsVideoBase)
	COPY_PANIC(EcsCpuVideoPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.ecs.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class EcsProgVideo : public EcsVideoBase {

public:
	RTTI_DECL1(EcsProgVideo, EcsVideoBase)
	COPY_PANIC(EcsProgVideo)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.prog.ecs")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class EcsOglFboPipe : public EcsVideoBase {

public:
	RTTI_DECL1(EcsOglFboPipe, EcsVideoBase)
	COPY_PANIC(EcsOglFboPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.ecs.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class EcsCpuVideo : public EcsVideoBase {

public:
	RTTI_DECL1(EcsCpuVideo, EcsVideoBase)
	COPY_PANIC(EcsCpuVideo)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.ecs")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class EcsOglFbo : public EcsVideoBase {

public:
	RTTI_DECL1(EcsOglFbo, EcsVideoBase)
	COPY_PANIC(EcsOglFbo)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.ecs")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class SdlEventAtom : public Sdl2EventsBase {

public:
	RTTI_DECL1(SdlEventAtom, Sdl2EventsBase)
	COPY_PANIC(SdlEventAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.event")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class EventState : public EventStateBase {

public:
	RTTI_DECL1(EventState, EventStateBase)
	COPY_PANIC(EventState)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("state.event")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagSCREEN
class SdlOglFboPipeSide : public Sdl2OglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboPipeSide, Sdl2OglVideoSinkDevice)
	COPY_PANIC(SdlOglFboPipeSide)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.sink.side")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlVideoProgAtom : public Sdl2CenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlVideoProgAtom, Sdl2CenterVideoSinkDevice)
	COPY_PANIC(SdlVideoProgAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video.prog")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlVideoAtomSA : public Sdl2CenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlVideoAtomSA, Sdl2CenterVideoSinkDevice)
	COPY_PANIC(SdlVideoAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class CpuKeyboardSource : public CpuKeyboardBase {

public:
	RTTI_DECL1(CpuKeyboardSource, CpuKeyboardBase)
	COPY_PANIC(CpuKeyboardSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.keyboard")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

using CenterCustomerRef = Ref<CenterCustomer, AtomParent>;

using TestRealtimeSrcRef = Ref<TestRealtimeSrc, AtomParent>;

using TestRealtimeSinkRef = Ref<TestRealtimeSink, AtomParent>;

using TestPollerSinkRef = Ref<TestPollerSink, AtomParent>;

using PortaudioSinkRef = Ref<PortaudioSink, AtomParent>;

#if defined flagFFMPEG
using AudioDecoderSrcRef = Ref<AudioDecoderSrc, AtomParent>;
#endif

using AudioDbgSrcRef = Ref<AudioDbgSrc, AtomParent>;

using AudioSplitterRef = Ref<AudioSplitter, AtomParent>;

using AudioSplitterUserRef = Ref<AudioSplitterUser, AtomParent>;

using AudioJoinerRef = Ref<AudioJoiner, AtomParent>;

using AudioJoinerUserRef = Ref<AudioJoinerUser, AtomParent>;

using AudioJoiner2UserRef = Ref<AudioJoiner2User, AtomParent>;

#if defined flagSCREEN
using VideoDbgSrcRef = Ref<VideoDbgSrc, AtomParent>;
#endif

#if defined flagLINUX
using WebcamPipeRef = Ref<WebcamPipe, AtomParent>;
#endif

using WebcamAtomRef = Ref<WebcamAtom, AtomParent>;

using AudioLoaderAtomRef = Ref<AudioLoaderAtom, AtomParent>;

using VideoLoaderAtomRef = Ref<VideoLoaderAtom, AtomParent>;

using EventStatePipeRef = Ref<EventStatePipe, AtomParent>;

using EcsEventsAtomRef = Ref<EcsEventsAtom, AtomParent>;

using EcsCpuVideoPipeRef = Ref<EcsCpuVideoPipe, AtomParent>;

using EcsProgVideoRef = Ref<EcsProgVideo, AtomParent>;

using EcsOglFboPipeRef = Ref<EcsOglFboPipe, AtomParent>;

using EcsCpuVideoRef = Ref<EcsCpuVideo, AtomParent>;

using EcsOglFboRef = Ref<EcsOglFbo, AtomParent>;

using X11SwFboProgRef = Ref<X11SwFboProg, AtomParent>;

#if defined flagOGL
using X11OglFboProgRef = Ref<X11OglFboProg, AtomParent>;
#endif

#if defined flagSDL2
using SdlOglShaderProgRef = Ref<SdlOglShaderProg, AtomParent>;
#endif

using X11SwShaderPipeRef = Ref<X11SwShaderPipe, AtomParent>;

using X11OglShaderPipeRef = Ref<X11OglShaderPipe, AtomParent>;

using SdlOglShaderPipeRef = Ref<SdlOglShaderPipe, AtomParent>;

using X11SwFboAtomPipeRef = Ref<X11SwFboAtomPipe, AtomParent>;

using X11OglFboAtomPipeRef = Ref<X11OglFboAtomPipe, AtomParent>;

using SdlOglFboAtomPipeRef = Ref<SdlOglFboAtomPipe, AtomParent>;

using OglCustomerRef = Ref<OglCustomer, AtomParent>;

using SdlContextAtomRef = Ref<SdlContextAtom, AtomParent>;

using SdlEventAtomPipeRef = Ref<SdlEventAtomPipe, AtomParent>;

using SdlEventAtomRef = Ref<SdlEventAtom, AtomParent>;

using EventStateRef = Ref<EventState, AtomParent>;

using TestEventSrcPipeRef = Ref<TestEventSrcPipe, AtomParent>;

using SdlImageLoaderRef = Ref<SdlImageLoader, AtomParent>;

using VolumeLoaderAtomRef = Ref<VolumeLoaderAtom, AtomParent>;

using X11VideoAtomPipeRef = Ref<X11VideoAtomPipe, AtomParent>;

using X11OglVideoAtomPipeRef = Ref<X11OglVideoAtomPipe, AtomParent>;

using X11OglFboAtomSARef = Ref<X11OglFboAtomSA, AtomParent>;

using X11SwVideoAtomPipeRef = Ref<X11SwVideoAtomPipe, AtomParent>;

using X11SwFboAtomSARef = Ref<X11SwFboAtomSA, AtomParent>;

using SdlOglFboAtomSARef = Ref<SdlOglFboAtomSA, AtomParent>;

using SdlOglFboPipeRef = Ref<SdlOglFboPipe, AtomParent>;

using SdlOglFboPipeSideRef = Ref<SdlOglFboPipeSide, AtomParent>;

using SdlOglFboAtomRef = Ref<SdlOglFboAtom, AtomParent>;

using SdlVideoAtomPipeRef = Ref<SdlVideoAtomPipe, AtomParent>;

using SdlVideoProgAtomRef = Ref<SdlVideoProgAtom, AtomParent>;

using SdlVideoAtomSARef = Ref<SdlVideoAtomSA, AtomParent>;

using SdlVideoAtomRef = Ref<SdlVideoAtom, AtomParent>;

using SdlAudioAtomRef = Ref<SdlAudioAtom, AtomParent>;

using SdlOglShaderAtomRef = Ref<SdlOglShaderAtom, AtomParent>;

using SdlOglShaderAtomSARef = Ref<SdlOglShaderAtomSA, AtomParent>;

using SdlOglTextureSourceRef = Ref<SdlOglTextureSource, AtomParent>;

using SdlOglVolumeSourceRef = Ref<SdlOglVolumeSource, AtomParent>;

using SdlOglAudioSinkRef = Ref<SdlOglAudioSink, AtomParent>;

using SdlOglKeyboardSourceRef = Ref<SdlOglKeyboardSource, AtomParent>;

using SdlOglAudioSourceRef = Ref<SdlOglAudioSource, AtomParent>;

using CpuKeyboardSourceRef = Ref<CpuKeyboardSource, AtomParent>;

}

}



#endif
