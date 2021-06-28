#include "EcsMultimedia.h"

#if HAVE_FFMPEG

#include <EcsAudioCore/EcsAudioCore.h>


NAMESPACE_ECS_BEGIN


FfmpegComponent::FfmpegComponent() {
	def_cap_sz = Size(1280,720);
	def_cap_fps = 30;
	
	file_in.SetParent(this);
	file_in.WhenStopped << Proxy(WhenStopped);
}

void FfmpegComponent::Initialize() {
	TODO // DevComponent::Initiralize
	
	//AddToContext<CenterSpec>(AsRef<CenterSource>());
}

void FfmpegComponent::Uninitialize() {
	file_in.Clear();
	
	//RemoveFromContext<CenterSpec>(AsRef<CenterSource>());
}

bool FfmpegComponent::LoadFileAny(String path) {
	vi.Stop();
	
	if (file_in.OpenFile(path)) {
		if (file_in.Open()) {
			if (file_in.IsOpenAudio() && file_in.IsOpenVideo())
				vi.SetCap(
					file_in.GetAudioStream().AsRefT(),
					file_in.GetVideoStream().AsRefT());
			else if (file_in.IsOpenAudio())
				vi.SetCap(
					file_in.GetAudioStream().AsRefT(),
					VideoStreamRef());
			else
				vi.SetCap(
					AudioStreamRef(),
					file_in.GetVideoStream().AsRefT());

			vi.Start(false);
			
			return true;
		}
		else {
			last_error = "couldn't open file " + path;
		}
	}
	
	return false;
}

VideoStream& FfmpegComponent::GetStream(VidCtx) {
	return file_in.GetVideoStream();
}

void FfmpegComponent::BeginStream(VidCtx) {
	file_in.GetVideoStream().FillBuffer();
}

void FfmpegComponent::EndStream(VidCtx) {
	TODO
	//if (any_sink_consumed)
	//	file_in.GetVideoStream().DropBuffer();
}

/*void FfmpegComponent::EmitVideoSource(double dt) {
	if (file_in.IsDeviceOpen()) {
		if (file_in.FillVideoBuffer()) {
			video_buf = &file_in.GetVideo();
			for(Ref<VideoSink> c : VideoSource::GetConnections())
				c->RecvVideo(video_buf, dt);
			
			file_in.DropFrames(0, 1);
		}
	}
}*/

AudioStream& FfmpegComponent::GetStream(AudCtx) {
	return file_in.GetAudioStream();
}

void FfmpegComponent::BeginStream(AudCtx) {
	file_in.GetAudioStream().FillBuffer();
}

/*void FfmpegComponent::BeginUpdate(AudioExchangePointRef expt) {
	off32 min_exchanged = file_in.GetPreviousExchangedAudioMinCount();
	off32 exchanged = expt->GetExchangedCount();
	if (min_exchanged <= exchanged)
		expt->SetOffset(exchanged - min_exchanged);
	else
		expt->SetOffset(0);
	
	TODO // absolute off32
}*/

void FfmpegComponent::EndStream(AudCtx) {
	file_in.GetAudioStream().DropBuffer();
}

/*void FfmpegComponent::EmitAudioSource(double dt) {
	if (file_in.IsDeviceOpen()) {
		if (file_in.FillAudioBuffer()) {
			audio_buf = &file_in.GetAudio();
			for(Ref<AudioSink> c : AudioSource::GetConnections())
				c->RecvAudio(*this, dt);
			file_in.DropFrames(1, 0);
		}
	}
}*/

/*void FfmpegComponent::Play(const RealtimeSourceConfig& config, Audio& aud) {
	//static DummySoundGenerator<float> gen;
	//gen.Play(config,snd);
	//snd.GetFrameFrom(audio_buf, config.sync);
	TODO
}*/



NAMESPACE_ECS_END

#endif
