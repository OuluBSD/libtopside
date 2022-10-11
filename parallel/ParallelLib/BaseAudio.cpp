#include "ParallelLib.h"


NAMESPACE_PARALLEL_BEGIN


AudioGenBase::AudioGenBase() {
	fmt.SetAudio(DevCls::CENTER, SoundSample::U8_LE, 2, 44100, 777);
	if (1)
		gen.GenerateNoise(fmt);
	else
		gen.GenerateStereoSine(fmt);
	
}

bool AudioGenBase::Initialize(const Script::WorldState& ws) {
	String waveform = ws.Get(".waveform");
	
	if (waveform == "noise")
		gen.GenerateNoise(fmt);
	else
		gen.GenerateStereoSine(fmt);
	
	const int src_ch_i = 0;
	Value& src_val = GetSource()->GetSourceValue(src_ch_i);
	src_val.SetFormat(fmt);
	return true;
}

void AudioGenBase::Uninitialize() {
	
}
bool AudioGenBase::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	const int sink_ch = 0;
	
	
	int frame = fmt.GetFrameSize();
	dword off = out.GetOffset().value;
	int64 offset = (int64)off * (int64)frame;
	ASSERT(offset < (int64)std::numeric_limits<int>::max());
	double time = off * fmt.GetFrameSeconds();
	out.Set(fmt, time);
	out.Data().SetCount(frame, 0);
	gen.Play((int)offset, out);
	
	RTLOG("AudioGenBase::Send: offset " << (int)off << " " << out.ToStringWithHash());
	
	return true;
}


NAMESPACE_PARALLEL_END
