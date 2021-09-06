#include "AtomLocal.h"

namespace TS {

namespace Serial {

AtomTypeCls CustomerAtom::GetAtomType()
{
	return ATOM0(CUSTOMER_ATOM, CUSTOMER, CENTER, RECEIPT, CENTER, ORDER);
}

void CustomerAtom::Visit(RuntimeVisitor& vis)
{
	vis.VisitThis<BaseT>(this);
}

AtomTypeCls CustomerAtom::GetType() const
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

}

}

