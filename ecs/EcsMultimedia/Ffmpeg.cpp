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
	TODO
	
}

void FfmpegComponent::Uninitialize() {
	file_in.Clear();
	
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
	
}



AudioStream& FfmpegComponent::GetStream(AudCtx) {
	return file_in.GetAudioStream();
}

void FfmpegComponent::BeginStream(AudCtx) {
	file_in.GetAudioStream().FillBuffer();
}

void FfmpegComponent::EndStream(AudCtx) {
	file_in.GetAudioStream().DropBuffer();
}


NAMESPACE_TOPSIDE_END

#endif
