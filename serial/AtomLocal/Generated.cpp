#include "AtomLocal.h"

namespace TS {

namespace Serial {

AtomTypeCls CenterCustomer::GetAtomType()
{
	return ATOM0(CENTER_CUSTOMER, CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);
}

void CenterCustomer::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CustomerBaseT<CenterCustomer>>(this);
}

AtomTypeCls CenterCustomer::GetType() const
{
	return GetAtomType();
}

AtomTypeCls TestRealtimeSrc::GetAtomType()
{
	return ATOM0(TEST_REALTIME_SRC, SOURCE, CENTER, ORDER, CENTER, AUDIO);
}

void TestRealtimeSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSourceAsync<TestRealtimeSrc>>(this);
}

AtomTypeCls TestRealtimeSrc::GetType() const
{
	return GetAtomType();
}

AtomTypeCls TestRealtimeSink::GetAtomType()
{
	return ATOM0(TEST_REALTIME_SINK, SINK, CENTER, AUDIO, CENTER, RECEIPT);
}

void TestRealtimeSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSinkSync<TestRealtimeSink>>(this);
}

AtomTypeCls TestRealtimeSink::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioHardwareSink::GetAtomType()
{
	return ATOM0(AUDIO_HARDWARE_SINK, SINK, CENTER, AUDIO, CENTER, RECEIPT);
}

void AudioHardwareSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSinkPolling<AudioHardwareSink>>(this);
	vis.VisitThis<PortaudioSink>(this);
}

AtomTypeCls AudioHardwareSink::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioDecoderSrc::GetAtomType()
{
	return ATOM0(AUDIO_DECODER_SRC, SOURCE, CENTER, ORDER, CENTER, AUDIO);
}

void AudioDecoderSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSourceAsync<AudioDecoderSrc>>(this);
	vis.VisitThis<FfmpegAtomBase>(this);
}

AtomTypeCls AudioDecoderSrc::GetType() const
{
	return GetAtomType();
}

void AudioDecoderSrc::StorePacket(Packet& p)
{
	AltStorePacket(p);
}

AtomTypeCls AudioDbgSrc::GetAtomType()
{
	return ATOM0(AUDIO_DBG_SRC, SOURCE, CENTER, ORDER, CENTER, AUDIO);
}

void AudioDbgSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSourceAsync<AudioDbgSrc>>(this);
	vis.VisitThis<AudioGenBase>(this);
}

AtomTypeCls AudioDbgSrc::GetType() const
{
	return GetAtomType();
}

void AudioDbgSrc::StorePacket(Packet& p)
{
	AltStorePacket(p);
}

AtomTypeCls AudioSideSrc::GetAtomType()
{
	return ATOM1(AUDIO_SIDE_SRC, SIDE_SOURCE, CENTER, AUDIO, CENTER, AUDIO, CENTER, RECEIPT);
}

void AudioSideSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSideSourceAsync<AudioSideSrc>>(this);
}

AtomTypeCls AudioSideSrc::GetType() const
{
	return GetAtomType();
}

AtomTypeCls AudioSideSink::GetAtomType()
{
	return ATOM1(AUDIO_SIDE_SINK, SIDE_SINK, CENTER, ORDER, CENTER, AUDIO, CENTER, AUDIO);
}

void AudioSideSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSideSinkAsync<AudioSideSink>>(this);
}

AtomTypeCls AudioSideSink::GetType() const
{
	return GetAtomType();
}

AtomTypeCls VideoDbgSrc::GetAtomType()
{
	return ATOM0(VIDEO_DBG_SRC, SOURCE, CENTER, ORDER, CENTER, VIDEO);
}

void VideoDbgSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSourceAsync<VideoDbgSrc>>(this);
	vis.VisitThis<VideoGenBase>(this);
}

AtomTypeCls VideoDbgSrc::GetType() const
{
	return GetAtomType();
}

void VideoDbgSrc::StorePacket(Packet& p)
{
	AltStorePacket(p);
}

AtomTypeCls AccelVideoDbgSrc::GetAtomType()
{
	return ATOM0(ACCEL_VIDEO_DBG_SRC, SOURCE, ACCEL, ORDER, ACCEL, VIDEO);
}

void AccelVideoDbgSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<AccelSourceAsync<AccelVideoDbgSrc>>(this);
	vis.VisitThis<AccelVideoGenBase>(this);
}

AtomTypeCls AccelVideoDbgSrc::GetType() const
{
	return GetAtomType();
}

void AccelVideoDbgSrc::StorePacket(Packet& p)
{
	AltStorePacket(p);
}

AtomTypeCls AccelCustomer::GetAtomType()
{
	return ATOM0(ACCEL_CUSTOMER, CUSTOMER, ACCEL, RECEIPT, ACCEL, ORDER);
}

void AccelCustomer::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CustomerBaseT<AccelCustomer>>(this);
}

AtomTypeCls AccelCustomer::GetType() const
{
	return GetAtomType();
}

AtomTypeCls VideoHardwareSink::GetAtomType()
{
	return ATOM0(VIDEO_HARDWARE_SINK, SINK, ACCEL, VIDEO, ACCEL, RECEIPT);
}

void VideoHardwareSink::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<AccelSideAsync<VideoHardwareSink>>(this);
	vis.VisitThis<DummyAlt>(this);
}

AtomTypeCls VideoHardwareSink::GetType() const
{
	return GetAtomType();
}

void VideoHardwareSink::StorePacket(Packet& p)
{
	AltStorePacket(p);
}

AtomTypeCls VideoShaderSrc::GetAtomType()
{
	return ATOM0(VIDEO_SHADER_SRC, SOURCE, ACCEL, ORDER, ACCEL, VIDEO);
}

void VideoShaderSrc::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<AccelSideAsync<VideoShaderSrc>>(this);
	vis.VisitThis<DummyAlt>(this);
}

AtomTypeCls VideoShaderSrc::GetType() const
{
	return GetAtomType();
}

void VideoShaderSrc::StorePacket(Packet& p)
{
	AltStorePacket(p);
}

AtomTypeCls VideoShaderBuffer::GetAtomType()
{
	return ATOM0(VIDEO_SHADER_BUFFER, SIDE_PIPE, ACCEL, ORDER, ACCEL, RECEIPT);
}

void VideoShaderBuffer::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<AccelSideAsync<VideoShaderBuffer>>(this);
	vis.VisitThis<DummyAlt>(this);
}

AtomTypeCls VideoShaderBuffer::GetType() const
{
	return GetAtomType();
}

void VideoShaderBuffer::StorePacket(Packet& p)
{
	AltStorePacket(p);
}

AtomTypeCls SdlContextAtom::GetAtomType()
{
	return ATOM0(SDL_CONTEXT_ATOM, DRIVER, CENTER, RECEIPT, CENTER, RECEIPT);
}

void SdlContextAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterDriver<SdlContextAtom>>(this);
	vis.VisitThis<SDL2ContextBase>(this);
}

AtomTypeCls SdlContextAtom::GetType() const
{
	return GetAtomType();
}

void SdlContextAtom::Forward(FwdScope& fwd)
{
	AltForward(fwd);
}

AtomTypeCls SdlVideoAtom::GetAtomType()
{
	return ATOM0(SDL_VIDEO_ATOM, SINK, ACCEL, VIDEO, ACCEL, RECEIPT);
}

void SdlVideoAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<AccelSinkPolling<SdlVideoAtom>>(this);
	vis.VisitThis<SDL2ScreenBase>(this);
}

AtomTypeCls SdlVideoAtom::GetType() const
{
	return GetAtomType();
}

AtomTypeCls SdlSwVideoAtom::GetAtomType()
{
	return ATOM0(SDL_SW_VIDEO_ATOM, SINK, CENTER, VIDEO, CENTER, RECEIPT);
}

void SdlSwVideoAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSinkPolling<SdlSwVideoAtom>>(this);
	vis.VisitThis<SDL2SwScreenBase>(this);
}

AtomTypeCls SdlSwVideoAtom::GetType() const
{
	return GetAtomType();
}

AtomTypeCls SdlAudioAtom::GetAtomType()
{
	return ATOM0(SDL_AUDIO_ATOM, SINK, CENTER, AUDIO, CENTER, RECEIPT);
}

void SdlAudioAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<CenterSinkPolling<SdlAudioAtom>>(this);
	vis.VisitThis<SDL2AudioOutputBase>(this);
}

AtomTypeCls SdlAudioAtom::GetType() const
{
	return GetAtomType();
}

}

}

