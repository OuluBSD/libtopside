#include "EcsCore.h"


NAMESPACE_OULU_BEGIN

Callback VideoSystem::WhenUninit;

bool VideoSystem::Initialize() {
	
	
	return true;
}

void VideoSystem::Start() {
	ents = GetMachine().Get<EntityStore>();
}

void VideoSystem::Update(double dt) {
	
	for (VideoSourceRef src : srcs) {
		VideoStream& aud_stream = src->GetVideoSource();
		bool buffer_full = aud_stream.GetVideoBufferSize() >= 2;
		
		src->Update(dt, buffer_full);
		if (src->Cfg().render)
			src->BeginVideoSource();
	}
	
	for (VideoExchangePointRef expt : expts) {
		VideoSourceRef src = expt->Source();
		if (src->Cfg().render)
			expt->Update(dt);
	}
	
	for (VideoSourceRef src :srcs) {
		if (src->Cfg().render)
			src->EndVideoSource();
	}
	
}

void VideoSystem::Stop() {
	
	
}

void VideoSystem::Uninitialize() {
	
	WhenUninit();
}

void VideoSystem::Add(VideoSourceRef src) {
	VectorFindAdd(srcs, src);
}

void VideoSystem::Remove(VideoSourceRef src) {
	VectorRemoveKey(srcs, src);
}

void VideoSystem::Add(VideoSinkRef sink) {
	VectorFindAdd(sinks, sink);
}

void VideoSystem::Remove(VideoSinkRef sink) {
	VectorRemoveKey(sinks, sink);
}

void VideoSystem::Add(VideoExchangePointRef expt) {
	VectorFindAdd(expts, expt);
}

void VideoSystem::Remove(VideoExchangePointRef expt) {
	VectorRemoveKey(expts, expt);
}








NAMESPACE_OULU_END
