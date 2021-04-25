#include "System.h"


NAMESPACE_OULU_BEGIN



MultiMediaComponent::MultiMediaComponent() {
	def_cap_sz = Size(1280,720);
	def_cap_fps = 30;
}

void MultiMediaComponent::Initialize() {
	devmgr.Refresh();
}

void MultiMediaComponent::Uninitialize() {
	
}

bool MultiMediaComponent::LoadFileAny(String path) {
	vi.Stop();
	
	/*
	TODO: can't have 2 MultiMediaInputs reading same cap currently
	for(int k = 0; k < devmgr.GetVirtualCount() && !vi.cap; k++) {
		MediaDevice& dev = devmgr.GetVirtual(k);
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
	
	MediaDevice& virt = devmgr.GetAddVirtual(path);
	
	#if HAVE_MEDIAFILE
	MediaFileInput& fin = virt.AddFileInput();
	
	if (fin.Open(path)) {
		media_buf.vid = &fin.GetVideo();
		media_buf.snd = &fin.GetSound();
		ASSERT(media_buf.vid || media_buf.snd);
		
		if (fin.OpenDevice(0, 0)) {
			vi.cap = &fin;

			vi.Start();
			
			Ref<Connector> conn = GetEntity().GetConnector();
			if (conn)
				conn->SignalMediaSource();
			
			return true;
		}
		else {
			last_error = "couldn't open file " + path;
		}
	}
	#else
	last_error = "media file support is not included in the program compilation";
	#endif
	
	return false;
}

bool MultiMediaComponent::LoadInput(int id) {
	if (id < 0 || id >= devmgr.GetNativeCount()) {
		last_error = "invalid input id: " + IntStr(id);
		return false;
	}
	
	MediaDevice& dev = devmgr.GetNative(id);
	for(int l = 0; l < dev.GetCaptureCount() && !vi.cap; l++) {
		MediaCaptureDevice& cap = dev.GetCapture(l);
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
	return false;
}

void MultiMediaComponent::EmitMedia() {
	
	if (vi.TestClearNewFrame()) {
		media_buf.vid = &vi.cap->GetVideo();
		media_buf.snd = &vi.cap->GetSound();
		for(const auto& c : MediaSource::GetSinks())
			c.sink->RecvMedia(media_buf);
	}
	
	if (vi.flag.IsRunning()) {
		// Set again signal flag
		
		Ref<Connector> conn = GetEntity().GetConnector();
		if (conn)
			conn->SignalMediaSource();
	}
}











void MultiMediaInput::Start() {
	Stop();
	flag.Start();
	Thread::Start(THISBACK(Process));
}

void MultiMediaInput::Stop() {
	flag.Stop();
}

void MultiMediaInput::Process() {
	ASSERT(cap);
	step_time.Reset();
	if (cap) {
		while (cap && cap->IsDeviceOpen() && flag.IsRunning()) {
			if (!cap->Step(ResetSeconds(step_time))) {
				Sleep(1);
				continue;
			}
			if (cap->Read()) {
				new_frame = true;
			}
			else {
				if (!cap->IsDeviceOpen())
					cap->ReopenDevice();
				else {
					last_error = "MultiMediaInput::Process", "reading video input frame failed: " + cap->GetLastError();
					WhenError();
					Sleep(100);
				}
			}
		}
	}
	flag.SetStopped();
}


void MultiMediaInput::Clear() {
	if (cap) {
		cap->Close();
		cap = 0;
	}
	path.Clear();
}


#ifdef flagOPENGL
void MultiMediaInput::PaintOpenGL(GLuint active_tex) {
	if (cap) {
		cap->GetVideo().PaintOpenGLTexture(active_tex);
	}
}
#endif






NAMESPACE_OULU_END
