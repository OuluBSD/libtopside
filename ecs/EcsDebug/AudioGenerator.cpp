#include "EcsDebug.h"

NAMESPACE_ECS_BEGIN


DebugAudioGeneratorExt::DebugAudioGeneratorExt() {
	fmt.SetAudio(SoundSample::U8_LE, 2, 44100, 777);
	gen.GenerateStereoSine(fmt);
	
}

bool DebugAudioGeneratorExt::Initialize(const Eon::WorldState& ws) {
	ExtComponent& ext = GetParent();
	Value& src_val = ext.GetSourceValue();
	src_val.SetFormat(fmt);
	return true;
}

void DebugAudioGeneratorExt::Uninitialize() {
	
}

void DebugAudioGeneratorExt::Forward(FwdScope& fwd) {
	
}

void DebugAudioGeneratorExt::StorePacket(int sink_ch,  int src_ch, Packet& p) {
	int frame = fmt.GetFrameSize();
	dword off = p->GetOffset().value;
	int64 offset = (int64)off * (int64)frame;
	ASSERT(offset < (int64)std::numeric_limits<int>::max());
	double time = off * fmt.GetFrameSeconds();
	p->Set(fmt, time);
	p->Data().SetCount(frame, 0);
	gen.Play((int)offset, p);
}


NAMESPACE_ECS_END
