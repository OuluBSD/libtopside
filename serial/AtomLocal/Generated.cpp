#include "AtomLocal.h"

namespace TS {

namespace Serial {

AtomTypeCls CenterCustomer::GetAtomType()
{
	return ATOM0(CENTER_CUSTOMER, CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);
}

void CenterCustomer::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
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
	vis.VisitThis<BaseT>(this);
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
	vis.VisitThis<BaseT>(this);
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
	vis.VisitThis<BaseT>(this);
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
	vis.VisitThis<BaseT>(this);
}

AtomTypeCls AudioDecoderSrc::GetType() const
{
	return GetAtomType();
}

void AudioDecoderSrc::StorePacket(Packet& p)
{
	AltStorePacket(p);
}

AtomTypeCls AccelCustomer::GetAtomType()
{
	return ATOM0(ACCEL_CUSTOMER, CUSTOMER, ACCEL, RECEIPT, ACCEL, ORDER);
}

void AccelCustomer::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
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
	vis.VisitThis<BaseT>(this);
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
	vis.VisitThis<BaseT>(this);
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
	vis.VisitThis<BaseT>(this);
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
	return ATOM0(SDL_CONTEXT_ATOM, SIDE_PIPE, CENTER, RECEIPT, CENTER, ORDER);
}

void SdlContextAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
}

AtomTypeCls SdlContextAtom::GetType() const
{
	return GetAtomType();
}

AtomTypeCls SdlEventAtom::GetAtomType()
{
	return ATOM0(SDL_EVENT_ATOM, SIDE_PIPE, CENTER, RECEIPT, CENTER, ORDER);
}

void SdlEventAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
}

AtomTypeCls SdlEventAtom::GetType() const
{
	return GetAtomType();
}

AtomTypeCls SdlVideoAtom::GetAtomType()
{
	return ATOM0(SDL_VIDEO_ATOM, SIDE_PIPE, CENTER, RECEIPT, CENTER, ORDER);
}

void SdlVideoAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
}

AtomTypeCls SdlVideoAtom::GetType() const
{
	return GetAtomType();
}

AtomTypeCls SdlAudioAtom::GetAtomType()
{
	return ATOM0(SDL_AUDIO_ATOM, SIDE_PIPE, CENTER, RECEIPT, CENTER, ORDER);
}

void SdlAudioAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
}

AtomTypeCls SdlAudioAtom::GetType() const
{
	return GetAtomType();
}

}

}

