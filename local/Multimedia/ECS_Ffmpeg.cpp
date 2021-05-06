#include "System.h"
#if HAVE_FFMPEG

#include <AudioCore/System.h>

NAMESPACE_OULU_BEGIN



FfmpegComponent::FfmpegComponent() {
	def_cap_sz = Size(1280,720);
	def_cap_fps = 30;
	
	file_in.WhenStopped << Proxy(WhenStopped);
}

void FfmpegComponent::Initialize() {
	
	AddToSystem<AudioSystem>(this);
}

void FfmpegComponent::Uninitialize() {
	
	RemoveFromSystem<AudioSystem>(this);
}

bool FfmpegComponent::LoadFileAny(String path) {
	vi.Stop();
	
	if (file_in.Open(path)) {
		if (file_in.OpenDevice(0, 0)) {
			vi.SetCap(&file_in);

			vi.Start(false);
			
			return true;
		}
		else {
			last_error = "couldn't open file " + path;
		}
	}
	
	return false;
}

VideoStream& FfmpegComponent::GetVideoSource() {
	return file_in;
}

void FfmpegComponent::BeginVideoSource() {
	file_in.FillVideoBuffer();
}

void FfmpegComponent::EndVideoSource(bool any_sink_consumed) {
	if (any_sink_consumed)
		file_in.DropVideoFrames(1);
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

AudioStream& FfmpegComponent::GetAudioSource() {
	return file_in;
}

void FfmpegComponent::BeginAudioSource() {
	file_in.FillAudioBuffer();
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

void FfmpegComponent::EndAudioSource() {
	file_in.DropAudioBuffer();
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



NAMESPACE_OULU_END

#endif
