#include "System.h"
#if HAVE_FFMPEG

#include <AudioCore/System.h>

NAMESPACE_OULU_BEGIN



FfmpegComponent::FfmpegComponent() {
	def_cap_sz = Size(1280,720);
	def_cap_fps = 30;
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

void FfmpegComponent::EmitVideoSource(double dt) {
	if (file_in.IsDeviceOpen()) {
		if (file_in.FillVideoBuffer()) {
			video_buf = &file_in.GetVideo();
			for(Ref<VideoSink> c : VideoSource::GetConnections())
				c->RecvVideo(video_buf, dt);
			
			file_in.DropFrames(0, 1);
		}
	}
}

void FfmpegComponent::EmitAudioSource(double dt) {
	if (file_in.IsDeviceOpen()) {
		if (file_in.FillAudioBuffer()) {
			sound_buf = &file_in.GetSound();
			for(Ref<AudioSink> c : AudioSource::GetConnections())
				c->RecvAudio(*this, dt);
			file_in.DropFrames(1, 0);
		}
	}
}

void FfmpegComponent::Play(const AudioSinkConfig& config, Sound& snd) {
	//static DummySoundGenerator<float> gen;
	//gen.Play(config,snd);
	//snd.GetFrameFrom(sound_buf, config.sync);
	TODO
}



NAMESPACE_OULU_END

#endif
