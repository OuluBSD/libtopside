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

class TestRealtimeSrc : public CenterSourceAsync<TestRealtimeSrc> {

public:
	RTTI_DECL1(TestRealtimeSrc, BaseT)
	COPY_PANIC(TestRealtimeSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.src.test")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void StorePacket(Packet& p) override;

};

class TestRealtimeSink : public CenterSinkSync<TestRealtimeSink> {

public:
	RTTI_DECL1(TestRealtimeSink, BaseT)
	COPY_PANIC(TestRealtimeSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("center.audio.sink.test.realtime")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void IntervalSinkProcess() override;

};

class AudioHardwareSink : public CenterSinkPolling<AudioHardwareSink>, public PortaudioSink {

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
	void StorePacket(Packet& p) override;

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
	void StorePacket(Packet& p) override;

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

class VideoHardwareSink : public AccelSideAsync<VideoHardwareSink>, public DummyAlt {

public:
	RTTI_DECL2(VideoHardwareSink, BaseT, DummyAlt)
	COPY_PANIC(VideoHardwareSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("accel.video.sink.hw")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void StorePacket(Packet& p) override;

};

class VideoShaderSrc : public AccelSideAsync<VideoShaderSrc>, public DummyAlt {

public:
	RTTI_DECL2(VideoShaderSrc, BaseT, DummyAlt)
	COPY_PANIC(VideoShaderSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("accel.video.src")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void StorePacket(Packet& p) override;

};

class VideoShaderBuffer : public AccelSideAsync<VideoShaderBuffer>, public DummyAlt {

public:
	RTTI_DECL2(VideoShaderBuffer, BaseT, DummyAlt)
	COPY_PANIC(VideoShaderBuffer)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("accel.video.buffer")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void StorePacket(Packet& p) override;

};

class SdlContextAtom : public CenterSideAsync<SdlContextAtom> {

public:
	RTTI_DECL1(SdlContextAtom, BaseT)
	COPY_PANIC(SdlContextAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.context")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void StorePacket(Packet& p) override;

};

class SdlEventAtom : public CenterSideAsync<SdlEventAtom> {

public:
	RTTI_DECL1(SdlEventAtom, BaseT)
	COPY_PANIC(SdlEventAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.event")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void StorePacket(Packet& p) override;

};

class SdlVideoAtom : public CenterSideAsync<SdlVideoAtom> {

public:
	RTTI_DECL1(SdlVideoAtom, BaseT)
	COPY_PANIC(SdlVideoAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.video")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void StorePacket(Packet& p) override;

};

class SdlAudioAtom : public CenterSideAsync<SdlAudioAtom> {

public:
	RTTI_DECL1(SdlAudioAtom, BaseT)
	COPY_PANIC(SdlAudioAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("sdl.audio")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void StorePacket(Packet& p) override;

};

using CenterCustomerRef = Ref<CenterCustomer, RefParent1<Loop>>;
using TestRealtimeSrcRef = Ref<TestRealtimeSrc, RefParent1<Loop>>;
using TestRealtimeSinkRef = Ref<TestRealtimeSink, RefParent1<Loop>>;
using AudioHardwareSinkRef = Ref<AudioHardwareSink, RefParent1<Loop>>;
using AudioDecoderSrcRef = Ref<AudioDecoderSrc, RefParent1<Loop>>;
using AudioDbgSrcRef = Ref<AudioDbgSrc, RefParent1<Loop>>;
using AccelCustomerRef = Ref<AccelCustomer, RefParent1<Loop>>;
using VideoHardwareSinkRef = Ref<VideoHardwareSink, RefParent1<Loop>>;
using VideoShaderSrcRef = Ref<VideoShaderSrc, RefParent1<Loop>>;
using VideoShaderBufferRef = Ref<VideoShaderBuffer, RefParent1<Loop>>;
using SdlContextAtomRef = Ref<SdlContextAtom, RefParent1<Loop>>;
using SdlEventAtomRef = Ref<SdlEventAtom, RefParent1<Loop>>;
using SdlVideoAtomRef = Ref<SdlVideoAtom, RefParent1<Loop>>;
using SdlAudioAtomRef = Ref<SdlAudioAtom, RefParent1<Loop>>;
}

}



#endif
