#ifndef _AtomMinimal_Generated_h_
#define _AtomMinimal_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Parallel {

class CenterCustomer : public CustomerBase {

public:
	RTTI_DECL1(CenterCustomer, CustomerBase)
	COPY_PANIC(CenterCustomer)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.customer")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class TestRealtimeSrc : public RollingValueBase {

public:
	RTTI_DECL1(TestRealtimeSrc, RollingValueBase)
	COPY_PANIC(TestRealtimeSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.test")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class TestRealtimeSink : public VoidSinkBase {

public:
	RTTI_DECL1(TestRealtimeSink, VoidSinkBase)
	COPY_PANIC(TestRealtimeSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.test.realtime")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

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

class PortaudioSink : public PortaudioSinkDevice {

public:
	RTTI_DECL1(PortaudioSink, PortaudioSinkDevice)
	COPY_PANIC(PortaudioSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.hw")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagFFMPEG
class AudioDecoderSrc : public FfmpegSourceDevice {

public:
	RTTI_DECL1(AudioDecoderSrc, FfmpegSourceDevice)
	COPY_PANIC(AudioDecoderSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("perma.audio.source.decoder")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class AudioDbgSrc : public AudioGenBase {

public:
	RTTI_DECL1(AudioDbgSrc, AudioGenBase)
	COPY_PANIC(AudioDbgSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.dbg_generator")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioSplitter : public VoidBase {

public:
	RTTI_DECL1(AudioSplitter, VoidBase)
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

class AudioSplitterUser : public VoidBase {

public:
	RTTI_DECL1(AudioSplitterUser, VoidBase)
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

class AudioJoiner : public VoidBase {

public:
	RTTI_DECL1(AudioJoiner, VoidBase)
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

class AudioJoinerUser : public VoidBase {

public:
	RTTI_DECL1(AudioJoinerUser, VoidBase)
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

class AudioJoiner2User : public VoidBase {

public:
	RTTI_DECL1(AudioJoiner2User, VoidBase)
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

#if defined flagOPENCV && defined flagLINUX
class WebcamPipe : public V4L2OpenCVCamera {

public:
	RTTI_DECL1(WebcamPipe, V4L2OpenCVCamera)
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

#if defined flagOPENCV && defined flagLINUX
class WebcamAtom : public V4L2OpenCVCamera {

public:
	RTTI_DECL1(WebcamAtom, V4L2OpenCVCamera)
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

#if defined flagSCREEN && defined flagFFMPEG
class AudioLoaderAtom : public FfmpegSourceDevice {

public:
	RTTI_DECL1(AudioLoaderAtom, FfmpegSourceDevice)
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

#if defined flagSCREEN && defined flagFFMPEG
class VideoLoaderAtom : public FfmpegSourceDevice {

public:
	RTTI_DECL1(VideoLoaderAtom, FfmpegSourceDevice)
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

#if defined flagSCREEN
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
#endif

#if defined flagSCREEN
class X11SwFboProg : public X11SwFboBase {

public:
	RTTI_DECL1(X11SwFboProg, X11SwFboBase)
	COPY_PANIC(X11SwFboProg)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.sw.fbo.program")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagOGL
class X11OglFboProg : public X11OglFboBase {

public:
	RTTI_DECL1(X11OglFboProg, X11OglFboBase)
	COPY_PANIC(X11OglFboProg)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.ogl.fbo.program")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagOGL && defined flagSDL2
class SdlOglFboProg : public SdlOglFboBase {

public:
	RTTI_DECL1(SdlOglFboProg, SdlOglFboBase)
	COPY_PANIC(SdlOglFboProg)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("any.ogl.fbo.program")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.ogl.fbo.program")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class X11SwShaderPipe : public X11SwShaderBase {

public:
	RTTI_DECL1(X11SwShaderPipe, X11SwShaderBase)
	COPY_PANIC(X11SwShaderPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("any.sw.fbo.pipe")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.sw.fbo.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagOGL
class X11OglShaderPipe : public X11OglShaderBase {

public:
	RTTI_DECL1(X11OglShaderPipe, X11OglShaderBase)
	COPY_PANIC(X11OglShaderPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("any.ogl.fbo.pipe")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.ogl.fbo.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagOGL && defined flagSDL2
class SdlOglShaderPipe : public SdlOglShaderBase {

public:
	RTTI_DECL1(SdlOglShaderPipe, SdlOglShaderBase)
	COPY_PANIC(SdlOglShaderPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("any.ogl.fbo.pipe")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.ogl.fbo.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class X11SwFboAtomPipe : public X11SwSinkDevice {

public:
	RTTI_DECL1(X11SwFboAtomPipe, X11SwSinkDevice)
	COPY_PANIC(X11SwFboAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.sw.fbo.sink")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagOGL
class X11OglFboAtomPipe : public X11OglSinkDevice {

public:
	RTTI_DECL1(X11OglFboAtomPipe, X11OglSinkDevice)
	COPY_PANIC(X11OglFboAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.ogl.fbo.sink")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagOGL && defined flagSDL2
class SdlOglFboAtomPipe : public SdlOglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboAtomPipe, SdlOglVideoSinkDevice)
	COPY_PANIC(SdlOglFboAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.ogl.fbo.sink")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class X11ContextAtom : public X11Context {

public:
	RTTI_DECL1(X11ContextAtom, X11Context)
	COPY_PANIC(X11ContextAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.context")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class X11EventAtomPipe : public X11EventsBase {

public:
	RTTI_DECL1(X11EventAtomPipe, X11EventsBase)
	COPY_PANIC(X11EventAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.event.pipe")
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

#if defined flagSDL2
class SdlContextAtom : public SdlContextBase {

public:
	RTTI_DECL1(SdlContextAtom, SdlContextBase)
	COPY_PANIC(SdlContextAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.context")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSDL2
class SdlEventAtomPipe : public SdlEventsBase {

public:
	RTTI_DECL1(SdlEventAtomPipe, SdlEventsBase)
	COPY_PANIC(SdlEventAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.event.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

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

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
class SdlOglImageLoader : public SdlOglImageBase {

public:
	RTTI_DECL1(SdlOglImageLoader, SdlOglImageBase)
	COPY_PANIC(SdlOglImageLoader)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.image.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

class VolumeLoaderAtom : public RawByteStaticSource {

public:
	RTTI_DECL1(VolumeLoaderAtom, RawByteStaticSource)
	COPY_PANIC(VolumeLoaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.volume.loader")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

#if defined flagSCREEN
class X11VideoAtomPipe : public X11SinkDevice {

public:
	RTTI_DECL1(X11VideoAtomPipe, X11SinkDevice)
	COPY_PANIC(X11VideoAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.video.pipe")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("any.video.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagOGL
class X11OglVideoAtomPipe : public X11OglSinkDevice {

public:
	RTTI_DECL1(X11OglVideoAtomPipe, X11OglSinkDevice)
	COPY_PANIC(X11OglVideoAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("glx.video.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagOGL
class X11OglFboAtomSA : public X11OglSinkDevice {

public:
	RTTI_DECL1(X11OglFboAtomSA, X11OglSinkDevice)
	COPY_PANIC(X11OglFboAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.ogl.fbo.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class X11SwVideoAtomPipe : public X11SwSinkDevice {

public:
	RTTI_DECL1(X11SwVideoAtomPipe, X11SwSinkDevice)
	COPY_PANIC(X11SwVideoAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.sw.video.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN
class X11SwFboAtomSA : public X11SwSinkDevice {

public:
	RTTI_DECL1(X11SwFboAtomSA, X11SwSinkDevice)
	COPY_PANIC(X11SwFboAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("x11.sw.fbo.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSDL2 && defined flagOGL
class SdlOglFboAtomSA : public SdlOglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboAtomSA, SdlOglVideoSinkDevice)
	COPY_PANIC(SdlOglFboAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSDL2 && defined flagOGL
class SdlOglFboPipe : public SdlOglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboPipe, SdlOglVideoSinkDevice)
	COPY_PANIC(SdlOglFboPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.sink")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSDL2 && defined flagOGL
class SdlOglFboAtom : public SdlOglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboAtom, SdlOglVideoSinkDevice)
	COPY_PANIC(SdlOglFboAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2
class SdlVideoAtomPipe : public SdlCenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlVideoAtomPipe, SdlCenterVideoSinkDevice)
	COPY_PANIC(SdlVideoAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video.pipe")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("any.video.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2
class SdlProgAtomPipe : public SdlCenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlProgAtomPipe, SdlCenterVideoSinkDevice)
	COPY_PANIC(SdlProgAtomPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.prog.pipe")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("any.prog.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2
class SdlVideoAtom : public SdlCenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlVideoAtom, SdlCenterVideoSinkDevice)
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

#if defined flagSDL2
class SdlAudioAtom : public SdlAudioSinkDevice {

public:
	RTTI_DECL1(SdlAudioAtom, SdlAudioSinkDevice)
	COPY_PANIC(SdlAudioAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.audio")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
class SdlOglShaderAtom : public SdlOglShaderBase {

public:
	RTTI_DECL1(SdlOglShaderAtom, SdlOglShaderBase)
	COPY_PANIC(SdlOglShaderAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.ogl.fbo.side")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("any.ogl.fbo.side")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
class SdlOglShaderAtomSA : public SdlOglShaderBase {

public:
	RTTI_DECL1(SdlOglShaderAtomSA, SdlOglShaderBase)
	COPY_PANIC(SdlOglShaderAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("ogl.fbo.source.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
class SdlOglTextureSource : public SdlOglTextureBase {

public:
	RTTI_DECL1(SdlOglTextureSource, SdlOglTextureBase)
	COPY_PANIC(SdlOglTextureSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.ogl.fbo.image")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
class SdlOglVolumeSource : public SdlOglTextureBase {

public:
	RTTI_DECL1(SdlOglVolumeSource, SdlOglTextureBase)
	COPY_PANIC(SdlOglVolumeSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.ogl.fbo.volume")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
class SdlOglAudioSink : public SdlOglFboReaderBase {

public:
	RTTI_DECL1(SdlOglAudioSink, SdlOglFboReaderBase)
	COPY_PANIC(SdlOglAudioSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.ogl.fbo.center.audio")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
class SdlOglKeyboardSource : public SdlOglKeyboardBase {

public:
	RTTI_DECL1(SdlOglKeyboardSource, SdlOglKeyboardBase)
	COPY_PANIC(SdlOglKeyboardSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.ogl.fbo.keyboard")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	static LinkTypeCls GetLinkType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
class SdlOglAudioSource : public SdlOglAudioBase {

public:
	RTTI_DECL1(SdlOglAudioSource, SdlOglAudioBase)
	COPY_PANIC(SdlOglAudioSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.ogl.center.fbo.audio")
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

#if defined flagOPENCV && defined flagLINUX
using WebcamPipeRef = Ref<WebcamPipe, AtomParent>;
#endif

#if defined flagOPENCV && defined flagLINUX
using WebcamAtomRef = Ref<WebcamAtom, AtomParent>;
#endif

#if defined flagSCREEN && defined flagFFMPEG
using AudioLoaderAtomRef = Ref<AudioLoaderAtom, AtomParent>;
#endif

#if defined flagSCREEN && defined flagFFMPEG
using VideoLoaderAtomRef = Ref<VideoLoaderAtom, AtomParent>;
#endif

#if defined flagSCREEN
using EventStatePipeRef = Ref<EventStatePipe, AtomParent>;
#endif

#if defined flagSCREEN
using X11SwFboProgRef = Ref<X11SwFboProg, AtomParent>;
#endif

#if defined flagSCREEN && defined flagOGL
using X11OglFboProgRef = Ref<X11OglFboProg, AtomParent>;
#endif

#if defined flagSCREEN && defined flagOGL && defined flagSDL2
using SdlOglFboProgRef = Ref<SdlOglFboProg, AtomParent>;
#endif

#if defined flagSCREEN
using X11SwShaderPipeRef = Ref<X11SwShaderPipe, AtomParent>;
#endif

#if defined flagSCREEN && defined flagOGL
using X11OglShaderPipeRef = Ref<X11OglShaderPipe, AtomParent>;
#endif

#if defined flagSCREEN && defined flagOGL && defined flagSDL2
using SdlOglShaderPipeRef = Ref<SdlOglShaderPipe, AtomParent>;
#endif

#if defined flagSCREEN
using X11SwFboAtomPipeRef = Ref<X11SwFboAtomPipe, AtomParent>;
#endif

#if defined flagSCREEN && defined flagOGL
using X11OglFboAtomPipeRef = Ref<X11OglFboAtomPipe, AtomParent>;
#endif

#if defined flagSCREEN && defined flagOGL && defined flagSDL2
using SdlOglFboAtomPipeRef = Ref<SdlOglFboAtomPipe, AtomParent>;
#endif

#if defined flagSCREEN
using X11ContextAtomRef = Ref<X11ContextAtom, AtomParent>;
#endif

#if defined flagSCREEN
using X11EventAtomPipeRef = Ref<X11EventAtomPipe, AtomParent>;
#endif

#if defined flagSCREEN
using OglCustomerRef = Ref<OglCustomer, AtomParent>;
#endif

#if defined flagSDL2
using SdlContextAtomRef = Ref<SdlContextAtom, AtomParent>;
#endif

#if defined flagSDL2
using SdlEventAtomPipeRef = Ref<SdlEventAtomPipe, AtomParent>;
#endif

using TestEventSrcPipeRef = Ref<TestEventSrcPipe, AtomParent>;

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
using SdlOglImageLoaderRef = Ref<SdlOglImageLoader, AtomParent>;
#endif

using VolumeLoaderAtomRef = Ref<VolumeLoaderAtom, AtomParent>;

#if defined flagSCREEN
using X11VideoAtomPipeRef = Ref<X11VideoAtomPipe, AtomParent>;
#endif

#if defined flagOGL
using X11OglVideoAtomPipeRef = Ref<X11OglVideoAtomPipe, AtomParent>;
#endif

#if defined flagOGL
using X11OglFboAtomSARef = Ref<X11OglFboAtomSA, AtomParent>;
#endif

#if defined flagSCREEN
using X11SwVideoAtomPipeRef = Ref<X11SwVideoAtomPipe, AtomParent>;
#endif

#if defined flagSCREEN
using X11SwFboAtomSARef = Ref<X11SwFboAtomSA, AtomParent>;
#endif

#if defined flagSDL2 && defined flagOGL
using SdlOglFboAtomSARef = Ref<SdlOglFboAtomSA, AtomParent>;
#endif

#if defined flagSDL2 && defined flagOGL
using SdlOglFboPipeRef = Ref<SdlOglFboPipe, AtomParent>;
#endif

#if defined flagSDL2 && defined flagOGL
using SdlOglFboAtomRef = Ref<SdlOglFboAtom, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2
using SdlVideoAtomPipeRef = Ref<SdlVideoAtomPipe, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2
using SdlProgAtomPipeRef = Ref<SdlProgAtomPipe, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2
using SdlVideoAtomRef = Ref<SdlVideoAtom, AtomParent>;
#endif

#if defined flagSDL2
using SdlAudioAtomRef = Ref<SdlAudioAtom, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
using SdlOglShaderAtomRef = Ref<SdlOglShaderAtom, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
using SdlOglShaderAtomSARef = Ref<SdlOglShaderAtomSA, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
using SdlOglTextureSourceRef = Ref<SdlOglTextureSource, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
using SdlOglVolumeSourceRef = Ref<SdlOglVolumeSource, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
using SdlOglAudioSinkRef = Ref<SdlOglAudioSink, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
using SdlOglKeyboardSourceRef = Ref<SdlOglKeyboardSource, AtomParent>;
#endif

#if defined flagSCREEN && defined flagSDL2 && defined flagOGL
using SdlOglAudioSourceRef = Ref<SdlOglAudioSource, AtomParent>;
#endif

}

}



#endif
