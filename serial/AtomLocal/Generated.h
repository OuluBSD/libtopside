#ifndef _AtomLocal_Generated_h_
#define _AtomLocal_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Serial {

class CenterCustomer : public Atom<CenterCustomer>, public CustomerBase {

public:
	RTTI_DECL2(CenterCustomer, AtomT, CustomerBase)
	COPY_PANIC(CenterCustomer)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.customer")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class TestRealtimeSrc : public Atom<TestRealtimeSrc>, public RollingValueBase {

public:
	RTTI_DECL2(TestRealtimeSrc, AtomT, RollingValueBase)
	COPY_PANIC(TestRealtimeSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.test")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class TestRealtimeSink : public Atom<TestRealtimeSink>, public VoidSinkBase {

public:
	RTTI_DECL2(TestRealtimeSink, AtomT, VoidSinkBase)
	COPY_PANIC(TestRealtimeSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.test.realtime")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class TestPollerSink : public Atom<TestPollerSink>, public VoidPollerSinkBase {

public:
	RTTI_DECL2(TestPollerSink, AtomT, VoidPollerSinkBase)
	COPY_PANIC(TestPollerSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.test.poller")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioHardwareSink : public Atom<AudioHardwareSink>, public PortaudioSink {

public:
	RTTI_DECL2(AudioHardwareSink, AtomT, PortaudioSink)
	COPY_PANIC(AudioHardwareSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.hw")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioDecoderSrc : public Atom<AudioDecoderSrc>, public FfmpegAtomBase {

public:
	RTTI_DECL2(AudioDecoderSrc, AtomT, FfmpegAtomBase)
	COPY_PANIC(AudioDecoderSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("perma.audio.source.decoder")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioDbgSrc : public Atom<AudioDbgSrc>, public AudioGenBase {

public:
	RTTI_DECL2(AudioDbgSrc, AtomT, AudioGenBase)
	COPY_PANIC(AudioDbgSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.dbg_generator")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioSplitter : public Atom<AudioSplitter>, public SplitterBase {

public:
	RTTI_DECL2(AudioSplitter, AtomT, SplitterBase)
	COPY_PANIC(AudioSplitter)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.src")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.src.center")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioSplitterUser : public Atom<AudioSplitterUser>, public SplitterBase {

public:
	RTTI_DECL2(AudioSplitterUser, AtomT, SplitterBase)
	COPY_PANIC(AudioSplitterUser)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.src")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.src.center.user")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioJoiner : public Atom<AudioJoiner>, public JoinerBase {

public:
	RTTI_DECL2(AudioJoiner, AtomT, JoinerBase)
	COPY_PANIC(AudioJoiner)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink.center")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioJoinerUser : public Atom<AudioJoinerUser>, public JoinerBase {

public:
	RTTI_DECL2(AudioJoinerUser, AtomT, JoinerBase)
	COPY_PANIC(AudioJoinerUser)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink.center.user")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioJoiner2User : public Atom<AudioJoiner2User>, public JoinerBase {

public:
	RTTI_DECL2(AudioJoiner2User, AtomT, JoinerBase)
	COPY_PANIC(AudioJoiner2User)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink2.center.user")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagSCREEN
class VideoDbgSrc : public Atom<VideoDbgSrc>, public VideoGenBase {

public:
	RTTI_DECL2(VideoDbgSrc, AtomT, VideoGenBase)
	COPY_PANIC(VideoDbgSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.src.dbg_generator")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined HAVE_OPENCV
class WebcamPipe : public Atom<WebcamPipe>, public OpenCVBase {

public:
	RTTI_DECL2(WebcamPipe, AtomT, OpenCVBase)
	COPY_PANIC(WebcamPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.webcam.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined HAVE_OPENCV
class WebcamAtom : public Atom<WebcamAtom>, public OpenCVBase {

public:
	RTTI_DECL2(WebcamAtom, AtomT, OpenCVBase)
	COPY_PANIC(WebcamAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.webcam")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class AudioLoaderAtom : public Atom<AudioLoaderAtom>, public FfmpegAtomBase {

public:
	RTTI_DECL2(AudioLoaderAtom, AtomT, FfmpegAtomBase)
	COPY_PANIC(AudioLoaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class VideoLoaderAtom : public Atom<VideoLoaderAtom>, public FfmpegAtomBase {

public:
	RTTI_DECL2(VideoLoaderAtom, AtomT, FfmpegAtomBase)
	COPY_PANIC(VideoLoaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class EventStatePipe : public Atom<EventStatePipe>, public EventStateBase {

public:
	RTTI_DECL2(EventStatePipe, AtomT, EventStateBase)
	COPY_PANIC(EventStatePipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("state.event.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagSCREEN
class EcsEventsAtom : public Atom<EcsEventsAtom>, public EcsEventsBase {

public:
	RTTI_DECL2(EcsEventsAtom, AtomT, EcsEventsBase)
	COPY_PANIC(EcsEventsAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ecs.system.events")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class EcsSwVideo : public Atom<EcsSwVideo>, public EcsVideoBase {

public:
	RTTI_DECL2(EcsSwVideo, AtomT, EcsVideoBase)
	COPY_PANIC(EcsSwVideo)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.ecs.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class EcsProgVideo : public Atom<EcsProgVideo>, public EcsVideoBase {

public:
	RTTI_DECL2(EcsProgVideo, AtomT, EcsVideoBase)
	COPY_PANIC(EcsProgVideo)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.prog.ecs")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class EcsOglFboPipe : public Atom<EcsOglFboPipe>, public EcsVideoBase {

public:
	RTTI_DECL2(EcsOglFboPipe, AtomT, EcsVideoBase)
	COPY_PANIC(EcsOglFboPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.ecs.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class EcsOglFbo : public Atom<EcsOglFbo>, public EcsVideoBase {

public:
	RTTI_DECL2(EcsOglFbo, AtomT, EcsVideoBase)
	COPY_PANIC(EcsOglFbo)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.ecs")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglCustomer : public Atom<OglCustomer>, public CustomerBase {

public:
	RTTI_DECL2(OglCustomer, AtomT, CustomerBase)
	COPY_PANIC(OglCustomer)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.customer")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class SdlContextAtom : public Atom<SdlContextAtom>, public SDL2ContextBase {

public:
	RTTI_DECL2(SdlContextAtom, AtomT, SDL2ContextBase)
	COPY_PANIC(SdlContextAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.context")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class SdlEventAtomPipe : public Atom<SdlEventAtomPipe>, public SDL2EventsBase {

public:
	RTTI_DECL2(SdlEventAtomPipe, AtomT, SDL2EventsBase)
	COPY_PANIC(SdlEventAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.event.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class SdlEventAtom : public Atom<SdlEventAtom>, public SDL2EventsBase {

public:
	RTTI_DECL2(SdlEventAtom, AtomT, SDL2EventsBase)
	COPY_PANIC(SdlEventAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.event")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class EventState : public Atom<EventState>, public EventStateBase {

public:
	RTTI_DECL2(EventState, AtomT, EventStateBase)
	COPY_PANIC(EventState)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("state.event")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class TestEventSrcPipe : public Atom<TestEventSrcPipe>, public TestEventSrcBase {

public:
	RTTI_DECL2(TestEventSrcPipe, AtomT, TestEventSrcBase)
	COPY_PANIC(TestEventSrcPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("event.src.test.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagSCREEN
class SdlImageLoader : public Atom<SdlImageLoader>, public SDL2ImageBase {

public:
	RTTI_DECL2(SdlImageLoader, AtomT, SDL2ImageBase)
	COPY_PANIC(SdlImageLoader)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.image.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class VolumeLoaderAtom : public Atom<VolumeLoaderAtom>, public VolumeLoaderBase {

public:
	RTTI_DECL2(VolumeLoaderAtom, AtomT, VolumeLoaderBase)
	COPY_PANIC(VolumeLoaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.volume.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlFboAtomSA : public Atom<SdlFboAtomSA>, public SDL2OglScreenBase {

public:
	RTTI_DECL2(SdlFboAtomSA, AtomT, SDL2OglScreenBase)
	COPY_PANIC(SdlFboAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlFboPipe : public Atom<SdlFboPipe>, public SDL2OglScreenBase {

public:
	RTTI_DECL2(SdlFboPipe, AtomT, SDL2OglScreenBase)
	COPY_PANIC(SdlFboPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlFboPipeSide : public Atom<SdlFboPipeSide>, public SDL2OglScreenBase {

public:
	RTTI_DECL2(SdlFboPipeSide, AtomT, SDL2OglScreenBase)
	COPY_PANIC(SdlFboPipeSide)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.pipe.side")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlFboAtom : public Atom<SdlFboAtom>, public SDL2OglScreenBase {

public:
	RTTI_DECL2(SdlFboAtom, AtomT, SDL2OglScreenBase)
	COPY_PANIC(SdlFboAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlVideoAtom : public Atom<SdlVideoAtom>, public SDL2CpuScreenBase {

public:
	RTTI_DECL2(SdlVideoAtom, AtomT, SDL2CpuScreenBase)
	COPY_PANIC(SdlVideoAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlVideoProgAtom : public Atom<SdlVideoProgAtom>, public SDL2CpuScreenBase {

public:
	RTTI_DECL2(SdlVideoProgAtom, AtomT, SDL2CpuScreenBase)
	COPY_PANIC(SdlVideoProgAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video.prog")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class SdlVideoAtomSA : public Atom<SdlVideoAtomSA>, public SDL2CpuScreenBase {

public:
	RTTI_DECL2(SdlVideoAtomSA, AtomT, SDL2CpuScreenBase)
	COPY_PANIC(SdlVideoAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class SdlAudioAtom : public Atom<SdlAudioAtom>, public SDL2AudioOutputBase {

public:
	RTTI_DECL2(SdlAudioAtom, AtomT, SDL2AudioOutputBase)
	COPY_PANIC(SdlAudioAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.audio")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagSCREEN
class OglShaderPipe : public Atom<OglShaderPipe>, public OglShaderBase {

public:
	RTTI_DECL2(OglShaderPipe, AtomT, OglShaderBase)
	COPY_PANIC(OglShaderPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.source.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglShaderAtom : public Atom<OglShaderAtom>, public OglShaderBase {

public:
	RTTI_DECL2(OglShaderAtom, AtomT, OglShaderBase)
	COPY_PANIC(OglShaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.source")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglShaderAtomSA : public Atom<OglShaderAtomSA>, public OglShaderBase {

public:
	RTTI_DECL2(OglShaderAtomSA, AtomT, OglShaderBase)
	COPY_PANIC(OglShaderAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.source.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglTextureSource : public Atom<OglTextureSource>, public OglTextureBase {

public:
	RTTI_DECL2(OglTextureSource, AtomT, OglTextureBase)
	COPY_PANIC(OglTextureSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.image")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglVolumeSource : public Atom<OglVolumeSource>, public OglTextureBase {

public:
	RTTI_DECL2(OglVolumeSource, AtomT, OglTextureBase)
	COPY_PANIC(OglVolumeSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.volume")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglAudioSink : public Atom<OglAudioSink>, public OglFboReaderBase {

public:
	RTTI_DECL2(OglAudioSink, AtomT, OglFboReaderBase)
	COPY_PANIC(OglAudioSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.center.audio")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglKeyboardSource : public Atom<OglKeyboardSource>, public OglKeyboardBase {

public:
	RTTI_DECL2(OglKeyboardSource, AtomT, OglKeyboardBase)
	COPY_PANIC(OglKeyboardSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.keyboard")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class OglAudioSource : public Atom<OglAudioSource>, public OglAudioBase {

public:
	RTTI_DECL2(OglAudioSource, AtomT, OglAudioBase)
	COPY_PANIC(OglAudioSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.audio")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

using CenterCustomerRef = Ref<CenterCustomer, AtomParent>;

using TestRealtimeSrcRef = Ref<TestRealtimeSrc, AtomParent>;

using TestRealtimeSinkRef = Ref<TestRealtimeSink, AtomParent>;

using TestPollerSinkRef = Ref<TestPollerSink, AtomParent>;

using AudioHardwareSinkRef = Ref<AudioHardwareSink, AtomParent>;

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

using EcsSwVideoRef = Ref<EcsSwVideo, AtomParent>;

using EcsProgVideoRef = Ref<EcsProgVideo, AtomParent>;

using EcsOglFboPipeRef = Ref<EcsOglFboPipe, AtomParent>;

using EcsOglFboRef = Ref<EcsOglFbo, AtomParent>;

using OglCustomerRef = Ref<OglCustomer, AtomParent>;

using SdlContextAtomRef = Ref<SdlContextAtom, AtomParent>;

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

using SdlVideoAtomRef = Ref<SdlVideoAtom, AtomParent>;

using SdlVideoProgAtomRef = Ref<SdlVideoProgAtom, AtomParent>;

using SdlVideoAtomSARef = Ref<SdlVideoAtomSA, AtomParent>;

using SdlAudioAtomRef = Ref<SdlAudioAtom, AtomParent>;

using OglShaderPipeRef = Ref<OglShaderPipe, AtomParent>;

using OglShaderAtomRef = Ref<OglShaderAtom, AtomParent>;

using OglShaderAtomSARef = Ref<OglShaderAtomSA, AtomParent>;

using OglTextureSourceRef = Ref<OglTextureSource, AtomParent>;

using OglVolumeSourceRef = Ref<OglVolumeSource, AtomParent>;

using OglAudioSinkRef = Ref<OglAudioSink, AtomParent>;

using OglKeyboardSourceRef = Ref<OglKeyboardSource, AtomParent>;

using OglAudioSourceRef = Ref<OglAudioSource, AtomParent>;

}

}



#endif
