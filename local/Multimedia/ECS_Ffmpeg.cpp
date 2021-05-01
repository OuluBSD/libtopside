#include "System.h"
#if HAVE_FFMPEG

#include <AudioCore/System.h>

NAMESPACE_OULU_BEGIN



FfmpegComponent::FfmpegComponent() {
	def_cap_sz = Size(1280,720);
	def_cap_fps = 30;
}

void FfmpegComponent::Initialize() {
	devmgr.Refresh();
	
	AddToSystem<AudioSystem>(this);
}

void FfmpegComponent::Uninitialize() {
	
	RemoveFromSystem<AudioSystem>(this);
}

bool FfmpegComponent::LoadFileAny(String path) {
	vi.Stop();
	
	/*
	TODO: can't have 2 MediaInputThreads reading same cap currently
	for(int k = 0; k < devmgr.GetVirtualCount() && !vi.cap; k++) {
		V4L2_Device& dev = devmgr.GetVirtual(k);
		if (dev.GetPath() == path) {
			MediaStream* open = dev.FindOpenDevice();
			if (open) {
				vi.cap = open;
				return true;
			}
			return false;
		}
	}*/
	
	if (path.Left(6) == "<input" && path.Right(1) == ">") {
		String numstr = path.Mid(6, path.GetCount() - 7);
		int id = StrInt(numstr);
		return LoadInput(id);
	}
	
	V4L2_Device& virt = devmgr.GetAddVirtual(path);
	FfmpegFileInput& fin = virt.AddFileInput();
	
	if (fin.Open(path)) {
		video_buf.Set(&fin.GetVideo());
		sound_buf.Set(&fin.GetSound());
		ASSERT(video_buf || sound_buf);
		
		if (fin.OpenDevice(0, 0)) {
			vi.cap = &fin;

			vi.Start();
			
			return true;
		}
		else {
			last_error = "couldn't open file " + path;
		}
	}
	
	return false;
}

bool FfmpegComponent::LoadInput(int id) {
	if (id < 0 || id >= devmgr.GetNativeCount()) {
		last_error = "invalid input id: " + IntStr(id);
		return false;
	}
	
	TODO
	#if 0
	V4L2_Device& dev = devmgr.GetNative(id);
	for(int l = 0; l < dev.GetCaptureCount() && !vi.cap; l++) {
		OpenCVCaptureDevice& cap = dev.GetCapture(l);
		int fmt, res;
		if (cap.FindClosestFormat(def_cap_sz, def_cap_fps, 0.5, 1.5, fmt, res)) {
			
			media_buf.vid = &cap.GetVideo();
			media_buf.snd = &cap.GetSound();
			ASSERT(media_buf.vid && media_buf.snd);
			
			if (cap.OpenDevice(fmt, res)) {
				vi.cap = &cap;
				vi.Start();
			
				Ref<Connector> conn = GetEntity().GetConnector();
				if (conn)
					conn->SignalMediaSource();
				
				return true;
			}
			else {
				last_error = "couldn't open webcam " + cap.GetPath();
			}
		}
		else {
			last_error =
				"couldn't find expected format " + def_cap_sz.ToString() +
				", " + IntStr(def_cap_fps) +
				"fps from webcam "+ cap.GetPath();
		}
	}
	#endif
	
	return false;
}

void FfmpegComponent::EmitVideoSource(double dt) {
	if (vi.flag.IsRunning()) {
		if (vi.TestClearNewVideoFrame()) {
			video_buf = &vi.cap->GetVideo();
			for(const auto& c : VideoSource::GetSinks())
				c.sink->RecvVideo(video_buf, dt);
		}
	}
}

void FfmpegComponent::EmitAudioSource(double dt) {
	if (vi.flag.IsRunning()) {
		if (vi.TestClearNewAudioFrame()) {
			sound_buf = &vi.cap->GetSound();
			for(const auto& c : AudioSource::GetSinks())
				c.sink->RecvAudio(*this, dt);
		}
		/*else {
			LOG("waiting data");
		}*/
	}
}

void FfmpegComponent::Play(const AudioSinkConfig& config, Sound& snd) {
	//static DummySoundGenerator<float> gen;
	//gen.Play(config,snd);
	snd.GetFrameFrom(sound_buf, config.sync);
}



NAMESPACE_OULU_END

#endif
