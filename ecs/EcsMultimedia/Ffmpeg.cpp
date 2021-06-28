#include "EcsMultimedia.h"

#if HAVE_FFMPEG

#include <EcsAudioCore/EcsAudioCore.h>


NAMESPACE_ECS_BEGIN


FfmpegExt::FfmpegExt() {
	def_cap_sz = Size(1280,720);
	def_cap_fps = 30;
	
	file_in.SetParent(this);
	file_in.WhenStopped << THISBACK(OnStop);
}

void FfmpegExt::SetError(String s) {
	last_error = s;
	LOG("FfmpegExt: error: " << s);
	OnError();
}

bool FfmpegExt::Initialize(const Eon::WorldState& ws) {
	//TODO // DevComponent::Initialize
	ExtComponent& ext = GetParent();
	TypeCompCls type = ext.GetType();
	
	//DUMP(ws);
	
	
	if (type.side.vd.val.type == ValCls::AUDIO) {
		if (ws.IsTrue(".stop_machine"))
			stops_machine = true;
	}
	else if (type.side.vd.val.type == ValCls::VIDEO) {
		if (ws.IsTrue(".stop_machine"))
			stops_machine = true;
	}
	else {
		SetError("Invalid ExtComponent type");
		return false;
	}
	
	
	file_path = ws.Get(".filepath");
	if (file_path.IsEmpty()) {
		SetError("no file path given");
		return false;
	}
	//DUMP(file_path);
	
	if (!LoadFileAny(file_path))
		return false;
	
	
	//AddToContext<CenterSpec>(AsRef<CenterSource>());
	return true;
}

void FfmpegExt::Uninitialize() {
	file_in.Clear();
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSource>());
}

void FfmpegExt::OnError() {
	if (stops_machine)
		GetParent()->GetEntity()->GetMachine().SetNotRunning();
}

void FfmpegExt::OnStop() {
	if (stops_machine)
		GetParent()->GetEntity()->GetMachine().SetNotRunning();
	WhenStopped();
}

bool FfmpegExt::LoadFileAny(String path) {
	vi.Stop();
	
	mode = INVALID_MODE;
	
	file_in.SetFormat(GetParent()->GetSourceValue().GetFormat());
	// TODO side-connection format
	
	if (file_in.OpenFile(path)) {
		if (file_in.Open()) {
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
			
			return true;
		}
		else {
			SetError("couldn't open file " + path);
		}
	}
	else {
		SetError("couldn't open file " + path);
	}
	
	
	return false;
}

void FfmpegExt::Forward(FwdScope& fwd) {
	if (mode == AUDIO_ONLY)
		file_in.FillAudioBuffer();
	else
		TODO
}

bool FfmpegExt::IsReady(ValDevCls vd) {
	if (mode == AUDIO_ONLY)
		return file_in.GetAudio().buf.GetCount();
	else
		TODO
}

void FfmpegExt::StorePacket(Packet& p) {
	if (mode == AUDIO_ONLY)
		file_in.GetAudio().StorePacket(p);
	else
		TODO
}

/*Stream& FfmpegExt::GetStream(VidCtx) {
	return file_in.GetVideoStream();
}

void FfmpegExt::BeginStream(VidCtx) {
	file_in.GetVideoStream().FillBuffer();
}*/

/*void FfmpegExt::EndStream(VidCtx) {
	TODO
	//if (any_sink_consumed)
	//	file_in.GetVideoStream().DropBuffer();
}*/

/*void FfmpegExt::EmitVideoSource(double dt) {
	if (file_in.IsDeviceOpen()) {
		if (file_in.FillVideoBuffer()) {
			video_buf = &file_in.GetVideo();
			for(Ref<VideoSink> c : VideoSource::GetConnections())
				c->RecvVideo(video_buf, dt);
			
			file_in.DropFrames(0, 1);
		}
	}
}*/

/*AudioStream& FfmpegExt::GetStream(AudCtx) {
	return file_in.GetAudioStream();
}

void FfmpegExt::BeginStream(AudCtx) {
	file_in.GetAudioStream().FillBuffer();
}*/

/*void FfmpegExt::BeginUpdate(AudioExchangePointRef expt) {
	off32 min_exchanged = file_in.GetPreviousExchangedAudioMinCount();
	off32 exchanged = expt->GetExchangedCount();
	if (min_exchanged <= exchanged)
		expt->SetOffset(exchanged - min_exchanged);
	else
		expt->SetOffset(0);
	
	TODO // absolute off32
}*/

/*void FfmpegExt::EndStream(AudCtx) {
	file_in.GetAudioStream().DropBuffer();
}*/

/*void FfmpegExt::EmitAudioSource(double dt) {
	if (file_in.IsDeviceOpen()) {
		if (file_in.FillAudioBuffer()) {
			audio_buf = &file_in.GetAudio();
			for(Ref<AudioSink> c : AudioSource::GetConnections())
				c->RecvAudio(*this, dt);
			file_in.DropFrames(1, 0);
		}
	}
}*/

/*void FfmpegExt::Play(const RealtimeSourceConfig& config, Audio& aud) {
	//static DummySoundGenerator<float> gen;
	//gen.Play(config,snd);
	//snd.GetFrameFrom(audio_buf, config.sync);
	TODO
}*/



NAMESPACE_ECS_END

#endif
