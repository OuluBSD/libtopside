#include "AtomLocal.h"

NAMESPACE_SERIAL_BEGIN





AudioGenBase::AudioGenBase() {
	fmt.SetAudio(DevCls::CENTER, SoundSample::U8_LE, 2, 44100, 777);
	gen.GenerateStereoSine(fmt);
	
}

bool AudioGenBase::AltInitialize(const Script::WorldState& ws) {
	Value& src_val = GetSource()->GetSourceValue();
	src_val.SetFormat(fmt);
	return true;
}

void AudioGenBase::AltUninitialize() {
	
}

void AudioGenBase::AltForward(FwdScope& fwd) {
	
}

void AudioGenBase::AltStorePacket(Packet& p) {
	int frame = fmt.GetFrameSize();
	dword off = p->GetOffset().value;
	int64 offset = (int64)off * (int64)frame;
	ASSERT(offset < (int64)std::numeric_limits<int>::max());
	double time = off * fmt.GetFrameSeconds();
	p->Set(fmt, time);
	p->Data().SetCount(frame, 0);
	gen.Play((int)offset, p);
	RTLOG("AudioGenBase::AltStorePacket: " << p->ToStringWithHash());
}

NAMESPACE_SERIAL_END
