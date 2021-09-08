#ifndef _AtomLocal_Generated_h_
#define _AtomLocal_Generated_h_

// This file is generated. Do not modify this file.

namespace TS {

namespace Serial {

class CustomerAtom : public AtomReceiptSink<CustomerAtom> {

public:
	RTTI_DECL1(CustomerAtom, BaseT)
	COPY_PANIC(CustomerAtom)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("loop.connected")
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("customer.test.single")
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
	RTTI_DECL1(AudioHardwareSink, BaseT)
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
	RTTI_DECL1(AudioDecoderSrc, BaseT)
	COPY_PANIC(AudioDecoderSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_UNDEF_TO_TRUE("perma.audio.source.decoder")
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;
	void StorePacket(Packet& p) override;

};

class VideoHardwareSink : public DummySideAsync<VideoHardwareSink> {

public:
	RTTI_DECL1(VideoHardwareSink, BaseT)
	COPY_PANIC(VideoHardwareSink)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class VideoShaderSrc : public DummySideAsync<VideoShaderSrc> {

public:
	RTTI_DECL1(VideoShaderSrc, BaseT)
	COPY_PANIC(VideoShaderSrc)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

class VideoShaderBuffer : public DummySideAsync<VideoShaderBuffer> {

public:
	RTTI_DECL1(VideoShaderBuffer, BaseT)
	COPY_PANIC(VideoShaderBuffer)
	ATOM_MAKE_ACTION_BEGIN
	ATOM_MAKE_ACTION_END
	static AtomTypeCls GetAtomType();
	void Visit(RuntimeVisitor& vis) override;
	AtomTypeCls GetType() const override;

};

using CustomerAtomRef = Ref<CustomerAtom, RefParent1<Loop>>;
using TestRealtimeSrcRef = Ref<TestRealtimeSrc, RefParent1<Loop>>;
using TestRealtimeSinkRef = Ref<TestRealtimeSink, RefParent1<Loop>>;
using AudioHardwareSinkRef = Ref<AudioHardwareSink, RefParent1<Loop>>;
using AudioDecoderSrcRef = Ref<AudioDecoderSrc, RefParent1<Loop>>;
using VideoHardwareSinkRef = Ref<VideoHardwareSink, RefParent1<Loop>>;
using VideoShaderSrcRef = Ref<VideoShaderSrc, RefParent1<Loop>>;
using VideoShaderBufferRef = Ref<VideoShaderBuffer, RefParent1<Loop>>;
}

}



#endif
