#ifndef _AtomLocal_Generated_h_
#define _AtomLocal_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Serial {

class CenterCustomer : public CustomerBaseT<CenterCustomer> {

public:
	RTTI_DECL1(CenterCustomer, BaseT)
	COPY_PANIC(CenterCustomer)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.customer")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class TestRealtimeSrc : public CenterSourceAsync<TestRealtimeSrc>, public RollingValueBase {

public:
	RTTI_DECL2(TestRealtimeSrc, BaseT, RollingValueBase)
	COPY_PANIC(TestRealtimeSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.test")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class TestRealtimeSink : public CenterSinkSync<TestRealtimeSink>, public VoidSinkBase {

public:
	RTTI_DECL2(TestRealtimeSink, BaseT, VoidSinkBase)
	COPY_PANIC(TestRealtimeSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.test.realtime")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioHardwareSink : public CenterSinkAsync<AudioHardwareSink>, public PortaudioSink {

public:
	RTTI_DECL2(AudioHardwareSink, BaseT, PortaudioSink)
	COPY_PANIC(AudioHardwareSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.hw")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioDecoderSrc : public CenterSourceAsync<AudioDecoderSrc>, public FfmpegAtomBase {

public:
	RTTI_DECL2(AudioDecoderSrc, BaseT, FfmpegAtomBase)
	COPY_PANIC(AudioDecoderSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("perma.audio.source.decoder")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioDbgSrc : public CenterSourceAsync<AudioDbgSrc>, public AudioGenBase {

public:
	RTTI_DECL2(AudioDbgSrc, BaseT, AudioGenBase)
	COPY_PANIC(AudioDbgSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.dbg_generator")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioSplitter : public CenterSourceAsync<AudioSplitter> {

public:
	RTTI_DECL1(AudioSplitter, BaseT)
	COPY_PANIC(AudioSplitter)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.src")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AudioJoiner : public CenterSinkAsync<AudioJoiner> {

public:
	RTTI_DECL1(AudioJoiner, BaseT)
	COPY_PANIC(AudioJoiner)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.side.sink")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class VideoDbgSrc : public CenterSourceAsync<VideoDbgSrc>, public VideoGenBase {

public:
	RTTI_DECL2(VideoDbgSrc, BaseT, VideoGenBase)
	COPY_PANIC(VideoDbgSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.video.src.dbg_generator")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AccelVideoDbgSrc : public AccelSourceAsync<AccelVideoDbgSrc>, public AccelVideoGenBase {

public:
	RTTI_DECL2(AccelVideoDbgSrc, BaseT, AccelVideoGenBase)
	COPY_PANIC(AccelVideoDbgSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("accel.video.src.dbg_generator")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class AccelCustomer : public CustomerBaseT<AccelCustomer> {

public:
	RTTI_DECL1(AccelCustomer, BaseT)
	COPY_PANIC(AccelCustomer)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("accel.customer")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class SdlContextAtom : public CenterDriver<SdlContextAtom>, public SDL2ContextBase {

public:
	RTTI_DECL2(SdlContextAtom, BaseT, SDL2ContextBase)
	COPY_PANIC(SdlContextAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.context")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class SdlVideoAtom : public AccelSinkPolling<SdlVideoAtom>, public SDL2ScreenBase {

public:
	RTTI_DECL2(SdlVideoAtom, BaseT, SDL2ScreenBase)
	COPY_PANIC(SdlVideoAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class SdlSwVideoAtom : public CenterSinkPolling<SdlSwVideoAtom>, public SDL2SwScreenBase {

public:
	RTTI_DECL2(SdlSwVideoAtom, BaseT, SDL2SwScreenBase)
	COPY_PANIC(SdlSwVideoAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.swvideo")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class SdlAudioAtom : public CenterSinkAsync<SdlAudioAtom>, public SDL2AudioOutputBase {

public:
	RTTI_DECL2(SdlAudioAtom, BaseT, SDL2AudioOutputBase)
	COPY_PANIC(SdlAudioAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.audio")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

using CenterCustomerRef = Ref<CenterCustomer, RefParent1<Loop>>;
using TestRealtimeSrcRef = Ref<TestRealtimeSrc, RefParent1<Loop>>;
using TestRealtimeSinkRef = Ref<TestRealtimeSink, RefParent1<Loop>>;
using AudioHardwareSinkRef = Ref<AudioHardwareSink, RefParent1<Loop>>;
using AudioDecoderSrcRef = Ref<AudioDecoderSrc, RefParent1<Loop>>;
using AudioDbgSrcRef = Ref<AudioDbgSrc, RefParent1<Loop>>;
using AudioSplitterRef = Ref<AudioSplitter, RefParent1<Loop>>;
using AudioJoinerRef = Ref<AudioJoiner, RefParent1<Loop>>;
using VideoDbgSrcRef = Ref<VideoDbgSrc, RefParent1<Loop>>;
using AccelVideoDbgSrcRef = Ref<AccelVideoDbgSrc, RefParent1<Loop>>;
using AccelCustomerRef = Ref<AccelCustomer, RefParent1<Loop>>;
using SdlContextAtomRef = Ref<SdlContextAtom, RefParent1<Loop>>;
using SdlVideoAtomRef = Ref<SdlVideoAtom, RefParent1<Loop>>;
using SdlSwVideoAtomRef = Ref<SdlSwVideoAtom, RefParent1<Loop>>;
using SdlAudioAtomRef = Ref<SdlAudioAtom, RefParent1<Loop>>;
}

}



#endif
