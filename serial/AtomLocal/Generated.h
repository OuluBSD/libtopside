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

#if defined flagGUI
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

#if defined flagGUI
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

#if defined flagGUI
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

#if defined flagGUI
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

#if defined flagGUI
class SdlFboAtomSA : public Atom<SdlFboAtomSA>, public SDL2ScreenBase {

public:
	RTTI_DECL2(SdlFboAtomSA, AtomT, SDL2ScreenBase)
	COPY_PANIC(SdlFboAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagGUI
class SdlFboPipe : public Atom<SdlFboPipe>, public SDL2ScreenBase {

public:
	RTTI_DECL2(SdlFboPipe, AtomT, SDL2ScreenBase)
	COPY_PANIC(SdlFboPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagGUI
class SdlFboPipeSide : public Atom<SdlFboPipeSide>, public SDL2ScreenBase {

public:
	RTTI_DECL2(SdlFboPipeSide, AtomT, SDL2ScreenBase)
	COPY_PANIC(SdlFboPipeSide)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo.pipe.side")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagGUI
class SdlFboAtom : public Atom<SdlFboAtom>, public SDL2ScreenBase {

public:
	RTTI_DECL2(SdlFboAtom, AtomT, SDL2ScreenBase)
	COPY_PANIC(SdlFboAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.fbo")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagGUI
class SdlVideoAtom : public Atom<SdlVideoAtom>, public SDL2SwScreenBase {

public:
	RTTI_DECL2(SdlVideoAtom, AtomT, SDL2SwScreenBase)
	COPY_PANIC(SdlVideoAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video")
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

#if defined flagGUI
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

#if defined flagGUI
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

#if defined flagGUI
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

#if defined flagGUI
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

#if defined flagGUI
using VideoDbgSrcRef = Ref<VideoDbgSrc, AtomParent>;
#endif

#if defined flagGUI
using OglCustomerRef = Ref<OglCustomer, AtomParent>;
#endif

using SdlContextAtomRef = Ref<SdlContextAtom, AtomParent>;

using SdlEventAtomPipeRef = Ref<SdlEventAtomPipe, AtomParent>;

using EventStatePipeRef = Ref<EventStatePipe, AtomParent>;

using SdlEventAtomRef = Ref<SdlEventAtom, AtomParent>;

using EventStateRef = Ref<EventState, AtomParent>;

using TestEventSrcPipeRef = Ref<TestEventSrcPipe, AtomParent>;

#if defined flagGUI
using SdlImageLoaderRef = Ref<SdlImageLoader, AtomParent>;
#endif

#if defined flagGUI
using VolumeLoaderAtomRef = Ref<VolumeLoaderAtom, AtomParent>;
#endif

#if defined flagGUI
using SdlFboAtomSARef = Ref<SdlFboAtomSA, AtomParent>;
#endif

#if defined flagGUI
using SdlFboPipeRef = Ref<SdlFboPipe, AtomParent>;
#endif

#if defined flagGUI
using SdlFboPipeSideRef = Ref<SdlFboPipeSide, AtomParent>;
#endif

#if defined flagGUI
using SdlFboAtomRef = Ref<SdlFboAtom, AtomParent>;
#endif

#if defined flagGUI
using SdlVideoAtomRef = Ref<SdlVideoAtom, AtomParent>;
#endif

using SdlAudioAtomRef = Ref<SdlAudioAtom, AtomParent>;

#if defined flagGUI
using OglShaderPipeRef = Ref<OglShaderPipe, AtomParent>;
#endif

#if defined flagGUI
using OglShaderAtomRef = Ref<OglShaderAtom, AtomParent>;
#endif

#if defined flagGUI
using OglTextureSourceRef = Ref<OglTextureSource, AtomParent>;
#endif

#if defined flagGUI
using OglVolumeSourceRef = Ref<OglVolumeSource, AtomParent>;
#endif

}

}



#endif
