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
class AccelVideoDbgSrc : public Atom<AccelVideoDbgSrc>, public AccelVideoGenBase {

public:
	RTTI_DECL2(AccelVideoDbgSrc, AtomT, AccelVideoGenBase)
	COPY_PANIC(AccelVideoDbgSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("accel.video.src.dbg_generator")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagGUI
class AccelCustomer : public Atom<AccelCustomer>, public CustomerBase {

public:
	RTTI_DECL2(AccelCustomer, AtomT, CustomerBase)
	COPY_PANIC(AccelCustomer)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("accel.customer")
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
class SdlVideoAtomSA : public Atom<SdlVideoAtomSA>, public SDL2ScreenBase {

public:
	RTTI_DECL2(SdlVideoAtomSA, AtomT, SDL2ScreenBase)
	COPY_PANIC(SdlVideoAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video.standalone")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagGUI
class SdlVideoAtom : public Atom<SdlVideoAtom>, public SDL2ScreenBase {

public:
	RTTI_DECL2(SdlVideoAtom, AtomT, SDL2ScreenBase)
	COPY_PANIC(SdlVideoAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagGUI
class SdlVideoPipe : public Atom<SdlVideoPipe>, public SDL2ScreenBase {

public:
	RTTI_DECL2(SdlVideoPipe, AtomT, SDL2ScreenBase)
	COPY_PANIC(SdlVideoPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagGUI
class SdlSwVideoAtom : public Atom<SdlSwVideoAtom>, public SDL2SwScreenBase {

public:
	RTTI_DECL2(SdlSwVideoAtom, AtomT, SDL2SwScreenBase)
	COPY_PANIC(SdlSwVideoAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.swvideo")
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
class OglShaderSource : public Atom<OglShaderSource>, public OglShaderBase {

public:
	RTTI_DECL2(OglShaderSource, AtomT, OglShaderBase)
	COPY_PANIC(OglShaderSource)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("accel.video.source")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

#if defined flagGUI
class OglShaderPipe : public Atom<OglShaderPipe>, public OglShaderBase {

public:
	RTTI_DECL2(OglShaderPipe, AtomT, OglShaderBase)
	COPY_PANIC(OglShaderPipe)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("accel.video.source.pipe")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};
#endif

using CenterCustomerRef = Ref<CenterCustomer, AtomParent>;

using TestRealtimeSrcRef = Ref<TestRealtimeSrc, AtomParent>;

using TestRealtimeSinkRef = Ref<TestRealtimeSink, AtomParent>;

using AudioHardwareSinkRef = Ref<AudioHardwareSink, AtomParent>;

using AudioDecoderSrcRef = Ref<AudioDecoderSrc, AtomParent>;

using AudioDbgSrcRef = Ref<AudioDbgSrc, AtomParent>;

using AudioSplitterRef = Ref<AudioSplitter, AtomParent>;

using AudioJoinerRef = Ref<AudioJoiner, AtomParent>;

#if defined flagGUI
using VideoDbgSrcRef = Ref<VideoDbgSrc, AtomParent>;
#endif

#if defined flagGUI
using AccelVideoDbgSrcRef = Ref<AccelVideoDbgSrc, AtomParent>;
#endif

#if defined flagGUI
using AccelCustomerRef = Ref<AccelCustomer, AtomParent>;
#endif

using SdlContextAtomRef = Ref<SdlContextAtom, AtomParent>;

using SdlEventAtomPipeRef = Ref<SdlEventAtomPipe, AtomParent>;

using EventStatePipeRef = Ref<EventStatePipe, AtomParent>;

using SdlEventAtomRef = Ref<SdlEventAtom, AtomParent>;

using EventStateRef = Ref<EventState, AtomParent>;

using TestEventSrcPipeRef = Ref<TestEventSrcPipe, AtomParent>;

#if defined flagGUI
using SdlVideoAtomSARef = Ref<SdlVideoAtomSA, AtomParent>;
#endif

#if defined flagGUI
using SdlVideoAtomRef = Ref<SdlVideoAtom, AtomParent>;
#endif

#if defined flagGUI
using SdlVideoPipeRef = Ref<SdlVideoPipe, AtomParent>;
#endif

#if defined flagGUI
using SdlSwVideoAtomRef = Ref<SdlSwVideoAtom, AtomParent>;
#endif

using SdlAudioAtomRef = Ref<SdlAudioAtom, AtomParent>;

#if defined flagGUI
using OglShaderSourceRef = Ref<OglShaderSource, AtomParent>;
#endif

#if defined flagGUI
using OglShaderPipeRef = Ref<OglShaderPipe, AtomParent>;
#endif

}

}



#endif
