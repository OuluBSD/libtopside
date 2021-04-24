#include "FusionCore.h"

NAMESPACE_OULU_BEGIN


void FusionDisplaySource::Initialize() {
	FusionComponent::Initialize();
	
	Ref<RenderingSystem> rend_sys = GetEntity().GetMachine().Get<RenderingSystem>();
	if (rend_sys)
		rend_sys	-> AddDisplaySource(*this);
}

void FusionDisplaySource::Uninitialize() {
	
    Ref<RenderingSystem> rend_sys = GetEntity().GetMachine().Get<RenderingSystem>();
	if (rend_sys)
		rend_sys->RemoveRenderable(*this);
	
	FusionComponent::Uninitialize();
}

void FusionDisplaySource::Reset() {
	auto* stream = Stream();
	if (stream) {
		stream->vframe_time.Reset();
		stream->vframes = 0;
	}
}

void FusionDisplaySource::PreProcess() {
	// pass
}

void FusionDisplaySource::PostProcess() {
	auto* stream = Stream();
	if (stream) {
		stream->vframes++;
		stream->vframe_time.Reset();
	}
}

void FusionDisplaySource::UpdateTexBuffers() {
	// pass
}

void FusionDisplaySource::Event(const CtrlEvent& e) {
	if (e.type == EVENT_WINDOW_RESIZE) {
		if (e.sz.cx >= 1 && e.sz.cy >= 1)
			SetVideoSize(e.sz);
	}
}

bool FusionDisplaySource::LoadResources() {
	return true;
}

void FusionDisplaySource::EmitDisplaySource(double dt) {
	for(const auto& c : DisplaySource::GetSinks())
		c.sink->RecvDisplaySink(*this, dt);
}

bool FusionDisplaySource::Render(const DisplaySinkConfig& config, SystemDraw& draw) {
	auto* stream = Stream();
	if (stream && ctx && IsOpen()) {
		Size new_sz = draw.GetPageSize();
		if (new_sz != stream->video_size) {
			stream->video_size = new_sz;
			ctx->UpdateTexBuffers();
		}
		stream->fps_limit = config.fps;
		return ctx->Render();
	}
	return true; // "nothing to do" is also success. Only busy video source fails
}

bool FusionDisplaySource::Link(DisplaySink& sink) {
	return true;
}

void FusionDisplaySource::SetVideoSize(Size sz) {
	auto* stream = Stream();
	if (stream && stream->video_size != sz) {
		stream->video_size = sz;
		UpdateTexBuffers();
	}
}



NAMESPACE_OULU_END
