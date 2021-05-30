#include "EcsMultimedia.h"

#if HAVE_FFMPEG

#include <EcsAudioCore/EcsAudioCore.h>


NAMESPACE_TOPSIDE_BEGIN


FfmpegComponent::FfmpegComponent() {
	def_cap_sz = Size(1280,720);
	def_cap_fps = 30;
	
	file_in.SetParent(this);
	file_in.WhenStopped << Proxy(WhenStopped);
}

void FfmpegComponent::Initialize() {
	
	AddToSystem<AudioSystem>(AsRef<AudioSource>());
}

void FfmpegComponent::Uninitialize() {
	file_in.Clear();
	
	RemoveFromSystem<AudioSystem>(AsRef<AudioSource>());
}

bool FfmpegComponent::LoadFileAny(String path) {
	vi.Stop();
	
	if (file_in.OpenFile(path)) {
		if (file_in.Open()) {
			vi.SetCap(
				file_in.GetAudioStream().AsRefT(),
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



NAMESPACE_TOPSIDE_END

#endif
