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
class SdlOglShaderProg : public SdlOglFboBase {

public:
	RTTI_DECL1(SdlOglShaderProg, SdlOglFboBase)
	COPY_PANIC(SdlOglShaderProg)
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
class SdlOglFboAtomPipe : public Sdl2OglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboAtomPipe, Sdl2OglVideoSinkDevice)
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
class SdlContextAtom : public Sdl2ContextBase {

public:
	RTTI_DECL1(SdlContextAtom, Sdl2ContextBase)
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
class SdlEventAtomPipe : public Sdl2EventsBase {

public:
	RTTI_DECL1(SdlEventAtomPipe, Sdl2EventsBase)
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
class SdlOglImageLoader : public Sdl2OglImageBase {

public:
	RTTI_DECL1(SdlOglImageLoader, Sdl2OglImageBase)
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
class SdlOglFboAtomSA : public Sdl2OglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboAtomSA, Sdl2OglVideoSinkDevice)
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
class SdlOglFboPipe : public Sdl2OglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboPipe, Sdl2OglVideoSinkDevice)
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
class SdlOglFboAtom : public Sdl2OglVideoSinkDevice {

public:
	RTTI_DECL1(SdlOglFboAtom, Sdl2OglVideoSinkDevice)
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
class SdlVideoAtomPipe : public Sdl2CenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlVideoAtomPipe, Sdl2CenterVideoSinkDevice)
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
class SdlProgAtomPipe : public Sdl2CenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlProgAtomPipe, Sdl2CenterVideoSinkDevice)
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
class SdlVideoAtom : public Sdl2CenterVideoSinkDevice {

public:
	RTTI_DECL1(SdlVideoAtom, Sdl2CenterVideoSinkDevice)
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
class SdlAudioAtom : public Sdl2AudioSinkDevice {

public:
	RTTI_DECL1(SdlAudioAtom, Sdl2AudioSinkDevice)
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

}

}



#endif