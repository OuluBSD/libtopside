#include "IMedia.h"
#include <SerialMach/SerialMach.h>

NAMESPACE_PARALLEL_BEGIN


template <class Backend>
MediaAtomBaseT<Backend>::MediaAtomBaseT() {
	def_cap_sz = Size(1280,720);
	def_cap_fps = 30;
	
	file_in.SetParent(this);
	file_in.WhenStopped << THISBACK(OnStop);
}

template <class Backend>
void MediaAtomBaseT<Backend>::SetError(String s) {
	last_error = s;
	LOG("MediaAtomBaseT: error: " << s);
	OnError();
}

template <class Backend>
bool MediaAtomBaseT<Backend>::Initialize(const Script::WorldState& ws) {
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
	RTLOG("MediaAtomBaseT: filepath=\"" << filepath << "\"");
	
	if (ws.Get(".vflip") == "true")
		vflip = true;
	
	if (filepath.IsEmpty()) {
		SetError("no file path given");
		return false;
	}
	//DUMP(filepath);
	
	
	AddAtomToUpdateList();
	
	return true;
}

template <class Backend>
bool MediaAtomBaseT<Backend>::PostInitialize() {
	if (!LoadFileAny(filepath))
		return false;
	
	//AddToContext<CenterSpec>(AsRef<CenterSource>());
	return true;
}

template <class Backend>
void MediaAtomBaseT<Backend>::Uninitialize() {
	file_in.Clear();
	
	RemoveAtomFromUpdateList();
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSource>());
}

template <class Backend>
void MediaAtomBaseT<Backend>::OnError() {
	if (stops_machine)
		GetParent().GetMachine().SetNotRunning();
}

template <class Backend>
void MediaAtomBaseT<Backend>::OnStop() {
	if (stops_machine)
		GetParent().GetMachine().SetNotRunning();
	WhenStopped();
}

template <class Backend>
bool MediaAtomBaseT<Backend>::LoadFileAny(String path) {
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
	
	if (!RealizeAudioFormat())
		;// this can be done with relatively fast data conversion //return false;
	
	if (!RealizeVideoFormat())
		return false;
	
	
	return true;
}

template <class Backend>
bool MediaAtomBaseT<Backend>::RealizeAudioFormat() {
	if (audio_ch >= 0) {
		Format fmt = file_in.GetAudio().GetFormat();
		if (fmt.IsValid()) {
			Value& audio_src = GetSource()->GetSourceValue(audio_ch);
			if (fmt != audio_src.GetFormat() && !GetLink()->NegotiateSourceFormat(audio_ch, fmt))
				return false;
		}
	}
	return true;
}

template <class Backend>
bool MediaAtomBaseT<Backend>::RealizeVideoFormat() {
	if (video_ch >= 0) {
		Format fmt = file_in.GetVideo().GetFormat();
		ASSERT(fmt.IsValid());
		Value& video_src = GetSource()->GetSourceValue(video_ch);
		if (fmt != video_src.GetFormat() && !GetLink()->NegotiateSourceFormat(video_ch, fmt))
			return false;
	}
	return true;
}

template <class Backend>
void MediaAtomBaseT<Backend>::Update(double dt) {
	time += dt;
	
}

template <class Backend>
bool MediaAtomBaseT<Backend>::IsReady(PacketIO& io) {
	video_packet_ready = false;
	audio_packet_ready = false;
	
	if (mode == AUDIO_ONLY || mode == AUDIOVIDEO) {
		bool was_valid_fmt = file_in.GetAudio().GetFormat().IsValid();
		
		file_in.FillAudioBuffer();
		
		bool is_valid_fmt = file_in.GetAudio().GetFormat().IsValid();
		if (!was_valid_fmt && is_valid_fmt) {
			// first packet fixed format. Now, negotiate connection format again...
			RealizeAudioFormat();
		}
	}
	
	if (mode == VIDEO_ONLY || mode == AUDIOVIDEO) {
		bool was_valid_fmt = file_in.GetVideo().GetFormat().IsValid();
		
		file_in.FillVideoBuffer();
		
		bool is_valid_fmt = file_in.GetVideo().GetFormat().IsValid();
		if (!was_valid_fmt && is_valid_fmt) {
			// first packet fixed format. Now, negotiate connection format again...
			RealizeVideoFormat();
		}
	}
	
	if (mode == AUDIO_ONLY && audio_ch >= 0)
		//audio_packet_ready = file_in.GetAudio().HasPacketOverTime(time);
		audio_packet_ready = !file_in.GetAudio().IsQueueEmpty();
	
	if (mode == VIDEO_ONLY && video_ch >= 0)
		//video_packet_ready = file_in.GetVideo().HasPacketOverTime(time);
		video_packet_ready = !file_in.GetVideo().IsQueueEmpty();
	
	if (mode == AUDIOVIDEO) {
		if (audio_ch >= 0)
			//audio_packet_ready = file_in.GetAudio().HasPacketOverTime(time);
			audio_packet_ready = file_in.GetAudio().IsQueueEmpty();
		
		if (video_ch >= 0)
			//video_packet_ready = file_in.GetVideo().HasPacketOverTime(time);
			video_packet_ready = file_in.GetVideo().IsQueueEmpty();
	}
	
	return audio_packet_ready || video_packet_ready;
}

template <class Backend>
bool MediaAtomBaseT<Backend>::Send(RealtimeSourceConfig& cfg, PacketValue& out, int src_ch) {
	bool succ = true;
	Format fmt = out.GetFormat();
	
	if (audio_packet_ready && fmt.IsAudio()) {
		succ = file_in.GetAudio().StorePacket(out); //, time);
		ASSERT(succ);
	}
	
	if (video_packet_ready && fmt.IsVideo()) {
		succ = file_in.GetVideo().StorePacket(out); //, time);
		ASSERT(succ);
	}
	
	return succ;
}


MEDIA_EXCPLICIT_INITIALIZE_CLASS(MediaAtomBaseT)


NAMESPACE_PARALLEL_END
