#include "AtomLocal.h"

#if HAVE_FFMPEG

NAMESPACE_SERIAL_BEGIN


FfmpegAtomBase::FfmpegAtomBase() {
	def_cap_sz = Size(1280,720);
	def_cap_fps = 30;
	
	file_in.SetParent(this);
	file_in.WhenStopped << THISBACK(OnStop);
}

void FfmpegAtomBase::SetError(String s) {
	last_error = s;
	LOG("FfmpegAtomBase: error: " << s);
	OnError();
}

bool FfmpegAtomBase::Initialize(const Script::WorldState& ws) {
	//TODO // DevComponent::Initialize
	AtomTypeCls type = GetType();
	
	//DUMP(ws);
	
	
	InterfaceSourceRef src_iface = GetSource();
	int src_count = src_iface->GetSourceCount();
	for(int i = 0; i < src_count; i++) {
		Format fmt = src_iface->GetSourceValue(i).GetFormat();
		if (fmt.IsAudio())
			audio_ch = i;
		else if (fmt.IsVideo())
			video_ch = i;
	}
	
	if (audio_ch >= 0 || video_ch >= 0) {
		if (ws.IsTrue(".stop_machine"))
			stops_machine = true;
	}
	else {
		SetError("invalid atom: no audio nor video interface output");
		return false;
	}
	
	
	String arg_filepath = ws.Get(".filepath");
	
	filepath = RealizeFilepathArgument(arg_filepath);
	RTLOG("FfmpegAtomBase: filepath=\"" << filepath << "\"");
	
	if (ws.Get(".vflip") == "true")
		vflip = true;
	
	if (filepath.IsEmpty()) {
		SetError("no file path given");
		return false;
	}
	//DUMP(filepath);
	
	
	AtomBase::GetMachine().template Get<AtomSystem>()->AddUpdated(AtomBase::AsRefT());
	
	return true;
}

bool FfmpegAtomBase::PostInitialize() {
	if (!LoadFileAny(filepath))
		return false;
	
	//AddToContext<CenterSpec>(AsRef<CenterSource>());
	return true;
}

void FfmpegAtomBase::Uninitialize() {
	file_in.Clear();
	
	AtomBase::GetMachine().template Get<AtomSystem>()->RemoveUpdated(AtomBase::AsRefT());
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSource>());
}

void FfmpegAtomBase::OnError() {
	if (stops_machine)
		GetParent().GetMachine().SetNotRunning();
}

void FfmpegAtomBase::OnStop() {
	if (stops_machine)
		GetParent().GetMachine().SetNotRunning();
	WhenStopped();
}

bool FfmpegAtomBase::LoadFileAny(String path) {
	ASSERT(!side_sink_conn.IsEmpty());
	
	vi.Stop();
	mode = INVALID_MODE;
	time = 0;
	
	if (!file_in.OpenFile(path) || !file_in.Open()) {
		SetError("couldn't open file " + path + ": " + file_in.GetLastError());
		return false;
	}
	
	if (file_in.IsOpenAudio() && file_in.IsOpenVideo()) {
		mode = AUDIOVIDEO;
		vi.SetCap(
			file_in.GetAudio().AsRefT(),
			file_in.GetVideo().AsRefT());
	}
	else if (file_in.IsOpenAudio()) {
		mode = AUDIO_ONLY;
		vi.SetCap(
			file_in.GetAudio().AsRefT(),
			VideoInputFrameRef());
	}
	else {
		mode = VIDEO_ONLY;
		vi.SetCap(
			AudioInputFrameRef(),
			file_in.GetVideo().AsRefT());
	}

	vi.Start(false);
	
	if (audio_ch >= 0) {
		Format fmt = file_in.GetAudio().GetFormat();
		ASSERT(fmt.IsValid());
		Value& audio_src = GetSource()->GetSourceValue(audio_ch);
		if (fmt != audio_src.GetFormat() && !NegotiateSourceFormat(audio_ch, fmt))
			return false;
	}
	
	if (video_ch >= 0) {
		Format fmt = file_in.GetVideo().GetFormat();
		ASSERT(fmt.IsValid());
		Value& video_src = GetSource()->GetSourceValue(video_ch);
		if (fmt != video_src.GetFormat() && !NegotiateSourceFormat(video_ch, fmt))
			return false;
	}
	
	
	return true;
}

void FfmpegAtomBase::Forward(FwdScope& fwd) {
	if (mode == AUDIO_ONLY || mode == AUDIOVIDEO)
		file_in.FillAudioBuffer();
	
	if (mode == VIDEO_ONLY || mode == AUDIOVIDEO)
		file_in.FillVideoBuffer();
}

void FfmpegAtomBase::Update(double dt) {
	time += dt;
}

bool FfmpegAtomBase::IsReady(PacketIO& io) {
	if (mode == AUDIO_ONLY)
		return file_in.GetAudio().HasPacketOverTime(time);
	
	if (mode == VIDEO_ONLY)
		return file_in.GetVideo().HasPacketOverTime(time);
	
	if (mode == AUDIOVIDEO)
		return file_in.GetAudio().HasPacketOverTime(time) ||
			   file_in.GetVideo().HasPacketOverTime(time);
		
	return false;
}

bool FfmpegAtomBase::ProcessPackets(PacketIO& io) {
	PacketIO::Sink& sink = io.sink[0];
	
	bool succ = true;
	
	if ((mode == AUDIO_ONLY || mode == AUDIOVIDEO) && audio_ch >= 0) {
		PacketIO::Source& src = io.src[audio_ch];
		Packet& out = src.p;
		sink.may_remove = true;
		src.from_sink_ch = 0;
		out = ReplyPacket(0, sink.p);
		
		succ = file_in.GetAudio().StorePacket(out, time);
		ASSERT(succ);
	}
	
	if ((mode == VIDEO_ONLY || mode == AUDIOVIDEO) && video_ch >= 0) {
		PacketIO::Source& src = io.src[video_ch];
		Packet& out = src.p;
		sink.may_remove = true;
		src.from_sink_ch = 0;
		out = ReplyPacket(0, sink.p);
		
		succ = file_in.GetVideo().StorePacket(out, time);
		ASSERT(succ);
	}
	
	// Send primary output packet when audio & video are side interfaces
	if (audio_ch != 0 && video_ch != 0) {
		PacketIO::Source& src = io.src[0];
		Packet& out = src.p;
		sink.may_remove = true;
		src.from_sink_ch = 0;
		out = ReplyPacket(0, sink.p);
	}
	
	return succ;
}


NAMESPACE_SERIAL_END

#endif
