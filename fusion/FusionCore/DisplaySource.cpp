#include "FusionCore.h"

NAMESPACE_TOPSIDE_BEGIN


void FusionDisplaySource::Initialize() {
	FusionComponent::Initialize();
	
	AddToSystem<RenderingSystem>(DisplaySource::AsRefT());
}

void FusionDisplaySource::Uninitialize() {
	RemoveFromSystem<RenderingSystem>(DisplaySource::AsRefT());
	
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

void FusionDisplaySource::EmitDisplay(double dt) {
	for(Ref<DisplaySink> c : DisplaySource::GetConnections())
		c->RecvDisplay(*this, dt);
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

bool FusionDisplaySource::Accept(ExchangeSinkProviderRef sink, CookieRef& src_c, CookieRef& sink_c) {
	return true;
}

void FusionDisplaySource::SetVideoSize(Size sz) {
	auto* stream = Stream();
	if (stream && stream->video_size != sz) {
		stream->video_size = sz;
		UpdateTexBuffers();
	}
}



NAMESPACE_TOPSIDE_END
