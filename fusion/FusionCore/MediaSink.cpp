#include "FusionCore.h"

NAMESPACE_TOPSIDE_BEGIN


void FusionMediaSink::Initialize() {
	FusionComponent::Initialize();
	stream.Clear();
}

void FusionMediaSink::Uninitialize() {
	
	FusionComponent::Uninitialize();
}

void FusionMediaSink::Reset() {
	// pass
}

void FusionMediaSink::PreProcess() {
	// pass
}

void FusionMediaSink::PostProcess() {
	// pass
}

void FusionMediaSink::ClearData() {
	// pass
}

void FusionMediaSink::UpdateTexBuffers() {
	auto* stream = Stream();
	if (stream) {
		ClearTex();
		Size res;
		TODO
		#if 0
		if (fmt.vid.res.IsEmpty())
			res = Size(fmt.snd.sample_rate, fmt.snd.channels);
		else
			res = fmt.vid.res;
		if (res.cx > 0 && res.cy > 0) {
#if HAVE_OPENGL
			Ogl_CreateTex(
				res, 4,
				0, 0,
				AcceleratorHeader::FILTER_MIPMAP,
				AcceleratorHeader::WRAP_CLAMP);
#endif
		}
		#endif
	}
}

bool FusionMediaSink::LoadResources() {
	return true;
}

void FusionMediaSink::Event(const CtrlEvent& e) {
	TODO
}

bool FusionMediaSink::LoadAsInput(const AcceleratorHeader& in) {
	const char* fn_name = "LoadAsInput";
	EntityRef e = GetEntity();
	Machine& m = e->GetMachine();
	String err;
	String path = in.GetPath();
	
	cfg.SetHeader(in);
	stream.Clear();
	
	auto type = in.GetType();
	
	TODO
	#if 0
	Ref<Connector> conn = GetEntity().GetConnector();
	if (!conn) {
		OnError(fn_name, "entity doesn't have Connector component");
		return false;
	}
	
	if (type != AcceleratorHeader::WEBCAM && !FileExists(path)) {
		OnError(fn_name, "file does not exist: \"" + path + "\"");
		return false;
	}
	
	if (type == AcceleratorHeader::VIDEO ||
		type == AcceleratorHeader::WEBCAM ||
		type == AcceleratorHeader::MUSIC) {
		Ref<FfmpegComponent> comp = e.Add<FfmpegComponent>();
		if (comp->LinkManually(*this)) {
			conn->SetUpdateInterfaces(true);
			if (path.IsEmpty() && type == AcceleratorHeader::WEBCAM)
				path = "<input0>";
			if (comp->LoadFileAny(path)) {
				MediaStreamThread& in = comp->GetInput();
				fmt = comp->GetMedia().GetFormat();
				ASSERT(fmt.IsValid());
				if (fmt.vid.IsValid()) {
					stream.sz = fmt.vid.res;
					stream.depth = 0;
				}
				else {
					stream.sz = Size(fmt.snd.sample_rate, fmt.snd.channels);
					stream.depth = 0;
				}
				UpdateTexBuffers();
				DLOG("FusionMediaSink::LoadAsInput: successfully loaded " + path);
				return true;
			}
			err = comp->GetLastError();
		}
		else {
			err = "couldn't link FfmpegComponent to FusionMediaSink";
		}
		comp->Destroy();
	}
	else if (type == AcceleratorHeader::MUSICSTREAM) {
		TODO
	}
	else {
		err = "unsupported type";
	}
	#endif
	
	if (err.IsEmpty()) err = "unknown error";
	OnError(fn_name, err);
	return false;
}

#if 0
void FusionMediaSink::RecvVideo(Video& video, double dt) {
	VideoFormat fmt = video.GetFormat(VidCtx);
	
	if (fmt != this->vid_fmt) {
		this->vid_fmt = fmt;
		UpdateTexBuffers();
	}
	
#if HAVE_OPENGL
	GLuint tex = Ogl_GetTex();
	if (tex > 0) {
		if (fmt.IsValid()) {
			if (!PaintOpenGLTexture(tex)) {
				OnError("RecvMedia", "painting opengl tex failed");
				ClearTex();
			}
		}
		/*else if (fmt.snd.IsValid()) {
			if (!media.GetAudio().PaintOpenGLTexture(tex)) {
				OnError("RecvMedia", "painting opengl tex failed");
				ClearTex();
			}
		}*/
	}
#else
	TODO
#endif
}
#endif

/*void FusionMediaSink::RecvAudio(AudioSource& src, double dt) {
	
	TODO
	
}*/
Audio& FusionMediaSink::GetValue(AudCtx) {
	TODO
}

Video& FusionMediaSink::GetValue(VidCtx) {
	TODO
}


NAMESPACE_TOPSIDE_END
