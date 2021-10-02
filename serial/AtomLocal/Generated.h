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

class SdlEventAtomSA : public Atom<SdlEventAtomSA>, public SDL2EventsBase {

public:
	RTTI_DECL2(SdlEventAtomSA, AtomT, SDL2EventsBase)
	COPY_PANIC(SdlEventAtomSA)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.event.standalone")
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

using CenterCustomerRef = Ref<CenterCustomer, RefParent1<Loop>>;

using TestRealtimeSrcRef = Ref<TestRealtimeSrc, RefParent1<Loop>>;

using TestRealtimeSinkRef = Ref<TestRealtimeSink, RefParent1<Loop>>;

using AudioHardwareSinkRef = Ref<AudioHardwareSink, RefParent1<Loop>>;

using AudioDecoderSrcRef = Ref<AudioDecoderSrc, RefParent1<Loop>>;

using AudioDbgSrcRef = Ref<AudioDbgSrc, RefParent1<Loop>>;

using AudioSplitterRef = Ref<AudioSplitter, RefParent1<Loop>>;

using AudioJoinerRef = Ref<AudioJoiner, RefParent1<Loop>>;

#if defined flagGUI
using VideoDbgSrcRef = Ref<VideoDbgSrc, RefParent1<Loop>>;
#endif

#if defined flagGUI
using AccelVideoDbgSrcRef = Ref<AccelVideoDbgSrc, RefParent1<Loop>>;
#endif

#if defined flagGUI
using AccelCustomerRef = Ref<AccelCustomer, RefParent1<Loop>>;
#endif

using SdlContextAtomRef = Ref<SdlContextAtom, RefParent1<Loop>>;

using SdlEventAtomSARef = Ref<SdlEventAtomSA, RefParent1<Loop>>;

#if defined flagGUI
using SdlVideoAtomSARef = Ref<SdlVideoAtomSA, RefParent1<Loop>>;
#endif

#if defined flagGUI
using SdlVideoAtomRef = Ref<SdlVideoAtom, RefParent1<Loop>>;
#endif

#if defined flagGUI
using SdlVideoPipeRef = Ref<SdlVideoPipe, RefParent1<Loop>>;
#endif

#if defined flagGUI
using SdlSwVideoAtomRef = Ref<SdlSwVideoAtom, RefParent1<Loop>>;
#endif

using SdlAudioAtomRef = Ref<SdlAudioAtom, RefParent1<Loop>>;

#if defined flagGUI
using OglShaderSourceRef = Ref<OglShaderSource, RefParent1<Loop>>;
#endif

#if defined flagGUI
using OglShaderPipeRef = Ref<OglShaderPipe, RefParent1<Loop>>;
#endif

}

}



#endif
