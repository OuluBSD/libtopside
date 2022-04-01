#ifndef _AtomLocal_Generated_h_
#define _AtomLocal_Generated_h_

// This file is generated. Do not modify this file.
// Last modified: 2022.4.1 19:22:00

namespace TS {

namespace Parallel {

class TestPollerSink : public VoidPollerSinkBase {

public:
	RTTI_DECL1(TestPollerSink, VoidPollerSinkBase)
	COPY_PANIC(TestPollerSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.test.poller")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioDecoderSrc : public FfmpegAtomBase {

public:
	RTTI_DECL1(AudioDecoderSrc, FfmpegAtomBase)
	COPY_PANIC(AudioDecoderSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("perma.audio.source.decoder")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioSplitter : public SplitterBase {

public:
	RTTI_DECL1(AudioSplitter, SplitterBase)
	COPY_PANIC(AudioSplitter)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.src")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.src.center")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioSplitterUser : public SplitterBase {

public:
	RTTI_DECL1(AudioSplitterUser, SplitterBase)
	COPY_PANIC(AudioSplitterUser)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.src")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.src.center.user")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioJoiner : public JoinerBase {

public:
	RTTI_DECL1(AudioJoiner, JoinerBase)
	COPY_PANIC(AudioJoiner)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink.center")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioJoinerUser : public JoinerBase {

public:
	RTTI_DECL1(AudioJoinerUser, JoinerBase)
	COPY_PANIC(AudioJoinerUser)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink.center.user")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioJoiner2User : public JoinerBase {

public:
	RTTI_DECL1(AudioJoiner2User, JoinerBase)
	COPY_PANIC(AudioJoiner2User)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink2.center.user")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagSCREEN
class VideoDbgSrc : public VideoGenBase {

public:
	RTTI_DECL1(VideoDbgSrc, VideoGenBase)
	COPY_PANIC(VideoDbgSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.src.dbg_generator")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined HAVE_OPENCV
class WebcamPipe : public OpenCVBase {

public:
	RTTI_DECL1(WebcamPipe, OpenCVBase)
	COPY_PANIC(WebcamPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.webcam.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined HAVE_OPENCV
class WebcamAtom : public OpenCVBase {

public:
	RTTI_DECL1(WebcamAtom, OpenCVBase)
	COPY_PANIC(WebcamAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.webcam")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class AudioLoaderAtom : public FfmpegAtomBase {

public:
	RTTI_DECL1(AudioLoaderAtom, FfmpegAtomBase)
	COPY_PANIC(AudioLoaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class VideoLoaderAtom : public FfmpegAtomBase {

public:
	RTTI_DECL1(VideoLoaderAtom, FfmpegAtomBase)
	COPY_PANIC(VideoLoaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class EventStatePipe : public EventStateBase {

public:
	RTTI_DECL1(EventStatePipe, EventStateBase)
	COPY_PANIC(EventStatePipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("state.event.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

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

#if defined flagSCREEN
class OglCustomer : public CustomerBase {

public:
	RTTI_DECL1(OglCustomer, CustomerBase)
	COPY_PANIC(OglCustomer)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.customer")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class SdlEventAtomPipe : public SDL2EventsBase {

public:
	RTTI_DECL1(SdlEventAtomPipe, SDL2EventsBase)
	COPY_PANIC(SdlEventAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.event.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class SdlEventAtom : public SDL2EventsBase {

public:
	RTTI_DECL1(SdlEventAtom, SDL2EventsBase)
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

class TestEventSrcPipe : public TestEventSrcBase {

public:
	RTTI_DECL1(TestEventSrcPipe, TestEventSrcBase)
	COPY_PANIC(TestEventSrcPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("event.src.test.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagSCREEN
class SdlImageLoader : public SDL2ImageBase {

public:
	RTTI_DECL1(SdlImageLoader, SDL2ImageBase)
	COPY_PANIC(SdlImageLoader)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.image.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class VolumeLoaderAtom : public VolumeLoaderBase {

public:
	RTTI_DECL1(VolumeLoaderAtom, VolumeLoaderBase)
	COPY_PANIC(VolumeLoaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.volume.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlFboAtomSA : public SDL2OglScreenBase {

public:
	RTTI_DECL1(SdlFboAtomSA, SDL2OglScreenBase)
	COPY_PANIC(SdlFboAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlFboPipe : public SDL2OglScreenBase {

public:
	RTTI_DECL1(SdlFboPipe, SDL2OglScreenBase)
	COPY_PANIC(SdlFboPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlFboPipeSide : public SDL2OglScreenBase {

public:
	RTTI_DECL1(SdlFboPipeSide, SDL2OglScreenBase)
	COPY_PANIC(SdlFboPipeSide)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.pipe.side")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlFboAtom : public SDL2OglScreenBase {

public:
	RTTI_DECL1(SdlFboAtom, SDL2OglScreenBase)
	COPY_PANIC(SdlFboAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlVideoAtomPipe : public SDL2CpuScreenBase {

public:
	RTTI_DECL1(SdlVideoAtomPipe, SDL2CpuScreenBase)
	COPY_PANIC(SdlVideoAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlVideoProgAtom : public SDL2CpuScreenBase {

public:
	RTTI_DECL1(SdlVideoProgAtom, SDL2CpuScreenBase)
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
class SdlVideoAtomSA : public SDL2CpuScreenBase {

public:
	RTTI_DECL1(SdlVideoAtomSA, SDL2CpuScreenBase)
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
class SdlVideoAtom : public SDL2CpuScreenBase {

public:
	RTTI_DECL1(SdlVideoAtom, SDL2CpuScreenBase)
	COPY_PANIC(SdlVideoAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglShaderPipe : public OglShaderBase {

public:
	RTTI_DECL1(OglShaderPipe, OglShaderBase)
	COPY_PANIC(OglShaderPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.source.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglShaderAtom : public OglShaderBase {

public:
	RTTI_DECL1(OglShaderAtom, OglShaderBase)
	COPY_PANIC(OglShaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.source")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglShaderAtomSA : public OglShaderBase {

public:
	RTTI_DECL1(OglShaderAtomSA, OglShaderBase)
	COPY_PANIC(OglShaderAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.source.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglTextureSource : public OglTextureBase {

public:
	RTTI_DECL1(OglTextureSource, OglTextureBase)
	COPY_PANIC(OglTextureSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.image")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglVolumeSource : public OglTextureBase {

public:
	RTTI_DECL1(OglVolumeSource, OglTextureBase)
	COPY_PANIC(OglVolumeSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.volume")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglAudioSink : public OglFboReaderBase {

public:
	RTTI_DECL1(OglAudioSink, OglFboReaderBase)
	COPY_PANIC(OglAudioSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.center.audio")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglKeyboardSource : public OglKeyboardBase {

public:
	RTTI_DECL1(OglKeyboardSource, OglKeyboardBase)
	COPY_PANIC(OglKeyboardSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.keyboard")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglAudioSource : public OglAudioBase {

public:
	RTTI_DECL1(OglAudioSource, OglAudioBase)
	COPY_PANIC(OglAudioSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.audio")
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

using AudioDecoderSrcRef = Ref<AudioDecoderSrc, AtomParent>;

using AudioDbgSrcRef = Ref<AudioDbgSrc, AtomParent>;

using AudioSplitterRef = Ref<AudioSplitter, AtomParent>;

using AudioSplitterUserRef = Ref<AudioSplitterUser, AtomParent>;

using AudioJoinerRef = Ref<AudioJoiner, AtomParent>;

using AudioJoinerUserRef = Ref<AudioJoinerUser, AtomParent>;

using AudioJoiner2UserRef = Ref<AudioJoiner2User, AtomParent>;

#if defined flagSCREEN
using VideoDbgSrcRef = Ref<VideoDbgSrc, AtomParent>;
#endif

#if defined HAVE_OPENCV
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

using OglCustomerRef = Ref<OglCustomer, AtomParent>;

#if defined flagSDL2
using SdlContextAtomRef = Ref<SdlContextAtom, AtomParent>;
#endif

using SdlEventAtomPipeRef = Ref<SdlEventAtomPipe, AtomParent>;

using SdlEventAtomRef = Ref<SdlEventAtom, AtomParent>;

using EventStateRef = Ref<EventState, AtomParent>;

using TestEventSrcPipeRef = Ref<TestEventSrcPipe, AtomParent>;

using SdlImageLoaderRef = Ref<SdlImageLoader, AtomParent>;

using VolumeLoaderAtomRef = Ref<VolumeLoaderAtom, AtomParent>;

using SdlFboAtomSARef = Ref<SdlFboAtomSA, AtomParent>;

using SdlFboPipeRef = Ref<SdlFboPipe, AtomParent>;

using SdlFboPipeSideRef = Ref<SdlFboPipeSide, AtomParent>;

using SdlFboAtomRef = Ref<SdlFboAtom, AtomParent>;

using SdlVideoAtomPipeRef = Ref<SdlVideoAtomPipe, AtomParent>;

using SdlVideoProgAtomRef = Ref<SdlVideoProgAtom, AtomParent>;

using SdlVideoAtomSARef = Ref<SdlVideoAtomSA, AtomParent>;

using SdlVideoAtomRef = Ref<SdlVideoAtom, AtomParent>;

using SdlAudioAtomRef = Ref<SdlAudioAtom, AtomParent>;

using OglShaderPipeRef = Ref<OglShaderPipe, AtomParent>;

using OglShaderAtomRef = Ref<OglShaderAtom, AtomParent>;

using OglShaderAtomSARef = Ref<OglShaderAtomSA, AtomParent>;

using OglTextureSourceRef = Ref<OglTextureSource, AtomParent>;

using OglVolumeSourceRef = Ref<OglVolumeSource, AtomParent>;

using OglAudioSinkRef = Ref<OglAudioSink, AtomParent>;

using OglKeyboardSourceRef = Ref<OglKeyboardSource, AtomParent>;

using OglAudioSourceRef = Ref<OglAudioSource, AtomParent>;

using CpuKeyboardSourceRef = Ref<CpuKeyboardSource, AtomParent>;

}

}



#endif
